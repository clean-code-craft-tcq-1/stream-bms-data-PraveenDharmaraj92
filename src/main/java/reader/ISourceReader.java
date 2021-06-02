/**
 * 
 */
package reader;

/**
 * Interface for source reader - FileReader, RandomValue Reader , etc for fetching battery parameter values
 */
public interface ISourceReader <T,E extends Object>{
	
	/**
	 * Method to read objects
	 * @return list of read objects
	 */
	public T readValues(E source) throws Exception;

}
