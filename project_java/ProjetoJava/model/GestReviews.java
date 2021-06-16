
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
    
    /************************** QUERY 1 *****************************/
    public void query1(String[] infoRev, String[] infoBus, String[] infoUser){

        System.out.println("Nome do ficheiro: reviews.csv");
        List<Review> reviewsValidas = auxRev(infoRev);
        System.out.println("\n");
        // ou List<Review> reviewsValidas = auxRev(infoRev).stream().collect(Collectors.toList());

        System.out.println("Nome do ficheiro: business.csv");
        auxBusiness(infoBus, reviewsValidas);
        System.out.println("\n");
        
        System.out.println("Nome do ficheiro: user.csv");
        auxUser(infoUser, reviewsValidas);
        System.out.println("\n");
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

        System.out.println("    Número de reviews errados: " + nrRevErradas);
        System.out.println("    Número de reviews com 0 impacto: " + nrRevSemImp);

        return reviewsValidas;
    }
    
    public void auxBusiness(String[] infoBus, List<Review> reviewsValidas){

        int nrTotalBus = 0;
        int totBusAval = 0;
    
        for(String s: infoBus){

            String[] camposBusiness = Business.parse(s);
            Business novoBusiness = new Business(camposBusiness);

            if(novoBusiness.getBusinessId().length() != 0){
                nrTotalBus++;
                totBusAval += nrBusAvaliados(novoBusiness, reviewsValidas);
            }
        }

        System.out.println("    Número de negócios: " + nrTotalBus);
        System.out.println("    Número de negócios avaliados: " + totBusAval);
        System.out.println("    Número de negócios não avaliados: " + (nrTotalBus - totBusAval));      
    }
    
    public void auxUser(String[] infoUser, List<Review> reviewsValidas){

        int nrUserTotal = 0;
        int usersAval = 0;
        int usersNaoAval = 0;

        for(String s: infoUser){

            String[] camposUser = User.parse(s);
            User novoUser = new User(camposUser);

            if(novoUser.getUserId().length() != 0){
                nrUserTotal++;
                usersAval += nrUsersAvaliaram(novoUser, reviewsValidas);
            }         
        }
        usersNaoAval = nrUserTotal - usersAval;

        System.out.println("    Número total de users: " + nrUserTotal);
        System.out.println("    Número de users que fizeram reviews: " + usersAval);
        System.out.println("    Número de users que nada avaliaram: " + usersNaoAval); 
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
    
    
    /***************************** QUERY 2 **************************************/
    public void revPorMes(List<Review> reviewsValidas){
        int nrRev = 0;
        int revJan=0, revFeb=0, revMar=0, revAbr=0, revMaio=0, revJun=0, revJul=0, revAgo=0, revSet=0, revOut=0, revNov=0, revDez=0;
        
        for(Review rev: reviewsValidas){
            switch(rev.getDate().getMonthValue()){
                case 1:
                    revJan++;
                    break;
                    
                case 2:
                    revFeb++;
                    break;
                    
                case 3:
                    revMar++;
                    break;
                
                case 4:
                    revAbr++;
                    break;
                    
                case 5:
                    revMaio++;
                    break;
                
                case 6:
                    revJun++;
                    break;
                    
                case 7:
                    revJul++;
                    break;
                    
                case 8:
                    revAgo++;
                    break;
                    
                case 9:
                    revSet++;
                    break;
                    
                case 10:
                    revOut++;
                    break;
                    
                case 11:
                    revNov++;
                    break;
                    
                case 12:
                    revDez++;
                    break;
            }
        }
        
        System.out.println("Reviews em janeiro: " + revJan);
        System.out.println("Reviews em fevereiro: " + revFeb);
        System.out.println("Reviews em março: " + revMar);
        System.out.println("Reviews em abril: " + revAbr);
        System.out.println("Reviews em maio: " + revMaio);
        System.out.println("Reviews em junho: " + revJun);
        System.out.println("Reviews em julho: " + revJul);
        System.out.println("Reviews em agosto: " + revAgo);
        System.out.println("Reviews em setembro: " + revSet);
        System.out.println("Reviews em outobro: " + revOut);
        System.out.println("Reviews em novembro: " + revNov);
        System.out.println("Reviews em dezembro: " + revDez);
    }
}
