/**
 * Classe que trabalha sobre ficheiros e faz load dos mesmos.
 *
 * @author grupo 64
 * @version 030621
 */

package loaders;

import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.ArrayList;

public class Loadlog {
    
    /**
     * Método que carrega cada uma das listas com o conteúdo dos respetivos ficheiros.
     * 
     * @param path array que contém, em cada indíce, o nome dos ficheiros a serem lidos
     * @param businesses lista de negócios a ser carregada
     * @param reviews lista de reviews a ser carregada
     * @param users lista de users a ser carregada
     */
    public boolean load(String[] path,
                        BusinessList businesses,
                        ReviewList reviews,
                        UserList users){

        try {
            Files.lines(Paths.get(path[0]))
                 .forEach(fields -> parse(fields,businesses));
                
            Files.lines(Paths.get(path[1]))
                 .forEach(fields -> parse(fields,reviews));
                        
            Files.lines(Paths.get(path[2]))
                 .forEach(fields -> parse(fields,users));        
            return true;
                
        } catch (IOException e){
            e.printStackTrace();
            return false;
        }
    }
    
    /**
     * Método que faz o parse de uma linha do ficheiro de modo a criar um negócio a partir dessa linha.
     * Após criar este negócio, adiciona-o à lista de negócios.
     *
     * @param s linha do ficheiro
     * @param businesses lista de negócios
     */
    public void parse (String s, BusinessList businesses){
            
        String[] tokens = s.split(";");              
            
        ArrayList<String> categories = new ArrayList<>();
        //for(String token : tokens) System.out.println(token);
        if(tokens.length >4) {

            String[] categorias = tokens[4].split(",");  
                
            for(String categoria : categorias){
                categories.add(categoria);
            }
        }
        Business business = new Business(tokens[0], tokens[1], tokens[2], tokens[3], categories);
            
        businesses.addBusiness(business.clone());
             
    }

    /**
     * Método que faz o parse de uma linha do ficheiro de modo a criar uma review a partir dessa linha.
     * Após criar esta review, adiciona-a à lista de reviews.
     *
     * @param s linha do ficheiro
     * @param reviews lista de reviews
     */
    public void parse (String s, ReviewList reviews){
       try{
            String[] tokens = s.split(";");  
                
            String[] tokensDate = tokens[7].split("-| |:");  

            LocalDateTime date;

            if (tokensDate.length == 6){
                date = LocalDateTime.of(Integer.parseInt( tokensDate[0] ),
                                        Integer.parseInt( tokensDate[1] ), 
                                        Integer.parseInt( tokensDate[2] ), 
                                        Integer.parseInt( tokensDate[3] ), 
                                        Integer.parseInt( tokensDate[4] ), 
                                        Integer.parseInt( tokensDate[5] ));
            }else{
                date = LocalDateTime.now();
            }
            Review review = new Review( tokens[0], 
                                        tokens[1], 
                                        tokens[2], 
                                        Float.parseFloat( tokens[3] ),
                                        Integer.parseInt( tokens[4] ),
                                        Integer.parseInt( tokens[5] ),
                                        Integer.parseInt( tokens[6] ),
                                        date,
                                        tokens[8] );
            reviews.addReview(review.clone());
        }
        catch(Exception e){
            //e.printStackTrace();
        }
    }
    
    /**
     * Método que faz o parse de uma linha do ficheiro de modo a criar um user a partir dessa linha.
     * Após criar este user, adiciona-o à lista de users.
     *
     * @param s linha do ficheiro
     * @param users lista de users
     */
    public void parse ( String s, UserList users){
            
        String[] tokens = s.split(";");  
            
        ArrayList<String> friends = new ArrayList<>();
        if(tokens.length > 3) {
            String[] amigos = tokens[3].split(",");  
                
            for(String amigo : amigos){
                    friends.add(amigo);
            }
        }
        User user = new User(tokens[0], tokens[1], friends);
            
        users.addUser(user.clone());
    }

    /**
     * Método que devolve um array em que, em cada indice, é guardado o nome de cada um dos 3 ficheiros a serem lidos.
     * @return o array com os nomes dos 3 ficheiros
     */
    public String[] getFichDefaut() {
        String[] ficheirosDefault = new String[3];
        ficheirosDefault[0] ="./input/business_full.csv";
        ficheirosDefault[1] ="./input/reviews_1M.csv";
        ficheirosDefault[2] ="./input/users_full.csv";
        return ficheirosDefault;
    }

}
