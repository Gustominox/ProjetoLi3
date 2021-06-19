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


 

}
