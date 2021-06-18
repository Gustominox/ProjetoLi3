
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
    public int[] nrRevPorMes(ReviewList reviews){
        int[12] revMes;
        for(Review rev: reviews.getList()){ //guardamos numa lista todas as reviews que o user fez
            revMes[rev.getDate().getMonthValue()-1]++;
        }
    return revMes;
    }

    public float[] classificacaoReview(int[] revMes, ReviewList reviews){

        float[12] clasPorMes;
        float[12] stars;
        for(Review rev: reviews.getList()){ //guardamos numa lista todas as reviews que o user fez
            stars[rev.getDate().getMonthValue()-1] += rev.getStars();

        }
        for(int i=0; i<12; i++){
            clasPorMes[i] = stars[i] / revMes[i];
        }
        return clasPorMes;
    }

    public float mediaGlobalReview(ReviewList reviews){
    float stars = 0;
    int nrRev = 0;
    for(Review rev: reviews.getList()){
        nrRev++;
        stars += rev.getStars();
    }
    float res = stars / nrRev;
    return res;
}

    public int[] userPorMes(ReviewList reviews, UserList users){
        //é uma lista com os user id
        List<String> aux = new ArrayList<>();
        int[12] nrUserMes;
        for(int i=1; i<=12; i++){
            ReviewList list = reviewsPorMes(reviews, i);
            for(Review rev: list.getList()){
                if(!list.contains(rev.getUserId())){
                    aux.add(rev.getUserId());
                    nrUserMes[i-1]++;
                }
            }
        }
        return nrUserMes;
    }

    public ReviewList reviewsPorMes(ReviewList reviews, int month){
        ReviewList res = new ReviewList();
        List<Review> aux = new ArrayLis<>();
        for(Review rev: reviews.getList()){
            if(rev.getDate().getMonthValue() == month){
                aux.add(rev.clone());
            }
        }
        res.setList(aux);
        return res;
    }

    public void estatica2(ReviewList reviews, UserList users){
        int[12] revPorMes = nrRevPorMes(reviews);
        int[12] claPorMes = classificacaoReview(revPorMes, reviews);
        float valorGlobal = mediaGlobalReview(reviews);
        int[12] userPorMes = userPorMes(reviews, users);

        StringBuilder sb =  new StringBuilder();
        for(int i=1; i<=12; i++){
            sp.append("  Mês " + i + ":");
            sp.append("\n");
            sp.append("    Número total de reviews - " + revPorMes[i]);
            sp.append("    Média de classificação de reviews - " + claPorMes[i]);
            sp.append("    Número de distintos utilizadores que avaliaram - " + userPorMes[i]);
            sp.append("\n");
        }
        sp.append("  Média global de reviews - " + valorGlobal);
        View view = new View();
        view.print(sb.toString());
    }
    /********************************* CONSULTAS INTERATIVAS ********************************/

    /**
Consulta 3

Dado um código de utilizador, determinar, para cada mês, quantas reviews fez,
quantos negócios distintos avaliou e que nota média atribuiu;

 */

public void consulta3(String userId, ReviewList review, BusinessList business){

    float[12] stars;
    int[12] revMes;
    List<Review> novaList  = new ArrayList<>();
    for(Review rev: review.getList()){ //guardamos numa lista todas as reviews que o user fez
        if(rev.getUserId().equals(userId)){
            novaList.add(rev.clone);
            revMes[rev.getDate().getMonthValue()-1]++;
            stars[rev.getDate().getMonthValue()-1] += rev.getStars();
        }

    }

    int[12] busMes;
    List<Business> novaList2  = new ArrayList<>();
    for(Review rev: novaList){ //percurremos a lista de todas as reviews que o user fez
        String id = rev.getBusinessId();
        for(Business bus: business.getList()){ //guardamos numa lista todos os negocios que o user fez um review
            if(bus.getBusinessId().equals(id) && !novaList2.contains(bus)){
                novaList2.add(bus.clone());//para ver se já não fez uma review desse business antes
                busMes[rev.getDate().getMonthValue()-1]++;
            }

        }

        imprimeQuery3(revMes, busMes, stars);
    }
}


public void imprimeQuery3(int[] revMes, int[] busMes, int[] stars){

    StringBuilder sb =  new StringBuilder();
    sb.append("  Janeiro:");
    sb.append("    Número de reviews: " + revMes[0] + " , número de negócios avaliados: " + busMes[0] + " , nota média: " + stars[0]/revMes[0]);
    sb.append("  Fevereiro:");
    sb.append("    Número de reviews: " + revMes[1] + " , número de negócios avaliados: " + busMes[1] + " , nota média: " + stars[1]/revMes[1]);
    sb.append("  Março:");
    sb.append("    Número de reviews: " + revMes[2] + " , número de negócios avaliados: " + busMes[2] + " , nota média: " + stars[2]/revMes[2]);
    sb.append("  Abril:");
    sb.append("    Número de reviews: " + revMes[3] + " , número de negócios avaliados: " + busMes[3] + " , nota média: " + stars[3]/revMes[3]);
    sb.append("  Maio:");
    sb.append("    Número de reviews: " + revMes[4] + " , número de negócios avaliados: " + busMes[4] + " , nota média: " + stars[4]/revMes[4]);
    sb.append("  Junho:");
    sb.append("    Número de reviews: " + revMes[5] + " , número de negócios avaliados: " + busMes[5] + " , nota média: " + stars[5]/revMes[5]);
    sb.append("  Julho:");
    sb.append("    Número de reviews: " + revMes[6] + " , número de negócios avaliados: " + busMes[6] + " , nota média: " + stars[6]/revMes[6]);
    sb.append("  Agosto:");
    sb.append("    Número de reviews: " + revMes[7] + " , número de negócios avaliados: " + busMes[7] + " , nota média: " + stars[7]/revMes[7]);
    sb.append("  Setembro:");
    sb.append("    Número de reviews: " + revMes[8] + " , número de negócios avaliados: " + busMes[8] + " , nota média: " + stars[8]/revMes[8]);
    sb.append("  Outubro:");
    sb.append("    Número de reviews: " + revMes[9] + " , número de negócios avaliados: " + busMes[9] + " , nota média: " + stars[9]/revMes[9]);
    sb.append("  Novembro:");
    sb.append("    Número de reviews: " + revMes[10] + " , número de negócios avaliados: " + busMes[10] + " , nota média: " + stars[10]/revMes[10]);
    sb.append("  Dezembro:");
    sb.append("    Número de reviews: " + revMes[11] + " , número de negócios avaliados: " + busMes[11] + " , nota média: " + stars[11]/revMes[11]);
    View view = new View();
    view.print(sb.toString());
}


    public void consulta5(int x, String user_id, ReviewList reviews, BusinessList businesses){

        StringBuilder sb =  new StringBuilder();

        User user = new User(user_id);
        ReviewList reviewsDoUser = user.getReviews(reviews);

        // todos os negocios mais avaliados daquele user
        BusinessList negociosMaisAval = new BusinessList();
        List<Business> aux = new ArrayList<>();

        Comparator<Business> comp = (u1,u2)->( u1.nrReviewsTotal(reviewsDoUser) - u2.nrReviewsTotal(reviewsDoUser)) ?
                                             ( u2.nrReviewsTotal(reviewsDoUser) - u1.nrReviewsTotal(reviewsDoUser)) :
                                               u1.getName().compareTo(u2.getName());

        for(Review rev: reviewsDoUser.getList()){
            Business bus = new Business(rev.getBusinessId());

            if(!aux.contains(bus)){
                aux.add(bus.clone());
            }
        }
        negociosMaisAval.setList(aux);

        // ordenar os negócios com os critérios estipulados
        aux.stream().map(Business::clone).sorted(comp).limit(x).collect(Collectors.toList());

        sb.append("User Id - " + user_id);

        int posicao = 1;
        for(Business bus: negociosMaisAval.getList()){
            sb.append("  " + posicao + "º Business Id (que avaliou " + bus.nrReviewsTotal(reviewsDoUser) + " vezes): " + bus.getBusinessId());
            posicao++;
        }
        View view = new View();
        view.print(sb.toString());
    }

    /**
Consulta 6

Determinar o conjunto dos X negócios mais avaliados (com mais reviews) em cada
ano, indicando o número total de distintos utilizadores que o avaliaram (X é um
inteiro dado pelo utilizador)

 */

 public void consulta6(int x, BusinessList businesses, ReviewList reviews){
        //ano             //lista de businesses desse ano
    Map<Integer, BusinessList> res = new HashMap<>();

        // business id        // users que avaliaram esse negócio
    Map<String, List<User>> usersPorNeg = new HashMap<>();

    Comparator<Business> comp = (b1,b2) -> b2.nrReviewsTotal(reviews) - b1.nrReviewsTotal(reviews);

    for(Review rev: reviews.getList()){ //estamos a percorrer as reviews (mais especificamente o ano)
        int ano = rev.getDate().getYear();
        
        if(!res.containsKey(ano)){ //se o ano nao se encontrar ainda no map

            BusinessList negociosDoAno = rev.negociosDoAno(businesses);

            if(negociosDoAno.getList().length() != 0){
                negociosDoAno.getList().stream().map(Business::clone).sorted(comp).limit(x).collect(Collectors.toList());
                res.put(rev.getDate().getYear(), negociosDoAno);
            }
        }
    }

    for(BusinessList negocios: res.values()){

        for(Business negocio: negocios.getList()){
            String business_id = bus.getBusinessId();
            ReviewList revDoNegocio = negocio.getReviews(reviews);
            
            List<User> aux = new ArrayList<>();
            for(Review rev: revDoNegocio.getList()){
                String user_id = rev.getUserId();

                User user = new User(user_id);
                if(!aux.contains(user)){
                    aux.add(user.clone());
                }
            }
            usersPorNeg.put(business_id, aux);
        }
    }

    StringBuilder sb =  new StringBuilder();
    for(Map.Entry<Integer, BusinessList> entry: res.entrySet){
        sb.append("  Ano " + entry.getKey());
        for(Business bus: entry.getvalue().getList()){
                sp.append("    Negócio: " + bus.getBusinessId());
                sp.append("      " + usersPorNeg.get(bus.getBusinessId()).size() + "users avaliaram este negócio");
        }
    }
    View view = new View();
    view.print(sb.toString());
 }


    public void consulta7(BusinessList businesses, ReviewList reviews){

        StringBuilder sb =  new StringBuilder();

        // key: cidade, value: três negócios mais famosos dessa cidade
        Map<String, BusinessList> todosNegPorCidade = new HashMap<>();

        Comparator<Business> comp = (b1,b2) -> b2.nrReviewsTotal(reviews) - b1.nrReviewsTotal(reviews);

        for(Business bus1: businesses.getList()){
            String cidade = bus1.getCity();

            // map com todos os negocios de uma determinada cidade
            if(!todosNegPorCidade.containsKey(cidade)){
                BusinessList negocios = new BusinessList();
                List<Business> aux = new ArrayList<>();

                for(Business bus2: businesses.getList()){
                    if(cidade.equals(bus2.getCity()))
                        aux.add(bus2.clone());
                }
                aux.stream().map(Business::clone).sorted(comp).limit(3).collect(Collectors.toList());
                negocios.setList(aux);

                todosNegPorCidade.put(cidade, negocios);

                sb.append("Cidade - " + cidade);

                int posicao = 1;
                for(Business bus3: negocios.getList()){
                    sb.append("  " + posicao + "º Business Id (mais famoso): " + bus3.getBusinessId());
                    posicao++;
                }
            }
            View view = new View();
            view.print(sb.toString());
        }
    }

    /**
Consulta 8

Determinar os códigos dos X utilizadores (sendo X dado pelo utilizador) que
avaliaram mais negócios diferentes, indicando quantos, sendo o critério de
ordenação a ordem decrescente do número de negócios;

 */


 public void consulta8(int x, BusinessList businesses, ReviewList reviews, UserList users){
        //user id
    Map<String, BusinessList> res = new HashMap<>();
    
    Comparator<User> comp = (u1,u2) -> u2.nrBusinessTotal(reviews, businesses) - u1.nrBusinessTotal(reviews, businesses);

    for(User user: users.getList()){
        BusinesssList negociosDoUser = user.negociosDoUser(reviews, businesses);

        if(negociosDoUser.getList().length() != 0){
                negociosDoUser.getList().stream().map(Business::clone).sorted(comp).limit(x).collect(Collectors.toList());
                res.put(user.getUserId(), negociosDoUser);
            }
    }

    StringBuilder sb =  new StringBuilder();
    for(Map.Entry<String, BusinessList> entry: res.entrySet){
        sb.append("  User: " + entry.getKey());
        sb.appende("    Número de negócios diferentes que avaliou: " + entry.getValue().getList().size());
    }
    View view = new View();
    view.print(sb.toString());
 }

    public void consulta9(int x, String business_id, ReviewList reviews, UserList users){

        StringBuilder sb =  new StringBuilder();

        Business negocio = new Business(business_id);
        ReviewList reviewsDoNegocio = negocio.getReviews(reviews);   // lista com todos as reviews daquele negócio

        List<User> topUsersDoNeg = new ArrayList<>();    // lista com os top x usuários do dito negócio

        for(Review rev: reviewsDoNegocio.getList()){
            String user_id = rev.getUserId();
            User user = new User(user_id);

            if(!topUsersDoNeg.contains(user))
                topUsersDoNeg.add(user.clone());
        }
       
        Comparator<User> comp = (u1,u2) -> u2.nrReviewsTotal(reviewsDoNegocio) - u1.nrReviewsTotal(reviewsDoNegocio);
        topUsersDoNeg.stream().map(User::clone).sorted(comp).limit(x).collect(Collectors.toList());

        sb.append("Business Id: " + business_id);

        int posicao = 1;
        for(User user: topUsersDoNeg){
            ReviewList reviewsDoUser = user.getReviews(reviewsDoNegocio);
            float media = reviewsDoUser.getClassificacaoMedia();       // cálculo da classificação média de cada top user
            
            sb.append("  " + posicao + "º User Id (que mais o avaliou): " + user.getUserId());
            sb.append("      Classificação média do négocio: " + media);
            posicao++;
        }
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



