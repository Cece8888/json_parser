#include "json.hpp"



struct  cella
{
    json info;
    cella* next;
    cella* prev;
    
}; typedef cella* lista; // lista

struct node
{
    std::pair<std::string,json> pair;
    node* next;
    node* prev;
    
}; typedef node* dic; //dizionario

struct json::impl{ 


    lista head_L; //lista
    lista tail_L; // lista
    double numero;
    double bool_check; // serve a dirmi se effettivamente i json è un booelano
    bool boolean;
    std::string s;
    dic head_D; //dizionario
    dic tail_D; //dizionario
    bool check_dic; // check_dic e check_lista controllano se e' una lista o dizionario utile nei casi {} e []
    bool check_lista;

};


    struct json::list_iterator{
        using iterator_category = std::forward_iterator_tag; // sto dichiarado un iterator di tipo forward
        using value_type =  json;
        using pointer =  json*;
        using reference =  json&;

        //metodi pubblici
        list_iterator(lista);    //costruttore (serve a list<Val>::begin e list<Val>::end)

        reference operator*() const;   //resituisce una reference a Val, const perchè non modificherà le variabili private
        pointer operator->() const;    // es: list<std::pait<int,int> l; l += std::pair<int,int> {1,2}; auto it = l.begin(); it->first; ci permette di accedere ai membri di val o ai veri metodi delle nostre struct
        list_iterator& operator++();     //prefix ++it
        list_iterator operator++(int);   //postfix it++
        bool operator==(list_iterator const&) const;   //it1 == it2
        bool operator!=(list_iterator const&) const;
       

        private:

        lista m_ptr; 
    };
    
    struct json::dictionary_iterator{

        using iterator_category = std::forward_iterator_tag; // sto dichiarado un iterator di tipo forward
        using value_type = std::pair<std::string, json>;
        using pointer = std::pair<std::string, json>*;
        using reference = std::pair<std::string, json>&;

        //metodi pubblici
        dictionary_iterator(dic);    //costruttore (serve a list<Val>::begin e list<Val>::end)

        reference operator*() const;   //resituisce una reference a Val, const perchè non modificherà le variabili private
        pointer operator->() const;    // es: list<std::pait<int,int> l; l += std::pair<int,int> {1,2}; auto it = l.begin(); it->first; ci permette di accedere ai membri di val o ai veri metodi delle nostre struct
        dictionary_iterator& operator++();     //prefix ++it
        dictionary_iterator operator++(int);   //postfix it++
        bool operator==(dictionary_iterator const&) const;   //it1 == it2
        bool operator!=(dictionary_iterator const&) const;
       


        private:

        dic m_ptr;

    };
    struct json::const_list_iterator{

        using iterator_category = std::forward_iterator_tag; // sto dichiarado un iterator di tipo forward
        using value_type =  json const;
        using pointer =  json const*;
        using reference =  json const&;

        //metodi pubblici
        const_list_iterator(lista);    //costruttore (serve a list<Val>::begin e list<Val>::end)

        reference operator*() const;   //resituisce una reference a Val, const perchè non modificherà le variabili private
        pointer operator->() const;    // es: list<std::pait<int,int> l; l += std::pair<int,int> {1,2}; auto it = l.begin(); it->first; ci permette di accedere ai membri di val o ai veri metodi delle nostre struct
        const_list_iterator& operator++();     //prefix ++it
        const_list_iterator operator++(int);   //postfix it++
        bool operator==(const_list_iterator const&) const;   //it1 == it2
        bool operator!=(const_list_iterator const&) const;
        

        private:

        lista m_ptr; 

    };
    struct json::const_dictionary_iterator{

        using iterator_category = std::forward_iterator_tag; // sto dichiarado un iterator di tipo forward
        using value_type = std::pair<std::string, json> const;
        using pointer = std::pair<std::string, json>  const*;
        using reference = std::pair<std::string, json>  const&;

        //metodi pubblici
        const_dictionary_iterator(dic);    //costruttore (serve a list<Val>::begin e list<Val>::end)

        reference operator*() const;   //resituisce una reference a Val, const perchè non modificherà le variabili private
        pointer operator->() const;    // es: list<std::pait<int,int> l; l += std::pair<int,int> {1,2}; auto it = l.begin(); it->first; ci permette di accedere ai membri di val o ai veri metodi delle nostre struct
        const_dictionary_iterator& operator++();     //prefix ++it
        const_dictionary_iterator operator++(int);   //postfix it++
        bool operator==(const_dictionary_iterator const&) const;   //it1 == it2
        bool operator!=(const_dictionary_iterator const&) const;
       


        private:

        node* m_ptr; 
    };


   json::json(){

        pimpl = new impl;
         pimpl->boolean = false;
        
        pimpl->bool_check = -1;
        pimpl->numero = std::numeric_limits<double>::quiet_NaN(); //uso la libreria limits, std::numeric_limit<double>::quiet_NaN();
        pimpl->s = "";
     
        pimpl->head_L = nullptr;
        pimpl->tail_L = nullptr;
        

        pimpl->head_D = nullptr;
        pimpl->tail_D = nullptr;
        

        pimpl->check_dic = false;
        pimpl->check_lista = false;

   }
    json::json(json const& p) : json() {
        //copy constructor copio elemento per elemento
    
      
       if(p.pimpl->bool_check != -1){
            pimpl->bool_check = p.pimpl->bool_check;
        }
           
            pimpl->boolean = p.pimpl->boolean;
            
        
         if(p.pimpl->check_dic){
            pimpl->check_dic = p.pimpl->check_dic;
        }
         if(p.pimpl->check_lista){
            pimpl->check_lista = p.pimpl->check_lista;
        }


        if(p.pimpl->numero == p.pimpl->numero){ //controllo che non sia un NaN
            pimpl->numero = p.pimpl->numero;
           
        }

        

        if(!p.pimpl->s.empty()){
            pimpl->s = p.pimpl->s;
            
        }  

        if(p.pimpl->head_D != nullptr){
            
           
            
            while(pimpl->head_D){
                // svuoto il dizionario
                dic tmp = pimpl->head_D;

                pimpl->head_D = pimpl->head_D->next;
                
                delete tmp;
            } 
            pimpl->head_D = nullptr;
            pimpl->tail_D = nullptr;

            dic tmp1 = p.pimpl->head_D;

            while(tmp1){
                //riempio la lista con l'oggetto temporaneo
                insert(tmp1->pair);
                tmp1 = tmp1->next;
            }
            
        }

        if(p.pimpl->head_L != nullptr){
            
           

            while(pimpl->head_L){
                //svuoto la lista
                lista tmp = pimpl->head_L;

                pimpl->head_L = pimpl->head_L->next;

                delete tmp;

            }

            pimpl->head_L = nullptr;
            pimpl->tail_L = nullptr;
            
            lista tmp1 = p.pimpl->head_L;
            while(tmp1){
                push_back(tmp1->info);
                tmp1 = tmp1 -> next;
            }

            


        }

     
    }
        
    json::json(json&& rhs) : json () {

          

        if(rhs.pimpl->head_D != nullptr){

            while(pimpl->head_D){
                //svuoto il dizionario
                dic tmp = pimpl->head_D;

                pimpl->head_D = pimpl->head_D->next;

                delete tmp;

            }

            pimpl->head_D = nullptr;
            pimpl->tail_D = nullptr;
            pimpl->head_D = rhs.pimpl->head_D;
            pimpl->tail_D = rhs.pimpl->head_D;
            rhs.pimpl->head_D = nullptr;
            rhs.pimpl->tail_D = nullptr;
        
          
        } else if(rhs.pimpl->head_L != nullptr){

            while(pimpl->head_L){
                //svuoto la lista
                lista tmp = pimpl->head_L;

                pimpl->head_L = pimpl->head_L->next;

                delete tmp;

            }

            pimpl->head_L = nullptr;
            pimpl->tail_L = nullptr;
            pimpl->head_L = rhs.pimpl->head_L;
            pimpl->tail_L = rhs.pimpl->head_L;
            rhs.pimpl->head_L = nullptr;
            rhs.pimpl->head_L = nullptr;
           
        }


        if(rhs.pimpl->bool_check != -1){
             pimpl->bool_check = pimpl->bool_check;
             pimpl->boolean = pimpl->boolean;
        }
           
           
            
        
         if(rhs.pimpl->check_dic){
            pimpl->check_dic = pimpl->check_dic;
        }
         if(rhs.pimpl->check_lista){
            pimpl->check_lista = pimpl->check_lista;
        }


        if(rhs.pimpl->numero == rhs.pimpl->numero){ //controllo che non sia un NaN
            pimpl->numero = pimpl->numero;
           
        }

        

        if(!rhs.pimpl->s.empty()){
            pimpl->s = pimpl->s;
            
        } 

            *this = std::move(rhs);
        }

    json::~json(){

        
         
        if(pimpl->head_D != nullptr){
            
            while(pimpl->head_D){
               
                dic temp = pimpl->head_D->next;
                delete pimpl->head_D;
                pimpl->head_D = temp;

            }

        
        }
        if(pimpl->head_L != nullptr){
            
            while(pimpl->head_L){
                lista temp = pimpl->head_L->next;
                delete pimpl->head_L;
                pimpl->head_L = temp;
            }
        
        }

        if(pimpl->numero == pimpl->numero || !pimpl->s.empty() || pimpl->boolean == 1){
            set_null();
           
        }
    
     
        delete pimpl;
    }

    json& json::operator=(json const& rhs){
        
        //deep copy
        
         
        if(rhs.pimpl->bool_check != -1){
            pimpl->bool_check = rhs.pimpl->bool_check;
        }
      

         if(rhs.pimpl->check_dic){
            pimpl->check_dic = rhs.pimpl->check_dic;
           
        }
         if(rhs.pimpl->check_lista){
            pimpl->check_lista = rhs.pimpl->check_lista;
            
        }

        if(rhs.pimpl->numero == rhs.pimpl->numero){//controllo che non sia un NaN
           
            
            pimpl->numero = rhs.pimpl->numero;
           
            
           
        }

        

        if(!rhs.pimpl->s.empty()){
            pimpl->s = rhs.pimpl->s;
            return *this;
        }

        if(rhs.pimpl->head_D != nullptr){ 
        if(this != &rhs){ // se non sono lo stesso oggetto

        while(pimpl->head_D){ // svuoto l'oggetto
            dic tmp = pimpl->head_D;
            pimpl->head_D = pimpl->head_D->next;
            delete tmp;
        }
        while(pimpl->head_L){ // svuoto l'oggetto
       
            lista tmp = pimpl->head_L;
            pimpl->head_L = pimpl->head_L->next;
            delete tmp;
        }
        pimpl->head_L = nullptr;
        pimpl->tail_L = nullptr;
        pimpl->head_D = nullptr;
        pimpl->tail_D = nullptr;

        dic temp1 = rhs.pimpl->head_D;
        while(temp1){ // riempio l'oggetto (*this) con l'oggetto temporaneo (rhs)
            insert(temp1->pair);
            temp1 = temp1->next;
        }
       

        } 
            return *this;
        }

        if(rhs.pimpl->head_L != nullptr){ 
        if(this != &rhs){ // se non sono lo stesso oggetto

        while(pimpl->head_L){ // svuoto l'oggetto
            lista tmp = pimpl->head_L;
            pimpl->head_L = pimpl->head_L->next;
            delete tmp;
        }

        pimpl->head_L = nullptr;
        pimpl->tail_L = nullptr;

        lista temp1 = rhs.pimpl->head_L;
        while(temp1){ // riempio l'oggetto (*this) con l'oggetto temporaneo (rhs)
            push_back(temp1->info);
            temp1 = temp1->next;
        }

        } 


        return *this;
        }

        
       
            pimpl->boolean = rhs.pimpl->boolean;
            
        

    return *this;
    }
    json& json::operator=(json&& rhs){

        
       

        if(rhs.pimpl->bool_check != -1){
            pimpl->bool_check = rhs.pimpl->bool_check;
        }

        pimpl->boolean = rhs.pimpl->boolean;
            
        if(rhs.pimpl->check_dic){
            pimpl->check_dic = rhs.pimpl->check_dic;
        }
         if(rhs.pimpl->check_lista){
            pimpl->check_lista = rhs.pimpl->check_lista;
        }

        if(rhs.pimpl->numero == rhs.pimpl->numero){ // se non e' un valore NaN
           
            pimpl->numero = rhs.pimpl->numero;
            
        }

       

        if(!rhs.pimpl->s.empty()){
            pimpl->s = rhs.pimpl->s;
            
        }

        if(rhs.pimpl->head_D != nullptr){ 
        if(this != &rhs){ // se non sono lo stesso oggetto

        while(pimpl->head_D){ // svuoto l'oggetto
            dic tmp = pimpl->head_D;
            pimpl->head_D = pimpl->head_D->next;
            delete tmp;
        }

        pimpl->head_D = rhs.pimpl->head_D; // rubo i puntatori dell'oggetto temporaneo
        pimpl->tail_D = rhs.pimpl->tail_D;

        rhs.pimpl->head_D = nullptr; // setto i puntatori dell'oggetto temporaneo a null cosi' il distruttore non crea problemi
        rhs.pimpl->tail_D = nullptr;
        

        } 

        }

        if(rhs.pimpl->head_L != nullptr){ 
        if(this != &rhs){ // se non sono lo stesso oggetto

        while(pimpl->head_L){ // svuoto l'oggetto
            lista tmp = pimpl->head_L;
            pimpl->head_L = pimpl->head_L->next;
            delete tmp;
        }

        pimpl->head_L = rhs.pimpl->head_L; // rubo i puntatori dell'oggetto temporaneo
        pimpl->tail_L = rhs.pimpl->tail_L;

        rhs.pimpl->head_L = nullptr; // setto i puntatori dell'oggetto temporaneo a null cosi' il distruttore non crea problemi
        rhs.pimpl->tail_L = nullptr;
        

        } 

        }
    return *this;
    }

    bool json::is_list() const{

        if(pimpl->check_lista) return true;
        else return false;


    }
    bool json::is_dictionary() const{

        if(pimpl->check_dic) return true;
        else return false;
    }
    bool json::is_string() const{
        if(!pimpl->s.empty()) return true;
        else return false;
    }
    bool json::is_number() const{
        
        if(pimpl->numero != pimpl->numero) return false; // i numeri nan sono gli unici numeri a non essere uguali a loro stessi!
        else return true;
    }
    bool json::is_bool() const{
        if(pimpl->bool_check != -1) return true;
        else return false;
    }
    bool json::is_null() const{
       if(pimpl->numero != pimpl->numero && pimpl->bool_check == -1 && pimpl->check_dic == false && pimpl->check_lista == false && pimpl->s.empty()) return true;
       else return false;
    }

    json const& json::operator[](std::string const& a) const{ // non modifica il contenuto!, funziona solo con i dizionari


    if(is_dictionary()){
        if(pimpl->head_D == nullptr) throw json_exception{"non posso modificare il dizionario"};
        else {
            dic p = pimpl->head_D;
            bool stop = false;
            while(p && !stop){

                if(p->pair.first == a){
                    stop = true;
                } else p = p->next;

            }

            if(!stop || p == nullptr){
               throw json_exception{"non posso modificare il dizionario"};
            } else {

                return p->pair.second;

            }
        }
    } else throw json_exception{"non e' un dizionario"};


    }
    json& json::operator[](std::string const& a){ // funziona con i dizionari
    
    std::pair<std::string,json> tmp1;

    if(is_dictionary()){
        if(pimpl->head_D == nullptr){ // nel caso del dizionario [] funziona
            
            //nel caso il nostro dizionario sia vuoto

            json tmp;  //tmp è un json nullo
            tmp.set_null();
            tmp1.first = a;
            tmp1.second = tmp;
            insert(tmp1);
            
            return pimpl->tail_D->pair.second;

        } else {
            //nel caso ci siano degli elementi nel nostro dizionario inizio a cercare la nostra chiave
            dic p = pimpl->head_D;
            bool stop = false;
            while(p && !stop){

                if(p->pair.first == a){
                    stop = true;
                } else p = p->next; //sposto il mio puntatore finchè non trovo la mia chiave

            }
        //se non trovo la chiave allora faccio un append con la nuova chiave e un json null
            if(!stop || p == nullptr){
                json tmp;
                tmp.set_null();
                tmp1.first = a;
                tmp1.second = tmp;
                insert(tmp1);
                return pimpl->tail_D->pair.second; // ritorno l'ultimo elemento
            } else {

                return p->pair.second;

            }

        }
    } else throw json_exception{"non e' un dizionario"};

    }

    double& json::get_number(){
        

        if(is_number()) return pimpl->numero;
        else throw json_exception{"non e' un numero"};
        
    }
    double const& json::get_number() const{
        

        if(is_number()) return pimpl->numero;
        else throw json_exception{"non e' un numero"};
    }

    bool& json::get_bool(){
        
        if(pimpl->bool_check != -1) return pimpl->boolean;
        else throw json_exception{"non e' un booleano"};
        
    }
    bool const& json::get_bool() const{
        if(pimpl->bool_check != -1) return pimpl->boolean;
        else throw json_exception{"non e' un booleano"};
    }

    std::string& json::get_string(){
        if(is_string()) return pimpl->s;
        else throw json_exception{"non e' una stringa"};
        
    }
    std::string const& json::get_string() const{
         if(is_string()) return pimpl->s;
        else throw json_exception{"non e' una stringa"};
    }

    void json::set_string(std::string const& a){

        //elimina il json corrente, e setta a null tutte le parti private
        set_null();
        pimpl->s = a;

       
    }
    void json::set_bool(bool b){

         //elimina il json corrente, e setta a null tutte le parti private
        set_null();
        pimpl->bool_check = b;
        pimpl->boolean = b;
    
        
    }
    void json::set_number(double a){
        set_null();
        pimpl->numero = a;

       
    }
    void json::set_null(){

        pimpl->boolean = false;
        
        pimpl->bool_check = -1;
        pimpl->numero = std::numeric_limits<double>::quiet_NaN(); //uso la libreria limits, std::numeric_limit<double>::quiet_NaN();
        pimpl->s = "";
       
         
       if(pimpl->check_lista){ //se ci sono degli elementi rimasti li elimino tutti 
           while(pimpl->head_L != nullptr){
              lista temp = pimpl->head_L->next;
                delete pimpl->head_L;
                pimpl->head_L = temp;
                
           }
            pimpl->head_L = nullptr;
            pimpl->tail_L = nullptr;
        } else {  
            pimpl->head_L = nullptr;
            pimpl->tail_L = nullptr;
        }
  
        if(pimpl->check_dic){ //se ci sono degli elementi rimasti li elimino tutti 
            while(pimpl->head_D != nullptr){
                
                dic temp = pimpl->head_D->next;
                delete pimpl->head_D;
                pimpl->head_D = temp;

            }
            pimpl->head_D = nullptr;
            pimpl->head_D = nullptr;
        } else { 
            pimpl->head_D = nullptr;
            pimpl->tail_D = nullptr;
        }

        pimpl->check_dic = false;
        pimpl->check_lista = false;
        
    }
    void json::set_list(){
      
        
        set_null();
        pimpl->check_lista = true;
      
    }
    void json::set_dictionary(){
        
        set_null();
        pimpl->check_dic = true;
    }



    void json::push_front(json const& a){ // solo per le lista
        
    //inserisco all'inizio 
    if(is_list()){ 
    lista nuovo = new cella;

    if(pimpl->head_L == nullptr){
        
        nuovo->next = nullptr;
        nuovo->prev = nullptr;
        nuovo->info = a;
        
        pimpl->head_L = nuovo;  
        pimpl->tail_L = nuovo;

        
        

        return;

    } else {

        nuovo->prev = nullptr;
        nuovo->next = pimpl->head_L;
        nuovo->info = a;
        pimpl->head_L->prev = nuovo;
        pimpl->head_L = nuovo;

        return;

    }
    } else throw json_exception{"non e' una lista"};

    }
    void json::push_back(json const& a){ // solo per le liste
      
    //inserisco alla fine
   if(is_list()){ 
    if(pimpl->head_L == nullptr){
        push_front(a);
        return;
    }
   

    lista nuovo = new cella;

    nuovo->next = nullptr;
    nuovo->info = a;
    nuovo->prev = pimpl->tail_L;
    pimpl->tail_L->next = nuovo;
    pimpl->tail_L = nuovo;
    
    return;
   } else throw json_exception{"non e' una lista"};
    }
    void json::insert(std::pair<std::string, json> const& a){ // solo per i dizionari

    if(is_dictionary()){ 
    dic nuovo = new node;

    if(pimpl->head_D == nullptr){
        nuovo->next = nullptr;
        nuovo->prev = nullptr;
        nuovo->pair = a;
        
        pimpl->head_D = nuovo;
        pimpl->tail_D = nuovo;

       

        return;

    } else {
        nuovo->next = nullptr;
        nuovo->prev = pimpl->tail_D;
        nuovo->pair = a;
        pimpl->tail_D->next = nuovo;
        pimpl->tail_D = nuovo;

        return;
    }
    } else throw json_exception{"non e' un dizionario"};

    }



/*
---------------------------------------------------------------------------------------------------------------------------------------------------
                                    IMPLEMENTAZIONE ITERATORE LISTA!
---------------------------------------------------------------------------------------------------------------------------------------------------
*/


json::list_iterator::list_iterator(lista p) : m_ptr(p) {
    //rimpiazzo mptr con la p che gli passo io.
}


//mi permette di fare *it, voglio restituire reference al Val contenuta nella cella puntata da m_ptr
typename json::list_iterator::reference //questo è il tipo restituito
json::list_iterator::operator*() const{

    return m_ptr->info;

}


//Devo restituire un puntatore al Val contenuto nella cella, lo usiamo solo quando il tipo val è strutturato
typename json::list_iterator::pointer //questo è il tipo restituito
json::list_iterator::operator->() const{

    return &(m_ptr->info);
}


//prefix increment ++it, incrementa it (cella successiva), e restituisci it.
typename json::list_iterator&
json::list_iterator::operator++(){

    m_ptr = m_ptr->next;
    return *this;
}


//postfix increment it++, restituisci it e poi incrementalo
typename json::list_iterator
json::list_iterator::operator++(int){

    list_iterator it = {m_ptr};  //costruisco una copia del mio puntatore con il mio costruttore
    ++(*this);
    return it; //restituisce l'oggetto prima di essere implementato 

}




bool json::list_iterator::operator==(list_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs puntano alla stessa area di memoria dentto il container

    return m_ptr == rhs.m_ptr;
}


bool json::list_iterator::operator!=(list_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs non puntano alla stessa area di memoria dentto il container

    return m_ptr != rhs.m_ptr;
}



typename json::list_iterator
json::begin_list(){ //posso modificare il contenuto sull'elemento puntato, quindi non è const
    //restituisco un nuovo iterator alla prima cella della lista
    if(!is_list()) throw json_exception{"non e' una lista"};
    else return {pimpl->head_L}; //chiamo il costruttore dell'iteratore
}


typename json::list_iterator
json::end_list(){
    //restituisco un nuovo iterator nullptr
    if(!is_list()) throw json_exception{"non e' una lista"};
    else return {nullptr}; //chiamo il costruttore dell'iteratore
}


/*
---------------------------------------------------------------------------------------------------------------------------------------------------
                                    IMPLEMENTAZIONE ITERATORE CONST LISTA
---------------------------------------------------------------------------------------------------------------------------------------------------
*/




json::const_list_iterator::const_list_iterator(lista p) : m_ptr(p) {
    //rimpiazzo mptr con la p che gli passo io.
}


//mi permette di fare *it, voglio restituire reference al Val contenuta nella cella puntata da m_ptr
typename json::const_list_iterator::reference //questo è il tipo restituito
json::const_list_iterator::operator*() const{

    return m_ptr->info;

}


//Devo restituire un puntatore al Val contenuto nella cella, lo usiamo solo quando il tipo val è strutturato
typename json::const_list_iterator::pointer //questo è il tipo restituito
json::const_list_iterator::operator->() const{

    return &(m_ptr->info);
}


//prefix increment ++it, incrementa it (cella successiva), e restituisci it.
typename json::const_list_iterator&
json::const_list_iterator::operator++(){

    m_ptr = m_ptr ->next;
    return *this;
}


//postfix increment it++, restituisci it e poi incrementalo
typename json::const_list_iterator
json::const_list_iterator::operator++(int){

    const_list_iterator it = {m_ptr};  //costruisco una copia del mio puntatore con il mio costruttore
    ++(*this);
    return it; //restituisce l'oggetto prima di essere implementato 

}




bool json::const_list_iterator::operator==(const_list_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs puntano alla stessa area di memoria dentto il container

    return m_ptr == rhs.m_ptr;
}


bool json::const_list_iterator::operator!=(const_list_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs non puntano alla stessa area di memoria dentto il container

    return m_ptr != rhs.m_ptr;
}



typename json::const_list_iterator
json::begin_list() const{ //posso modificare il contenuto sull'elemento puntato, quindi non è const
    //restituisco un nuovo iterator alla prima cella della lista
    if(!is_list()) throw json_exception{"non e' una lista"};
    else return const_list_iterator(pimpl->head_L); //chiamo il costruttore dell'iteratore
}


typename json::const_list_iterator
json::end_list() const{
    //restituisco un nuovo iterator nullptr
    if(!is_list()) throw json_exception{"non e' una lista"};
    else return const_list_iterator(nullptr); //chiamo il costruttore dell'iteratore
}



/*
---------------------------------------------------------------------------------------------------------------------------------------------------
                                    IMPLEMENTAZIONE ITERATORE DIZIONARIO
---------------------------------------------------------------------------------------------------------------------------------------------------
*/

json::dictionary_iterator::dictionary_iterator(dic p) : m_ptr(p) {
    //rimpiazzo mptr con la p che gli passo io.
    
}


//mi permette di fare *it, voglio restituire reference al Val contenuta nella cella puntata da m_ptr
typename json::dictionary_iterator::reference //questo è il tipo restituito
json::dictionary_iterator::operator*() const{

    return m_ptr->pair;

}


//Devo restituire un puntatore al Val contenuto nella cella, lo usiamo solo quando il tipo val è strutturato
typename json::dictionary_iterator::pointer //questo è il tipo restituito
json::dictionary_iterator::operator->() const{

    return &(m_ptr->pair);
}


//prefix increment ++it, incrementa it (cella successiva), e restituisci it.
typename json::dictionary_iterator&
json::dictionary_iterator::operator++(){

    m_ptr = m_ptr->next;
    return *this;
}


//postfix increment it++, restituisci it e poi incrementalo
typename json::dictionary_iterator
json::dictionary_iterator::operator++(int){

    dictionary_iterator it = {m_ptr};  //costruisco una copia del mio puntatore con il mio costruttore
    ++(*this);
    return it; //restituisce l'oggetto prima di essere implementato 

}




bool json::dictionary_iterator::operator==(dictionary_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs puntano alla stessa area di memoria dentro il container

    return m_ptr == rhs.m_ptr;
}


bool json::dictionary_iterator::operator!=(dictionary_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs non puntano alla stessa area di memoria dentro il container

    return m_ptr != rhs.m_ptr;
}



typename json::dictionary_iterator
json::begin_dictionary(){ //posso modificare il contenuto sull'elemento puntato, quindi non è const
    //restituisco un nuovo iterator alla prima cella della lista
    if(!is_dictionary()) throw json_exception{"non e' un dizionario"};
    else return {pimpl->head_D}; //chiamo il costruttore dell'iteratore
}


typename json::dictionary_iterator
json::end_dictionary(){
    //restituisco un nuovo iterator nullptr
    if(!is_dictionary()) throw json_exception{"non e' un dizionario"};
    else return {nullptr}; //chiamo il costruttore dell'iteratore
}

/*
---------------------------------------------------------------------------------------------------------------------------------------------------
                                    IMPLEMENTAZIONE ITERATORI CONST DIZIONARI
---------------------------------------------------------------------------------------------------------------------------------------------------
*/


json::const_dictionary_iterator::const_dictionary_iterator(dic p) : m_ptr(p) {
    //rimpiazzo mptr con la p che gli passo io.
}


//mi permette di fare *it, voglio restituire reference al Val contenuta nella cella puntata da m_ptr
typename json::const_dictionary_iterator::reference //questo è il tipo restituito
json::const_dictionary_iterator::operator*() const{

    return m_ptr->pair;

}


//Devo restituire un puntatore al Val contenuto nella cella, lo usiamo solo quando il tipo val è strutturato
typename json::const_dictionary_iterator::pointer //questo è il tipo restituito
json::const_dictionary_iterator::operator->() const{

    return &(m_ptr->pair);
}


//prefix increment ++it, incrementa it (cella successiva), e restituisci it.
typename json::const_dictionary_iterator&
json::const_dictionary_iterator::operator++(){

    m_ptr = m_ptr ->next;
    return *this;
}


//postfix increment it++, restituisci it e poi incrementalo
typename json::const_dictionary_iterator
json::const_dictionary_iterator::operator++(int){

    const_dictionary_iterator it = {m_ptr};  //costruisco una copia del mio puntatore con il mio costruttore
    ++(*this);
    return it; //restituisce l'oggetto prima di essere implementato 

}




bool json::const_dictionary_iterator::operator==(const_dictionary_iterator const& rhs) const{

    return m_ptr == rhs.m_ptr;
}


bool json::const_dictionary_iterator::operator!=(const_dictionary_iterator const& rhs) const{
    //it1 == rhs dobbiamo controllare se it1 e rhs non puntano alla stessa area di memoria dentto il container

    return m_ptr != rhs.m_ptr;
}



typename json::const_dictionary_iterator
json::begin_dictionary() const{ //posso modificare il contenuto sull'elemento puntato, quindi non è const
    //restituisco un nuovo iterator alla prima cella della lista
    if(!is_dictionary()) throw json_exception{"non e' un dizionario"};
    else return {pimpl->head_D}; //chiamo il costruttore dell'iteratore
}


typename json::const_dictionary_iterator
json::end_dictionary() const{
    //restituisco un nuovo iterator nullptr
    if(!is_dictionary()) throw json_exception{"non e' un dizionario"};
    else return {nullptr}; //chiamo il costruttore dell'iteratore
}


/*
---------------------------------------------------------------------------------------------------------------------------------------------------
                                    IMPLEMENTAZIONE GRAMMATICA
---------------------------------------------------------------------------------------------------------------------------------------------------
*/

//SETTO LA LISTA
void A(std::istream& lhs, json& rhs){

    char c = ' ';
    json tmp;
    lhs >> c;
    if(c == ']') return; // nel caso scrivessi [] esco subito
    else lhs.putback(c); // ributto dentro il primo carattere
    lhs >> tmp;
    rhs.push_back(tmp);

    
    lhs >> c; // laggo la virgola o la parentesi chiusa
    if(c != ',' && c != ']') throw json_exception{"lista scritta incorrettamente"};
    if(c == ',') A(lhs,rhs);
    else return;
    
   
}

//SETTO IL DIZIONARIO
void B(std::istream& lhs, json& rhs){
   
   std::pair<std::string, json> tmp;
   
        char c = ' ';
        std::string s;
        bool continua = true;


        lhs >> c; //leggo " oppure '}'
        if(c != '"' && c != '}') throw json_exception{"dizionario scritto incorrettamente"};


        if(c == '}') return;

        while(continua){ 
       
        std::string line; //stringa temporanea
        getline(lhs,line,'"'); //leggo la stringa fino alla prima "
        s += line;  //aggiungo la stringa temporanea alla stringa principale
        if(line.back() != '\\'){ //se l'ultimo elemento e' '/' allora continuo a leggere lo stream
            
            continua = false;
           
        }
        if(continua) s += '"'; //aggiungo le virgolette solo nel caso ci sia \"

        }
        tmp.first += s; 
        lhs >> c; //leggo :
       
        if(c != ':') throw json_exception{"dizionario scritto non correttamente, [':' mancante]"};
        
        lhs >> tmp.second;  //leggo il secondo json
  

        rhs.insert(tmp);
        lhs >> c; //leggo se inseriamo una virgola ',' o una parentesi graffa chiusa '}'
        if(c != ',' && c != '}') throw json_exception{"dizionario scritto incorettamente"}; 
        if(c == ',') B(lhs,rhs);
        else return;
 }

void C(std::istream& lhs, json& rhs){

    std::string s;
     
        bool continua = true;

        
        while(continua){ 
        
        std::string line;
        getline(lhs,line,'"'); //la funzione getline mi prende tutta la stringa fino all'ultima ", es: "pippo
        s += line;
        if(line.back() != '\\'){ //nel caso non ci fosse \ ossia (\"), esco dal while, senno ricomincio a scrivere dentro line
            
            continua = false;
           
        }
        if(continua) s += '"'; // alla fine di tutto aggiungo "

        }
        
        rhs.set_string(s);
}

void D(std::istream& lhs, json& rhs, char& c){

        std::string temp;
        std::string check1 = "true";
        std::string check2 = "false";
        int i = 1;
        temp += c;          // aggiungo la 't' o la 'f'
       
        if(c == 't'){
            
            while(temp != "true"){
                lhs >> c;
                if(c != check1[i]) throw json_exception{"e' stato scritto un booleano non corretto ['true' scritto sbagliato] "}; //controllo che non stia scrivendo qualcosa di diverso da true
                temp += c;
                
                i++;
            }
        } else {
       
        while((temp != "false")){ 
            
        lhs >> c; //continuo la scrittura di "rue" o "alse"
        if(c != check2[i]) throw json_exception{"e' statto scritto un booleano non corretto ['false' scritto sbagliato]"}; // controllo che non stia scrivendo qualcosa di diverso da false

        temp += c;
        i++;
        
        }
        }
        

        if(temp != "true" && temp != "false") throw json_exception{"booleano incorretto"};

        if(temp == "true") rhs.set_bool(1);
        if(temp == "false") rhs.set_bool(0); 
    

}

void E(std::istream& lhs, json& rhs){
        char c;
        std::string temp;
        std::string check = "null";
        int i = 1;
        temp += 'n';
        
        while(temp != "null"){
            lhs >> c;
            if(c != check[i]) throw json_exception{"parser non corretto"};
            temp += c;
           
            i++;
        }

        if(temp == "null") rhs.set_null();
        else throw json_exception{"parser non corretto"};

}

std::istream& operator>>(std::istream& lhs, json& rhs){
    char c = 0;
    lhs >> c;
   
    if(c == '{'){
       rhs.set_dictionary();
       B(lhs,rhs);
       return lhs;
    }  
    if(c == '['){
        
        rhs.set_list();
        A(lhs,rhs);
        return lhs;
    } 
     if(c == '"'){
        
        C(lhs,rhs);
        return lhs;
    } 
     if(c == 't' || c == 'f'){
        
        D(lhs,rhs,c);
        return lhs;
    } 
     if((c <= '9' && c >= '0') || c == '.' || c == '-'){ // il punto serve per i casi in cui inzio a scrivere .123 -> 0.123
        
        double numero = 0;

            
        
            lhs.putback(c);
            lhs >> numero;
           
           rhs.set_number(numero);
      return lhs;
        

    } 
     if(c == 'n'){
        E(lhs,rhs);
        return lhs;
    } 
    else {
        
        throw json_exception{"parser non corretto"};
    }

    
    return lhs;
   
    

}

std::ostream& operator<<(std::ostream& lhs, json const& rhs){
    
   //controllo che sia effettivante un valore booleano
   if(rhs.is_bool()){ 

    //stampo il bool
    if(rhs.get_bool()){
        lhs << "true";
        
    } else {
        lhs << "false";

    }
    return lhs;
    }

    //stampo il numero
   if(rhs.is_number()){
    lhs << rhs.get_number();
    return lhs;
   } 

   //stampo la stringa
   if(rhs.is_string()){ 
   std::string temp = rhs.get_string();
   if(temp.size() != 0){
    lhs << "\"" << rhs.get_string() << "\"";
    return lhs;
   } 
   }
   

    
  
    //stampo il dizionario
    if(rhs.is_dictionary()){ 
    auto it = rhs.begin_dictionary();
    lhs <<"{";
    if(it == nullptr) lhs << "}"; //se la lista fosse vuota stampo solo {}
    else { 
    
    lhs << std::endl;

    while(it != rhs.end_dictionary()){
        
       
        lhs << "   "; 
        lhs<<"\""<<it->first<<"\"";
        lhs <<" : ";
      lhs<<it->second;

        *++it;
        if(it != rhs.end_dictionary()) lhs << ",";
        
        lhs <<std::endl;
    }
    
    
    lhs <<"}";
    lhs << std::endl;
    }
    return lhs;
    }

   
   //stampo la lista
    if(rhs.is_list()){
       json::const_list_iterator it3 = rhs.begin_list();
        lhs << "[";
        if(it3 == nullptr) lhs << "]";
        else { 

        while(it3 != rhs.end_list()){
           lhs << " " << *it3;
            *++it3;
            if(it3 != rhs.end_list()) lhs << " ,";
            
        }
        lhs << " ]";
        }
        return lhs;
        
    }
    
    lhs << "null"; // se il json non è nessuno di questi è null

    return lhs;
    
}






int main(){


	json a;
	std::cin >> a;
	

	std::cout<<a;

return 0;
}
