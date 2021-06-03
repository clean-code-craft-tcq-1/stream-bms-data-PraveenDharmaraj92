package battery;

import java.io.File;
import java.util.List;

import converter.IConverter;
import reader.ISourceReader;
import streamer.IStreamer;

public class BatteryParameterStreamer {

	public void streamValues(List<String> valueListToStream, IStreamer streamer) throws Exception {
		streamer.stream(valueListToStream);
	}

	public BatteryParameter readSource(ISourceReader<BatteryParameter, File> sourceReader, File jsonFile) throws Exception {
		return sourceReader.readValues(jsonFile);
	}

	public List<String> convertValues(IConverter<List<String>, BatteryParameter> converter,
			BatteryParameter batteryParam) {
		return converter.convert(batteryParam);
	}
	
	public void streamValuesToReceiver(ISourceReader sourceReader, File jsonFile, IConverter converter, IStreamer streamer) throws Exception{
		BatteryParameter batteryParameter = readSource(sourceReader, jsonFile);
		List<String> csvList = convertValues(converter, batteryParameter);
		streamValues(csvList, streamer);
	}
	
}
