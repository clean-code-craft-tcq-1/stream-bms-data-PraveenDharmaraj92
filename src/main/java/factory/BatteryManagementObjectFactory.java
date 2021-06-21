package factory;

public class BatteryManagementObjectFactory {

	private static BatteryManagementObjectFactory instance;

	public <T extends Object> T getObject(String className) throws Exception {
		Class<T> object = (Class<T>) Class.forName(className);
		return object.newInstance();
	}

	public static BatteryManagementObjectFactory getInstance() {
		if (instance == null) {
			instance = new BatteryManagementObjectFactory();
		}
		return instance;
	}

}
