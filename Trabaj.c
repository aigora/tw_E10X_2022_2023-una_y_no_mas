#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define N 50

typedef struct {
    char energia[N];
    double numeros[24];
} Dato;

int columna = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void printTable(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Imprimir encabezado de la tabla
    fgets(line, sizeof(line), file);
    printf("%s", line);

    // Imprimir separador de columnas
    fgets(line, sizeof(line), file);
    printf("%s", line);

    // Imprimir datos de la tabla
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

int comparardatos(const void* a, const void* b) {
    const Dato* datoA = (const Dato*)a;
    const Dato* datoB = (const Dato*)b;

    if (datoA->numeros[columna - 1] > datoB->numeros[columna - 1]) {
        return -1;
    } else if (datoA->numeros[columna - 1] < datoB->numeros[columna - 1]) {
        return 1;
    } else {
        return 0;
    }
}

void ordenarmayoramenor(const char* nombreArchivoCSV, const char* nombreArchivoTXT, int col, int year, int mes) {
    FILE* archivoCSV = fopen(nombreArchivoCSV, "r");
    FILE* archivoTXT = fopen(nombreArchivoTXT, "w");

    if (archivoCSV == NULL || archivoTXT == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    Dato datos[N];
    char linea[N];
    int indice = 0;

    // Leer el archivo CSV y guardar los datos en un vector de datos
    while (fgets(linea, N, archivoCSV) != NULL) {
        char* token = strtok(linea, ",");
        strncpy(datos[indice].energia, token, N);

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros[i] = atof(token);
        }

        indice++;
    }

    int numDatos = indice;
    columna = col;

    // Filtrar los datos por año y mes
    Dato datosFiltrados[N];
    int numDatosFiltrados = 0;
    for (int i = 0; i < numDatos; i++) {
        int mesArchivo = (columna - 1) % 12;
        int yearArchivo = (columna - 1) / 12 + 2021;

        if (yearArchivo == year && mesArchivo == mes) {
            datosFiltrados[numDatosFiltrados] = datos[i];
            numDatosFiltrados++;
        }
    }

    // Ordenar los datos filtrados por número de mayor a menor
    qsort(datosFiltrados, numDatosFiltrados, sizeof(Dato), comparardatos);

    // Mostrar los datos ordenados en la salida estándar
    printf("Energías de ese año y mes ordenadas de mayor a menor:\n\n");
    for (int i = 0; i < numDatosFiltrados; i++) {
        printf("%s,%.2lf\n", datosFiltrados[i].energia, datosFiltrados[i].numeros[columna - 1]);
    }

    // Escribir los datos ordenados en el archivo de texto
    for (int i = 0; i < numDatosFiltrados; i++) {
        fprintf(archivoTXT, "%s,%.2lf\n", datosFiltrados[i].energia, datosFiltrados[i].numeros[columna - 1]);
    }

    fclose(archivoCSV);
    fclose(archivoTXT);
}

void menuPrincipal() {
    char opcion;
    int mes, year;
    const char* archivoCSV = "re.csv";
    const char* archivoTXT = "energiasmayoramenorporfechas.txt";
    printf("\n--- Menu Principal ---\n");
    printf("Opciones:\n");
    printf("a) Realizar acción A\n");
    printf("b) Realizar acción B\n");
    printf("c) Salir del programa\n");

    printf("\nEscribe tu opción: ");
    scanf(" %c", &opcion);
    clearInputBuffer();

    switch (opcion) {
        case 'a':
        case 'A':
            system("cls");
            printf("Has elegido consultar los datos por las fechas.\n");
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

            int columna = (year - 2021) * 12 + mes;

            printf("A continuación se muestra una lista de los datos en esta fecha %i-%i ordenados de mayor a menor.\n\n", mes, year);
            ordenarmayoramenor(archivoCSV, archivoTXT, columna, year, mes);
            printf("\nPulsa cualquier tecla para continuar.");
            getchar();
            fflush(stdin);
            system("cls");
            break;

        case 'b':
        case 'B':
            printf("\nRealizando Acción B...\n");
            // Codigo para la Acción B
            break;

        case 'c':
        case 'C':
            printf("\nSaliendo del programa...\n");
            exit(0);

        default:
            printf("\nOpción inválida. Inténtalo de nuevo.\n");
            break;
    }
}

int main() {
    printf("<<<<WELCOME TO S T A T S M A R T>>>>\n");
    printf("\nA continuación verás los valores de los registros obtenidos entre 2021 y 2022 de nuestras energías. Están separadas en años y meses.");
    printf("\n\nEstas energías son:");
    printf("\n1. Hidráulica");
    printf("\n2. Turbinación de bombeo");
    printf("\n3. Nuclear");
    printf("\n4. Carbón");
    printf("\n5. Motores diesel");
    printf("\n6. Turbina de gas");
    printf("\n7. Turbina de vapor");
    printf("\n8. Ciclo combinado");
    printf("\n9. Hidreolica");
    printf("\n10. Eólica");
    printf("\n11. Solar fotovoltaica");
    printf("\n12. Otras renovables");
    printf("\n13. Cogeneración");
    printf("\n14. Residuos no renovables");
    printf("\n15. Residuos renovables");
    printf("\n16. Generación total");
    printf("\n\nPresiona Enter para continuar...");
    while (getchar() != '\n');

    system("cls"); // Utiliza "cls" en Windows para limpiar la pantalla

    const char* filename = "generacion.csv"; // Reemplaza "archivo.csv" con la ruta y nombre de tu archivo CSV
    printTable(filename);

    printf("\nPresiona Enter para continuar...");
    while (getchar() != '\n');
    system("cls"); // Utiliza "cls" en Windows para limpiar la pantalla

    menuPrincipal();

    return 0;
}
