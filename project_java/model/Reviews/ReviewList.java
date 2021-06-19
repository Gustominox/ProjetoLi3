/**
 * Dados sobre um objeto ReviewList.
 * 
 * @author grupo 64
 * @version
 */

package model.Reviews;

import view.View;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.HashMap;

public class ReviewList {
    private List<Review> list ; 
 
    /*********************************************** CONSTRUTOR ***********************************************/

    public ReviewList (){
        this.list = new ArrayList<>();
    }
 
    /******************************************** GETTERS E SETTERS ********************************************/

    /**
     * Método que obtém a lista de reviews.
     * @return lista de negócios
     */
    public List<Review> getList () {
        List<Review> nova =list;
     return nova;
    }

    /**
     * Método que muda a lista de reviews.
     * @param novaList nova lista de negócios
     */
    public void setList(List<Review> novaList){
        this.list = novaList.stream().map(Review::clone).collect(Collectors.toList());
    }
 

    /******************************************** MÉTODOS ********************************************/

    /**
     * Método que devolve a última review da lista.
     * @return última review
     */
    public Review getLast(){
        Review e = list.get(list.size()-1);
        return e;
    }
 
    /**
     * Método que devolve a review que se encontra num dado índice da lista.
     * @param n índice
     * @return última review
     */
    public Review getReview(int n){
        Review e = list.get(n);
        return e;
    }

    /**
     * Método que adiciona uma review à lista.
     * @param review review a adicionar
     */
    public void addReview(Review review){
        list.add(review);
    }
 
    /**
     * Método que mostra uma review que se encontra num dado índice da lista.
     * @param n índice
     */
    public void consultarReview(int n) {
 
         Review e = list.get(n);
         e.toString();
     }
 
    /**
     * Método que devolve o tamanho da lista de reviews.
     * @return tamanho
     */
    public int size() {
        return list.size();
    }
 
    /**
     * Método que mostra todas os nomes das reviews da lista.
     */
    public void mostrarReviews(){
        View view = new View();
        int aux = 0;
        for(Review review : list) {
            aux++;

            StringBuilder sb = new StringBuilder();
            sb.append( aux + "-" + review.toString()).append("\n");
            view.print(sb.toString());
        }
    }
 
    /**
     * Método que devolve a review (da lista) com o dado review id.
     * @param id review id
     * @return review com o dado id
     */
    public Review getReview(String id) {
        Review procura =null;
        for ( Review review : list){
            if(review.getReviewId().equals(id)){
                procura = review;
            }
        }
        return procura;
    }
    
    /**
     * Método que o map de users, cada um associado à sua lista de reviews.
     * Por outras palavras, para cada user, é criado a lista de todas as reviews que esse user fez.
     * @return map - key: user id | value: lista de reviews desse user
     */
    public Map<String,List<Review>> reviewsPorUser(){
        Map <String,List<Review>> resultado = new HashMap<>();
        for(Review rev: this.list){
            resultado.putIfAbsent(rev.getUserId(),new ArrayList<>());
            resultado.get(rev.getUserId()).add(rev.clone());
        }
        return resultado;
    }

    // consulta a Review consoante o nome da msm 
    /*
    public Review verReview( String nome ) {
        View view = new View ();
        Review procura =null;
        try{
        for (Review review : list ){
           if (review.getName().equals(nome)){
              procura = review;
           }
        }
    }
        catch (InputMismatchException e) {
            view.notAnInstruction();
        }
        return procura;
    }
    */

    /*
    public Review criaReview(String nome ){
        Review newReview = new Review();
        nova.setReview(nome);
        this.list.add(nova);
        return nova;
    }
    */

 }

