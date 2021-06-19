package controller;

import java.io.*;
import java.lang.*;
import java.time.DateTimeException;
import java.util.*;
import java.util.AbstractMap.SimpleEntry;
import java.util.stream.*;

import model.*;
import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;

public class Testes{

    public void runTestes(){
        GestReviews gestRev = new GestReviews();
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();


        /************** Estatística 1 *************/

        System.out.println("Estatística 1:");
    
        Crono.start();
        gest.estatistica1();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /************** Estatística 2 *************/

        System.out.println("Estatistica 2:");

        Crono.start();
        gest.estatistica2();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);
        

        /*************** Consulta 1 ***************/

        System.out.println("Consulta Interativa 1:");
    
        Crono.start();
        gest.consulta1();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 2 ***************/

        System.out.println("Consulta Interativa 2:");

        Crono.start();
        gest.consulta2(4, 2014);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 3 ***************/

        System.out.println("Consulta Interativa 3:");

        Crono.start();
        gest.consulta3("YoVfDbnISlW0f7abNQACIg");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 4 ***************/

        System.out.println("Consulta Interativa 4:");

        Crono.start();
        gest.consulta4("RuvuXYEz_fhJZVNXjC7kzw"); 

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 5 ***************/

        System.out.println("Consulta Interativa 5:");

        Crono.start();
        gest.consulta5(5, "YoVfDbnISlW0f7abNQACIg");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 6 ***************/

        System.out.println("Consulta interativa 6:");

        Crono.start();
        gest.consulta6(6);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 7 ***************/

        System.out.println("Consulta interativa 7:")

        Crono.start();
        gest.consulta7();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 8 ***************/
    
        System.out.println("Consulta interativa 8:")

        Crono.start();
        gest.consulta8(8);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 9 ***************/

        System.out.println("Consulta interativa 9:")

        Crono.start();
        gest.consulta9(10,"RuvuXYEz_fhJZVNXjC7kzw");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 10 ***************/

        System.out.println("Consulta interativa 10:")

        Crono.start();
        gest.consulta10();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


    }
}