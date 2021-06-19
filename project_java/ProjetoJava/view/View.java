package view;

import model.Businesses.*;
import model.Reviews.*;
import model.Users.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.AbstractMap.SimpleEntry;


public class View {

    /**
     * Método que apresenta o menu principal do programa
     */
    public void  menu(){
        
        StringBuilder sb = new StringBuilder ( );
        sb.append("\n---------------------------------------------------------\n\t\t\t  ");
        sb.append("Menu \n---------------------------------------------------------\n");
        sb.append("0) - Estatisticas \n");
        sb.append("1) - Lista ordenada alfabeticamente com os identificadores dos negócios nunca avaliados e o seu respetivo total;\n");
        sb.append("2) - Dado um mês e um ano (válidos), determinar o número total global de reviews realizadas e o número total de users distintos que as realizaram;\n");
        sb.append("3) - Dado um código de utilizador, determinar, para cada mês, quantas reviews fez,quantos negócios distintos avaliou e que nota média atribuiu;\n");
        sb.append("4) - Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado,por quantos users diferentes e a média de classificação;\n");
        sb.append("5) - Dado o código de um utilizador determinar a lista de nomes de negócios que mais avaliou (e quantos), ordenada por ordem decrescente de quantidade e, paraquantidades iguais, por ordem alfabética dos negócios;\n");
        sb.append("6) - Determinar o conjunto dos X negócios mais avaliados (com mais reviews) em cada ano, indicando o número total de distintos utilizadores que o avaliaram (X é uminteiro dado pelo utilizador);\n");
        sb.append("7) - Determinar, para cada cidade, a lista dos três mais famosos negócios em termos de número de reviews;\n");
        sb.append("8) - Determinar os códigos dos X utilizadores (sendo X dado pelo utilizador) que avaliaram mais negócios diferentes, indicando quantos, sendo o critério deordenação a ordem decrescente do número de negócios\n");
        sb.append("9) - Dado o código de um negócio, determinar o conjunto dos X users que mais o avaliaram e, para cada um, qual o valor médio de classificação (ordenação cf. 5)n\n");

        System.out.print(sb.toString());
         
    }

    /**
     * Método que apresenta o menu das estatísticas
     */
    public void menuEstatisticas () {
        StringBuilder sb = new StringBuilder ( );
        sb.append("Estatisticas que pretende consultar:\n");
        sb.append("ESTATISCAS 1)\n  -número total de registos de reviews errados\n");
        sb.append("  -número total de negócios\n");
        sb.append("  -total de diferentes negócios avaliados (nº reviews > 0)\n");
        sb.append("  -número total de negócios não avaliados\n");
        sb.append("  -número total de users \n");
        sb.append("  -numero total de users que realizaram reviews\n");
        sb.append("  -total de users que nada avaliaram\n");
        sb.append("  -total de users inativos (sem reviews)\n");
        sb.append("  -reviews com 0 impacto (0 valores no somatório de cool, funny ou useful)\n");
        sb.append("ESTATISCAS 2)\n  -Número total de reviews por mês\n");
        sb.append("  -Média de classificação de reviews por mês e o valor global (média global de reviews);\n");
        sb.append("  -Número de distintos utilizadores que avaliaram em cada mês .\n");

        System.out.println(sb.toString());
    }


    /**
     * Método que apresenta no ecrã uma string dada como argumento
     */
    public void print(String string) {
        System.out.println (string);
    }   
    
    /**
     * Método que apresenta no ecrã uma variavel dada como argumento
     */
    public void printVar(String var){
        System.out.println (var + ":");
    }

    /**
     * Método que apresenta no ecrã uma mensagem caso a escolha de uma opção seja errada
     */
    public void printOpErrada() {
        System.out.println ("OPCAO ERRADA, Tente Novamente\n");
    }

    /**
     * Método que limpa o ecrã 
     */
    public void clearScreen(){
       System.out.println("\033[H\033[2J"); 
    }

    /**
     * Método que apresenta no ecrã uma mensagem caso a instrução definida não exista
     */
    public void notAnInstruction(){
        System.out.print("Esta instruçao nao esta definida!\n");
    }

    /**
     * Método que apresenta um prompt para o nível 1
     */
    public void promptNivel1 (){
        System.out.print("\n# > ");
    }

    /**
     * Método que apresenta um prompt para o nível 2
     */
    public void promptNivel2 (){
        System.out.print("\n# >> ");
    }
 
    /**
     * Método que apresenta um prompt para o nível 3
     */
    public void promptNivel3 (){
        System.out.print("\n# >>> ");
    }

    /**
     * Método que apresenta no ecrã uma mensagem para informar o utilzador que deve fazer press Enter
     */
    public void pressEnter() {
        System.out.println("Press Enter to Continue");
    }

    /**
     * Método que apresenta no ecrã uma mensagem a pedir o nome do ficheiro que o utilizador pretender 
    */
    public void fichQueQuer() {
        System.out.println("Nome do ficheiro que pretende\n");
    }
    public void espera() {
        
    }
    public void consulta1(SimpleEntry<Integer, Set<String>> n) {
        
        StringBuilder sb = new StringBuilder();

        sb.append("Consulta 1:\n");
        sb.append("    Numero Total de Business:").append(n.getKey());
        
        for (String s : n.getValue()) {
            sb.append("    Business:").append(s).append("\n");         
        }
        System.out.println(sb.toString());
    }

    public void consulta2(SimpleEntry<Integer, Integer> r) {

        StringBuilder sb = new StringBuilder();

        sb.append("Consulta 2:\n");
        sb.append("    Numero Total de Reviews:").append(r.getKey()).append("\n");
        sb.append("    Numero de Users Distintos:").append(r.getValue()).append("\n");
        
        System.out.println(sb.toString());
    }

    public void pedeMes() {
        System.out.print("Insira o Mes que pretende consultar: ");
    }

    public void pedeAno() {
        System.out.print("Insira o Ano que pretende consultar: ");
    }

    public void pedeUser() {
        System.out.print("Insira o UserId que pretende consultar: ");
    }

    public void executando() {
        System.out.println("Processing...\n ! Please Wait !");
    }

    public void pedeBusinessID() {
        System.out.print("Insira o BusinessId que pretende consultar: ");
    }
    
    public void consulta3(float[] stars,int[] revMes, int[] busMes){

        StringBuilder sb =  new StringBuilder();
        for(int i=0; i < 12; i++){
            int nmes = i + 1;
            sb.append("  Mes:" + nmes).append("\n");
            sb.append("    Número de reviews: " + revMes[i] );
            sb.append(" , Número de negócios avaliados: " + busMes[i] ); 
            sb.append(" , Nota média: " + stars[i]/revMes[i]).append("\n");
    
        }
    
        System.out.println(sb.toString());
    }

    public void consulta4(Map<Integer, List<Integer>> map) {
        StringBuilder sb =  new StringBuilder();
        
        for(Map.Entry<Integer, List<Integer>> entry : map.entrySet()){
           // int nmes = i + 1;
            sb.append("  Mes:" + entry.getKey()).append("\n");
            sb.append("    Número de reviews: "           + entry.getValue().get(0) );
            sb.append(" , Número de negócios avaliados: " + entry.getValue().get(1) ); 
            sb.append(" , Nota média: "                   + entry.getValue().get(2)).append("\n");
    
        }
        System.out.println(sb.toString());
    }

    

    public void consulta5(Map<String,Integer> ordenados, String user_id) {

        StringBuilder sb =  new StringBuilder();
        
        sb.append("User Id - ").append(user_id).append("\n");

        int posicao = 1;
        for(Map.Entry<String,Integer> bus: ordenados.entrySet()){
            sb.append("  ").append(posicao).append("º Business (que avaliou ");
            sb.append(bus.getValue()).append(" vezes): ").append(bus.getKey()).append("\n");
            posicao++;
        }
       System.out.println(sb.toString());
    }

    public void consulta7(Map<String, List<SimpleEntry<Business, Integer>>> cidades) {


        for (Map.Entry<String, List<SimpleEntry<Business,Integer>>> entry : cidades.entrySet()) {

            StringBuilder sb =  new StringBuilder();
            sb.append("Cidade - ").append(entry.getKey()).append("\n");

            int posicao = 1;
            for (SimpleEntry<Business,Integer> bus : entry.getValue()) {
                sb.append("  ").append(posicao).append("º Business Id (com ").append(bus.getValue()).append(" reviews): ").append(bus.getKey().getBusinessId()).append(bus.getValue()).append("\n");
                posicao++;
            }

            System.out.println(sb.toString());
        }  

    }

    public void consulta9(String business_id,Map<String, List<Review>> ordenados) {
       
        StringBuilder sb =  new StringBuilder();
        sb.append("Business Id: ").append(business_id).append("\n");

        int posicao = 1;
        for(Map.Entry<String, List<Review>> user: ordenados.entrySet()){
      
            float classificacao = 0;
            for(Review rev: user.getValue()){
                classificacao += rev.getStars();
            }
            float media = classificacao / user.getValue().size();

            sb.append("  ").append(posicao).append("º User Id : ")
                           .append(user.getKey()).append("\n")
                           .append("\tNumero de reviews: ").append(user.getValue().size()).append("\n");
            sb.append("\tClassificação média do négocio: ").append(media).append("\n\n");
            posicao++;
        }
        System.out.println(sb.toString());
    }

    public void consulta10( Map<String,List<String>>state ,
                            Map<String,List<Business>> cidades ,
                            Map<String,SimpleEntry< Float,Integer>> busMedia ) {
                
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<String,List<String>> entry : state.entrySet()) {

            sb.append("State: ").append(entry.getKey()).append("\n");
            for (String s : entry.getValue()) {
                List<Business> bs = cidades.get(s);
                sb.append("\tCity: ").append(s).append("\n");
                for (Business business : bs) {
                    SimpleEntry<Float,Integer> m;
                    if(busMedia.containsKey(business.getBusinessId())) {
                        m = busMedia.get(business.getBusinessId());
                    }else {
                        m =  new SimpleEntry<>(0.0f, 1);
                    }
                
                    Float med = m.getKey()/m.getValue();
                    sb.append("\t\tBusiness: ").append(business.getName())
                      .append(" whit Stars: ").append(med).append("\n");
                    
                }
            }
        }
        System.out.println(sb.toString());
        
    }

    

}

    