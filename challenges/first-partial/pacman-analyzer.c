//Hecho por Hugo Masharelli Rocha Avila A01633090
//Programacion Avanzada
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

//paquete
struct package{
    char name[150];
    char installDate[150];
    char lastUpdate[150];
    int upgradesAmount;
    char uninstallDate[150];
};

//struct con el paquete de funciones que estaremos usando
struct package packages[2000];
int obtenerLineas(FILE *file, char *buffer, size_t size);
void analizarLog(char *logFile, char *report);
int tipoDePaquete(char* line);
char* obtenerNobre(char* line);
char* obtenerFecha(char* line);

//Main
int main(int argc, char **argv) {

    if (argc != 5) {
	printf("Mal el numero de parametros usar: [-input logfile.txt -output desiredoutput.txt]\n");
    } else{
        analizarLog(argv[2], argv[4]);
    }
    return 0;
}

//Funcion para obtener la fecha del documento
char* obtenerFecha(char* line){
    int tamano = 0;
    for (tamano; line[tamano] != ']'; tamano++);
    tamano++;
    char *fecha = calloc(1, tamano);
    int contador = 0;
    for (int i = 0; i < tamano; i++, contador++){
        fecha[contador] = line[i];
    }
    return fecha;
}

//Funcion para ver el tipo de paquete que estoy recibiendo
int tipoDePaquete(char* line){
    int inicio = 0;
    for (int i = 0; i < 2; i++){
        for (inicio; line[inicio] != '\0'; inicio++){ 

            if (line[inicio] == ']'){
                break;
            }
        }
        inicio += 2;
    }
    if (line[inicio] == 'r' && line[inicio + 1] == 'e' && line[inicio + 2] == 'm' && line[inicio + 3] == 'o'){
        return 3;
    }
    if (line[inicio] == 'u' && line[inicio + 1] == 'p' && line[inicio + 2] == 'g' && line[inicio + 3] == 'r'){
        return 2;
    }
    if (line[inicio] == 'i' && line[inicio + 1] == 'n' && line[inicio + 2] == 's' && line[inicio + 3] == 't'){
        return 1;
    }
    return 0;
}
//Obtenemos el nombre de la funcion
char* obtenerNobre(char* line){
    int contador = 0, inicio = 0, size = 0;
    for (int i = 0; i < 2; i++){
        for (inicio; line[inicio] != ']'; inicio++);
        inicio += 2;
    }
    
    for (inicio; line[inicio] != ' '; inicio++);
    inicio++;
    for (int j = inicio + 1; line[j] != ' '; j++){
        size++;
    }
    char *nombre = calloc(1, size);
    for (int j = inicio; line[j] != ' '; j++, contador++){
        nombre[contador] = line[j];
    }
    return nombre;
}
//Encontramos la linea donde se utiliza
int obtenerLineas(FILE *file, char *buffer, size_t size){
    if (size == 0){
        return 0;
    }
    size_t currentSize = 0;
    int c;
    while ((c = (char) getc(file)) != '\n' && currentSize < size){
        if (c == EOF){
            break;
        }
        buffer[currentSize] = (char) c;
        currentSize++;
        
    }
    if (currentSize == 0){
        return 0;
    }
    buffer[currentSize] ='\0';
    return currentSize;
}
//Analizamos el archivo de texto para ver que onda y escribimos sobre ellos
void analizarLog(char *logFile, char *report) {
    printf("Generando reporte de [%s] log file\n", logFile);
    char line[255];
    int c;
    
    FILE*  file;
    file = fopen(logFile, "r");
    if (file == NULL){
        printf("Error al abrir el log file \n");
        return;
    }
    int writer = open(report, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (writer < 0) {
        perror("Un error ocurrio mientras se creaba/abria el reporte del archivo"); 
        return;
    }
    
    int installed = 0, removed = 0, upgraded = 0, current = 0;
    while (c = obtenerLineas(file, line, 255) > 0){
        int n = tipoDePaquete(line);
        if (n == 1){
            char* name = obtenerNobre(line);
            char* date = obtenerFecha(line);
            strcpy(packages[current].name, name);
            strcpy(packages[current].installDate, date);
            packages[current].upgradesAmount = 0;
            strcpy(packages[current].uninstallDate, "-");
            current++;
            installed++;
        } else if (n == 2){
            char* name = obtenerNobre(line);
            char* date = obtenerFecha(line);
            for (int i = 0; i < 1500; i++){
                if (strcmp(packages[i].name, name) == 0){
                    strcpy(packages[i].lastUpdate, date);
                    if (packages[i].upgradesAmount == 0){
                        upgraded++;
                    }
                    packages[i].upgradesAmount++;
                    break;
                }
            }
        } else if (n == 3){ 
            char* name = obtenerNobre(line);
            char* date = obtenerFecha(line);
            for (int i = 0; i < 1500; i++){
                if (strcmp(packages[i].name, name) == 0){
                    strcpy(packages[i].uninstallDate, date);
                }
                break;
            }
            removed++;
        }
        
    } 
    write(writer, "Pacman Packages Report\n", strlen("Pacman Packages Report\n"));
    write(writer,"----------------------\n",strlen("----------------------\n"));
    char aux[10];
    write(writer, "Installed packages : ", strlen("Installed packages : "));
    sprintf(aux, "%d\n", installed);
    write(writer, aux, strlen(aux));
    write(writer, "Upgraded packages : ",strlen("Upgraded packages : "));
    sprintf(aux, "%d\n", upgraded);
    write(writer, aux, strlen(aux));
    write(writer, "Removed packages : ",strlen("Removed packages : "));
    sprintf(aux, "%d\n", removed);
    write(writer, aux, strlen(aux));
    write(writer, "Current installed : \n",strlen("Current installed : "));
    sprintf(aux, "%d\n", (installed-removed));
    write(writer, aux, strlen(aux));

    write(writer, "\n\nList of packages\n", strlen("\n\nList of packages\n"));
    write(writer,"----------------------\n",strlen("----------------------\n"));
    for(int i = 0; i < 1500; i++){
        if(strcmp(packages[i].name, "") != 0){
            write(writer, "- Package name         : ",strlen("- Package name         : "));
            write(writer,packages[i].name, strlen(packages[i].name));
            write(writer, "\n   - Install date      : ",strlen("\n   - Install date      : "));
            write(writer,packages[i].installDate, strlen(packages[i].installDate));
            write(writer, "\n   - Last update date  : ",strlen("\n   - Last update date  : "));
            write(writer,packages[i].lastUpdate, strlen(packages[i].lastUpdate));
            write(writer, "\n   - How many updates  : ",strlen("\n   - How many updates  : "));
            sprintf(aux, "%d", packages[i].upgradesAmount);
            write(writer,aux, strlen(aux));
            write(writer, "\n   - Removal date      : ",strlen("\n   - Removal date      : "));
            write(writer,packages[i].uninstallDate, strlen(packages[i].uninstallDate));
            write(writer, "\n",strlen("\n"));
        } else if (strcmp(packages[i].name, "") == 0){
            break;
        }
    }

    if (close(writer) < 0)  
    { 
        perror("Error while trying to close the report file"); 
        exit(1); 
    } 

    printf("Report is generated at: [%s]\n", report);
}