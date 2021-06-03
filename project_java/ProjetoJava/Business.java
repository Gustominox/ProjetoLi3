/**
 * Escreva a descrição da classe Business aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class Business
{
    private String businessId;
    private String name;
    private String city;
    private String state;
    private List<List<String>> categories;
    
    public Business(){
        this.businessId = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<List<String>>();
    }
    
    public Business(String businessId, String name, String city, String state, List<List<String>> categories){
        this.businessId = businessId;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = new ArrayList<List<String>>();
        for(List<String> subList1 : categories){
          List<String>  subList2 = subList1.stream().collect(Collectors.toList());
          this.categories.add(subList2);
        }
    }
    
    public Business(Business bus){
        this.businessId = bus.getBusinessId();
        this.name = bus.getName();
        this.city = bus.getCity();
        this.state = bus.getState();
        this.categories = bus.getCategories();
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
    
    public List<List<String>> getCategories(){
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
    
    public void setCategories(List<List<String>> categories){
        this.categories = new ArrayList<List<String>>();
        for(List<String> subList1 : categories){
          List<String>  subList2 = subList1.stream().collect(Collectors.toList());
          this.categories.add(subList2);
        }
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
            this.state.equals(bus.getState());
            
            // falta para as categorias
            
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("BusinessId: ").append(this.businessId);
        sb.append("Name: ").append(this.name);
        sb.append("City: ").append(this.city);
        sb.append("State: ").append(this.state);
        
        //falta para as categorias
        
        return sb.toString();
    }            
}
