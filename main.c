/*
Practica grafos
 
Nombres:
Luis Antonio Blanco Conde
Alejandro Octavio Salas Comparán


*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ListaSimple.h"
void main()
{

int opc,llave;
short int checa;
C *inicio;
inicio = NULL;
do
{
printf("\n\tMenu"
"\n\t1.Inserta Ciudad"
"\n\t2.Inserta conexiones de la ciudad"
"\n\t3.Despliega ciudades"
"\n\t4.Recorrido (1)-Por rutas"
"\n\t5.Recorrido (2)-Por ruta mas corta"
"\n\t6.Recorrido (3)-Por ruta mas eficiente y menos eficiente"
"\n\t7.Busqueda de ciclos"
"\n\t0.Salir\n\tOpcion: ");
fflush(stdin);
if(scanf("%d",&opc))
{
    system("cls");
    switch (opc)
    {
    case 1:
    checa = inserta_final(&inicio,inicio,1);
    if(checa == 1)
    {
        printf("\n\tExito en la alta de la ciudad");
    }
    else
    {
        printf("\n\tError en la creacion del nodo");
    }
        break;
    case 2:
    if(inicio)
    {
        if(inicio->sig_ciudad)
        {
            printf("A que ciudad desea ingresarle una conexion?");
            desplegar(inicio,0);
            printf("\n\tOpcion: ");
            fflush(stdin);
            if(scanf("%d",&llave))
            {
                checa=inserta_conex(&inicio,llave);
                if(checa==-1)
                {
                printf("\n\tError, ciudad no existente");  
                }
                else if(checa==0)
                {
                printf("\n\tError de captura"); 
                }
                else if(checa==-5)
                {
                printf("\n\tError, No se pueden hacer conexiones entre la misma ciudad");  
                }
                else if(checa == -2)
                {
                    printf("\n\tError, conexion no existente");
                }
                else if(checa == 1)
                {
                    printf("\n\tExito al crear la conexion entre las ciudades");
                }
                else if(checa == -3)
                {
                    printf("\n\tYa existe la conexion entre las ciudades ingresades");
                }
                else if(checa == -4)
                {
                    printf("\n\tError en la creacion del nodo");
                }
            }
            else
            {
                printf("Error de captura");
            }             
        }
        else
        {
            printf("\n\tSolo exite una ciudad ingresada en el grafo, ingrese mas para acceder a esta opcion");
        } 
    }
    else
    {
         printf("\n\tNo hay ciudades ingresadas");
    }
        break;
    case 3:if(inicio)
    {
        printf("\nLas siguientes ciudades son las que actualmente estan registradas:\n");
        desplegar(inicio,1);  
    }
    else
    {
        printf("\n\tNo hay ciudades ingresadas");
    }
        break;
    case 4:
    if(inicio)
    {
    checa = recorridos_total(&inicio,0);
    if(checa==1)
    {
        printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\tExito de impresion de caminos");
    }
    else if(checa == -1)
    {
        printf("\n\tCiudad ingresada no existente");
    }
    else if(checa == -2)
    {
        printf("\n\tNo se puede ingresar el mismo nodo");
    }
    else if(checa == -3)
    {
        printf("\n\tNo hay conexiones en el nodo de origen");
    }
    else if(checa == 0)
    {
        printf("\n\tNo hay ninguna conexion entre los nodos ingresados");
    }
    }
    else
    {
        printf("\n\tNo hay ciudades ingresadas");
    }
        break;
    case 6:
    if(inicio)
    {
        checa = recorridos_total(&inicio,1);
    if(checa==1)
    {
        printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\tExito de impresion de caminos");
    }
    else if(checa == -1)
    {
        printf("\n\tCiudad ingresada no existente");
    }
    else if(checa == -2)
    {
        printf("\n\tNo se puede ingresar el mismo nodo");
    }
    else if(checa == -3)
    {
        printf("\n\tNo hay conexiones en el nodo de origen");
    }
    else if(checa == 0)
    {
        printf("\n\tNo hay ninguna conexion entre los nodos ingresados");
    }
    }
    else
    {
         printf("\n\tNo hay ciudades ingresadas");
    }
        break;
    case 5:
    if(inicio)
    {
        checa = recorridos_total(&inicio,2);
    if(checa==1)
    {
        printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\tExito de impresion del camino!");
    }
    else if(checa == -1)
    {
        printf("\n\tCiudad ingresada no existente");
    }
    else if(checa == -2)
    {
        printf("\n\tNo se puede ingresar el mismo nodo");
    }
    else if(checa == -3)
    {
        printf("\n\tNo hay conexiones en el nodo de origen");
    }
    else if(checa == 0)
    {
        printf("\n\tNo hay ninguna conexion entre los nodos ingresados");
    }        
    }
    else
    {
         printf("\n\tNo hay ciudades ingresadas");
    }
        break;
    case 7: 
    if(inicio){
        checa=recorridos_total(&inicio,7);
        if(checa==1)
            {
                printf("\n\n|°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
                printf("\n\tExito de impresion de caminos");
            }
            else if(checa == -1)
            {
                printf("\n\tCiudad ingresada no existente");
            }
            else if(checa == -3)
            {
                printf("\n\tNo hay conexiones en el nodo de origen");
            }
            else if(checa == 0)
            {
                printf("\n\tNo hay ningun ciclo");
            }
    }
    
        break;
    case 0:
        system("cls");
        printf("\n\n\n\t\t\tADIOS");
        break;
    default:
        printf("\n\tError de captura");
        break;
    }
}
else
{
    printf("\n\tError de captura");
}
printf("\n\n\n\t");
system("pause");
system("cls");
}while (opc!=0);
}
