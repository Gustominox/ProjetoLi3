import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;
import controller.*;
import jdk.internal.net.http.common.Log;
import view.*;
import loaders.*;

import java.io.IOException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner ;

        //gest.consulta5(10,"YoVfDbnISlW0f7abNQACIg");
       
    public class Programa {
    
        
        
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
            int instruction=0;
            int n;
            
            
            while(instruction!=-1){
                view.clearScreen();

                view.menu();
                view.promptNivel1();
                try{
                    instruction = scan.nextInt();
                    scan.nextLine();
                }
                catch (InputMismatchException e) {
                    instruction = -1;
                    view.notAnInstruction();
                }
                view.clearScreen();
            switch (instruction){
            

                case 0:
                view.menuEstatisticas();
                scan.nextLine();

                break;
                case 1:
                break;
                case 2:

                break;
                case 3:

                break;
                case 4:

                break;
                case 5:

                break;
                case 6:
                    gest.consulta6();
                break;
                case 7:

                break;
            
                case 8:
            
                break;
                case 9:
            
                break;
            }
        }   
    }   
    
    
    
    }
    
        
        
        
        