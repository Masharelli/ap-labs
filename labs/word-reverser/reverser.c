//Rocha Avila Hugo Masahrelli
//A01633090
#include <string.h>
#include <stdio.h>

void cambiar(char* a, char*b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void alReves(char* almacenamiento, int tamano ){
       char* a = almacenamiento;
       char* b = almacenamiento + tamano - 1;
       for(char i = 0; i < tamano/2; i++){
           cambiar(a++, b--);
       }
}

 int main(){
    char c = 0;
    char almacenamiento[64];
    while((c = getchar()) != EOF ){
       scanf("%s", almacenamiento);
       alReves(almacenamiento,strlen(almacenamiento));
       printf("Al revez la palabra es: %s\n", almacenamiento);
       }
     return 0;
 }
