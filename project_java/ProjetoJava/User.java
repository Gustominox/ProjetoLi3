/**
 * Escreva a descrição da classe User aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class User
{
    private String userId;
    private String name;
    //private String friends;
    
    public User(){
        this.userId = "";
        this.name = "";
    }
    
    public User(String user_id, String name){
        this.userId = userId;
        this.name = name;
    }
    
    public User(User user){
        this.userId = user.getUserId();
        this.name = user.getName();
    }
    
    public String getUserId(){
        return this.userId;
    }
    
    public String getName(){
        return this.name;
    }
    
    public void setUserId(String userId){
        this.userId = userId;
    }
    
    public void setName(String name){
        this.name = name;
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
