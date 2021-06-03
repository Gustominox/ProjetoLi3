
/**
 * Classe que manipula as fontes de dados (ficheiros de texto) deste projeto.
 *
 * @author grupo 64
 * @version 030621
 */

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class ManipuladorFich
{
    /**
     * Esse método recorre à classe BufferedReader que gerará o buffer que será utilizado para realizar a leitura do arquivo .txt.
     */
    public static void leitor(String path) throws IOException {
        BufferedReader buffRead = new BufferedReader(new FileReader(path));
        String linha = "";
        while (true){
            if (linha != null) {
                System.out.println(linha);

            } else break;
            
            linha = buffRead.readLine();
        }
        buffRead.close();
    }
}
