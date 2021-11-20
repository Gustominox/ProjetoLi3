/**
 * Class que contem o codigo das consultas
 *
 * @author grupo 64
 * @version 030621
 */
package model;

import java.io.*;
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
/**
    * Método que obtém a lista de business 
    * @return lista dos business
    */
    public BusinessList getBus() {
        return bus;
    }
/**
    * Método que define a lista de business 
    * @param  Nova lista de negocios
    */
    public void setBus(BusinessList bus) {
        this.bus = bus;
    }
/**
    * Método que obtém a lista de review 
    * @return lista dos review
    */ 
    public ReviewList getRev() {
        return rev;
    }
/**
    * Método que define a lista de reviews 
    * @param  Nova lista de reviews
    */

    public void setRev(ReviewList rev) {
        this.rev = rev;
    }
 /**
    * Método que obtém a lista de user 
    * @return lista dos user
    */
    public UserList getUser() {
        return user;
    }
/**
    * Método que define a lista de user 
    * @param  Nova lista de user
    */
    public void setUser(UserList user) {
        this.user = user;
    }

    
    /**
     * Construtor parametrizado.
     */
    public GestReviews(BusinessList bus, ReviewList rev, UserList user){
        this.bus = bus;
        this.rev = rev;
        this.user = user;
    }

    /**
     * Método que guarda o estado do programa num ficheiro.
     * @param nomeFich nome do ficheiro onde será guardado
     */
    public void guardaEstado(String nomeFich) throws FileNotFoundException, IOException{
        FileOutputStream fos = new FileOutputStream(nomeFich);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        
        oos.writeObject(this);
        
        fos.flush();
        fos.close();
    }
    
    /**
     * Método que devolve a lista das reviews válidas.
     * @param reviews lista de todas as reviews (válidas e inválidas)
     * @return lista das reviews válidas
     */
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
    

    /********************************************** ESTATISTICAS **********************************************/

    /**
     * Método que apresenta os resultados de todos os requisitos da estatística 1.
     */
    public void estatistica1(){

        View view = new View();
        // ReviewList reviewsValidas = reviewsValidas(rev);
        
        view.print("Nome do ficheiro: reviews.csv\n");
        Map<String,Integer> businessAvaliados = dadosSobreReview();
        
        view.print("Nome do ficheiro: business.csv\n");
        dadosSobreBusiness(businessAvaliados);
        
        view.print("Nome do ficheiro: users.csv\n");
        dadosSobreUser();
    }
    
    /**
     * Método que devolve um conjunto de todos os negócios avaliados (pelo seu id).
     * Este método calcula, ainda, o número de reviews erradas e o número de reviews sem impacto, imprimindo-os no ecrã.
     */
    public Map<String,Integer> dadosSobreReview(){

        int nrRevErradas = 0;
        int nrRevSemImpacto = 0;

        StringBuilder sb =  new StringBuilder();
        Map<String,Integer> busAvaliados = new HashMap<>();

        for(Review rev: this.rev.getList()){
            busAvaliados.put(rev.getBusinessId(),0);
            if(rev.getReviewId().length() == 0) nrRevErradas++;
            else{
                int somatorio = rev.getCool() + rev.getFunny() + rev.getUseful();
                if(somatorio == 0) nrRevSemImpacto++;
            }
        }
        sb.append("    Número de reviews errados: " + nrRevErradas).append("\n");
        sb.append("    Número de reviews com 0 impacto: " + nrRevSemImpacto).append("\n");

        View view = new View();
        view.print(sb.toString());   
        return busAvaliados;     
    }

    /**
     * Método que calcula o número total de negócios (avaliados e não avaliados), o número de negócios avaliados e
     * o número de negócios não avaliados. Para isso, para além da lista de negócios e da lista de reviews válidas
     * recebe como argumento o map devolvido pelo método dadosSobreReview().
     * Esse map contém todos os business id que tiveram alguma review.
     *
     * @param businessAvaliados map dos business avaliados (pelo seu id)
     */
    public void dadosSobreBusiness(Map<String,Integer> businessAvaliados){

        int nrBusTotal = 0;
        int busAval = 0;
        
        StringBuilder sb =  new StringBuilder();

        for(Business b: this.bus.getList()){

            if(b.getBusinessId().length() != 0){
                nrBusTotal++;
                if (businessAvaliados.containsKey(b.getBusinessId()))
                    busAval++;
            }
        }
        sb.append("    Número total de negócios: " + nrBusTotal).append("\n");
        sb.append("    Número de negócios avaliados: " + busAval).append("\n");
        sb.append("    Número de negócios não avaliados: " + (nrBusTotal - busAval)).append("\n"); 

        View view = new View();
        view.print(sb.toString());      
    }

    /**
     * Método que calcula o número total de users (com ou sem reviews), o número de users que fizeram reviews e
     * o número de users nada avaliaram. Para isto, para além da lista de users, recebe a lista de reviews válidas.
     */
    public void dadosSobreUser(){

        StringBuilder sb =  new StringBuilder();
        View view = new View();

        int nrUserTotal = 0;
        int usersAval = 0;
        int usersNaoAval = 0;
        Map<String,Integer> userAvaliados = new HashMap<>();

        for (Review r: this.rev.getList()) {
            userAvaliados.put(r.getUserId(),0);
        }
        for(User user: this.user.getList()){
            if(user.getUserId().length() != 0){
                nrUserTotal++;
                
                if (userAvaliados.containsKey(user.getUserId()))
                    usersAval++;
            }         
        }
        usersNaoAval = nrUserTotal - usersAval;

        sb.append("    Número total de users: " + nrUserTotal).append("\n");
        sb.append("    Número de users que fizeram reviews: " + usersAval).append("\n");
        sb.append("    Número de users que nada avaliaram: " + usersNaoAval).append("\n");

        view.print(sb.toString()); 
    }
    
    
    
    /**
     * Método que apresenta os resultados de todos os requisitos da estatística 2.
     *
     * Neste método, é calculado:
     * o número total de reviews por mês;
     * a média de classificação de reviews por mês;
     * o número de distintos utilizadores que avaliaram por mês;
     * e, ainda, a média da classificação global de reviews (de todos os meses).
     */
    public float estatistica2(   int[] revPorMes ,
                                float[] claPorMes,  
                                int[] nrUserMes ){
        
        
        float valorGlobal;
        float stars = 0;
        int nrRev = 0;
        float[] starsArr = new float[12];
        //HashSet<String> userVisitados = new HashSet<>();
        
        for(Review rev: this.rev.getList()){
            starsArr[rev.getDate().getMonthValue()-1] += rev.getStars();
            revPorMes[rev.getDate().getMonthValue()-1]++;
            stars += rev.getStars(); 
            nrRev++;
        }

        for(int i=0; i<12; i++){
            claPorMes[i] = starsArr[i] / revPorMes[i];
        }
        valorGlobal = stars / nrRev;
        return valorGlobal;
        
    }

    /**
     * Método que devolve um array em que cada indice do array corresponde a um mês (valor do mês - 1).
     * Cada indice contém o número de users distintos que avaliaram nesse mês.
     *
     * @return array com todos os meses e o número de users distintos que avaliaram em cada mês.
     */
    public int[] userPorMes(){
        
        HashSet<String> userVisitados = new HashSet<>();
        int[] nrUserMes = new int[12];
        for(Review rev: this.rev.getList()){
            if(!userVisitados.contains(rev.getUserId())){

                nrUserMes [rev.getDate().getMonthValue()-1]++;
                userVisitados.add(rev.getUserId());       
            
            }
        }
        return nrUserMes;
    }

    /******************************************* CONSULTAS INTERATIVAS *******************************************/

    /**
    * QUERY 1
    * Devolve a lista ordenada alfabeticamente com os identificadores dos negócios nunca
    * avaliados e o seu respetivo total.
    */
    public SimpleEntry<Integer,Set<String>> consulta1(){
        Set<String> aux = new TreeSet<String>(); // para ficar já ordenado
        HashSet<String> avaliados = new HashSet<>();

        for (Review r : rev.getList()) {
            avaliados.add(r.getBusinessId());
        }

        for(Business i: bus.getList()){ // vou percorrer os business tds 
            String id = i.getBusinessId();
             if (!avaliados.contains(id)){ // procura nas reviews o id 
                aux.add(id);
                //System.out.println(id);
            }
        }
        int tamanho = aux.size();
        return new SimpleEntry<>(tamanho,aux);
    }

    /**
    * QUERY 2
    * Dado um mês e um ano (válidos), determina o número total global de reviews
    * realizadas e o número total de users distintos que as realizaram.
    *
    * @param mes o mes dado
    * @param ano o ano dado
    */
    public SimpleEntry<Integer, Integer> consulta2 (int mes, int ano) throws DateTimeException{
    
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

    /**
    * QUERY 3
    * Dado um código de utilizador, determina, para cada mês, quantas reviews fez,
    * quantos negócios distintos avaliou e que nota média atribuiu.
    *
    * @param userId o user id dado
    */
    public void consulta3(String userId,float[] stars  ,
                                        int[]   revMes ,
                                        int[]   busMes ){

        List<Review> novaList  = new ArrayList<>();
        for(Review rev: this.rev.getList()){ //guardamos numa lista todas as reviews que o user fez
            if(rev.getUserId().equals(userId)){
                novaList.add(rev.clone());
                revMes[rev.getDate().getMonthValue()-1]++;
                stars[rev.getDate().getMonthValue()-1] += rev.getStars();
            }

        }
        
        List<Business> novaList2  = new ArrayList<>();
        for(Review rev: novaList){ //percurremos a lista de todas as reviews que o user fez
            String id = rev.getBusinessId();
            for(Business b: this.bus.getList()){ //guardamos numa lista todos os negocios que o user fez um review
                if(b.getBusinessId().equals(id) && !novaList2.contains(b)){
                    novaList2.add(b.clone());//para ver se já não fez uma review desse business antes
                    busMes[rev.getDate().getMonthValue()-1]++;
                }
            }
        }
    }

    /**
     * QUERY 4 
     * Dado o código de um negócio, determina, mês a mês, quantas vezes foi avaliado,
     * por quantos users diferentes e a média de classificação.
     *
     * @param business_id business id dado
     */
    public Map<Integer, List<Integer>> consulta4 (String businessId){
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

    /** 
     * QUERY 5
     * Dado o código de um utilizador determina a lista de nomes de negócios que mais
     * avaliou (e quantos), ordenada por ordem decrescente de quantidade e, para
     * quantidades iguais, por ordem alfabética dos negócios.
     *
     * @param x número de negócios que o user dado mais avaliou
     * @param user_id o user id dado
     */
    public Map<String, Integer> consulta5( String user_id){

        User user = new User(user_id);
        ReviewList reviewsDoUser = user.getReviews(this.rev);
        
        Map<String,Integer> busNr = new HashMap<>();
        // usado para analisar se o business já existe (ou não) no map anterior pelo seu business id
        List<String> busId = new ArrayList<>();

        Comparator<Map.Entry<String,Integer>> cmp = (p1,p2)-> ( p1.getValue() != p2.getValue() ) ?
                                                              ( p2.getValue() -  p1.getValue() ) :
                                                                p1.getKey().compareTo(p2.getKey());

        for(Review r: reviewsDoUser.getList()){
            Business bus = this.bus.getBusiness(r.getBusinessId());
                     
            if( !busId.contains(bus.getBusinessId()) ){
                busNr.put(bus.getName(), 1);
                busId.add(bus.getBusinessId());
                
            }else{
                int n = busNr.get(bus.getName());
                busNr.remove(bus.getName());
                busNr.put(bus.getName(), n+1);
            }
        }

        Map<String, Integer> ordenados = busNr.entrySet().stream()
                                              .sorted(cmp)//Collections.reverseOrder(Map.Entry.comparingByValue()))
                                              .collect(Collectors.toMap(
                                                       Map.Entry::getKey,
                                                       Map.Entry::getValue,
                                                       (a, b) -> { throw new AssertionError(); },
                                                       LinkedHashMap::new
                                               ));
        return ordenados;
    }

    /**
     * QUERY 6
     * Determina o conjunto dos X negócios mais avaliados (com mais reviews) em cada
     * ano, indicando o número total de distintos utilizadores que o avaliaram (X é um
     * inteiro dado pelo utilizador).
     *
     * @param x número de negócios mais avaliados
     */
    
    public Map<Integer,Map<String,Integer>> consulta6(int x){
        Map<Integer,Map<String,Integer>>anos = new HashMap<>();
        for(Review r: this.rev.getList()){
            

            if(!anos.containsKey(r.getDate().getYear())){
                Map<String,Integer> aux = new HashMap<>();
                aux.put(r.getBusinessId(), 1);
                
                anos.put(r.getDate().getYear(), aux);
            }
            else{
                Map<String,Integer> busNr = anos.get(r.getDate().getYear());
                if(!busNr.containsKey(r.getBusinessId())){
                
                    busNr.put(r.getBusinessId(), 1);
                }else{
                    int n = busNr.get(r.getBusinessId());
                    busNr.remove(r.getBusinessId());
                    busNr.put(r.getBusinessId(), n+1);
                }
                anos.remove(r.getDate().getYear());
                    
                anos.put(r.getDate().getYear(), busNr);
            }
        }


        Comparator<Map.Entry<String,Integer>> cmp = (p1,p2)-> ( p1.getValue() != p2.getValue() ) ?
                                                              ( p2.getValue() -  p1.getValue() ) :
                                                                p1.getKey().compareTo(p2.getKey());
        Map<Integer, Map<String,Integer>> ret = new HashMap<>();
        for (Map.Entry<Integer, Map<String,Integer>> entry : anos.entrySet()) {

        
            Map<String, Integer> ordenados = entry.getValue().entrySet().stream()
                                              .sorted(cmp).limit(x)//Collections.reverseOrder(Map.Entry.comparingByValue()))
                                              .collect(Collectors.toMap(
                                                       Map.Entry::getKey,
                                                       Map.Entry::getValue,
                                                       (a, b) -> { throw new AssertionError(); },
                                                       LinkedHashMap::new
                                               ));
            int ano = entry.getKey();
            
            ret.put(ano, ordenados);
        } 
        return ret;
        
    }
  
    /**
     * QUERY 7
     * Determina, para cada cidade, a lista dos três mais famosos negócios em termos de
     * número de reviews.
     */
    public Map<String, List<SimpleEntry<Business,Integer>>> consulta7(){
        

        List<String> cidadesVisitadas = new ArrayList<>();
        Map<String,List<SimpleEntry<Business,Integer>>> cidades = new HashMap<>();

        Map<String,Integer> busNr = new HashMap<>();
        Comparator<SimpleEntry<Business,Integer>> comp = (b1,b2) -> b2.getValue() - b1.getValue();

        for(Review r: this.rev.getList()){
            if(!busNr.containsKey(r.getBusinessId())){
                
                busNr.put(r.getBusinessId(), 1);
            }else{
                int n = busNr.get(r.getBusinessId());
                busNr.remove(r.getBusinessId());
                busNr.put(r.getBusinessId(), n+1);
            }
        }
        for(Business b: this.bus.getList()){

            if(!cidadesVisitadas.contains(b.getCity())){
                List<SimpleEntry<Business,Integer>> idBusCidade = new ArrayList<>();
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
        Map<String,List<SimpleEntry<Business,Integer>>> ret = new HashMap<>();
        for (Map.Entry<String, List<SimpleEntry<Business,Integer>>> entry : cidades.entrySet()) {

        
            List<SimpleEntry<Business,Integer>> ordenados = entry.getValue().stream().sorted(comp).limit(3).collect(Collectors.toList());
            String city = entry.getKey();
            
            ret.put(city, ordenados);
        }  
        return ret;
    }

    /**
     * QUERY 8
     * Determina os códigos dos X utilizadores (sendo X dado pelo utilizador) que
     * avaliaram mais negócios diferentes, indicando quantos, sendo o critério de
     * ordenação a ordem decrescente do número de negócios.
     *
     * @param x número utilizadores que avaliaram mais negócios diferentes
     */
    
    public Map<String, List<String>> consulta8 (int x){
            
        
        Map<String,List<String>> negDoUser = new HashMap<>();
    
        for(Review review: this.rev.getList()){
            String userId = review.getUserId();
            String busId = review.getBusinessId();

            if(negDoUser.containsKey(userId)){
                if(!existe(negDoUser.get(userId), busId)){
                    negDoUser.get(userId).add(busId);
                }
            }
            else{
                List<String> aux =  new ArrayList<>();
                aux.add(busId);
                negDoUser.put(userId,aux);
            }
        }

        Comparator<Map.Entry<String, List<String>>> cmp = (p1,p2) -> p2.getValue().size() - p1.getValue().size();

        Map<String, List<String>> ordenados = negDoUser.entrySet().stream().sorted(cmp)
                                                       .limit(x)
                                                       .collect(Collectors.toMap(
                                                                Map.Entry::getKey,
                                                                Map.Entry::getValue,
                                                                (a, b) -> { throw new AssertionError(); },
                                                                LinkedHashMap::new
                                                             ));
        
        return ordenados;
    }

    /**
     * QUERY 9
     * Dado o código de um negócio, determina o conjunto dos X users que mais o
     * avaliaram e, para cada um, qual o valor médio de classificação (ordenação cf. 5).
     *
     * @param x número de users que mais avaliaram esse negócio
     * @param business_id id do negócio dado
     */
    public  Map<String, List<Review>> consulta9(int x, String business_id){

        Business negocio = new Business(business_id);
        ReviewList reviewsDoNegocio = negocio.getReviews(this.rev);   // lista com todos as reviews daquele negócio

        Map<String, List<Review>> userRev = new HashMap<>();

        for(Review r: reviewsDoNegocio.getList()){

            if(!userRev.containsKey(r.getUserId())){
                List<Review> aux = new ArrayList<>();
                aux.add(r.clone());
                userRev.put(r.getUserId(), new ArrayList<>(aux));
            }else{
                List<Review> aux = userRev.get(r.getUserId());
                userRev.remove(r.getUserId());
                aux.add(r.clone());
                userRev.put(r.getUserId(), new ArrayList<>(aux));
            }
        }
        Comparator<Map.Entry<String, List<Review>>> cmp = (p1,p2) -> p2.getValue().size() - p1.getValue().size();
    
        Map<String, List<Review>> ordenados = userRev.entrySet().stream().sorted(cmp)
                                                  //.limit(x)
                                                  .collect(Collectors.toMap(
                                                           Map.Entry::getKey,
                                                           Map.Entry::getValue,
                                                           (a, b) -> { throw new AssertionError(); },
                                                           LinkedHashMap::new
                                                        ));
        return ordenados;
    }

    /**
     * QUERY 10
     *  Determinar para cada estado, cidade a cidade, a média de classificação de cada negócio.
     */
    public void consulta10( Map<String,List<String>>state ,
                                                Map<String,List<Business>> cidades ,
                                                Map<String,SimpleEntry< Float,Integer>> busMedia ) {
    

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

    
    
        for(Review r: this.rev.getList()){
            if(!busMedia.containsKey(r.getBusinessId())){
            
                busMedia.put(r.getBusinessId(), new SimpleEntry<>(r.getStars(), 1));
            }else{
                SimpleEntry<Float,Integer> n = busMedia.get(r.getBusinessId());
            
                busMedia.remove(r.getBusinessId());
                busMedia.put(r.getBusinessId(), new SimpleEntry<>(n.getKey()+r.getStars(),n.getValue()+1));
            }
        }
     
    }

    /************************************* MÉTODOS AUXILIARES *************************************/

    /**
     * Método que testa se um dado business id existe na lista de negócios dada.
     * @param businesses lista de negócios
     * @param busId business id a ser procurado
     * @return true se existir
     */
    public boolean existe(List<String> businesses, String busId){
        for(String s: businesses){
            if(s.equals(busId)){
                return true;
            }
        }
        return false;
    }

    /**
     * Método que soma os valores de uma dada lista.
     * @param list lista cujos valores serão somados
     * @return resultado da soma
     */
    public static float sum(List<Float> list) {
        int sum = 0;
        for (Float i: list) {
            sum += i;
        }
        return sum;
    }

}