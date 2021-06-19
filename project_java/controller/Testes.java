/**
 * Class que executa testes as consultas
 *
 * @author grupo 64
 * @version (a version number or a date)
 */
package controller;

import java.lang.Runtime;
import java.util.*;
import java.util.AbstractMap.SimpleEntry;

import loaders.Loadlog;
import model.*;
import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;
import view.View;

public class Testes{


     /**
     * Correr os testes
     */
   
    public void runTestes(){
        View view = new View();
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

        long memUsadaAntes = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();


        /************** Estatistica 1 *************/

        System.out.println("Estatística 1:");
    
        Crono.start();
        gest.estatistica1();
        view.clearScreen();
        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /************** Estatistica 2 *************/

        System.out.println("Estatistica 2:");

        Crono.start();
        int[] revPorMes = new int[12];
        float[] claPorMes  = new float[12];  
        int[] nrUserMes = new int[12];

        gest.estatistica2(revPorMes, claPorMes ,nrUserMes);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois1 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual1 = memUsadaDepois1 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual1);
        

        /*************** Consulta 1 ***************/

        System.out.println("Consulta Interativa 1:");
    
        Crono.start();
        gest.consulta1();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois2 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual2 = memUsadaDepois2 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual2);


        /*************** Consulta 2 ***************/

        System.out.println("Consulta Interativa 2:");

        Crono.start();
        gest.consulta2(4, 2014);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois3 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual3 = memUsadaDepois3 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual3);


        /*************** Consulta 3 ***************/

        System.out.println("Consulta Interativa 3:");

        Crono.start();
        float[] stars = new float[12];
        int[] revMes = new int[12];
        int[] busMes = new int[12];
        gest.consulta3("YoVfDbnISlW0f7abNQACIg", stars, revMes, busMes);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois4 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual4 = memUsadaDepois4 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual4);


        /*************** Consulta 4 ***************/

        System.out.println("Consulta Interativa 4:");

        Crono.start();
        gest.consulta4("RuvuXYEz_fhJZVNXjC7kzw"); 

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois5 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual5 = memUsadaDepois5 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual5);


        /*************** Consulta 5 ***************/

        System.out.println("Consulta Interativa 5:");

        Crono.start();
        gest.consulta5("YoVfDbnISlW0f7abNQACIg");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois6 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual6 = memUsadaDepois6 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual6);


        /*************** Consulta 6 ***************/

        System.out.println("Consulta interativa 6:");

        Crono.start();
        gest.consulta6(6);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois7 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual7 = memUsadaDepois7 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual7);

        /*************** Consulta 7 ***************/

        System.out.println("Consulta interativa 7:");

        Crono.start();
        gest.consulta7();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois8 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual8 = memUsadaDepois8 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual8);

        /*************** Consulta 8 ***************/
    
        System.out.println("Consulta interativa 8:");

        Crono.start();
        gest.consulta8(10);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois9 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual9 = memUsadaDepois9 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual9);


        /*************** Consulta 9 ***************/

        System.out.println("Consulta interativa 9:");

        Crono.start();
        gest.consulta9(10,"RuvuXYEz_fhJZVNXjC7kzw");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois10 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual10 = memUsadaDepois10 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual10);


        /*************** Consulta 10 ***************/

        System.out.println("Consulta interativa 10:");

        Crono.start();
        Map<String,List<String>>state = new HashMap<>();
        Map<String,List<Business>> cidades = new HashMap<>(); 
        Map<String,SimpleEntry< Float,Integer>> busMedia = new HashMap<>();
        gest.consulta10(state,cidades,busMedia);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois11 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual11 = memUsadaDepois11 - memUsadaAntes;
        System.out.println("    Memória: " + memAtual11);


    }
}