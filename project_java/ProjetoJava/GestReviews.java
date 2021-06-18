
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
        
        for(Review rev: reviews.getList()){
            if(rev.getReviewId().length() != 0)
                aux.add(rev.clone());
        }
        reviewsValidas.setList(aux);
        return reviewsValidas;
    }
    
    /************************** QUERY 1 *****************************/
    public void estatistica1(ReviewList reviews, BusinessList businesses, UserList users){


        View view = new View();
        ReviewList reviewsValidas = reviewsValidas(reviews);

        
        view.print("Nome do ficheiro: reviews.csv\n");
        Map<String,Integer> businessAvaliados= dadosSobreReview(reviews);
        

        view.print("Nome do ficheiro: business.csv\n");
        dadosSobreBusiness(businesses, reviewsValidas,businessAvaliados);
        
        view.print("Nome do ficheiro: users.csv\n");
        dadosSobreUser(users, reviewsValidas);
        

    }
    
    public void dadosSobreUser(UserList users, ReviewList reviewsValidas){

        StringBuilder sb =  new StringBuilder();

        View view = new View();
        int nrUserTotal = 0;
        int usersAval = 0;
        int usersNaoAval = 0;

        Map<String,Integer>userAvaliados = new HashMap<>();

        for (Review rev: reviewsValidas.getList()) {
            
            userAvaliados.put(rev.getUserId(),0);
        }
        for(User user: users.getList()){

            if(user.getUserId().length() != 0){
                nrUserTotal++;
                
                if (userAvaliados.containsKey(user.getUserId()))
                    usersAval++;
            }         
        }
        usersNaoAval = nrUserTotal - usersAval;

        sb.append("    Número total de users: " + nrUserTotal);
        sb.append("    Número de users que fizeram reviews: " + usersAval);
        sb.append("    Número de users que nada avaliaram: " + usersNaoAval);

        view.print(sb.toString()); 
    }
    
    public void dadosSobreBusiness(BusinessList businesses, ReviewList reviewsValidas, Map<String,Integer> businessAvaliados){

        int nrBusTotal = 0;
        int busAval = 0;
        
        StringBuilder sb =  new StringBuilder();

        for(Business bus: businesses.getList()){

            if(bus.getBusinessId().length() != 0){
                nrBusTotal++;
                if (businessAvaliados.containsKey(bus.getBusinessId()))
                    busAval++;
            }
        }
        sb.append("    Número total de negócios: " + nrBusTotal);
        sb.append("    Número de negócios avaliados: " + busAval);
        sb.append("    Número de negócios não avaliados: " + (nrBusTotal - busAval)); 

        View view = new View();
        view.print(sb.toString());      
    }
    
    public Map<String,Integer> dadosSobreReview(ReviewList reviews){

        int nrRevErradas = 0;
        int nrRevSemImpacto = 0;
        StringBuilder sb =  new StringBuilder();
        Map<String,Integer>busAvaliados = new HashMap<>();
        for(Review rev: reviews.getList()){
            busAvaliados.put(rev.getBusinessId(),0);
            if(rev.getReviewId().length() == 0) nrRevErradas++;
            else{
                int somatorio = rev.getCool() + rev.getFunny() + rev.getUseful();
                if(somatorio == 0) nrRevSemImpacto++;
            }
        }
        sb.append("    Número de reviews errados: " + nrRevErradas);
        sb.append("    Número de reviews com 0 impacto: " + nrRevSemImpacto);

        View view = new View();
        view.print(sb.toString());   
        return busAvaliados;     
    }

    public int nrBusAval(Business business, ReviewList reviewsValidas){
        String busId = business.getBusinessId();

        for(Review rev: reviewsValidas.getList()){
            if(busId.equals(rev.getBusinessId())){
                return 1;
            }
        }
        return 0;
    }
    
    public int nrUsersAvaliaram(User user, ReviewList reviewsValidas){
        String userId = user.getUserId();

        for(Review rev: reviewsValidas.getList()){
            if(userId.equals(rev.getUserId())){
                return 1;
            }
        }
        return 0;
    }
    
    
    /***************************** QUERY 2 **************************************/
    public int[] nrRevPorMes(ReviewList reviews){
        int[] revMes = new int[12];
        for(Review rev: reviews.getList()){ //guardamos numa lista todas as reviews que o user fez
            revMes[rev.getDate().getMonthValue()-1]++;
        }
    return revMes;
    }

    public float[] classificacaoReview(int[] revMes, ReviewList reviews){

        float[] clasPorMes = new float[12]; ;
        float[] stars = new float[12];;
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
        int[] nrUserMes = new int[12];
        for(int i=1; i<=12; i++){
            ReviewList list = reviewsPorMes(reviews, i);
            for(Review rev: list.getList()){
                if(!list.getList().contains(rev.getUserId())){
                    aux.add(rev.getUserId());
                    nrUserMes[i-1]++;
                }
            }
        }
        return nrUserMes;
    }

    public ReviewList reviewsPorMes(ReviewList reviews, int month){
        ReviewList res = new ReviewList();
        List<Review> aux = new ArrayList<>();
        for(Review rev: reviews.getList()){
            if(rev.getDate().getMonthValue() == month){
                aux.add(rev.clone());
            }
        }
        res.setList(aux);
        return res;
    }

    public void estatica2(ReviewList reviews, UserList users){
        int[] revPorMes = nrRevPorMes(reviews);
        float[] claPorMes = classificacaoReview(revPorMes, reviews);
        float valorGlobal = mediaGlobalReview(reviews);
        int[] userPorMes = userPorMes(reviews, users);

        StringBuilder sb =  new StringBuilder();
        for(int i=1; i<=12; i++){
            sb.append("  Mês " + i + ":");
            sb.append("\n");
            sb.append("    Número total de reviews - " + revPorMes[i]);
            sb.append("    Média de classificação de reviews - " + claPorMes[i]);
            sb.append("    Número de distintos utilizadores que avaliaram - " + userPorMes[i]);
            sb.append("\n");
        }
        sb.append("  Média global de reviews - " + valorGlobal);
        View view = new View();
        view.print(sb.toString());
    }
    /********************************* CONSULTAS INTERATIVAS ********************************/

    /**
Consulta 3

Dado um código de utilizador, determinar, para cada mês, quantas reviews fez,
quantos negócios distintos avaliou e que nota média atribuiu;

 */
//FEITA
public void consulta3(String userId, ReviewList review, BusinessList business){

    float[] stars = new float[12];
    int[] revMes = new int[12];
    List<Review> novaList  = new ArrayList<>();
    for(Review rev: review.getList()){ //guardamos numa lista todas as reviews que o user fez
        if(rev.getUserId().equals(userId)){
            novaList.add(rev.clone());
            revMes[rev.getDate().getMonthValue()-1]++;
            stars[rev.getDate().getMonthValue()-1] += rev.getStars();
        }

    }

    int[] busMes = new int[12];
    List<Business> novaList2  = new ArrayList<>();
    for(Review rev: novaList){ //percurremos a lista de todas as reviews que o user fez
        String id = rev.getBusinessId();
        for(Business bus: business.getList()){ //guardamos numa lista todos os negocios que o user fez um review
            if(bus.getBusinessId().equals(id) && !novaList2.contains(bus)){
                novaList2.add(bus.clone());//para ver se já não fez uma review desse business antes
                busMes[rev.getDate().getMonthValue()-1]++;
            }

        }

    }

    imprimeQuery3(revMes, busMes, stars);
}


public void imprimeQuery3(int[] revMes, int[] busMes, float[] stars){

    StringBuilder sb =  new StringBuilder();
    for(int i=0; i < 12; i++){
        int nmes = i + 1;
        sb.append("  Mes:" + nmes).append("\n");
        sb.append("    Número de reviews: " + revMes[i] );
        sb.append(" , Número de negócios avaliados: " + busMes[i] ); 
        sb.append(" , Nota média: " + stars[i]/revMes[i]).append("\n");
    
    }
    View view = new View();
    view.print(sb.toString());
}

public void consulta5(int x, String user_id, ReviewList reviews){

    StringBuilder sb =  new StringBuilder();
    View view = new View();

    User user = new User(user_id);
    ReviewList reviewsDoUser = user.getReviews(reviews);

    Map<Business,Integer> busNr = new HashMap<>();
    
    Comparator<Map.Entry<Business,Integer>> cmp = (p1,p2)-> ( p1.getValue() != p2.getValue() ) ?
                                                            ( p2.getValue() - p1.getValue() ) :
                                                              p1.getKey().getName().compareTo(p2.getKey().getName());

    for(Review r: reviewsDoUser.getList()){
        Business bus = this.bus.getBusiness(r.getBusinessId());
        if(!busNr.containsKey(bus)){
            busNr.put(bus.clone(), 1);
        }else{
            int n = busNr.get(bus);
            busNr.remove(bus);
            busNr.put(bus.clone(), n+1);
        }
    }
    
    // ordenar os negócios com os critérios estipulados
    Map<Business,Integer> ordenados = busNr.entrySet().stream().sorted(cmp).limit(x)
                                           .collect(Collectors.toMap(e->e.getKey().clone(), e->e.getValue()));

    sb.append("User Id - ").append(user_id).append("\n");

    int posicao = 1;
    for(Map.Entry<Business,Integer> bus: ordenados.entrySet()){
        sb.append("  ").append(posicao).append("º Business Id (que avaliou ");
        sb.append(bus.getValue()).append(" vezes): ").append(bus.getKey().getBusinessId()).append("\n");
        posicao++;
    }
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
    
    Map<String,Integer> busNr = new HashMap<>();
    
    for(Review r: reviews.getList()){
        if(!busNr.containsKey(r.getBusinessId())){
            
            busNr.put(r.getBusinessId(), 1);
        }else{
            int n = busNr.get(r.getBusinessId());
            busNr.remove(r.getBusinessId());
            busNr.put(r.getBusinessId(), n+1);
        }
    }
/*
    for(Business b: businesses.getList()){
        if(!busNr.containsKey(b.getBusinessId())){
            
            busNr.put(b.getBusinessId(), 0);
        }
    }
*/
    Comparator<Business> comp = (b1,b2) -> 
    busNr.get(b2.getBusinessId()) - busNr.get(b1.getBusinessId());

    //System.out.println(busNr.toString());
    for(Review rev: reviews.getList()){ //estamos a percorrer as reviews (mais especificamente o ano)
        int ano = rev.getDate().getYear();
  // 2001 -> [busId,BusId]      
        if(!res.containsKey(ano)){ //se o ano nao se encontrar ainda no map

            BusinessList negociosDoAno = rev.negociosDoAno(businesses,reviews, ano);
            System.out.println(negociosDoAno.getList().toString());
            if(negociosDoAno.getList().size() != 0){
                List<Business> negociosDoAnoOrd = negociosDoAno.getList().stream().map(Business::clone).sorted(comp).limit(10).collect(Collectors.toList());
                BusinessList busi = new BusinessList(negociosDoAnoOrd); 
                res.put(rev.getDate().getYear(), busi);
            }
        }
    }
    
    for(BusinessList negocios: res.values()){
        for(Business negocio: negocios.getList()){
            String business_id = negocio.getBusinessId();
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
    for(Map.Entry<Integer, BusinessList> entry: res.entrySet()){
        sb.append("  Ano " + entry.getKey());
        for(Business bus: entry.getValue().getList()){
                sb.append("    Negócio: " + bus.getBusinessId());
                sb.append("      " + usersPorNeg.get(bus.getBusinessId()).size() + " users avaliaram este negócio").append("\n");
        }
    }
    View view = new View();
    view.print(sb.toString());
 }

// FEITA
// retorna 3 neg mais famosos de cada cidade
    public void consulta7(BusinessList businesses, ReviewList reviews){
        
        View view = new View();

        List<String> cidadesVisitadas = new ArrayList<>();
        Map<String,List<SimpleEntry<Business,Integer>>> cidades = new HashMap<>();

        Map<String,Integer> busNr = new HashMap<>();
        Comparator<SimpleEntry<Business,Integer>> comp = (b1,b2) -> b2.getValue() - b1.getValue();

        for(Review r: reviews.getList()){
            if(!busNr.containsKey(r.getBusinessId())){
                
                busNr.put(r.getBusinessId(), 1);
            }else{
                int n = busNr.get(r.getBusinessId());
                busNr.remove(r.getBusinessId());
                busNr.put(r.getBusinessId(), n+1);
            }
        }

        for(Business b: businesses.getList()){

            if(!cidadesVisitadas.contains(b.getCity())){
                ArrayList<SimpleEntry<Business,Integer>> idBusCidade = new ArrayList<>();
                if(busNr.containsKey(b.getBusinessId()))
                    idBusCidade.add(new SimpleEntry<>( b.clone(),busNr.get(b.getBusinessId())));
                else idBusCidade.add(new SimpleEntry<>( b.clone(),0));
                //cidades.remove(b.getCity());
                cidades.put(b.getCity(), idBusCidade);
                cidadesVisitadas.add(b.getCity());
            }else{
                List<SimpleEntry<Business,Integer>> idBusCidade = cidades.get(b.getCity());
                if(busNr.containsKey(b.getBusinessId()))
                    idBusCidade.add(new SimpleEntry<>( b.clone(),busNr.get(b.getBusinessId())));
                else idBusCidade.add(new SimpleEntry<>( b.clone(),0));
                cidades.remove(b.getCity());
                cidades.put(b.getCity(), idBusCidade);
            }
        }
        for (Map.Entry<String, List<SimpleEntry<Business,Integer>>> entry : cidades.entrySet()) {

            StringBuilder sb =  new StringBuilder();
            sb.append("Cidade - ").append(entry.getKey()).append("\n");

            List<SimpleEntry<Business,Integer>> ordenados = entry.getValue().stream().sorted(comp).limit(3).collect(Collectors.toList());
            int posicao = 1;
            for (SimpleEntry<Business,Integer> bus : ordenados) {
                sb.append("  ").append(posicao).append("º Business Id (com ").append(bus.getValue()).append(" reviews): ").append(bus.getKey().getBusinessId()).append(bus.getValue()).append("\n");
                posicao++;
            }
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

    List<User> listUsers =  users.getList().stream().map(User::clone).sorted(comp).limit(x).collect(Collectors.toList());

    for(User user: listUsers){
        BusinessList negociosDoUser = user.negociosDoUser(reviews, businesses);

        if(negociosDoUser.getList().size() != 0){
                //negociosDoUser.getList().stream().map(Business::clone).collect(Collectors.toList());
                res.put(user.getUserId(), negociosDoUser);
            }
    }

    StringBuilder sb =  new StringBuilder();
    for(Map.Entry<String, BusinessList> entry: res.entrySet()){
        sb.append("  UserId: " + entry.getKey());
        sb.append("    Número de negócios diferentes que avaliou: " + entry.getValue().getList().size());
    }
    View view = new View();
    view.print(sb.toString());
 }








    public void consulta9(int x, String business_id, ReviewList reviews, UserList users){

        StringBuilder sb =  new StringBuilder();

        Business negocio = new Business(business_id);
        ReviewList reviewsDoNegocio = negocio.getReviews(reviews);   // lista com todos as reviews daquele negócio

        Map<String, List<Review>> userRev = new HashMap<>();

        for(Review r: reviewsDoNegocio.getList()){
            if(!userRev.containsKey(r.getUserId())){
                List<Review> aux = new ArrayList<>();
                aux.add(r.clone());
                userRev.put(r.getUserId(), aux);
            }else{
                List<Review> aux = userRev.get(r.getUserId());
                userRev.remove(r.getUserId());
                aux.add(r.clone());
                userRev.put(r.getUserId(), aux);
            }
        }
       
        Comparator<Map.Entry<String,List<Review>>> cmp = (p1,p2) -> p2.getValue().size() - p1.getValue().size();
        
        Map<String, List<Review>> ordenados = userRev.entrySet().stream().sorted(cmp)
                                                     .limit(x).collect(Collectors
                                                     .toMap(e->e.getKey(), 
                                                            e->e.getValue().stream().map(Review::clone)
                                                                           .collect(Collectors.toList())));

        sb.append("Business Id: ").append(business_id).append("\n");

        int posicao = 1;
        for(Map.Entry<String,List<Review>> user: ordenados.entrySet()){
          
            float classificacao = 0;
            for(Review rev: user.getValue()){
                classificacao += rev.getStars();
            }
            float media = classificacao / user.getValue().size();

            sb.append("  ").append(posicao).append("º User Id (que mais o avaliou): ")
                           .append(user.getKey()).append("\n");
            sb.append("      Classificação média do négocio: ").append(media).append("\n");
            posicao++;
        }
        View view = new View();
        view.print(sb.toString());
    }


    

















////////// CONSULTAS ITERATIVAS 
    /* querie 1 */

    public  SimpleEntry<Integer,Set<String>> consulta1(){
        Set<String> aux = new TreeSet<String>(); // para ficar já ordenado
        HashSet<String> avaliados = new HashSet<>();

        for (Review r : rev.getList()) {
            avaliados.add(r.getBusinessId());
        }

        for(Business i: bus.getList()){ // vou percorrer os business tds 
            String id = i.getBusinessId(); // 
             if (!avaliados.contains(id)){ // procura nas reviews o id 
                aux.add(id);  // 
                //System.out.println(id);
                }
            }
            int tamanho = aux.size();
            return new SimpleEntry<>(tamanho,aux);
        }



     /* querie 2 */

 public SimpleEntry<Integer, Integer> consulta2 (int mes, int ano) throws DateTimeException{
    
    //if ((mes < 1 && mes > 12 || ano > 2021) || ano==2021 && mes>6) throw new DateTimeException("Data inserida nao e valida"); //ate a data atual 
    //else{
        int qt=0;
        Set <String> user = new TreeSet<>();
        for (Review review : rev.getList()){
        if (review.getDate().getMonthValue() == mes ){
            if(review.getDate().getYear() == ano){
                qt++;
                user.add(review.getUserId());
            }
        }
    }

     return new SimpleEntry<>(qt,user.size());
    }
//}







/* querie 4 */ 
//Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado,
//por quantos users diferentes e a média de classificação;
public Map<Integer, List<Integer>> query4 (String businessId){
    Map<Integer,List<Integer>>map = new HashMap<>();
   
    for (int mes=1;mes<=12 ;mes++){
            int nRev =0;
            int media;
            int stars=0;
            List <Integer> lista2=new ArrayList<>();
            Set <String>set = new TreeSet<>();
            for( Review r : rev.getList()){
                if (r.getBusinessId().equals(businessId)){
                    if (r.getDate().getMonthValue() == mes ){ // retorna o mes de 1 a 12
                        nRev++;
                        set.add(r.getUserId());
                        stars += r.getStars();
                    }
                 }
            }
        int nUser =set.size();
        lista2.add(nRev);
        lista2.add(nUser);
        if(nRev > 0)
            media= stars/nRev;
        else media = 0;
        lista2.add(media);
        map.put(mes,lista2);
    }
    return map;
}







public static float sum(List<Float> list) {
    int sum = 0;
    for (Float i: list) {
        sum += i;
    }
    return sum;
}

public void consulta10() {
    
    Map<String,List<String>>state = new HashMap<>();
    Map<String,List<Business>> cidades = new HashMap<>();

    for(Business b : this.bus.getList()){ 
        if(!cidades.containsKey(b.getCity())){
            List<Business> aux = new ArrayList<>();
            
            aux.add(b.clone());
            cidades.put(b.getCity(), aux);
        }else{
            List<Business> aux = cidades.get(b.getCity());
            if(!aux.contains(b)){
                cidades.remove(b.getCity());
                aux.add(b.clone());
            }
            cidades.put(b.getCity(), aux);
        }
    }

    for(Business b : this.bus.getList()){ 
        if(!state.containsKey(b.getState())){
            List<String> aux = new ArrayList<>();
            aux.add(b.getCity());
            state.put(b.getState(), aux);
        }
        else{
            List<String> aux = state.get(b.getState());
            if(!aux.contains(b.getCity())){
                state.remove(b.getState());
                aux.add(b.getCity());    
            }
             state.put(b.getState(), aux);
        }
    }
    
    Map<String,SimpleEntry< Float,Integer>> busMedia = new HashMap<>();
    
    for(Review r: rev.getList()){
        if(!busMedia.containsKey(r.getBusinessId())){
            
            busMedia.put(r.getBusinessId(), new SimpleEntry<>(r.getStars(), 1));
        }else{
            SimpleEntry<Float,Integer> n = busMedia.get(r.getBusinessId());
            
            busMedia.remove(r.getBusinessId());
            busMedia.put(r.getBusinessId(), new SimpleEntry<>(n.getKey()+r.getStars(),n.getValue()+1));
        }
    }

   // System.out.println(cidades.toString());
    

    StringBuilder sb = new StringBuilder();
    for (Map.Entry<String,List<String>> entry : state.entrySet()) {

        sb.append("State: ").append(entry.getKey()).append("\n");
        for (String s : entry.getValue()) {
            List<Business> bs = cidades.get(s);
            sb.append("\tCity: ").append(s).append("\n");
            for (Business business : bs) {

                SimpleEntry<Float,Integer> m;
                if(busMedia.containsKey(business.getBusinessId())) {

                     m = busMedia.get(business.getBusinessId());
                
                }else {
                     m =  new SimpleEntry<>(0.0f, 1);
                }
                
                Float med = m.getKey()/m.getValue();
                sb.append("\t\tBusiness: ").append(business.getName())
                .append(" whit Stars: ").append(med).append("\n");
                
                //System.out.println(i);
                //i++;
            }
        }

    }
    View view = new View();
    view.print(sb.toString());
}










}



