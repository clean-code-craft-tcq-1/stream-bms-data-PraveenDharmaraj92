/**
 * 
 */
package battery;

import java.util.ArrayList;
import java.util.List;

/**
 * Class to hold battery parameter values
 */
public class BatteryParameter {

	private List<List<String>> batteryParamValueList = new ArrayList<>();

	public List<List<String>> getBatteryParamValueList() {
		return batteryParamValueList;
	}

	public void setBatteryParamValueList(List<List<String>> batteryParamValueList) {
		this.batteryParamValueList = batteryParamValueList;
	}

}
