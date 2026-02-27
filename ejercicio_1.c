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
        baraja[i]=baraja[j];
        baraja[j]=temp;
    }
}

void mostrarCarta(Carta c){
    const char*valores[]={"As","2","3","4","5","6","7","8","9","10","J","Q","K"};
    printf("%s de %c",valores[c.valor-1],c.palo);
}

int preguntajugador(int jugador){
    int opc;
    printf("\nJugador %d: ¿Deseas quedarte en el juego? (1=Si, 0=No): ",jugador);
    scanf("%d",&opc);
    return opc;
}

// Evaluación completa de manos con jerarquía
int evaluarMano(Carta mano[], Carta river[]){
    Carta todas[7];
    for(int i=0;i<2;i++) 
        todas[i]=mano[i];
    for(int i=0;i<5;i++) 
        todas[i+2]=river[i];

    // Contar valores
    int counts[14]={0};
    for(int i=0;i<7;i++) 
        counts[todas[i].valor]++;

    // Contar palos
    int palos[4]={0}; // T,P,C,D
    for(int i=0;i<7;i++){
        switch(todas[i].palo){
            case 'T': 
                palos[0]++; 
                break;
            case 'P': 
                palos[1]++; 
                break;
            case 'C': 
                palos[2]++; 
                break;
            case 'D': 
                palos[3]++; 
                break;
        }
    }

    // Detectar repeticiones
    int pares=0,tercia=0,poker=0;
    for(int v=1;v<=13;v++){
        if(counts[v]==2) 
            pares++;
        if(counts[v]==3) 
            tercia++;
        if(counts[v]==4) 
            poker=1;
    }

    // Detectar corridas V2.0
    int corrida=0; 
    int valores[14]={0}; 
    for(int i=0;i<7;i++) 
        valores[todas[i].valor]=1;
    for(int start=1;start<=9;start++){ 
        int consecutivas=0; 
        for(int k=0;k<5;k++){ 
            if(valores[start+k]) 
            consecutivas++; 
        }
        if(consecutivas==5){ 
            corrida = 1; 
            break; 
        } 
    } 
    // Caso especial: A-10-11-12-13 
    if(valores[1] && valores[10] && valores[11] && valores[12] && valores[13]) 
        corrida = 1;
    
    // Detectar color
    int color=0;
    for(int p=0;p<4;p++) 
        if(palos[p]>=5) 
            color=1;

    // Corrida de color y corrida real
    int corridaColor=0,corridaReal=0;
    if(color && corrida) 
        corridaColor=1;
    if(color && counts[1]>0 && counts[10]>0 && counts[11]>0 && counts[12]>0 && counts[13]>0)
        corridaReal=1;

    // Jerarquía
    if(corridaReal) 
        return 10;          // Corrida real
    else if(corridaColor) 
        return 9;     // Corrida de color
    else if(poker) 
        return 8;            // Póker
    else if(tercia && pares>0) 
        return 7;// Full House
    else if(color) 
        return 6;            // Color
    else if(corrida) 
        return 5;          // Corrida
    else if(tercia) 
        return 4;           // Tercia
    else if(pares>=2) 
        return 3;         // Dos pares
    else if(pares==1) 
        return 2;         // Un par
    else {
        // Carta más alta
        int max=0;
        for(int i=0;i<7;i++) 
            if(todas[i].valor>max) 
                max=todas[i].valor;
            return max; // aquí devolvemos la carta más alta para desempates
    }
}

void mostrarMano(int score,int jugador){
    printf("Jugador %d = ",jugador);
    switch(score){
        case 10: 
            printf("Corrida Real\n"); 
            break;
        case 9: 
            printf("Corrida de Color\n"); 
            break;
        case 8: 
            printf("Póker\n"); 
            break;
        case 7: 
            printf("Full House\n"); 
            break;
        case 6: 
            printf("Color\n"); 
            break;
        case 5: 
            printf("Corrida\n"); 
            break;
        case 4: 
            printf("Tercia\n"); 
            break;
        case 3: 
            printf("Dos Pares\n"); 
            break;
        case 2: 
            printf("Un Par\n"); 
            break;
        default: 
            printf("Carta más alta (%d)\n", score); break;
    }
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
    printf("\n--- Segunda Ronda ---\n"); 
    for(int i=0;i<3;i++) 
        river[i] = baraja[pos++]; 
    printf("River: "); 
    for(int i=0;i<3;i++){ 
        mostrarCarta(river[i]); 
        printf(" | "); 
    }

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

    //Tercera Ronda
    printf("\n--- Tercera Ronda ---\n");
    river[3]=baraja[pos++];
    printf("River: ");
    for(int i=0;i<4;i++){ 
        mostrarCarta(river[i]); 
        printf(" | "); 
    }

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

    //Cuarta Ronda
    printf("\n--- Cuarta Ronda ---\n");
    river[4]=baraja[pos++];
    printf("River final: ");
    for(int i=0;i<5;i++){
        mostrarCarta(river[i]); 
        printf(" | ");
    }

    //Evaluación final
    int score1=evaluarMano(j1.mano,river);
    int score2=evaluarMano(j2.mano,river);
    printf("\nEvaluación final:\n");
    mostrarMano(score1,1);
    mostrarMano(score2,2);
    if(score1>score2)
        printf("Jugador 1 gana. \n");
    else if(score2>score1)
        printf("Jugador 2 gana.\n");
    else  
        printf("Empate. \n");
    
    return 0;
}
