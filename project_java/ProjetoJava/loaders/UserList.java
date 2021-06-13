package loaders;

import model.User;
import java.util.List;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;

public class UserList {
    private List<User> list ; 
 
    public UserList (){
        this.list = new ArrayList<>();
    }
 
    public List<User> getList () {
        List<User> nova =list;
     return nova;
    }
 
    public User getLast(){
        User e = list.get(list.size()-1);
        return e;
    }
 
    public User getUser(int n){
     User e = list.get(n);
     return e;
     }
 
     /*
    public User criaUser(String nome ){
        User newUser = new User();
        nova.setUser(nome);
        this.list.add(nova);
        return nova;
    }
 */
    public void addUser(User user){
        list.add(user);
     }
 
     public void consultarUser(int n) {
 
         User e = list.get(n);
         e.toString();
     }
 
     public int size() {
         return list.size();
     }
 
     // so o nome de tds as Users 
     public void mostrarUsers(){
     View view = new View();
     StringBuilder sb = new StringBuilder();
     int aux=0;
     for(User i : list) {
       aux++;
        sb.append( aux + "-" + i.getUser()).append("\n");
     }
     view.print(sb.toString());
 
     }
 
     // consulta a User consoante o nome da msm 
     public User verUser(String nome ) {
         View view = new View ();
         User eq =null;
         try{
         for (User i : list ){
           if (i.getUser().equals(nome)){
              eq= i;
           }
         }
     }
         catch (InputMismatchException e) {
             view.notAnInstruction();
              }
        return eq;
 
     }
 
 
 
     // dado o nome do jogador diz td sobre ele 
     public Jogador consultajogador (String nome) {
         View view = new View ();
         Jogador f = null ;
     try{
     for (User aux :list ){
         for (Jogador i : aux.getJogadores().values()){
              if (i.getNome().equals(nome)){
                   f= i;
                 }
         
             }
         }
     }
     catch (InputMismatchException e) {
        view.notAnInstruction();
         }
     return f ;
     }
 
     public User getUsera(String nomejogador) {
         User i =null;
         for ( User aux :list){
            for (Jogador jog : aux.getJogadores().values()){
                i= verUser(jog.getHistorico().get(0));
            }
         }
         return i;
     }
 
     public void mudaJogador(Jogador jogador , User novUser){
         int i;
         i = getUsera(jogador.getNome()).removerjogador(jogador.getNome());
         if (i>=0){
         novUser.adicionarjogador(jogador, i);
         }
     }
 
 
 }
 
