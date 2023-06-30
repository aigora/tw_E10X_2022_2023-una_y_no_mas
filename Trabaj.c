#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define MAX_LINE_LENGTH 1000

void verTabla(const char* generacion);
void menuPrincipal();
float calcularMedia(const char* nombreArchivoCSV, int columna);

float mediaGuardada = 0.0;
int contadorMedias = 0;

// Estructura para almacenar una media junto con la fecha correspondiente
struct MediaCalculada {
    int mes;
    int year;
    float valor;
    int contador;
};

struct MediaCalculada mediasCalculadas[100]; // Arreglo para almacenar las medias calculadas

int main() {
    printf("<<<<WELCOME TO S T A T S M A R T>>>>\n");
    printf("\nA continuacion veras los valores de los registros obtenidos entre 2021 y 2022 de nuestras energias. Estan separadas en años y meses.");
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
    system("cls"); // Utiliza "cls" en Windows para limpiar la pantalla

    menuPrincipal();

    return 0;
}

void verTabla(const char* generacion) {
    FILE* file = fopen(generacion, "r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Imprimir encabezado de la tabla
    fgets(line, sizeof(line), file);
    printf("%-16s", "Energía");

    // Obtener los nombres de los meses
    char* token = strtok(line, ",");
    while (token != NULL) {
        printf("%-12s", token);
        token = strtok(NULL, ",");
    }

    printf("\n");

    // Imprimir separador de columnas
    fgets(line, sizeof(line), file);
    printf("%s\n", line);

    // Imprimir datos de la tabla
    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ",");
        while (token != NULL) {
            printf("%-12s", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(file);
}
void menuPrincipal() {
    char opcion;
    int mes, year;
    const char* nombreArchivoCSV = "generacion.csv";
    do{
    printf("\n--- Menu Principal ---\n");
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

            printf("Introduzca el año: ");
            do {
                scanf("%i", &year);
                if (year != 2021 && year != 2022) {
                    printf("El año introducido no está en nuestro registro de datos, intenta de nuevo: ");
                }
            } while (year != 2021 && year != 2022);

            system("cls");
            printf("\nLa fecha elegida es %i-%i\n", mes, year);

            // Aquí puedes implementar la lógica para ordenar de mayor a menor
            // los datos correspondientes a la fecha seleccionada
            // y mostrar los resultados
            printf("Funcionalidad no implementada.\n");
            printf("\nPulsa cualquier tecla para volver al menú principal.");
            getchar();
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

            printf("Introduzca el año: ");
            do {
                scanf("%i", &year);
                if (year != 2021 && year != 2022) {
                    printf("El año introducido no está en nuestro registro de datos, intenta de nuevo: ");
                }
            } while (year != 2021 && year != 2022);
            getchar();
            system("cls");

            printf("\nA continuacion se muestra la media del mes %i y año %i.\n\n", mes, year);

            int columna = (year - 2021) * 12 + mes;

            // Verificar si la media ya ha sido calculada previamente
            int mediaCalculada = 0;
            for (int i = 0; i < contadorMedias; i++) {
                if (mediasCalculadas[i].mes == mes && mediasCalculadas[i].year == year) {
                    printf("La media del mes %i y año %i ya ha sido calculada %d veces: %.2f\n", mes, year, mediasCalculadas[i].contador, mediasCalculadas[i].valor);
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

            printf("\nPulsa Enter para volver al menú principal.");
            getchar();  // Esperar la entrada del usuario
            system("cls"); // Utiliza "cls" en Windows para limpiar la pantalla
            menuPrincipal();
            break;

        case 'c':
        case 'C':
            printf("\nSaliendo del programa...\n");
            if (contadorMedias > 0) {
                printf("Has calculado las siguientes medias:\n");
                for (int i = 0; i < contadorMedias; i++) {
                    printf("Media del mes %i y año %i: %.2f (calculada %d veces)\n", mediasCalculadas[i].mes, mediasCalculadas[i].year, mediasCalculadas[i].valor, mediasCalculadas[i].contador);
                }
            } else {
                printf("No has realizado ninguna media.\n");
            }
            exit(0);

        default:
            system("cls");
            printf("\nOpción inválida. Inténtalo de nuevo.\n");
            break;
    }
    }while (opcion != 'c' && opcion != 'C');
}


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

