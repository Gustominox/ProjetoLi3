
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
    
    public void auxBusiness(String[] infoBus, List<Review> reviewsValidas){

        Business bus = new Business();
        
        int nrTotalBus = 0;
        int totBusAval = 0;
    
        for(String s: infoBus){

            String[] camposBusiness = bus.parse(s);
            Business novoBusiness = new Business(camposBusiness);

            if(novoBusiness != null){
                nrTotalBus++;
                totBusAval += nrBusAvaliados(novoBusiness, reviewsValidas);
            }
        }

        System.out.println("Número de negócios: " + nrTotalBus);
        System.out.println("Número de negócios avaliados: " + totBusAval);
        System.out.println("Número de negócios não avaliados: " + (nrTotalBus - totBusAval));      
    }
    
    public int nrBusAvaliados(Business novoBusiness, List<Review> reviewsValidas){

        String busId = novoBusiness.getBusinessId();

        for(Review rev: reviewsValidas){
            if(busId.equals(rev.getBusinessId())){
                return 1;
            }
        }
        return 0;
    }
}
