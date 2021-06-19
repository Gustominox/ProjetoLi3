
/**
 * Lança uma exceção quando o User não é válido.
 *
 * @author grupo 64
 * @version (a version number or a date)
 */

package model.Users;
public class UserNotValidException extends Exception
{
    public UserNotValidException(){
        super();
    }
    
    public UserNotValidException(String msg){
        super(msg);
    }
}
