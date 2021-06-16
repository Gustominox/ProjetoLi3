
/**
 * Write a description of class GestReviews here.
 *
 * @author grupo 64
 * @version 030621
 */
 


import java.io.*;
import java.lang.*;
import java.util.*;
import java.util.AbstractMap.SimpleEntry;

import model.Business.*;
import model.Reviews.*;
import model.Users.*;
import java.util.stream.*;


public class GestReviews{
     private BusinessList bus ;
     private ReviewList  rev ;
     private UserList user ;
    

  /*  public void guardaEstado(String nomeFich) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(nomeFich);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        
        oos.writeObject(this);
        
        fos.flush();
        fos.close();
    }
<<<<<<< HEAD
////// ESTATISTICA
O QUE FALTA :
1. Apresenta ao utilizador os dados referentes aos últimos ficheiros lidos,
designadamente, nome do ficheiro, número total de registos de reviews errados,
número total de negócios x, 
total de diferentes negócios avaliados (nº reviews > 0) x ,
total de não avaliados, ------------- na msm funçao de cima
número total de users e total dos que realizaram reviews,
total de users que nada avaliaram, total de users inativos (sem reviews) e total de
reviews com 0 impacto (0 valores no somatório de cool, funny ou useful).
2. Apresenta em ecrã ao utilizador os números gerais respeitantes aos dados actuais já
registados nas estruturas, designadamente:
a. Número total de reviews por mês;
b. Média de classificação de reviews por mês e o valor global (média global de
reviews);
c. Número de distintos utilizadores que avaliaram em cada mês (não interessa
quantas vezes avaliou).
*/

public int NTotaldeNegocios(){
    return bus.getList().size();
=======
    
    public List<Review> reviewsValidas(String[] infoRev){
        List<Review> reviewsValidas = new ArrayList<>();
        
        for(String s: infoRev){
            String[] camposRev = Review.parse(s);
            Review novoRev = new Review(camposRev);
            
            if(novoRev.getReviewId().length() != 0)
                reviewsValidas.add(novoRev.clone());
        }
        
        return reviewsValidas;
    }
    
    /************************** QUERY 1 *****************************/
    public void query1(String[] infoRev, String[] infoBus, String[] infoUser){
        List<Review> reviewsValidas = reviewsValidas(infoRev);
        
        System.out.println("Nome do ficheiro: reviews.csv");
        auxRev(infoRev);
        System.out.println("\n");

        System.out.println("Nome do ficheiro: business.csv");
        auxBusiness(infoBus, reviewsValidas);
        System.out.println("\n");
        
        System.out.println("Nome do ficheiro: users.csv");
        auxUser(infoUser, reviewsValidas);
        System.out.println("\n");
    }
    
    public void auxRev(String[] infoRev){

        int nrRevErradas = 0;
        int nrRevSemImp = 0;

        for(String s: infoRev){
            String[] camposRev = Review.parse(s);
            Review novoRev = new Review(camposRev);

            if(novoRev.getReviewId().length() == 0) nrRevErradas++;
            else{
                int cool = novoRev.getCool();
                int funny = novoRev.getFunny();
                int useful = novoRev.getUseful();
                int somatorio = cool + funny + useful;
                if(somatorio == 0) nrRevSemImp++;
            }
        }

        System.out.println("    Número de reviews errados: " + nrRevErradas);
        System.out.println("    Número de reviews com 0 impacto: " + nrRevSemImp);

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
>>>>>>> 0cee1a6d619cfa3e607479d4e4eea4f4a4fca27a
}
public int TotalDifNegoAvaliadosNaoavaliados(){
    Set<String> business = new TreeSet<String> (); //para garantir que sao dif 
      for (Review i : rev.getList()){
              business.add(i.getBusinessId());
          }
     return  business.size();
    }

































////////// CONSULTAS ITERATIVAS 
    /// querie 1 

public  SimpleEntry<Integer,Set<String>> query1(){
        Set<String> aux = new TreeSet<String>(); // para ficar já orenado
        for(Business i: bus.getList()){ // vou percorrer os business tds 
            String id = i.getBusinessId(); // 
             if ( !this.rev.getList().stream().anyMatch(l->l.getBusinessId().equals(id))){ // procura nas reviews o id 
                aux.add(id);  // 
                }
            }
            int tamanho = aux.size();
            return new SimpleEntry(tamanho,aux);
        }


public Map<String,Map<String,List<SimpleEntry<String,Integer>>>> query10() {
    int stars ; 
    int count=0;
    Map<String,Map<String,List<SimpleEntry<String,Integer>>>> ret = new HashMap <String,Map<String,List<SimpleEntry<String,Integer>>>>();
    SimpleEntry<String,Integer> med = new SimpleEntry<String,Integer> (null, null);
    HashMap<String,Set<String>>aux = new HashMap<String,Set<String>>();
    for(Business a : this.bus.getList()){
       if (aux.containsKey(a.getState())){
         if (!ret.get(a.getState()).containsKey(a.getCity())){
              ret.get(a.getState()).put(a.getState(), null);
         };
       }
       else {
           ret.put
       }
       aux2.addAll(a.getCity());
       aux.put(a.getState(), aux2);
       String id = a.getBusinessId();
       for ( Review review : rev.getList()){
        if (review.getBusinessId().equals(id)){
              stars =+ (int) review.getStars();
              count++;

          }

     
    }


    return aux;    
}



         //estado               //cidade                // id    // media  
//public Map<String,Map<String,List<SimpleEntry<String,Integer>>> func (int mes, int ano ){

    //}
    





}



