/**
 * Escreva a descrição da classe User aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class User
{
    private String userId;
    private String name;
    private List<String> friends;
    
    public User(){
        this.userId = "";
        this.name = "";
        this.friends = new ArrayList<>();
    }
    
    public User(String user_id, String name, List<String> friends){
        this.userId = userId;
        this.name = name;
        this.friends = friends.stream().collect(Collectors.toList());
    }
    
    public User(User user){
        this.userId = user.getUserId();
        this.name = user.getName();
        this.friends = user.getFriends();
    }
    
    public String getUserId(){
        return this.userId;
    }
    
    public String getName(){
        return this.name;
    }
    
    public List<String> getFriends(){
        return this.friends;
    }
    
    public void setUserId(String userId){
        this.userId = userId;
    }
    
    public void setName(String name){
        this.name = name;
    }
    
    public void setFriends(List<String> friends){
        this.friends = friends.stream().collect(Collectors.toList());
    }
    
    public User clone(){
        return new User(this);
    }
    
    public boolean equals(Object obj){
        if (obj == this) return true;
        if (obj == null || ! obj.getClass().equals(this.getClass())) return false;
        User bus = (User) obj;
        return  this.userId.equals(bus.getUserId()) &&
            this.name.equals(bus.getName());            
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("UserId: ").append(this.userId);
        sb.append("Name: ").append(this.name);
        return sb.toString();
    } 
}
