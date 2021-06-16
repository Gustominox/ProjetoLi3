
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
        String path1 = "reviews1.csv";
        String path2 = "business1.csv";
        String path3 = "users1.csv";
        
        String[] infoRev = ManipuladorFich.lerFicheiro(path1);
        String[] infoBus = ManipuladorFich.lerFicheiro(path2);
        String[] infoUser = ManipuladorFich.lerFicheiro(path3);
        
        GestReviews gRev = new GestReviews();
        gRev.query1(infoRev, infoBus, infoUser);
    }
}
