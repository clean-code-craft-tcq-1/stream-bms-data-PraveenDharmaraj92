package converter;

import java.util.ArrayList;
import java.util.List;

import battery.BatteryParameter;

public class CSVConverter implements IConverter<List<String>, BatteryParameter> {

	@Override
	public List<String> convert(BatteryParameter batteryParam) {
		List<String> commaSeparatedValueList = new ArrayList<String>();

		batteryParam.getBatteryParamValueList().stream()
				.forEach(paramValues -> commaSeparatedValueList.add(String.join(",", paramValues)));

		return commaSeparatedValueList;
	}

}
