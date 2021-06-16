
/**
 * Write a description of class Teste here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */

import java.io.IOException;

public class Teste
{
    public static void main(String args[]) throws IOException {
        String path1 = "ProjetoJava/reviews1.csv";
        String path2 = "ProjetoJava/business1.csv";
        String path3 = "ProjetoJava/user1.csv";
        
        String[] infoRev = ManipuladorFich.lerFicheiro(path1);
        String[] infoBus = ManipuladorFich.lerFicheiro(path2);
        String[] infoUser = ManipuladorFich.lerFicheiro(path3);
        
        GestReviews gRev = new GestReviews();
        gRev.principal(infoRev, infoBus, infoUser);
    }
}
