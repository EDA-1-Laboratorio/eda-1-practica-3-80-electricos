#include <stdio.h>

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

    printf("---Pizzas 80% eléctricos ---\n");
    printf("¿Cuántas pizzas desea ordenar? ");
    scanf("%d", &n);

    if (n>MAX){
        printf("Por el momento no aceptamos pedidos tan grandes\n");
        return 1;
    }

    //Captura de datos
    for (int i = 0; i < n; i++){

        printf("\n--- Pizza %d ---\n", i + 1);

        printf("Radio de la pizza: ");
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

    // Calcular total inicial
    for (int i = 0; i < n; i++) {
        total += pizzas[i].precio;
    }

    // Imprimir ticket
    printf("\n================ TICKET ================\n");

 

    printf("\nTOTAL A PAGAR: $%.2f\n", total);
    printf("========================================\n");

    return 0;
}
