package battery;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.mockito.Mockito;

import converter.IConverter;
import factory.BatteryManagementObjectFactory;
import junit.framework.Assert;
import reader.ISourceReader;
import streamer.ConsoleStreamer;
import streamer.IStreamer;

public class BatteryParameterStreamerTest {

	private static final File JSON_FILE = new File("resources/BatteryParamValues.json");
	private static final String CONVERTER_KEY = "CONVERTER";
	private static final String READER_KEY = "READER";
	private static final String STREAMER_KEY=  "STREAMER";
	
	

	@Rule
	public ExpectedException exceptionRule = ExpectedException.none();

	@Test
	public void givenSource_ReadValues_assertNotEmpty() throws Exception {
		ISourceReader reader = getReader();
		BatteryParameter batteryParam = (BatteryParameter) reader.readValues(JSON_FILE);
		org.junit.Assert.assertNotNull(batteryParam);
		org.junit.Assert.assertTrue(batteryParam.getBatteryParamValueList().size() > 0);
	}

	@Test
	public void givenSource_ThrowExceptionForNullFile() throws Exception {
		exceptionRule.expect(Exception.class);
		exceptionRule.expectMessage("Invalid File");
		ISourceReader reader = getReader();
		reader.readValues(null);
	}

	@Test
	public void givenSource_ThrowExceptionForInvalidFile() throws Exception {
		exceptionRule.expect(Exception.class);
		exceptionRule.expectMessage("Invalid File");
		ISourceReader reader = getReader();
		reader.readValues(new File("D:\\invalidfile.json"));
	}

	
	@Test
	public void givenSource_ValueListConvertToCSVFormat_assertNotEmpty() throws Exception {
		BatteryParameter batteryParam = getBatteryParameter();
		IConverter converter = getConverter();
		List<String> csvList = (List<String>) converter.convert(batteryParam);
		org.junit.Assert.assertNotNull(csvList);
		org.junit.Assert.assertTrue(csvList.size() > 0);
	}
	
	@Test
	public void givenCSVStreamToConsoleAssertOutput() throws Exception{
		List<String> commaSeparatedStringList = new ArrayList<>();
		ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
		String commaSeparatedValue = "1.1,10";
		commaSeparatedStringList.add(commaSeparatedValue);
		System.setOut(new PrintStream(outputStream));
		IStreamer streamer = getStreamer();
		streamer.stream(commaSeparatedStringList);
		org.junit.Assert.assertEquals("Streamed output is not equal", commaSeparatedValue, outputStream.toString().trim());
	}

	@Test
	public void givenCSVStreamValuesVerifyStream() throws Exception {
		List<String> commaSeparatedStringList = new ArrayList<>();
		IStreamer mockConsoleStreamer = Mockito.mock(ConsoleStreamer.class);
		BatteryParameterStreamer handler = new BatteryParameterStreamer();
		handler.streamValues(commaSeparatedStringList, mockConsoleStreamer);
		Mockito.verify(mockConsoleStreamer).stream(commaSeparatedStringList);
	}

	@Test
	public void givenSourceReadConvertAndStreamValues() throws Exception {
		BatteryParameterStreamer handler = new BatteryParameterStreamer();

		ISourceReader reader = getReader();
		IConverter converter = getConverter();

		BatteryParameter batteryParam = getBatteryParameter();
		List<String> csvList = (List<String>) converter.convert(batteryParam);

		ISourceReader spyJsonReader = Mockito.spy(reader);
		IStreamer mockStreamer = Mockito.mock(IStreamer.class);

		handler.streamValuesToReceiver(spyJsonReader, JSON_FILE, converter, mockStreamer);

		Mockito.verify(spyJsonReader).readValues(JSON_FILE);
		Mockito.verify(mockStreamer).stream(csvList);
	}

	private BatteryParameter getBatteryParameter() throws Exception {
		return (BatteryParameter) getReader().readValues(JSON_FILE);
	}

	private ISourceReader getReader() throws Exception {
		String readerClass = BatteryManagementProperties.getInstance().getProperties().get(READER_KEY).toString();
		return BatteryManagementObjectFactory.getInstance().getObject(readerClass);
	}

	private IConverter getConverter() throws Exception {
		String converterClass = BatteryManagementProperties.getInstance().getProperties().get(CONVERTER_KEY).toString();
		return BatteryManagementObjectFactory.getInstance().getObject(converterClass);
	}
	

	private IStreamer getStreamer() throws Exception {
		String streamerClass = BatteryManagementProperties.getInstance().getProperties().get(STREAMER_KEY).toString();
		return BatteryManagementObjectFactory.getInstance().getObject(streamerClass);
	}

}
