/**
 * 
 */
package reader;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import com.fasterxml.jackson.databind.ObjectMapper;

import battery.BatteryParameter;

/**
 * JSON File reader
 */
public class JsonReader implements ISourceReader<BatteryParameter, File> {

	@Override
	public BatteryParameter readValues(final File file) throws Exception {
		validateFile(file);
		ObjectMapper objectMapper = new ObjectMapper();
		BatteryParameter batteryParam = null;
		try {
			batteryParam = objectMapper.readValue(new FileInputStream(file), BatteryParameter.class);

		} catch (IOException e) {
			e.printStackTrace();
		}
		return batteryParam;
	}
	
	public void validateFile(final File file) throws Exception{
		if(file==null||!file.exists()){
			throw new Exception("Invalid File");
		}
	}

}
