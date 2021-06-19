/**
 * Dados sobre um objeto Review.
 * 
 * @author grupo 64
 * @version
 */

package model.Reviews;

import java.io.Serializable;
import model.Businesses.*;
import java.util.ArrayList;
import java.util.List;
import java.time.LocalDateTime;


public class Review implements Serializable
{
    private String reviewId;
    private String userId;
    private String businessId;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String text;
    
    /*********************************************** CONSTRUTORES ***********************************************/

    public Review(){
         this.reviewId = "";
         this.userId = "";
         this.businessId = "";
         this.stars = 0;
         this.useful = 0;
         this.funny = 0;
         this.cool = 0;
         this.date = LocalDateTime.now();
         this.text = "";
    }

    public Review(String reviewId, String userId, String businessId, float stars, int useful,
               int funny, int cool, LocalDateTime date, String text){
         this.reviewId = reviewId;
         this.userId = userId;
         this.businessId = businessId;
         this.stars = stars;
         this.useful = useful;
         this.funny = funny;
         this.cool = cool;
         this.date = date;
         this.text = text;
    }

    public Review(Review rev){
         this.reviewId = rev.getReviewId();
         this.userId = rev.getUserId();
         this.businessId = rev.getBusinessId();
         this.stars = rev.getStars();
         this.useful = rev.getUseful();
         this.funny = rev.getFunny();
         this.cool = rev.getCool();
         this.date = rev.getDate();
         this.text = rev.getText();
    }

    /**
     * Construtor que cria um objeto User a partir de uma string.
     */
    
    
    /******************************************** GETTERS E SETTERS ********************************************/

    /**
     * Método que obtém o review id.
     * @return review id
     */
    public String getReviewId(){
        return this.reviewId;
    }

    /**
     * Método que obtém o user id.
     * @return user id
     */
    public String getUserId(){
        return this.userId;
    }

    /**
     * Método que obtém o business id.
     * @return business id
     */
    public String getBusinessId(){
        return this.businessId;
    }

    /**
     * Método que obtém o número de stars.
     * @return número de stars
     */
    public float getStars(){
        return this.stars;
    }

    /**
     * Método que obtém o valor de useful.
     * @return valor de useful
     */
    public int getUseful(){
        return this.useful;
    }

    /**
     * Método que obtém o valor de funny.
     * @return valor de funny
     */
    public int getFunny(){
        return this.funny;
    }

    /**
     * Método que obtém o valor de cool.
     * @return valor de cool
     */
    public int getCool(){
        return this.cool;
    }

    /**
     * Método que obtém a data.
     * @return data
     */
    public LocalDateTime getDate(){
        return this.date;
    }

    /**
     * Método que obtém o texto da review.
     * @return texto (todo como uma string)
     */
    public String getText(){
        return this.text;
    }
    
    /**
     * Método que muda o review id.
     * @param reviewId novo review id
     */
    public void setReviewId(String reviewId){
        this.reviewId = reviewId;
    }

    /**
     * Método que muda o user id.
     * @param userId novo user id
     */
    public void setUserId(String userId){
        this.userId = userId;
    }

    /**
     * Método que muda o business id.
     * @param businessId novo business id
     */
    public void setBusinessId(String businessId){
        this.businessId = businessId;
    }

    /**
     * Método que muda o número de stars.
     * @param stars novo número de stars
     */
    public void setStars(float stars){
        this.stars = stars;
    }

    /**
     * Método que muda o valor do useful.
     * @param useful novo valor do useful
     */
    public void setUseful(int useful){
        this.useful = useful;
    }

    /**
     * Método que muda o valor de funny.
     * @param funny novo valor de funny
     */
    public void setFunny(int funny){
        this.funny = funny;
    }

    /**
     * Método que muda o valor de cool.
     * @param cool novo valor de cool
     */
    public void setCool(int cool){
        this.cool = cool;
    }

    /**
     * Método que muda a data.
     * @param date nova data
     */
    public void setDate(LocalDateTime date){
        this.date = date;
    }

    /**
     * Método que muda o texto da review.
     * @param text novo texto da review
     */
    public void setText(String text){
        this.text = text;
    }

    /**
     * Método que devolve a lista dos negócios de um determinado ano.
     * @param businesses lista de todos os negócios
     * @param review lista de todos os reviews
     * @param anoPar ano
     * @return lista de negócios desse ano
     */
    public BusinessList negociosDoAno(BusinessList businesses,ReviewList review,int anoPar){
       
        BusinessList negocios = new BusinessList();
        List<Business> aux = new ArrayList<>();

        for(Business bus: businesses.getList()){
            for(Review r : review.getList())
                if(r.getBusinessId().equals(bus.getBusinessId()))    
                    if(r.getDate().getYear() == anoPar)
                    aux.add(bus.clone());
        
        }
        negocios.setList(aux);
        return negocios;
    }

    /**
     * Método que devolve um clone de um objeto Review.
     * @return clone
     */
    public Review clone(){
        return new Review(this);
    }
    
    /**
     * Método que reescreve o equals de um objeto Review.
     * @param obj objeto Review
     * @return verdadeiro se dois objetos Review forem iguais.
     */
    public boolean equals(Object obj){
        if (obj == this) return true;
        if (obj == null || ! obj.getClass().equals(this.getClass())) return false;
        Review rev = (Review) obj;
        return  this.reviewId.equals(rev.getReviewId()) &&
            this.userId.equals(rev.getUserId())&&
            this.businessId.equals(rev.getBusinessId()) &&
            this.stars == rev.getStars() &&
            this.useful == rev.getUseful() &&
            this.funny == rev.getFunny() &&
            this.cool == rev.getCool() &&
            this.date == rev.getDate() &&
            this.text.equals(rev.getText());
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Review ID: ").append(this.reviewId);
        sb.append("User ID: ").append(this.userId);
        sb.append("Business ID: ").append(this.businessId);
        sb.append("Stars: ").append(this.stars);
        sb.append("Useful: ").append(this.useful);
        sb.append("Funny: ").append(this.funny);
        sb.append("Cool: ").append(this.cool);
        sb.append("Date: ").append(this.date);
        sb.append("Text: ").append(this.text);
        return sb.toString();
    }
}
