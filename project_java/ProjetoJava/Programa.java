import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;
//import controller.*;
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

public class Programa {

    
    
    public static void main (String[] args ) throws IOException{

        Loadlog log = new Loadlog();

        BusinessList businesses = new BusinessList();
        ReviewList reviews       = new ReviewList();
        UserList users          = new UserList();
        
        log.load(log.getFichDefaut(), businesses, reviews, users);
        GestReviews gest = new GestReviews(businesses, reviews, users);
        //reviews.mostrarReviews();
        // Map<Integer,List<Integer>>map =gest.query4("_bZOUUc6Sr_W3BxbOUJacw");
        // System.out.println( map.toString());
        //gest.consulta9(3,"rQ8NMRJfhTTV77gFoVYHyA",reviews,users);
        //gest.consulta3("djp57omz9cccV1wI0_sqqA",reviews,businesses);
        //gest.estatistica1(reviews, businesses, users);
        gest.consulta10();
        //System.out.println( gest.consulta1().toString());
        //System.out.println( gest.consulta2(4,2014).toString());
       // gest.consulta5(10,"YoVfDbnISlW0f7abNQACIg",reviews);
        
    }



}





