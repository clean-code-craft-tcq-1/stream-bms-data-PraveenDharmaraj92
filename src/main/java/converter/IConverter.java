package converter;

public interface IConverter<T,E extends Object> {
	
	public T convert(E source); 

}
