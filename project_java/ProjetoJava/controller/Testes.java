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


        /************** Estatística 1 *************/

        System.out.println("Estatística 1:");
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();

        Crono.start();
        gest.estatistica1();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);

        
        /*************** Consulta 1 ***************/

        System.out.println("Consulta Interativa 1:");
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();

        Crono.start();
        gest.consulta1();

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 2 ***************/

        System.out.println("Consulta Interativa 2:");
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();

        Crono.start();
        gest.consulta2(4, 2014);

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 3 ***************/

        System.out.println("Consulta Interativa 3:");
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();

        Crono.start();
        gest.consulta3("YoVfDbnISlW0f7abNQACIg");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 4 ***************/

        System.out.println("Consulta Interativa 4:");
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();

        Crono.start();
        gest.consulta4("RuvuXYEz_fhJZVNXjC7kzw"); 

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);


        /*************** Consulta 5 ***************/

        System.out.println("Consulta Interativa 5:");
        long memUsadaAntes = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();

        Crono.start();
        gest.consulta5(5, "YoVfDbnISlW0f7abNQACIg");

        System.out.println("    Tempo de execução: " + Crono.getTimeAsString());
        long memUsadaDepois = RunTime.getRuntime().totalMenory() - RunTime.getRuntime().freeMemory();
        long memAtual = memUsadaDepois - memUsadaAntes;
        System.out.println("    Memória: " + memAtual);
    }
}