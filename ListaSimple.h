#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAXCIUDAD 30
typedef struct conexion N;
typedef struct City C;
typedef struct guardado G;
struct City
{
    char ciudad[30];//nombre de la ciudad
    C *ant_ciudad;//siguiente ciudad ingresada
    C *sig_ciudad;//ciudad anterior  
    N *lista;//Lista de adyacencias
    int llave;//posicion en la lista
    int cuantos;//cantidad de conexiones
    int band;//Bandera de nodo visitado o no 
    int terminado;//bandera que determina si se llego por lo menos una vez a fin
    int peso;//Variable auxiliar al momento de guardar datos en la pila
};
struct conexion
{
    C *conex;//Apuntador al nodo de ciudad conectora
    int distancia;//distancia entre los nodos conectados   
    N *sig_dato;//siguiente adyacencia
};
struct guardado
{
   char ciudad[30];
   int cuantos;
};
//////////////////////////////////////////////////////////////////////////
void guarda(C*inicio)
{

}
//////////////////////////////////////////////////////////////////////////
C* inserta_queue(C*,C*,N*);
C* pop_queue(C*);
C* copia_lista(C*,C*);
void despliega_queue(C*);
void despliega_queue_normal(C*);
int suma_peso(C*,int);
int despliegue_ciudad_opc(C*);
short int recorridos_total(C**,int);
void recorrido_profundidad(C*,C*,C*);
void recorrido_corto_max(C*,C*,C*,C**,C**);
void recorrido_profundidad_cant(C*,C*,C*,C**);
void reinicia(C*);
short int inserta_final(C**,C*,int);
C* busca_ciudad(C*,int);
void desplegar(C*,int);
void desplegar_conex(N*,int);
short int inserta_conex(C**,int);
short int checa_conex(N*,C*);
short int inserta_conex_final(N**,N*);
int cuenta_datos(N*,int);
int cant_conex(C*,int);
void checa_repetidos(C *actual,C*visitados,C*fin,C*);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
C *Crea_nodo(void)//Funcion creada para la creacion de un nodo de tipo C*
{
return (C*)malloc(sizeof(C));
}   
//////////////////////////////////////////////////////////////////////////
void checa_repetidos(C *actual,C*visitados,C*fin,C*before)//Recorrido que examina nodo por nodo para llegar al nodo fin
{
        if(actual!=fin || actual->band!=2)
        {     
                N *aux; 
                if(actual==fin){
                    actual->band = 2;
                }
                else
                    actual->band = 1;
                aux = actual->lista;
                while(aux)
                {
                    if(aux->conex->band!=1&&aux->conex!=before)
                    {   
                        aux->conex->peso=aux->distancia;
                        visitados = inserta_queue(actual,visitados,aux);
                        checa_repetidos(aux->conex,visitados,fin,actual);
                        visitados = pop_queue(visitados);
                    }
                    aux = aux->sig_dato;      
                }
        actual->band = 0;
        }
        else
        {
            fin->terminado = fin->terminado+1;
            visitados = inserta_queue(actual,visitados,NULL);
            printf("\nEl recorrido %d:\n",fin->terminado);
            despliega_queue(visitados);
            visitados = pop_queue(visitados);
            printf("\nSe cicla\n");
        }    
}
//////////////////////////////////////////////////////////////////////////
short int recorridos_total(C **lista,int opc)//Funcion que determina por opc que recorrido hara
{
    //si opc es 0, es la impresion de todos los caminos, 1 el de mayor y menor peso y 2 la de menor cantidad de conexiones
    short int checa;
C *inicio,*fin,*visitados,*aux,*max;
int llave_1,llave_2;
max = NULL;
aux=NULL;
visitados = NULL;

printf("\n\tIngrese ciudad de origen: ");
llave_1 = despliegue_ciudad_opc(*lista);
inicio = busca_ciudad(*lista,llave_1);
if(inicio)
{
    if(opc==7){
        fin=inicio;
        checa_repetidos(inicio,visitados,fin,NULL);
        if(fin->terminado==0){  
            reinicia(*lista);
            return 0;
        }
        else{
            reinicia(*lista);
            return 1;
        }
    }
    printf("\n\tIngrese ciudad de fin: ");
    llave_2 = despliegue_ciudad_opc(*lista);
    fin = busca_ciudad(*lista,llave_2);
    if(fin)
    {
        if(inicio==fin)
         return -2;
        if(!inicio->lista)
         return -3;
           if(opc == 0)
              recorrido_profundidad(inicio,visitados,fin); 
           else if(opc == 1)
           {
              recorrido_corto_max(inicio,visitados,fin,&aux,&max);
              if(aux)
              {
                  printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
                  printf("\n\tEl recorrido mas optimo de %s a %s es:\n",inicio->ciudad,fin->ciudad);
                  despliega_queue_normal(aux);
                  printf("\n\tsu distancia es: %d",suma_peso(aux,0));
                  printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
                  printf("\n\tEl recorrido menos optimo de %s a %s es:\n",inicio->ciudad,fin->ciudad);
                  despliega_queue_normal(max);
                  printf("\n\tsu distancia es: %d",suma_peso(max,0));
              }   
           }
           else if(opc == 2)
           {
               recorrido_profundidad_cant(inicio,visitados,fin,&aux);
               if(aux)
               {
                  printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
                  printf("\n\tEl recorrido con menor cantidad de conexiones de %s a %s es:\n",inicio->ciudad,fin->ciudad);
                  despliega_queue_normal(aux);
                  printf("\n\tCantidad de conexiones: %d",cant_conex(aux,0));
               }
           }
          if(fin->terminado!=0)
          {
            reinicia(*lista);
            return 1;
          } 
          else
          {
            reinicia(*lista);
             return 0; 
          }
    }
    else
    {
        return -1;
    }
}
else
{
    return -1;
}
}
//////////////////////////////////////////////////////////////////////////
C* inserta_queue(C*inicio,C*visitados,N *nodo)//hace la insercion del dato al inicio de la pila
{
        C *nuevo;
        nuevo = NULL;
        nuevo = Crea_nodo();
        if(nuevo)
        {   
              if(nodo)
        {
            nuevo->peso=nodo->distancia;            
        }
            else
            {
                nuevo->peso=0;
            }
            
            strcpy(nuevo->ciudad,inicio->ciudad);
            if(!visitados)
                nuevo->sig_ciudad = NULL;
            else
                nuevo->sig_ciudad = visitados;     
        }
        return nuevo;
}
//////////////////////////////////////////////////////////////////////////
C* pop_queue(C*visitados)//Elimina el ultimo dato ingresado de la pila
{
    C*aux;
    aux = visitados;
    aux = NULL;
    visitados = visitados->sig_ciudad;
    free(aux); 
    return visitados;
}
//////////////////////////////////////////////////////////////////////////
int suma_peso(C *visitados, int suma)//Suma del peso de la pila
{
    C* aux;
    aux = visitados;
    if(aux)
    {
       suma_peso(aux->sig_ciudad,suma+aux->peso);
    }
    else 
    return suma;
}
//////////////////////////////////////////////////////////////////////////
void despliega_queue_normal(C *visitados)//despliegue de la pila ingresada por los datos copiados
{
C *aux;
aux = visitados;
if(aux)
{
    printf("\nCiudad: %s",aux->ciudad); 
     despliega_queue_normal(aux->sig_ciudad);
}
}
//////////////////////////////////////////////////////////////////////////
void despliega_queue(C *visitados)//Despliegue de la pila empezando desde el primer nodo que se ingreso
{
C *aux;
aux = visitados;
if(aux)
{
    despliega_queue(aux->sig_ciudad);
    printf("\nCiudad: %s",aux->ciudad); 
}
}
//////////////////////////////////////////////////////////////////////////
void recorrido_profundidad(C *actual,C*visitados,C*fin)//Recorrido que examina nodo por nodo para llegar al nodo fin
{
    /*Este recorrido se ocupa en los siguientes pero solo con modificaciones de las datos que pide
    aqui empieza hasta llegar a punto muerto o que llegue al nodo que buscamos, si el nodo si es el final se imprimira la pila que llamamos queue sin querer
    y se eliminara el dato fin para que pueda revisar mas formas de llegar a, si el nodo se queda sin conexiones, se borra de la pila*/
if(actual!=fin)
{     
        N *aux; 
        actual->band = 1;
        aux = actual->lista;
        while(aux)
        {
            if(aux->conex->band==0)
            {   
                aux->conex->peso=aux->distancia;
                visitados = inserta_queue(actual,visitados,aux);
                recorrido_profundidad(aux->conex,visitados,fin);
                visitados = pop_queue(visitados);
            }
               aux = aux->sig_dato;      
        }
actual->band = 0;
}
else
{
    fin->terminado = fin->terminado+1;
    printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\tRecorrido %d\n",fin->terminado);
    visitados = inserta_queue(actual,visitados,NULL);
   despliega_queue(visitados);
   printf("\n\tLa distancia total entre las ciudades es:%d\n",suma_peso(visitados,0));
    visitados = pop_queue(visitados);
}
}
//////////////////////////////////////////////////////////////////////////
void recorrido_profundidad_cant(C *actual,C*visitados,C*fin,C**menor)//Recorrido que regresa el recorrido que menor cantidad de conexiones tenga
{
if(actual!=fin)
{     
        N *aux; 
        actual->band = 1;
        aux = actual->lista;
        while(aux)
        {
            if(aux->conex->band==0)
            {   
                aux->conex->peso=aux->distancia;
                visitados = inserta_queue(actual,visitados,aux);
                recorrido_profundidad_cant(aux->conex,visitados,fin,&(*menor));
                visitados = pop_queue(visitados);
            }
               aux = aux->sig_dato;      
        }
actual->band = 0;
}
else
{
    C *recorre;
   
fin->terminado = fin->terminado+1;    
visitados = inserta_queue(actual,visitados,NULL);
 recorre=visitados;
    if(fin->terminado == 1)
    {
        while(recorre)
        {
            *menor = copia_lista(recorre,*menor);
            recorre = recorre->sig_ciudad;
        }
    }
    else
    {
         if(cant_conex(visitados,0)<=cant_conex(*menor,0))
         {
           C *ant = *menor;
            while(*menor)
          {
                *menor = (*menor)->sig_ciudad;
                ant = NULL;
               free(ant);
           }
             while(recorre)
             {
                *menor = copia_lista(recorre,*menor);
                recorre = recorre->sig_ciudad;
             } 
         }
    }
     visitados = pop_queue(visitados);
}
}
//////////////////////////////////////////////////////////////////////////
int cant_conex(C* actual,int cont)//Funcion que determina la cantidad de conexiones de un recorrido
{
    C*aux=actual;
    if(aux)
    {
         cant_conex(actual->sig_ciudad,cont+1);
    }
    else
    {
        return cont-1;
    }
}
//////////////////////////////////////////////////////////////////////////
void recorrido_corto_max(C *actual,C*visitados,C*fin,C**menor,C**mayor)//Recorrido que guarda el recorrido de menor y mayor peso en dos variables auxiliares
{
if(actual!=fin)
{     
        N *aux; 
        actual->band = 1;
        aux = actual->lista;
        while(aux)
        {
            if(aux->conex->band==0)
            {   
                aux->conex->peso=aux->distancia;
                visitados = inserta_queue(actual,visitados,aux);
                recorrido_corto_max(aux->conex,visitados,fin,&(*menor),&(*mayor));
                visitados = pop_queue(visitados);
            }
               aux = aux->sig_dato;      
        }
actual->band = 0;
}
else
{
    C*recorre,*ant;
    fin->terminado = fin->terminado+1;
    visitados = inserta_queue(actual,visitados,NULL);
    recorre=visitados;
    if(fin->terminado == 1)
    {
        while(recorre)
        {
            *mayor = copia_lista(recorre,*mayor);
            *menor = copia_lista(recorre,*menor);
            recorre = recorre->sig_ciudad;
        }
    }
    else
    {  
        if(suma_peso(visitados,0) <= suma_peso(*menor,0))
        {
            ant = *menor;
            while(*menor)
          {
                *menor = (*menor)->sig_ciudad;
                ant = NULL;
               free(ant);
           }
           while(recorre)
           {
               *menor = copia_lista(recorre,*menor); 
               recorre = recorre->sig_ciudad;
           }
               
        }  
        else if(suma_peso(visitados,0)>=suma_peso(*mayor,0))    
        {
            ant = *mayor;
            while(*mayor)
            {
                ant = *mayor;
                *mayor = (*mayor)->sig_ciudad;
                ant = NULL;
                free(ant);
            }
         while(recorre)
           {
                *mayor = copia_lista(recorre,*mayor);
                recorre = recorre->sig_ciudad;
           }
        }
    }
    visitados = pop_queue(visitados);
}
}
//////////////////////////////////////////////////////////////////////////
C* copia_lista(C*visitados,C*aux)//Funcion que guarda la de visitados en aux para guardar sus valores determinando que recorrido haga
{
    C *nuevo;
    N *nodo;
    nuevo = NULL;
    nodo = NULL;
    while(!nodo)
        nodo = (N*)malloc(sizeof(N));
    while(!nuevo)
        nuevo = Crea_nodo();
    nodo->distancia = visitados->peso;   
    strcpy(nuevo->ciudad,visitados->ciudad);
    nuevo->peso = nodo->distancia;
        nuevo->sig_ciudad = aux; 
return nuevo;

}
//////////////////////////////////////////////////////////////////////////
void reinicia(C *lista)//Funcion que limpia las variables de nodos visitados
{
    if(lista)
    {
        lista->terminado=0;
        lista->band=0;
        reinicia(lista->sig_ciudad);
    }
}
//////////////////////////////////////////////////////////////////////////
int despliegue_ciudad_opc(C *inicio)/*Funcion para verificar si existe la opcion ingresada*/
{
   int opc;
           
            desplegar(inicio,0);
            printf("\n\tOpcion: ");
            fflush(stdin);
            if(scanf("%d",&opc))
            {
                return opc;
            }
            else
            {
                return -1;
            }
}
//////////////////////////////////////////////////////////////////////////
short int inserta_conex(C **inicio,int llave)//Funcion de insercion de conexiones
{
    /*Funcion que hace la conexion entre los nodos dados guardando en sus 
    respectivas listas la direccion del nodo*/
    short int checa;
    int opc,peso;
    C *aux,*aux2;
    N *nuevo,*nuevo2;
    aux2 = NULL;
    aux = NULL;
    aux = busca_ciudad(*inicio,llave);
    if(aux)
    {
         printf("\n\tIngrese a que ciudad desea hacer la conexion");
         desplegar(*inicio,0);
         printf("\n\tOpcion: ");
         fflush(stdin);
         if(scanf("%d",&opc))
         {
             aux2 = busca_ciudad(*inicio,opc);
             if(aux2)
             {
                 if(aux == aux2)
                 return -5;
                checa = checa_conex(aux->lista,aux2);
                if(checa == 0)
                 return -3;
                 nuevo2=(N*)malloc(sizeof(N));
                 if(!nuevo2)
                 return -4;
                nuevo=(N*)malloc(sizeof(N));
                 if(!nuevo)
                 return -4;
                nuevo2->conex = aux;
                nuevo->conex = aux2;
                printf("\n\tIngrese distancia en km entre %s y %s: ",aux->ciudad,aux2->ciudad);
                fflush(stdin);
                do
                {
                    while(!scanf("%d",&opc))
                    {
                        fflush(stdin);
                        printf("\n\tError de captura, reingrese dato");
                    }
                    if(opc<=0)
                    {
                       printf("\n\tDato invalido, reingrese dato"); 
                    }                    
                } while (opc <= 0);
                nuevo2->distancia = opc;
                nuevo->distancia = opc;
                nuevo->sig_dato = NULL;
                nuevo2->sig_dato = NULL;
                checa = inserta_conex_final(&(aux)->lista,nuevo);
                aux->cuantos = cuenta_datos(aux->lista,0);
                checa = inserta_conex_final(&(aux2)->lista,nuevo2);
                aux2->cuantos = cuenta_datos(aux2->lista,0);
                return checa;
             }
             else
             {
                 return -2;
             }
         }
         else
         {
             return 0;
         }
    }
    else
    {
        return -1;
    }
}
//////////////////////////////////////////////////////////////////////////
int cuenta_datos(N *nodo,int cont)//Funcion para saber la cantidad de conexiones de un nodo
{
    if(nodo)
    {
        return cuenta_datos(nodo->sig_dato,cont+1);
    }
    else
    {
        return cont;
    }
}
//////////////////////////////////////////////////////////////////////////
short int checa_conex(N*aux,C*nodo)//Funcion que revisa que el nodo ingresado no sea el mismo que el de actual
{
if(aux)
{
    if(aux->conex==nodo)
    {
        return 0;
    }
    else
    {
        return(checa_conex(aux->sig_dato,nodo));
    }  
}
else
{
    return 1;
}
}
//////////////////////////////////////////////////////////////////////////
short int inserta_conex_final(N **aux,N* nuevo)//Funcion que inserta al final de la lista la conexion del nodo
{
    if(!*aux)
    {
        *aux = nuevo;
        return 1;
    }
    else
    {
        return(inserta_conex_final(&(*aux)->sig_dato,nuevo));
    }
    
}
//////////////////////////////////////////////////////////////////////////
C *busca_ciudad(C *inicio,int opc)//funcion que valida que exista la opcion ingresada de la ciudad
{
    if(inicio)
    {
        if(inicio->llave==opc)
        {
            return inicio;
        }
        else
        {
            return (busca_ciudad(inicio->sig_ciudad,opc));
        }    
    }
    else
       return NULL;
}
//////////////////////////////////////////////////////////////////////////
short int inserta_final(C **inicio,C *aux,int llave)//Funcion que inserta la ciudad al final de la lista principal
{
    if(!*inicio)
    {
         C *nuevo; 
         char ciudad[MAXCIUDAD];
        nuevo = Crea_nodo();   
        if(!nuevo)
            return 0;
            else
            {
                printf("\n\tIngrese Nombre de la ciudad: ");
                fflush(stdin);   
                scanf("%29s",&ciudad);
                strcpy(nuevo->ciudad,ciudad);
                nuevo->lista = NULL;
                nuevo->sig_ciudad=NULL;
                nuevo->llave = llave;
                nuevo->ant_ciudad = aux;
                nuevo->cuantos=0;
                nuevo->band=0;
                nuevo->terminado=0;
                *inicio = nuevo;
                return 1;
            }     
    }
    else
    {
        return(inserta_final(&(*inicio)->sig_ciudad,*inicio,llave+1));
    }  
}
//////////////////////////////////////////////////////////////////////////
void desplegar_conex(N *lista,int cont)//Funcion que solo imprime las conexiones de un lugar
{
    if(lista)
    {
        printf("\n\tConexion %d. %s esta a %d km de distancia",cont,lista->conex->ciudad,lista->distancia);
        desplegar_conex(lista->sig_dato,cont+1);
    }
}
//////////////////////////////////////////////////////////////////////////
void desplegar(C *inicio,int band)//Funcion que despliega todas las ciudades con sus conexiones si la bandera es 1
{
    if(inicio!=NULL)
    {   
        printf("\n\t///////////////////////////////////////////////////////");
        printf("\n\t%d. %s cantidad: %d",inicio->llave,inicio->ciudad,inicio->cuantos);
        if(inicio->lista&&band!=0)
        {
            printf("\n\tConexiones: ",inicio->ciudad);
            desplegar_conex(inicio->lista,1);
        }
        
        desplegar(inicio->sig_ciudad,band);
    }
}
//////////////////////////////////////////////////////////////////////////
#endif