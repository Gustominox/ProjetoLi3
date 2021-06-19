/**
 * Class para gravar ficheiros com o estado do programa
 * 
 * @author grupo 64 
 * @version 
 */

package loaders;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;

import model.GestReviews;
import model.Businesses.Business;
import model.Reviews.Review;
import model.Users.User;
public class Writelog {
    

    public void gravar(GestReviews gest,String nome){
    
        try {

        FileOutputStream fileOut = new FileOutputStream(nome + ".dat");
            for (Business bus : gest.getBus().getList()) {
                // Creates an ObjectOutputStream
                ObjectOutputStream objOut = new ObjectOutputStream(fileOut);
                // Writes objects to the output stream
                objOut.writeObject(bus);
                objOut.close();
            }
            for (Review rev : gest.getRev().getList()) {
                // Creates an ObjectOutputStream
                ObjectOutputStream objOut = new ObjectOutputStream(fileOut);
                // Writes objects to the output stream
                objOut.writeObject(rev);
                objOut.close();
            }
            for (User use : gest.getUser().getList()) {
                // Creates an ObjectOutputStream
                ObjectOutputStream objOut = new ObjectOutputStream(fileOut);
                // Writes objects to the output stream
                objOut.writeObject(use);
                objOut.close();        
            }
        }catch (Exception e) {
            e.getStackTrace();
        }
    
    }

    
}
