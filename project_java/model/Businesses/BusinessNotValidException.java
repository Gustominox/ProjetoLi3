
/**
 * Lança uma exceção quando o business não é válido.
 *
 * @author grupo 64
 * @version (a version number or a date)
 */
package model.Businesses;

public class BusinessNotValidException extends Exception
{
    public BusinessNotValidException(){
        super();
    }
    
    public BusinessNotValidException(String msg){
        super(msg);
    }
}
