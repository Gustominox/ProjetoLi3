/**
 * Escreva a descrição da classe Business aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

package model.Businesses;

import java.util.List;
import java.util.Set;
import java.util.ArrayList;
import java.util.stream.Collectors;

import model.Reviews.Review;
import model.Reviews.ReviewList;

import java.util.Arrays;

public class Business
{
    private String businessId;
    private String name;
    private String city;
    private String state;
    private List<String> categories;
    
    public Business(){
        this.businessId = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<String>();
    }

    public Business(String id){
        this.businessId = id;
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<String>();
    }
    
    public Business(String businessId, String name, String city, String state, List<String> categories){
        this.businessId = businessId;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories.stream().collect(Collectors.toList());
    }
    
    public Business(Business bus){
        this.businessId = bus.getBusinessId();
        this.name = bus.getName();
        this.city = bus.getCity();
        this.state = bus.getState();
        this.categories = bus.getCategories();
    }
    
    public Business(String[] info){
        try{
           addBusiness(info);
       }
       catch(BusinessNotValidException e){
           new Business();
       }
   }
    
    public String getBusinessId(){
        return this.businessId;
    }
    
    public String getName(){
        return this.name;
    }
    
    public String getCity(){
        return this.city;
    }
    
    public String getState(){
        return this.state;
    }
    
    public List<String> getCategories(){
        return this.categories;
    }
    
    public void setBusinessId(String businessId){
        this.businessId = businessId;
    }
    
    public void setName(String name){
        this.name = name;
    }
    
    public void setCity(String city){
        this.city = city;
    }
    
    public void setState(String state){
        this.state = state;
    }
    
    public void setCategories(List<String> categories){
        this.categories = categories.stream().collect(Collectors.toList());
    }

    public int nrReviewsTotal(ReviewList reviews){
        int total = 0;

        for(Review rev: reviews.getList()){
            if(this.businessId.equals(rev.getBusinessId()))
                total++;
        }
        return total;
    }

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
     * Método que constrói um objeto Business, caso todos os campos sejam válidos.
     */
    public void addBusiness(String[] linha) throws BusinessNotValidException{

        if(linha[0].length() != 22)
            throw new BusinessNotValidException(linha[0]);
        
        if(linha[1].length() == 0)
            throw new BusinessNotValidException(linha[1]);
        
        if(linha[2].length() == 0)
            throw new BusinessNotValidException(linha[2]);
        
        if(linha[3].length() != 2)
            throw new BusinessNotValidException(linha[3]);
        
        if(linha[4].length() == 0)
            throw new BusinessNotValidException(linha[4]);
        
        setBusinessId(linha[0]);
        setName(linha[1]);
        setCity(linha[2]);
        setState(linha[3]);

        String[] aux = linha[4].split(",");
        List<String> categorias = new ArrayList<>();
        for(String s: aux)
            categorias.add(s);
        setCategories(categorias);
    }
    
    public static Business parse(String info){
        String[] camposBus = info.split(";");
        
        return new Business(camposBus[0],
                        camposBus[1],
                        camposBus[2],
                        camposBus[3],
                        Arrays.asList(camposBus[4].split(",")));
    }
    
    public Business clone(){
        return new Business(this);
    }    
    
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
