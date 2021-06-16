
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

        System.out.println("Nome do ficheiro: reviews.csv");

        List<Review> reviewsValidas = auxRev(infoRev);

        // ou List<Review> reviewsValidas = auxRev(infoRev).stream().collect(Collectors.toList());

        System.out.println("Nome do ficheiro: business.csv");

        auxBusiness(infoBus, reviewsValidas);

        System.out.println("Nome do ficheiro: user.csv");

        auxUser(infoUser, reviewsValidas);
    }
    
    public List<Review> auxRev(String[] infoRev){

        int nrRevErradas = 0;
        int nrRevSemImp = 0;

        List<Review> reviewsValidas = new ArrayList<>();

        for(String s: infoRev){
            String[] camposRev = Review.parse(s);
            Review novoRev = new Review(camposRev);

            if(novoRev == null) nrRevErradas++;
            else reviewsValidas.add(novoRev.clone());
            
            int cool = novoRev.getCool();
            int funny = novoRev.getFunny();
            int useful = novoRev.getUseful();
            int somatorio = cool + funny + useful;
            if(somatorio == 0) nrRevSemImp++;
        }

        System.out.println("Número de reviews errados: " + nrRevErradas);
        System.out.println("Número de reviews com 0 impacto: " + nrRevSemImp);

        return reviewsValidas;
    }
    
    public void auxBusiness(String[] infoBus, List<Review> reviewsValidas){

        int nrTotalBus = 0;
        int totBusAval = 0;
    
        for(String s: infoBus){

            String[] camposBusiness = Business.parse(s);
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
    
    public void auxUser(String[] infoUser, List<Review> reviewsValidas){

        int nrUserTotal = 0;
        int usersAval = 0;
        int usersNaoAval = 0;

        for(String s: infoUser){

            String[] camposUser = User.parse(s);
            User novoUser = new User(camposUser);

            if(novoUser != null){
                nrUserTotal++;
                usersAval += nrUsersAvaliaram(novoUser, reviewsValidas);
            }         
        }
        usersNaoAval = nrUserTotal - usersAval;

        System.out.println("Número total de users: " + nrUserTotal);
        System.out.println("Número de users que fizeram reviews: " + usersAval);
        System.out.println("Número de users que nada avaliaram: " + usersNaoAval); 
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
    
    public int nrUsersAvaliaram(User novoUser, List<Review> reviewsValidas){
        String userId = novoUser.getUserId();

        for(Review rev: reviewsValidas){
            if(userId.equals(rev.getUserId())){
                return 1;
            }
        }
        return 0;
    }
}
