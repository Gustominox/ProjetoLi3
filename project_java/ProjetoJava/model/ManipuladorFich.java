/**
 * Classe que manipula as fontes de dados (ficheiros de texto) deste projeto.
 *
 * @author grupo 64
 * @version 030621
 */

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
//throws LinhaIncorretaException

public class ManipuladorFich
{
    /**
     * A partir de um contéudo de um ficheiro, este método devolve uma lista de strings em que cada string corresponde a uma linha do ficheiro
     */    
    public static String[] lerFicheiro(String nomeFich) {
        List<String> lines;
        String[] linesArray;
        try { 
            lines = Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8);
            linesArray = lines.toArray(new String[0]);}
        catch(IOException exc) {
            lines = new ArrayList<>();
            linesArray = null;
        }
        return linesArray;
    }
    
    /**public static String[][] parse(String nomeFich){
        List<String> linhas = lerFicheiro(nomeFich);
        for(String s: linhas){
            System.out.println(s);
        }
        String[][] linhaPartida = new String[50][4];
        String[] temp;
        int i=0, j=0;
        
        for(String linha: linhas){
           temp = linha.split(";",3);
           linhaPartida[i]=temp;
           System.out.println(linhaPartida[i] );
            i++;
        }
        
        return linhaPartida;
    }*/   
}
