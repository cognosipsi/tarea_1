#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"

typedef struct{
        char nombre[40];
        char marca[40];
        char genero[2][40];
        int min_jugadores;
        int max_jugadores;
        char extension[40];
} juego;

const char *get_csv_field(char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }
    return NULL;
}
char * _strdup(const char * str) {
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}

void opcion_1(List *L) {
    FILE *fp = fopen ("50 juegos.csv", "r"); //abrimos archivo
    char linea[1024];
    int i;
    int j;
    int l;
    int k=0;
    juego *info;
    const char *aux;
    while (fgets (linea, 1023, fp) != NULL) { //lee las lineas del archivo csv hasta fin de texto
        info=(juego*)malloc(sizeof(juego)); //se reserva memoria
        j=0;
        l=0;
        for(i=0;i<6;i++){
            aux = get_csv_field(linea, i); //almacenamos en aux los strings entre comas del archivo csv
            if(i==0){
                strcpy(info->nombre, aux);
            }
            if(i==1){
                strcpy(info->marca, aux);
            }
            if(i==2){
                while(aux[j]!=',' && aux[j]!='\0'){
                    info->genero[0][j]=aux[j];
                    j++;
                }
                info->genero[0][j]='\0';
                if(aux[j]==','){
                    j+=2;
                    while(aux[j]==' ' || isalpha(aux[j])){
                        info->genero[1][l]=aux[j];
                        j++;
                        l++;
                    }
                    info->genero[1][l]='\0';
                }
            }
            if(i==3){
                info->min_jugadores=atoi(aux);
            }
            if(i==4){
                info->max_jugadores=atoi(aux);
            }
            if(i==5){
                strcpy(info->extension, aux);
            }
        }
        push_back(L,info);
    }
}

void opcion_3(List *L) {
    char nombre[40];
    char marca[40];
    int n;
    char genero[2][40];
    int min_jugadores;
    int max_jugadores;
    char extension[40];
    juego *info=(juego*)malloc(sizeof(juego));
 
    printf("Ingrese el nombre del juego\n");
    fgets(nombre, 40, stdin);
    scanf("%s", &nombre);
    strcpy(info->nombre, nombre);
 
    printf("Ingrese la marca del juego\n");
    scanf("%s", &marca);
    strcpy(info->marca, marca);
    
    printf("Ingrese la cantidad de generos a ingresar\n");
    scanf("%d", &n);
    printf("Ingrese el genero\n");
    scanf("%s", &genero[0]);
    strcpy(info->genero[0], genero[0]);
    if (n == 2) {
        printf("Ingrese el otro genero\n");
        scanf("%s", &genero[1]);
        strcpy(info->genero[1], genero[1]);
    }
    
    printf("Ingrese el numero minimo de jugadores\n");
    scanf("%s", &min_jugadores);
    info->min_jugadores = min_jugadores;
    
    printf("Ingrese el numero maximo de jugadores\n");
    scanf("%s", &max_jugadores);
    info->max_jugadores = max_jugadores;
    
    printf("Ingrese extension\n");
    scanf("%s", &extension);
    strcpy(info->extension, extension);
 
    push_back(L,info); //se van agregando al final de la lista los elementos ingresados por el usuario
}


void opcion_4(List *L) {
    int CantJugadores;
    scanf("%d", &CantJugadores);
    juego *iterador = first(L);
    while (iterador != NULL) {
        if (iterador->max_jugadores >= CantJugadores) {     //validamos que la cantidad de jugadores ingresada se encuentra
            if (iterador->min_jugadores <= CantJugadores) { //en el rango entre la cantidad minima y maxima de jugadores del
                printf("%s ", iterador->nombre);            //juego actual de la lista
                printf("%s ", iterador->marca);
                printf("%s ", iterador->genero[0]);
                if (iterador->genero[1] != NULL) {
                    printf("%s ", iterador->genero[1]);
                }
                printf("%d ", iterador->min_jugadores);
                printf("%d ", iterador->max_jugadores);
                printf("%s ", iterador->extension);
                printf("\n");
            }
        }
        iterador = next(L); //se itera la lista
    }
}

void opcion_5(char *marca, List* L) {
    juego *iterador;
    bool no_existe = true;
    iterador=first(L);
    while (iterador != NULL) {
        if (strcmp(iterador->marca, marca) == 0) {  //comparamos el nombre de la marca ingresada por el usuario con el nombre
            printf("%s ", iterador->nombre);        //de la marca del juego actual de la lista
            printf("%s ", iterador->marca);
            printf("%s ", iterador->genero[0]);
            if (iterador->genero[1] != NULL) {
                printf("%s ", iterador->genero[1]);
            }
            printf("%d ", iterador->min_jugadores);
            printf("%d ", iterador->max_jugadores);
            printf("%s ", iterador->extension);
            printf("\n");
            no_existe = false;
        }
        iterador = next(L); //se itera la lista
    }
    if (no_existe) {
        printf("No hay ningun juego de esta marca\n");
    }
}

void opcion_6(char* nombre,List* L){
    juego *iterador;
    bool no_existe = true;
    iterador=first(L);
    while (iterador != NULL) {
        if (strcmp(iterador->nombre, nombre) == 0) {    //se compara el nombre ingresado por el usuario con el nombre del juego actual de
            printf("%s ", iterador->nombre);            //la lista
            printf("%s ", iterador->marca);
            printf("%s ", iterador->genero[0]);
            if (iterador->genero[1] != NULL) {
                printf("%s ", iterador->genero[1]);
            }
            printf("%d ", iterador->min_jugadores);
            printf("%d ", iterador->max_jugadores);
            printf("%s ", iterador->extension);
            printf("\n");
            no_existe = false;
        }
        iterador = next(L); //se itera la lista
    }
    if (no_existe) {
        printf("No hay ningun juego con este nombre\n");
    }
}

void opcion_7(char* genero, List* L) {
    juego *iterador;
    bool no_existe = true;
    iterador=first(L);
    while (iterador != NULL) {
        if (strcmp(iterador->genero[0], genero) == 0 || strcmp(iterador->genero[1], genero) == 0) {
            printf("%s ", iterador->nombre);
            printf("%s ", iterador->marca);
            printf("%s ", iterador->genero[0]);
            if (iterador->genero[1] != NULL) {
                printf("%s ", iterador->genero[1]);
            }
            printf("%d ", iterador->min_jugadores);
            printf("%d ", iterador->max_jugadores);
            printf("%s ", iterador->extension);
            printf("\n");
            no_existe = false;
        }
        iterador = next(L);
    }
    if (no_existe) {
        printf("No hay ningun juego de este genero\n");
    }
}

void opcion_8(char* genero,int jugadores, List* L) {
    juego *iterador;
    iterador=first(L);
    while (iterador != NULL) {
        if ( (strcmp(iterador->genero[0], genero) == 0 || strcmp(iterador->genero[1], genero) == 0) && (iterador->max_jugadores >= jugadores && iterador->min_jugadores<=jugadores)) {
            printf("%s ", iterador->nombre);
            printf("%s ", iterador->marca);
            printf("%s ", iterador->genero[0]);
            if (iterador->genero[1] != NULL) {
                printf("%s ", iterador->genero[1]);
            }
            printf("%d ", iterador->min_jugadores);
            printf("%d ", iterador->max_jugadores);
            printf("%s ", iterador->extension);
            printf("\n");
        }
        iterador = next(L);
    }
}

void opcion_9(List *L) {
    juego *iterador = first(L);
    while (iterador != NULL) {
        printf("%s ", iterador->nombre);
        printf("%s ", iterador->marca);
        printf("%s ", iterador->genero[0]);
        if (iterador->genero[1] != NULL) {
            printf("%s ", iterador->genero[1]);
        }
        printf("%d ", iterador->min_jugadores);
        printf("%d ", iterador->max_jugadores);
        printf("%s ", iterador->extension);
        printf("\n");
        iterador = next(L);
    }
}

void opcion_10(List *L) {
    bool no_existe = true;
    juego *iterador = first(L);
    while (iterador != NULL) {
        if ((strcmp(iterador->extension, "No aplica") != 0)&&(strcmp(iterador->extension, "No aplic") != 0)&&(strcmp(iterador->extension, "No aplica ") != 0)){
            no_existe = false;
            printf("%s\n", iterador->extension);
        }
        iterador = next(L);
    }
    if (no_existe) {
        printf("No hay ninguna extension\n");
    }
}