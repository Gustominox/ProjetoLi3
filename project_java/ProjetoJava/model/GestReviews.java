
/**
 * Write a description of class GestReviews here.
 *
 * @author grupo 64
 * @version 030621
 */
 

import java.io.*;
import java.lang.*;
import java.util.*;
import java.util.stream.*;

public class GestReviews
{
    public void guardaEstado(String nomeFich) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(nomeFich);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        
        oos.writeObject(this);
        
        fos.flush();
        fos.close();
    }
    
    // Nome query1
    public void principal(String[] infoRev, String[] infoBus, String[] infoUser){

        ManipuladorFich fich = new ManipuladorFich();

        System.out.println("Nome do ficheiro: reviews.csv");

        List<Review> reviewsValidas = auxRev(infoRev);

        // ou List<Review> reviewsValidas = auxRev(infoRev).stream().collect(Collectors.toList());

        System.out.println("Nome do ficheiro: business.csv");

        auxBusiness(infoBus, reviewsValidas);

        System.out.println("Nome do ficheiro: user.csv");

        auxUser(infoUser, reviewsValidas);
    }
}
