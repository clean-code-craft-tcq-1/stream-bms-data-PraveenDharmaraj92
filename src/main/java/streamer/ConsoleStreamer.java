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
	public void stream(List<String> commaSeparatedValueList) throws InterruptedException {

		for (String value : commaSeparatedValueList) {
				System.out.println(value);
				Thread.sleep(1000);
		}

	}

}
