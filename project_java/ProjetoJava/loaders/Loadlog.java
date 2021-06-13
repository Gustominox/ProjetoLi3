package loaders;
import model.*;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.AbstractMap.SimpleEntry;
import java.util.stream.Stream;

public class Loadlog {
        
        public boolean load(String[] path,
                            BusinessList businesses,
                            ReviewList reviews,
                            UserList users){

            try {
                Files.lines(Paths.get(path[0]))
                     .forEach(fields -> parse(fields,businesses));
                
                Files.lines(Paths.get(path[0]))
                     .forEach(fields -> parse(fields,reviews));
                        
                Files.lines(Paths.get(path[0]))
                     .forEach(fields -> parse(fields,users));        
                return true;
            } catch (IOException e){
                e.printStackTrace();
                return false;
            }
        }
    

       
        
        public void parse ( String s, BusinessList businesses){
            
            String[] tokens = s.split(";");  
            
            String[] categorias = tokens[4].split(",");  
            
            ArrayList<String> categories = new ArrayList<>();

            for(String categoria : categorias){
                categories.add(categoria);
            }

            Business business = new Business(tokens[0], tokens[1], tokens[2], tokens[3], categories);
            
            businesses.addBusiness(business);
             
        }


        public void parse ( String s, ReviewList reviews){
            
            String[] tokens = s.split(";");  
            
            String[] tokensDate = s.split("-| |:");  

            LocalDateTime date = LocalDateTime.of(Integer.parseInt( tokensDate[0] ),
                                                  Integer.parseInt( tokensDate[1] ), 
                                                  Integer.parseInt( tokensDate[2] ), 
                                                  Integer.parseInt( tokensDate[3] ), 
                                                  Integer.parseInt( tokensDate[4] ), 
                                                  Integer.parseInt( tokensDate[5] ));

            Review review = new Review( tokens[0], 
                                        tokens[1], 
                                        tokens[2], 
                                        Float.parseFloat( tokens[3]),
                                        Integer.parseInt( tokens[4] ),
                                        Integer.parseInt( tokens[5] ),
                                        Integer.parseInt( tokens[6] ),
                                        date,
                                        tokens[8] );
            
            reviews.addReview(review);
             
        }
        


        public void parse ( String s, UserList users){
            
            String[] tokens = s.split(";");  
            
            String[] amigos = tokens[3].split(",");  
            
            ArrayList<String> friends = new ArrayList<>();

            for(String amigo : amigos){
                friends.add(amigo);
            }

            User user = new User(tokens[0], tokens[1], friends);
            
            users.addUser(user);
             
        }

        public String[] getFichDefaut() {
            String[] ficheirosDefault = new String[3];
            ficheirosDefault[0] ="business_full.csv";
            ficheirosDefault[1] ="reviews_1M.csv";
            ficheirosDefault[2] ="users_full.csv";
            return ficheirosDefault;
        }

        

}
