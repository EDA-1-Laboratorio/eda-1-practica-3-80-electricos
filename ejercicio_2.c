#include <stdio.h>
#include <math.h>

#define MAX 20 //maximo de pizzas a ordenar

struct Pizzas {
    float radio;
    int cantidadIngredientes;
    char Ingredientes[10][20]; //guardar máximo 10 ingredientes de 20 caracteres
    float precio;
};

float calcularPrecio(float radio, int cantidadIngredientes){
    float precioBase=radio*10;
    float precioIngredientes=cantidadIngredientes*15;
    return precioBase+precioIngredientes;
}

int main() {
    int n;
    struct Pizzas pizzas [MAX];
    float total=0;

    printf("---Pizzas 80 por ciento eléctricos ---\n");
    printf("\ntoppings disponibles:");
    printf("\nPeperoni");
    printf("\nQueso");
    printf("\nCarne");
    printf("\nChampiñones");
    printf("\nMorrón");
    printf("\nPiña");
    printf("\nPapas");
    printf("\nPollo");
    printf("\nLonganiza");
    printf("\nPeperoni");
    printf("\nRecuerde la promoción, 2x1 al comprar dos pizzas del mismo tamaño"); 
    printf("\n¿Cuántas pizzas desea ordenar? ");
    scanf("%d", &n);

    if (n>MAX){
        printf("Por el momento no aceptamos pedidos tan grandes\n");
        return 1;
    }

    //Captura de datos
    for (int i = 0; i < n; i++){

        printf("\n--- Pizza %d ---\n", i + 1);

        printf("Radio de la pizza(cm): ");
        scanf("%f", &pizzas[i].radio);

        printf("Cantidad de Ingredientes: ");
        scanf("%d", &pizzas[i].cantidadIngredientes);
        
        if (pizzas[i].cantidadIngredientes > 10){
            printf("Error: máximo 10 ingredientes\n");
            return 1;
        }

        for (int j = 0; j < pizzas[i].cantidadIngredientes; j++) {
            printf("Topping %d: ", j + 1);
            scanf("%s", pizzas[i].Ingredientes[j]);
        }

        pizzas[i].precio = calcularPrecio(
            pizzas[i].radio,
            pizzas[i].cantidadIngredientes
        );
    }

    // Aplicar promoción 2x1
        int aplicada[MAX] = {0};  

         for (int i = 0; i < n; i++) {

          if (aplicada[i]) continue; 

        int pareja = -1;

    // Buscar otra pizza del mismo tamaño
        for (int j = i + 1; j < n; j++) {
        if (!aplicada[j] && pizzas[i].radio == pizzas[j].radio) {
            pareja = j;
            break;
        }
    }

         if (pareja != -1) {
        // Se encontró pareja → 2x1
        total += pizzas[i].precio;  // solo se paga una
        aplicada[i] = 1;
        aplicada[pareja] = 1;
        
      
        
    } else {
        // No hay pareja → se paga normal
        total += pizzas[i].precio;
        aplicada[i] = 1;
        
    }
}
    printf("\n================ TICKET ================\n");
   for (int i = 0; i < n; i++) {
    printf("Pizza %d - Radio: %.2f cm - Precio: $%.2f", i+1, pizzas[i].radio, pizzas[i].precio);
    // Si tuvo 2x1
    if (aplicada[i] && i+1 < n && pizzas[i].radio == pizzas[i+1].radio) {
        printf(" (2x1 aplicado)");
    }
    printf("\n");
}
    printf("\nTOTAL A PAGAR: $%.2f\n", total);
    printf("========================================\n");

   
    return 0;
}
