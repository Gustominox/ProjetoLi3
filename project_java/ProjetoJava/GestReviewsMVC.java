import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;
import controller.*;
import view.*;
import loaders.*;
import model.*;
import java.io.IOException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner ;

        //
       
    public class GestReviewsMVC {
    
        
        
        public static void main (String[] args ) throws IOException{
    
            Scanner scan = new Scanner(System.in);
            View view = new View();
            Controller controller = new Controller();
            BusinessList listaBusinesses = new BusinessList();
            ReviewList   listaReviews    = new ReviewList();
            UserList     listaUsers      = new UserList(); 
            
            Loadlog loader = new Loadlog();

            loader.load(loader.getFichDefaut(), listaBusinesses
                                              , listaReviews
                                              , listaUsers);

            GestReviews gest = new GestReviews( listaBusinesses
                                                , listaReviews
                                                , listaUsers);
    
            
            int r = 0;
            while (r < 1) {
            
                r = controller.menu(gest); 

            }
            int instruction=0;
            
            
    }   
    
    
    
    }
    
        
        
        
        