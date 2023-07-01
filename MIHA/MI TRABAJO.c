#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define MAX_LINE_LENGTH 1000

// Estructura para almacenar los datos de energía
typedef struct {
    char energia[N];
    double numeros[24];
} Dato;

// Estructura para almacenar una media junto con la fecha correspondiente
struct MediaCalculada {
    int mes;
    int year;
    float valor;
    int contador;
};

// Estructura para almacenar los valores ordenados
struct ValorOrdenado {
    int mes;
    int year;
    double valor;
};

// Variables globales
float mediaGuardada = 0.0;
int contadorMedias = 0;
int contadorValoresOrdenados = 0;
int columna;

// Declaración de funciones
void verTabla(const char* generacion);
void menuPrincipal();
int comparardatos(const void *a, const void *b);
void ordenarmayoramenor(const char *nombreArchivoCSV, const char *nombreArchivoTXT, int col);
float calcularMedia(const char* nombreArchivoCSV, int columna);
void mostrarContenidoArchivo(const char* nombreArchivo);

// Arreglos para almacenar medias y valores ordenados
struct MediaCalculada mediasCalculadas[100];
struct ValorOrdenado valoresOrdenados[100];

//Funcion Principal
int main() {
    printf("<<<<WELCOME TO S T A T S M A R T>>>>\n");
    printf("\nA continuacion veras los valores de los registros obtenidos entre 2021 y 2022 de nuestras energias. Estan separadas en anos y meses.");
    printf("\n\nEstas energias son:");
    printf("\n1. Hidraulica");
    printf("\n2. Turbinacion de bombeo");
    printf("\n3. Nuclear");
    printf("\n4. Carbon");
    printf("\n5. Motores diesel");
    printf("\n6. Turbina de gas");
    printf("\n7. Turbina de vapor");
    printf("\n8. Ciclo combinado");
    printf("\n9. Hidreolica");
    printf("\n10. Eolica");
    printf("\n11. Solar fotovoltaica");
    printf("\n12. Otras renovables");
    printf("\n13. Cogeneracion");
    printf("\n14. Residuos no renovables");
    printf("\n15. Residuos renovables");
    printf("\n16. Generacion total");
    printf("\n\nA continuacion la tabla con los valores de esas energias...");
    printf("\n\nPresiona Enter para continuar...");
    while (getchar() != '\n');

    system("cls"); // Utiliza "cls" en Windows para limpiar la pantalla

    verTabla("generacion.csv"); // Mostrar la tabla de generación

    printf("\nPresiona Enter para continuar...");
    while (getchar() != '\n');
    system("cls"); 

    menuPrincipal();

    return 0;
}

//Función para ver los valores del fichero generacion
void verTabla(const char* generacion) {
    FILE* file = fopen(generacion, "r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Leer y mostrar la primera línea (encabezado de la tabla)
    if (fgets(line, sizeof(line), file) != NULL) {
        printf("%-16s", "Fechas");

        char* token = strtok(line, ",");
        while (token != NULL) {
            printf("%-16s", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    // Leer y mostrar el resto de las líneas (datos de la tabla)
    int fila = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        int col = 0;

        while (token != NULL) {
            if (col == 0) {
                printf("%d-%s\t", fila, token);  // Mostrar valor de la columna Fechas
                fila++;
            } else {
                printf("%-16s", token);  // Mostrar valor de las columnas de energía
            }

            token = strtok(NULL, ",");
            col++;
        }

        printf("\n");
    }

    fclose(file);
}

//Función menu principal aqui decides que quieres calcular
void menuPrincipal() {
    char opcion;
    int mes, year;
    const char* nombreArchivoCSV = "generacion.csv";
    do{
    printf("--- Menu Principal ---\n");
    printf("Opciones:\n");
    printf("a) Ordenadar de mayor a menor \n");
    printf("b) Media\n");
    printf("c) Salir del programa\n");

    printf("\nEscribe tu opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) {
        case 'a':
case 'A':
    system("cls");
    printf("Elija la fecha de la que quieres buscar datos entre los años 2021-2022:\n\n");
    printf("Introduzca el mes: ");

    do {
        scanf("%i", &mes);
        if (mes < 1 || mes > 12) {
            printf("Mes incorrecto, intenta de nuevo: ");
        }
    } while (mes < 1 || mes > 12);

    printf("Introduzca el ano: ");
    do {
        scanf("%i", &year);
        if (year != 2021 && year != 2022) {
            printf("El ano introducido no esta en nuestro registro de datos, intenta de nuevo: ");
        }
    } while (year != 2021 && year != 2022);
    getchar();
    system("cls");
    printf("\nLa fecha elegida es %i-%i\n", mes, year);

    columna = (year - 2021) * 12 + mes;

    ordenarmayoramenor(nombreArchivoCSV, "ordeno.txt", columna);

    break;

        case 'b':
        case 'B':
            system("cls");
            printf("Elija la fecha de la que quieres buscar datos entre los años 2021-2022:\n\n");
            printf("Introduzca el mes: ");

            do {
                scanf("%i", &mes);
                if (mes < 1 || mes > 12) {
                    printf("Mes incorrecto, intenta de nuevo: ");
                }
            } while (mes < 1 || mes > 12);

            printf("Introduzca el ano: ");
            do {
                scanf("%i", &year);
                if (year != 2021 && year != 2022) {
                    printf("El año introducido no está en nuestro registro de datos, intenta de nuevo: ");
                }
            } while (year != 2021 && year != 2022);
            getchar();
            system("cls");

            printf("\nA continuacion se muestra la media del mes %i y ano %i.\n\n", mes, year);

            int columna = (year - 2021) * 12 + mes;

            // Verificar si la media ya ha sido calculada previamente
            int mediaCalculada = 0;
            for (int i = 0; i < contadorMedias; i++) {
                if (mediasCalculadas[i].mes == mes && mediasCalculadas[i].year == year) {
                    printf("La media del mes %i y ano %i ya ha sido calculada %d veces: %.2f\n", mes, year, mediasCalculadas[i].contador, mediasCalculadas[i].valor);
                    mediaCalculada = 1;
                    break;
                }
            }

            if (!mediaCalculada) {
                // Cálculo de la media en base a la tabla generacion
                float media = calcularMedia(nombreArchivoCSV, columna);

                // Guardar la media en el arreglo mediasCalculadas
                mediasCalculadas[contadorMedias].mes = mes;
                mediasCalculadas[contadorMedias].year = year;
                mediasCalculadas[contadorMedias].valor = media;
                mediasCalculadas[contadorMedias].contador = 1;
                contadorMedias++;

                // Guardar la media en un archivo
                FILE* archivo = fopen("media.txt", "w");
                if (archivo != NULL) {
                    fprintf(archivo, "Media del mes %i y año %i: %.2f\n", mes, year, media);
                    fclose(archivo);
                    printf("La media se ha guardado.\n");
                } else {
                    printf("No se pudo abrir el archivo para guardar la media.\n");
                }

                printf("\nLa media del mes %i y año %i es: %.2f\n", mes, year, media);
            }

            printf("\nPulsa Enter para volver al Menu Principal.");
            getchar();  // Esperar la entrada del usuario
            system("cls");
            menuPrincipal();
            break;
            case 'c':
case 'C':
    system("cls");
    printf("VUELVA PRONTO.\nVALORES CALCULADOS:\n\n ");
    if (contadorMedias > 0) {
        printf("***Has calculado las siguientes medias:\n");
        for (int i = 0; i < contadorMedias; i++) {
            printf("Media del mes %i y ano %i: %.2f (calculada %d veces)\n", mediasCalculadas[i].mes, mediasCalculadas[i].year, mediasCalculadas[i].valor, mediasCalculadas[i].contador);
        }
    } else {
        printf("No has realizado ninguna media.\n");
    }
    printf("\n***Has ordenados estos valores:\n");
    mostrarContenidoArchivo("ordeno.txt");
    printf("\n\nSaliendo del programa...\n\n");
    printf("\nPulsa Enter para salir del programa.");
    getchar();
    exit(0);

        default:
            system("cls");
            printf("\nOpcion invalida. Intentalo de nuevo.\n");
            break;
    }
    }while (opcion != 'c' && opcion != 'C');
}

// Función para comparar dos datos en función de una columna específica
int comparardatos(const void *a, const void *b) {
    const Dato *datoA = (const Dato *)a;
    const Dato *datoB = (const Dato *)b;

    double numeroA = datoA->numeros[columna - 1];
    double numeroB = datoB->numeros[columna - 1];

    if (numeroA < numeroB) return 1;
    if (numeroA > numeroB) return -1;
    return 0;
}

//Funcion para ordenar los valores de mayor a menor dependiendo del mes y año introducido por teclado
void ordenarmayoramenor(const char *nombreArchivoCSV, const char *nombreArchivoTXT, int col) {
    FILE *archivoCSV = fopen(nombreArchivoCSV, "r");
    int columna = col;
    FILE *archivoTXT = fopen(nombreArchivoTXT, "w");

    if (archivoCSV == NULL || archivoTXT == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    Dato datos[N];
    char linea[MAX_LINE_LENGTH];
    int indice = 0;

    // Saltar las primeras 5 líneas (encabezados)
    for (int i = 0; i < 5; i++) {
        if (fgets(linea, sizeof(linea), archivoCSV) == NULL) {
            printf("Error al leer el archivo.\n");
            fclose(archivoCSV);
            fclose(archivoTXT);
            return;
        }
    }

    while (fgets(linea, sizeof(linea), archivoCSV) != NULL) {
        char *token = strtok(linea, ",");
        strncpy(datos[indice].energia, token, N);

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros[i] = atof(token);
        }

        indice++;
    }

    int numDatos = indice;
    columna = col;
    qsort(datos, numDatos, sizeof(Dato), comparardatos);

    printf("Energias del mes y ano especificados ordenadas de mayor a menor:\n\n");
    for (int i = 0; i < numDatos; i++) {
        printf("%s,%.2lf\n", datos[i].energia, datos[i].numeros[columna - 1]);
        fprintf(archivoTXT, "%s,%.2lf\n", datos[i].energia, datos[i].numeros[columna - 1]);
    }
    fclose(archivoCSV);
    fclose(archivoTXT);

    printf("\nSe han guardado los datos ordenados en el archivo.\n");
    printf("Pulsa Enter para volver al menú principal.");
    while (getchar() != '\n'); // Limpiar el buffer de entrada

    system("cls");
}

//Función para calcular la media del mes y año introducido por teclado
float calcularMedia(const char* nombreArchivoCSV, int columna) {
    FILE* file = fopen(nombreArchivoCSV, "r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 0.0;
    }

    char line[MAX_LINE_LENGTH];
    float suma = 0.0;
    int contador = 0;

    // Saltar las primeras dos líneas
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    // Leer los datos y calcular la media
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        int col = 0;

        while (token != NULL) {
            if (col == columna) {
                float valor = atof(token);
                suma += valor;
                contador++;
                break;
            }

            token = strtok(NULL, ",");
            col++;
        }
    }

    fclose(file);

    // Calcular la media
    float media = suma / contador;
    return media;
}

//Funcion para mostrar valores del fichero
void mostrarContenidoArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[MAX_LINE_LENGTH];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    fclose(archivo);
}
