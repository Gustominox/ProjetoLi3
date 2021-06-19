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
import java.util.Set;
import java.util.AbstractMap.SimpleEntry;

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
    
            
            int instruction = 0;
            while (instruction != -1) {
                
                view.clearScreen();
                view.menu();
                view.promptNivel1();
                
                try{
                    instruction = scan.nextInt();
                    scan.nextLine();
                        
                }
                catch (InputMismatchException e) {
                    
                    view.notAnInstruction();
                    instruction = -1;
                }
        
                
                view.clearScreen();
                
                switch(instruction){
                    
                    case 0 :
                        view.menuEstatisticas();
                        view.promptNivel2();
                        int j = scan.nextInt();
                        scan.nextLine();
                        view.clearScreen();
                        if(j == 1) gest.estatistica1();
                        else if(j == 2) gest.estatistica2();
                        else view.notAnInstruction();
                        view.pressEnter();
                        scan.nextLine();

                        break; 
                    case 1 :
                        SimpleEntry <Integer,Set<String>> n; 
                        n = gest.consulta1();
                        view.consulta1(n);
                        view.pressEnter();
                        scan.nextLine(); 
                        break;
        
                    case 2: 
                        view.pedeMes();    
                        int mes = scan.nextInt();
                        scan.nextLine();
                        view.pedeAno();
                        int ano = scan.nextInt();
                        scan.nextLine();
                            
                        SimpleEntry <Integer,Integer> ret;
                        ret = gest.consulta2 (mes,ano);
                        view.consulta2(ret);
                        view.pressEnter();
                        scan.nextLine();
                        
                        break;
                        
                    case 3: 

                        float[] stars = new float[12];
                        int[] revMes = new int[12];
                        int[] busMes = new int[12];
                        view.pedeUser();
                        String user3 = scan.nextLine();
                        gest.consulta3(user3,stars,revMes,busMes);
                        view.consulta3(stars,revMes,busMes);
                        view.pressEnter();
                        scan.nextLine();
                        break;
                    
                    case 4 : 
                        view.pedeBusinessID();    
                        String businessID = scan.nextLine();
                        
                        Map<Integer, List<Integer>> map = gest.consulta4(businessID);
                        view.consulta4(map);
                        view.pressEnter();
                        scan.nextLine();
                        
                        break;
                        
                    case 5: 
                        view.pedeUser();
                        String user = scan.nextLine();
                        Map<String, Integer> map1 = gest.consulta5(user);
                        view.consulta5(map1,user);
                        view.pressEnter();
                        scan.nextLine();
                        //YoVfDbnISlW0f7abNQACIg
                        break;
        

                    case 6 : 
                        //view.q7(gest.query7());
                        break; 
                            
                    case 7 : 
                        //view.q7(gest.query7());
                        Map<String, List<SimpleEntry<Business,Integer>>>  map2 = gest.consulta7();
                        view.consulta7(map2);
                        view.pressEnter();
                        scan.nextLine();
                        break; 
                            
                    case 8: 
                        int nUsers = scan.nextInt();
                        scan.nextLine();
                        //view.q8(nUsers,gest.query8(nUsers));
                        break;   
        
                    case 9: 

                        view.pedeBusinessID();    
                        String businessID1 = scan.nextLine();
                        
                        Map<String, List<Review>> ordenados = gest.consulta9(10,businessID1);//RuvuXYEz_fhJZVNXjC7kzw
                        view.consulta9(businessID1,ordenados);
                        view.pressEnter();
                        scan.nextLine();
                        
                        break;
                    case 10:

                        view.executando();
                        Map<String,List<String>>state = new HashMap<>();
                        Map<String,List<Business>> cidades = new HashMap<>();

                        Map<String,SimpleEntry< Float,Integer>> busMedia = new HashMap<>();
                        gest.consulta10(state,cidades,busMedia);
                        view.consulta10(state,cidades,busMedia);
                        view.pressEnter();
                        scan.nextLine();
                        break;
                        default : 
                        //view.notAnInstruction();
                       
                        
                        
                }
                
                
                instruction = 0;
            }
            scan.close();
            
    }   
    
    
    
    }
    
        
        
        
        