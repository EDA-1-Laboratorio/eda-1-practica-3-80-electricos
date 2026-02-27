#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.1416

//struct para el circulo
typedef struct {
int x;//cordenada x del centro
int y;//cordenada y
float radio;
} circulo;

//fucion para validar un nuevo circulo
circulo crear_circulo(int x, int y, float radio){
circulo c;


  if (radio <= 0){
    printf("Error: El radio debe ser mayor a 0. Por lo tanto se tomara el radio como 1\n");
    c.radio;
  }
  else {
    c.radio = radio;
  }
c.x = x;
c.y = y;

  return c;
  }


//funcion para calcular la distancia entre centro
float distancia_centros (circulo c1, circulo c2){
  return sqrt(pow(c1.x - c2.x,2) + pow(c1.y - c2.y,2));

}

//funcion para ver si se intersectan 
bool interseccion(circulo c1, circulo c2){
  float distancia = distancia_centros (c1, c2);

  //verificar si no tienen interseccion
  if (distancia > c1.radio + c2.radio){
    return false;
  }

  //verificar si uno esta adentro de otro
  if (distancia < fabs(c1.radio - c2.radio)){
    return false;
  }

  //caso contrario de las anterios (que si se intersectan)
  return true;

}


// >Opcional< Funcion para calcular el area de interseccion

//---------------------------------------------------------

float area_i(circulo c1, circulo c2){
  if (!interseccion (c1, c2)){   //false
    return 0.0;
  }

  float d = distancia_centros(c1, c2);
  float r1 = c1.radio;
  float r2 = c2.radio;
  
// para círculos concéntricos
    if (d == 0) {
        float r_menor = (r1 < r2) ? r1 : r2;
        return PI * r_menor * r_menor;
    }
// para un círculo dentro del otro
    if (d + fmin(r1, r2) <= fmax(r1, r2)) {
        return PI * pow(fmin(r1, r2), 2);
    }
// caso especial: para circulos de mismo radio
if (r1 == r2) {
        // Fórmula simplificada para círculos del mismo radio
        float angulo = 2 * acos(d / (2 * r1));
        return 2 * r1 * r1 * (angulo - sin(angulo));
  
// area de la interseccion
      float parte1 = r1 * r1 * acos((d*d + r1*r1 - r2*r2) / (2*d*r1)); 
      float parte2 = r2 * r2 * acos((d*d + r2*r2 - r1*r1) / (2*d*r2));
      float parte3 = 0.5 * sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));
      return parte1 + parte2 - parte3;

  
}
}
//Funcion para la entrada de datos para el circulo

circulo leer_c (int num){
  circulo c;
int x, y, lectura;
float radio;

printf ("\n\n---------    Por favor ingrese los datos círculo %d    ---------\n\n",num);

  do {
        printf("Coordenada 'x' del centro: ");
        lectura = scanf("%d", &x);
        while (getchar() != '\n'); 
    } while (lectura != 1);
    
    do {
        printf("Coordenada y del centro: ");
        lectura = scanf("%d", &y);
        while (getchar() != '\n');
    } while (lectura != 1);
    
    do {
        printf("Radio del círculo: ");
        lectura = scanf("%f", &radio);
        while (getchar() != '\n');
        
        if (lectura == 1 && radio <= 0) {
            printf("Error: El radio debe ser positivo. Intente nuevamente.\n");
            lectura = 0;
        }
    } while (lectura != 1);
    
    c = crear_circulo(x, y, radio);
    return c;
}


//funcion para imprimir el circulo
void imprimir_circulo(circulo c, int num) {
    printf("Círculo %d: Centro (%d, %d), Radio = %.2f\n", 
           num, c.x, c.y, c.radio);
} 
//main
int main(){
circulo circulo1, circulo2;
  printf("\n            -------------------------------           \n");
  printf("\n            Interseccion de circunferencias           \n");
  printf("\n            -------------------------------           \n");

  circulo1 = leer_c(1);
  circulo2 = leer_c(2);

  printf("\n\nRESULTADOS:\n");
    imprimir_circulo(circulo1, 1);
    imprimir_circulo(circulo2, 2);

  if (interseccion(circulo1, circulo2)) {
        printf("\n Los círculos tienen al menos un punto de intersección.\n");
        float area = area_i(circulo1, circulo2);
            printf("  Área: %.2f unidades cuadradas\n", area);
} else {
        printf("\n Los círculos no tienen puntos de intersección.\n");
    }

return 0;
}
