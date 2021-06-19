package model.Businesses;


import view.View;

import java.util.List;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.stream.Collectors;

public class BusinessList {
    private List<Business> list ; 
 
    /**
     * Construtor parametrizado
     */
    public BusinessList(List<Business> list) {
        this.list = list;
    }

    /**
     * Construtor por omissão
     */
    public BusinessList (){
        this.list = new ArrayList<>();
    }
 
    /**
    * Método que obtém a lista de negócios.
    * @return lista de negócios
    */
    public List<Business> getList () {
        List<Business> nova =list;
     return nova;
    }

    /**
    * Método que muda a lista de negócios.
    * @param novalist nova lista de negócios
    */
    public void setList(List<Business> novaList){
        this.list = novaList.stream().map(Business::clone).collect(Collectors.toList());
    }
 
    /**
     * Método que devolve o último negócio da lista de negócios.
     *@return último négocio da lista de negócios
     */
    public Business getLast(){
        Business e = list.get(list.size()-1);
        return e;
    }
 
    /**
    * Método que devolve o negócio que se encontra num dado índice
    * @param n índice
    * @return o negócio que se encontra no índice dado
    */
    public Business getBusiness(int n){
     Business e = list.get(n);
     return e;
    }
 
    /**
    * Método que adiciona um dado negócio à lista de negócios.
    * @param business negócio
    */
    public void addBusiness(Business business){
        list.add(business);
    }
 
    /**
     * Método que mostra o negócio dando um índice
     * @param n índice do negócio que pretende ver
     */
    public void consultarBusiness(int n) {
 
         Business e = list.get(n);
         e.toString();
    }
 
    /**
     * Método que devolve o tamanho da lista de negócios.
     * @return tamanho da lista de negócios
     */
    public int size() {
         return list.size();
    }
 
    /**
     * Método que mostra só os nomes de todos os negócios.
     */
    public void mostrarBusinesss(){
        View view = new View();
        StringBuilder sb = new StringBuilder();
        int aux = 0;
        for(Business business : list) {
            aux++;
            sb.append( aux + "-" + business.toString()).append("\n");
        }
        view.print(sb.toString());
 
    }

    /**
     * Método que devolve o negócio dando o nome do negócio.
     * @param nome do negócio  
     * @return o negócio com o nome dado como argumento
     */
    public Business verBusiness( String nome ) {
        View view = new View ();
        Business procura =null;
        try{
            for (Business business : list ){
                if (business.getName().equals(nome)){
                    procura = business;
                }
            }
        }
        catch (InputMismatchException e) {
             view.notAnInstruction();
        }
        return procura;
    }
 
    /**
     * Método que devolve o negócio dando o seu id.
     * @param id do negócio  
     * @return o negócio com o id dado como argumento
     */
    public Business getBusiness(String id) {
        Business procura =null;
        for ( Business business : list){
            if(business.getBusinessId().equals(id)){
                procura = business.clone();
            }
        }
        return procura;
    }
    
    /**
     * Método que devolve a lista de negócios que pertencem ao estado dado como argumento.
     * @param id estado 
     * @return a lista de negócios que pertencem ao estado dado como argumento
     */
    public BusinessList getBusinessEstado(String id) {
        
        BusinessList lista = new BusinessList();
        for (Business business : list){
           if(business.getState().equals(id)){
               lista.addBusiness(business.clone());
           }
        }
        return lista;
    }

     /*
    public Business criaBusiness(String nome ){
        Business newBusiness = new Business();
        nova.setBusiness(nome);
        this.list.add(nova);
        return nova;
    }
    */
 }
 
