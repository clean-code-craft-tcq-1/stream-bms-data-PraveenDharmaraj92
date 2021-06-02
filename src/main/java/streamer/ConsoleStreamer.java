/**
 * 
 */
package streamer;

import java.util.List;

/**
 *
 */
public class ConsoleStreamer implements IStreamer {

	/*
	 * (non-Javadoc)
	 * 
	 * @see streamer.IStreamer#stream(java.util.List)
	 */
	@Override
	public void stream(List<String> commaSeparatedValueList) {

		for (String value : commaSeparatedValueList) {
			try {
				System.out.println(value);
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}

}
