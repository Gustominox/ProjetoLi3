/**
 * Escreva a descrição da classe User aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

package model.Users;


import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.Arrays;

import model.Businesses.*;
import model.Reviews.*;

public class User
{
    private String userId;
    private String name;
    private List<String> friends;
    
    /**
     * Construtor por omissão.
     */
    public User(){
        this.userId = "";
        this.name = "";
        this.friends = new ArrayList<>();
    }

    /**
     * Contrutor que cria um objeto User a partir de um user id.
     */
    public User(String id){
        this.userId = id;
        this.name = "";
        this.friends = new ArrayList<>();
    }
    
    /**
     * Construtor parametrizado.
     */
    public User(String user_id, String name, List<String> friends){
        this.userId = user_id;
        this.name = name;
        this.friends = friends.stream().collect(Collectors.toList());
    }
    
    /**
     * Construtor de cópia.
     */
    public User(User user){
        this.userId = user.getUserId();
        this.name = user.getName();
        this.friends = user.getFriends();
    }
    
    /**
    * Método que obtém o user Id do user.
    * @return user Id do user
    */
    public String getUserId(){
        return this.userId;
    }
    
    /**
    * Método que obtém o nome do user.
    * @return nome do user
    */
    public String getName(){
        return this.name;
    }
    
    /**
    * Método que obtém os friends do user.
    * @return friends do user
    */
    public List<String> getFriends(){
        return this.friends;
    }
    
    /**
    * Método que muda o user Id do user.
    * @param userId novo user Id 
    */
    public void setUserId(String userId){
        this.userId = userId;
    }
    
    /**
    * Método que muda o nome do user.
    * @param name novo nome 
    */
    public void setName(String name){
        this.name = name;
    }
    
    /**
    * Método que muda os friends do user.
    * @param friends novos friends 
    */
    public void setFriends(List<String> friends){
        this.friends = friends.stream().collect(Collectors.toList());
    }

    /**
     * Método que vai buscar todas as reviews de um user.
     *
     *@param reviews lista de reviews
     *@return lista das reviews do user
     */
    public ReviewList getReviews(ReviewList reviews){
        ReviewList reviewsDoUser = new ReviewList();
        List<Review> aux = new ArrayList<>();

        for(Review rev: reviews.getList()){
            if(this.userId.equals(rev.getUserId()))
                aux.add(rev.clone());
        }
        reviewsDoUser.setList(aux);
        return reviewsDoUser;
    }

    /**
     * Método que devolve a lista de negócios distintos que o user avaliou
     * @param reviews lista de reviews
     * @param businesses lista de business
     * @return lista de negócios distintos que o user avaliou
     */    
    public BusinessList negociosDoUser(ReviewList reviews, BusinessList businesses){
        BusinessList negocios = new BusinessList();
        List<Business> busList = new ArrayList<>();

        for(Review rev: reviews.getList()){

            if(rev.getUserId().equals(getUserId())){
               for(Business bus: businesses.getList()){
                    if(bus.getBusinessId().equals(rev.getBusinessId()) && !busList.contains(bus)){
                        busList.add(bus.clone());
                    }
                }
            }
        }

        negocios.setList(busList);
        return negocios;
    }

    /**
    * Método que faz um clone de um user.
    * @return o clone
    */  
    public User clone(){
        return new User(this);
    }
    
    /**
     * Método que reescreve o equals de um objeto User.
     * @param obj objeto User
     * @return verdadeiro se dois objetos User forem iguais.
     */
    public boolean equals(Object obj){
        if (obj == this) return true;
        if (obj == null || ! obj.getClass().equals(this.getClass())) return false;
        User user = (User) obj;
        return  this.userId.equals(user.getUserId()) &&
            this.name.equals(user.getName()) &&
            this.friends.equals(user.getFriends());            
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("UserId: ").append(this.userId);
        sb.append("Name: ").append(this.name);
        String friendsString = "";
        for (String s : this.friends){
                friendsString += s + "\t";
        }
        sb.append("Friends: ").append(friendsString);
        return sb.toString();
    } 
}
