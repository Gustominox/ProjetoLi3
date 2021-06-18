
/**
 * Write a description of class GestReviews here.
 *
 * @author grupo 64
 * @version 030621
 */



import java.io.*;
import java.lang.*;
import java.time.DateTimeException;
import java.util.*;
import java.util.AbstractMap.SimpleEntry;

import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;
import java.util.stream.*;
import view.*;


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

//public int NTotaldeNegocios(){
//    return bus.getList().size();
//}
//public int TotalDifNegoAvaliadosNaoavaliados(){
//    Set<String> business = new TreeSet<String> (); //para garantir que sao dif 
//      for (Review i : rev.getList()){
//              business.add(i.getBusinessId());
//          }
//     return  business.size();
//    }


    public GestReviews(BusinessList bus, ReviewList rev, UserList user) {
        this.bus = bus;
        this.rev = rev;
        this.user = user;
    }

    public void guardaEstado(String nomeFich) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(nomeFich);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        
        oos.writeObject(this);
        
        fos.flush();
        fos.close();
    }
    
    public ReviewList reviewsValidas(ReviewList reviews){
        ReviewList reviewsValidas = new ReviewList();
        List<Review> aux = new ArrayList<>();
        
        for(Review rev: reviews){
            if(novoRev.getReviewId().length() != 0)
                aux.add(rev.clone());
        }
        reviewsValidas.setList(aux);
        return reviewsValidas;
    }
    
    /************************** QUERY 1 *****************************/
    public void estatistica1(ReviewList reviews, BusinessList businesses, UserList users){

        StringBuilder sb =  new StringBuilder();

        ReviewList reviewsValidas = reviewsValidas(reviews);

        sb.append("Nome do ficheiro: reviews.csv");
        dadosSobreReview(reviews);
        sb.append("\n");

        sb.append("Nome do ficheiro: business.csv");
        dadosSobreBusiness(businesses, reviewsValidas);
        sb.append("\n");
        
        sb.append("Nome do ficheiro: users.csv");
        dadosSobreUser(users, reviewsValidas);
        sb.append("\n");

        View view = new View();
        view.print(sb.toString());
    }
    
    public void dadosSobreUser(UserList users, ReviewList reviewsValidas){

        StringBuilder sb =  new StringBuilder();

        int nrUserTotal = 0;
        int usersAval = 0;
        int usersNaoAval = 0;

        for(User user: users){

            if(user.getUserId().length() != 0){
                nrUserTotal++;
                usersAval += nrUsersAvaliaram(user, reviewsValidas);
            }         
        }
        usersNaoAval = nrUserTotal - usersAval;

        sb.append("    Número total de users: " + nrUserTotal);
        sb.append("    Número de users que fizeram reviews: " + usersAval);
        sb.append("    Número de users que nada avaliaram: " + usersNaoAval);

        View view = new View();
        view.print(sb.toString()); 
    }
    
    public void auxBusiness(String[] infoBus, List<Review> reviewsValidas){

        int nrTotalBus = 0;
        int totBusAval = 0;
    
        for(String s: infoBus){

            Business camposBusiness = Business.parse(s);
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
    
    public int nrUsersAvaliaram(User user, ReviewList reviewsValidas){
        String userId = user.getUserId();

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
        StringBuilder sb =  new StringBuilder();
        sb.append("Reviews em janeiro: " + revJan);
        sb.append("Reviews em fevereiro: " + revFeb);
        sb.append("Reviews em março: " + revMar);
        sb.append("Reviews em abril: " + revAbr);
        sb.append("Reviews em maio: " + revMaio);
        sb.append("Reviews em junho: " + revJun);
        sb.append("Reviews em julho: " + revJul);
        sb.append("Reviews em agosto: " + revAgo);
        sb.append("Reviews em setembro: " + revSet);
        sb.append("Reviews em outobro: " + revOut);
        sb.append("Reviews em novembro: " + revNov);
        sb.append("Reviews em dezembro: " + revDez);

        View view = new View();
        view.print(sb.toString());
    }

















////////// CONSULTAS ITERATIVAS 
    /* querie 1 */

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



     /* querie 2 */

 public SimpleEntry<Integer, Integer> query2 (int mes, int ano) throws DateTimeException{
    
    if ((mes < 1 && mes > 12 || ano > 2021) || ano==2021 && mes>6) throw new DateTimeException("Data inserida nao e valida"); //ate a data atual 
    else{
        int qt=0;
        Set <String> user = new TreeSet();
        for (Review review : rev.getList()){
        if (review.getDate().getMonth().equals(mes) ){
            if(review.getDate().getYear() == ano){
                qt++;
                user.add(review.getUserId());
            }
        }
    }
     user.size();      
     return new SimpleEntry (qt,user);
    }
}







/* querie 4 */ 
//Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado,
//por quantos users diferentes e a média de classificação;
public Map<Integer, List<Integer>> query4 (String businessId){
    Map<Integer,List<Integer>>map = new HashMap<>();
   for (int mes=1;mes<=12 ;mes++){
        int quantidade =0;
        int media;
        int stars=0;
        List <Integer> lista2=new ArrayList<>();
        Set <String>lista = new TreeSet<>();
        for( Review r : rev.getList()){
            if (r.getBusinessId().equals(businessId)){
                if (r.getDate().getMonthValue() == mes ){ // retorna o mes de 1 a 12
                    quantidade++;
                    lista.add(r.getUserId());
                    stars += r.getStars();
        }
    }
}
    int valor =lista.size();
    lista2.add(quantidade);
    lista2.add(valor);
    if(quantidade > 0)
        media= stars/quantidade;
    else media = 0;
    lista2.add(media);
    map.put(mes,lista2);
}
    return map;
}


/*
public List<SimpleEntry<String, Integer>> query5(String userId){
    List <Review> lista = this.rev.reviewsPorUser().get(userId);
    List<SimpleEntry<String, Integer>> resultado = new ArrayList <>();
    
    if(lista != null){
        for(Review r: lista){
            for (Business i: bus.getList() ){
                if ( i.getName().equals(userId))
                 String nome = 
            
            


            if(!resultado.stream().anyMatch(s->s.getKey().equals(nome))){
                int count = (int) lista.stream().filter(s->s.getBusinessId().equals(r.getBusinessId())).count();
                resultado.add(new SimpleEntry<String,Integer>(nome,count));
            }            
        }
        
        sort(resultados.values(),Collections.reverseOrder());;
        return resultado;
    }
    else return null;
}

*/




////////// CONSULTAS ITERATIVAS 
    /// querie 1 
/*
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
*/
/*
public Map<String,Map<String,List<SimpleEntry<String,Integer>>>> query10() {
    Map<String,Map<String,List<SimpleEntry<String,Integer>>>> ret = new HashMap <String,Map<String,List<SimpleEntry<String,Integer>>>>();
    for(Business aux : this.bus.getList()){ 
        ret.putIfAbsent(aux.getState(),null);//// ver se tem o estado 
        ret.get(aux.getState()).putIfAbsent(aux.getCity(), null); // ver se tem a cidade senao tiver acrescenta       
        String id = aux.getBusinessId();
        int media=(int) this.rev.getList().stream().filter(l->l.getBusinessId().equals(id)).
                map(l->l.getStars()).collect(Collectors.toList());//.average();
        ret.get(aux.getState()).get(aux.getCity()).add( new SimpleEntry(id,media));
    
       }
       return ret;
    }

*/





         //estado               //cidade                // id    // media  
//public Map<String,Map<String,List<SimpleEntry<String,Integer>>> func (int mes, int ano ){

    //}
    





}



