#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "opcion.h"

int main()
{
    int op;
    List* L = create_list();
    int CantJugadores;
    while (op != 11) {
        /* MENU */ 
        printf("1.- Importar juegos desde un archivo CSV\n");
        printf("2.- Exportar juegos CSV\n");
        printf("3.- Agregar juego\n");
        printf("4.- Buscar por cantidad de jugadores\n");
        printf("5.- Buscar juegos por marca\n");
        printf("6.- Buscar juego por nombre\n");
        printf("7.- Buscar juego por tipo\n");
        printf("8.- Buscar juegos por mas de un criterio\n");
        printf("9.- Mostrar todos los juegos\n");
        printf("10.- Mostrar extensiones\n");
        printf("11.- Salir\n");
        printf("Indica la opcion: ");
        scanf("%d", &op);
        if (op==1){
            opcion_1(L);
        }
        if (op==3){
            opcion_3(L);
        }
        if (op==4) {
            opcion_4(L);
        }
        if (op==5) {
            char marca[40];
            scanf("%s", &marca);
            opcion_5(marca, L);
        }
        if (op==6) {
            char nombre[40];
            scanf("%s", &nombre);
            opcion_6(nombre, L);
        }
        if (op==7) {
            char genero[40];
            scanf("%s", &genero);
            opcion_7(genero, L);
        }
        if (op==8) {
            char genero[40];
            int jugadores;
            scanf("%s", &genero);
            scanf("%d", &jugadores);
            opcion_8(genero, jugadores, L);
        }
        if (op==9) {
            opcion_9(L);
        }
        if (op==10) {
            opcion_10(L);
        }
    }
    return 0;
}