package battery;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class BatteryManagementProperties {

	private static BatteryManagementProperties instance = new BatteryManagementProperties();

	private final Properties properties = new Properties();

	private BatteryManagementProperties() {
		try {
			InputStream propertiesInputStream = getClass().getClassLoader()
					.getResourceAsStream("resources/batterymanagement.properties");
			properties.load(propertiesInputStream);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public Properties getProperties() {
		return properties;
	}

	public static BatteryManagementProperties getInstance() {
		if (null == instance) {
			instance = new BatteryManagementProperties();
		}
		return instance;
	}

}
