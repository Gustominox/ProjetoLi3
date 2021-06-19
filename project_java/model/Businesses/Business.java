/**
 * Dados sobre um objeto Business.
 * 
 * @author grupo 64 
 * @version 
 */

package model.Businesses;

import java.util.List;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.stream.Collectors;
import model.Reviews.Review;
import model.Reviews.ReviewList;


public class Business implements Serializable
{
    private String businessId;
    private String name;
    private String city;
    private String state;
    private List<String> categories;
    
    /**
     * Construtor por omissão.
     */
    public Business(){
        this.businessId = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<String>();
    }

    /**
     * Contrutor que recebe um business id.
     */
    public Business(String id){
        this.businessId = id;
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<String>();
    }
    
    /**
     * Construtor parametrizado.
     */
    public Business(String businessId, String name, String city, String state, List<String> categories){
        this.businessId = businessId;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories.stream().collect(Collectors.toList());
    }
    
    /**
     * Construtor de cópia.
     */
    public Business(Business bus){
        this.businessId = bus.getBusinessId();
        this.name = bus.getName();
        this.city = bus.getCity();
        this.state = bus.getState();
        this.categories = bus.getCategories();
    }
    
    /**
    * Método que obtém o business Id do negócio.
    * @return business Id do negócio
    */
    public String getBusinessId(){
        return this.businessId;
    }
    
    /**
    * Método que obtém o nome do negócio.
    * @return nome do negócio
    */
    public String getName(){
        return this.name;
    }
    
    /**
    * Método que obtém a cidade do negócio.
    * @return a cidade do negócio
    */
    public String getCity(){
        return this.city;
    }
    
    /**
    * Método que obtém estado do negócio.
    * @return estado do negócio
    */
    public String getState(){
        return this.state;
    }
    
    /**
    * Método que obtém as categorias do negócio.
    * @return categorias do negócio
    */
    public List<String> getCategories(){
        return this.categories;
    }
    
    /**
    * Método que muda o business Id do negócio.
    * @param businessId do negócio
    */
    public void setBusinessId(String businessId){
        this.businessId = businessId;
    }
    
    /**
    * Método que muda o nome do negócio.
    * @param name do negócio
    */
    public void setName(String name){
        this.name = name;
    }
    
    /**
    * Método que muda a cidade do negócio.
    * @param city do negócio
    */
    public void setCity(String city){
        this.city = city;
    }
    
    /**
    * Método que muda o estado do negócio.
    * @param state do negócio
    */
    public void setState(String state){
        this.state = state;
    }
    
    /**
    * Método que muda as categorias do negócio.
    * @param categories do negócio
    */
    public void setCategories(List<String> categories){
        this.categories = categories.stream().collect(Collectors.toList());
    }

    /**
     * Método que vai buscar todas as reviews de um negócio.
     *
     *@param reviews lista de reviews
     *@return lista das reviews do negócio
     */
    public ReviewList getReviews(ReviewList reviews){
        ReviewList reviewsDoBus = new ReviewList();
        List<Review> aux = new ArrayList<>();

        for(Review rev: reviews.getList()){
            if(this.businessId.equals(rev.getBusinessId()))
                aux.add(rev.clone());
        }
        reviewsDoBus.setList(aux);
        return reviewsDoBus;
    }
    
    /**
    * Método que faz um clone de um negócio.
    * @return o clone
    */    
    public Business clone(){
        return new Business(this);
    }    
    
    /**
     * Método que reescreve o equals de um objeto Business.
     * @param obj objeto Business
     * @return verdadeiro se dois objetos Business forem iguais.
     */
    public boolean equals(Object obj){
        if (obj == this) return true;
        if (obj == null || ! obj.getClass().equals(this.getClass())) return false;
        Business bus = (Business) obj;
        return  this.businessId.equals(bus.getBusinessId()) &&
            this.name.equals(bus.getName())&&
            this.city.equals(bus.getCity()) &&
            this.state.equals(bus.getState()) &&
            this.categories.equals(bus.getCategories());
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Business ");
        sb.append("[ BusinessId: ").append(this.businessId);
        sb.append("; Name: ").append(this.name);
        sb.append("; City: ").append(this.city);
        sb.append("; State: ").append(this.state);
        sb.append("; Categories: ").append(this.state);
        
        for (String s : this.categories){
                sb.append(s).append(", ");
        }
        sb.append("]");
        return sb.toString();
    }            
}
