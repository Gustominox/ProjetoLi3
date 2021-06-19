package controller;

import java.time.DateTimeException;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Set;
import java.util.AbstractMap.SimpleEntry;

import model.*;
import view.*;

public class Controller {


    private String nextLine;




    public void menuEstatisticas(){
        Scanner scan= new Scanner(System.in);
        View view =new View();
        //GestReviews gest = new GestReviews();
        int instruction ;
        try{
            instruction = scan.nextInt();
            scan.nextLine();
       }
       catch (InputMismatchException e) {
           view.notAnInstruction();
       }

    }


 

	public int menu(GestReviews gest){
        Scanner scan= new Scanner(System.in);
        View view =new View();
 
        view.clearScreen();
        view.menu();
        view.promptNivel1();
        int instruction=-1;
        try{
             instruction = scan.nextInt();
             scan.nextLine();
        }
        catch (Exception e) {
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
              else ;
              scan.nextLine();
            case 1 :
                SimpleEntry <Integer,Set<String>> n; 
                n = gest.consulta1();
                view.consulta1(n);
                scan.nextLine(); 
                view.pressEnter();
                break;

            case 2: 
                view.pedeMes();    
                int mes = scan.nextInt();
                scan.nextLine();
                view.pedeAno();
                int ano = scan.nextInt();
                scan.nextLine();
                    
                SimpleEntry <Integer,Integer> r;
                r = gest.consulta2 (mes,ano);
                view.consulta2(r);
                scan.nextLine();
                view.pressEnter();
                break;
                
            case 3: 
                String user3 = scan.nextLine();
                //view.q3(user3,gest.query3(user3));
                break;
            
            case 4 : 
                 String businessID = scan.nextLine();
                 //view.q4( gest.query4(businessID),businessID);
                 break;
                
            case 5: 
                String user =scan.nextLine();
                gest.consulta5(10,"YoVfDbnISlW0f7abNQACIg");
                //view.query5(user,gest.query5(user));
                break;

            case 7 : 
                //view.q7(gest.query7());
                break; 
                    
            case 8: 
                int nUsers = scan.nextInt();
                scan.nextLine();
                //view.q8(nUsers,gest.query8(nUsers));
                break;   

            case 9: 
                gest.consulta9(10,"RuvuXYEz_fhJZVNXjC7kzw");
                break;
            default : 
                //view.notAnInstruction();
                scan.close();
                return -1;
                
        }
        scan.close();
        return 0;
    }
    
}
