//Simulador de Póker (2 Players)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 52
#define NUM_PALOS 4
#define NUM_VALORES 13

typedef struct Naipe
{
    int valor; // 1=As , 2-10, 11=J, 12=Q, 13=K
    char palo; // T=treboles, P=picas, C=corazones, D=diamantes
}Carta;

typedef struct Jugador
{
    Carta mano[2];
    int activo;
}Player;

//Crear la baraja
void CrearBaraja(Carta baraja[]){
    char palos[NUM_PALOS]={'T','P','C','D'};
    int k=0;
    for(int p=0;p<NUM_PALOS;p++){
        for(int v=1; v<=NUM_VALORES;v++){
            baraja[k].valor=v;
            baraja[k].palo=palos[p];
            k++;
        }
    }
}

void barajar(Carta baraja[]){
    for(int i=NUM_CARTAS-1;i>0;i--){
        int j=rand()%(i+1);
        Carta temp=baraja[i];
        baraja[i]=temp;
    }
}

void mostrarCarta(Carta c){
    char*valores[]={"As","2","3","4","5","6","7","8","9","10","J","Q","K"};
    printf("%s de %c",valores[c.valor-1],c.palo);
}

int preguntajugador(int jugador){
    int opc;
    printf("\nJugador %d: ¿Deseas quedarte en el juego? (1=Si, 0=No): ",jugador);
    scanf("%d",&opc);
    return opc;
}

//Evaluacion de manos(Casi)
int evaluarMano(Carta mano[], Carta river[]){
    int max=0;
    for(int i=0;i<2;i++){
        if(mano[i].valor>max)
            max=mano[i].valor;
    }
    for(int i=0;i<5;i++){
        if(river[i].valor>max)
            max=river[i].valor;
    }
    return max;
}
//Programa Principal
int main(){
    srand(time(NULL));
    Carta baraja[NUM_CARTAS];
    CrearBaraja(baraja);
    barajar(baraja);

    Player j1={.activo=1}, j2={.activo=1};
    Carta river[5];

    //Reparto inicial
    j1.mano[0]=baraja[0]; j1.mano[1]=baraja[1];
    j2.mano[0]=baraja[2]; j2.mano[1]=baraja[3];
    int pos=4;

    //Primera Ronda
    printf("\n--- Primera Ronda ---\n");
    printf("Jugador 1 recibe: "); mostrarCarta(j1.mano[0]); printf(" y "); mostrarCarta(j1.mano[1]); printf("\n");
    printf("Jugador 2 recibe: "); mostrarCarta(j2.mano[0]); printf(" y "); mostrarCarta(j2.mano[1]); printf("\n");

    j1.activo=preguntajugador(1);
    j2.activo=preguntajugador(2);

    if(!j1.activo){
        printf("\nJugador 2 gana por retiro.\n");
        return 0;
    }
    if(!j2.activo){
        printf("\nJugador 1 gana por retiro.\n");
        return 0;
    }

    //Segunda Ronda
    
}
