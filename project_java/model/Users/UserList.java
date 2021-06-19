package model.Users;


import view.View;

import java.util.List;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.stream.Collectors;

public class UserList {
    private List<User> list ; 
 
    /**
     * Construtor por omissão
     */
    public UserList (){
        this.list = new ArrayList<>();
    }
 
    /**
    * Método que obtém a lista de users.
    * @return lista de users
    */
    public List<User> getList () {
        List<User> nova =list;
     return nova;
    }

    /**
    * Método que muda a lista de users.
    * @param novalist nova lista de users
    */
    public void setList(List<User> novaList){
        this.list = novaList.stream().map(User::clone).collect(Collectors.toList());
    }
 
    /**
     * Método que devolve o último user da lista de users.
     * @return último user da lista de users
     */
    public User getLast(){
        User e = list.get(list.size()-1);
        return e;
    }
 
    /**
    * Método que devolve o user que se encontra num dado índice
    * @param n índice
    * @return o user que se encontra no índice dado
    */
    public User getUser(int n){
        User e = list.get(n);
        return e;
    }
 
    /**
    * Método que adiciona um dado user à lista de users.
    * @param user user que pretende adicionar à lista de users
    */
    public void addUser(User user){
        list.add(user);
    }
 
    /**
     * Método que mostra o user dando um índice
     * @param n índice do user que pretende ver
     */
    public void consultarUser(int n) {
        User e = list.get(n);
        e.toString();
    }
 
    /**
     * Método que devolve o tamanho da lista de users.
     * @return tamanho da lista de users
     */
    public int size() {
        return list.size();
    }
 
    /**
    * Método que mostra só os nomes de todos os users.
    */
    public void mostrarUsers(){
        View view = new View();
        StringBuilder sb = new StringBuilder();
        int aux = 0;
        for(User user : list) {
            aux++;
            sb.append( aux + "-" + user.toString()).append("\n");
        }
        view.print(sb.toString());
 
    }
 
    /**
     * Método que devolve o user dando o nome do user.
     * @param nome do user  
     * @return o user com o nome dado como argumento
     */ 
    public User verUser( String nome ) {
        View view = new View ();
        User procura =null;
        try{
            for (User user : list ){
                if (user.getName().equals(nome)){
                    procura = user;
                }
            }
        }
        catch (InputMismatchException e) {
            view.notAnInstruction();
        }
        return procura;
    }
 
    /**
     * Método que devolve o user dando o seu id.
     * @param id do user  
     * @return o user com o id dado como argumento
     */
    public User getUser(String id) {
        User procura =null;
        for ( User user : list){
            if(user.getUserId().equals(id)){
                procura = user;
            }
        }
        return procura;
    }

         /*
    public User criaUser(String nome ){
        User newUser = new User();
        nova.setUser(nome);
        this.list.add(nova);
        return nova;
    }
 */
 }
 
