#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

// Funci�n para limpiar el b�fer de entrada del teclado
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Funci�n para imprimir la tabla desde un archivo CSV
void printTable(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Imprimir cada l�nea del archivo
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

// Funci�n para mostrar el men� principal y realizar acciones basadas en la opci�n seleccionada
void menuPrincipal() {
    char opcion;

    printf("--- Men� Principal ---\n");
    printf("Opciones:\n");
    printf("a) Realizar acci�n A\n");
    printf("b) Realizar acci�n B\n");
    printf("c) Salir del programa\n");

    printf("\nEscribe tu opci�n: ");
    scanf(" %c", &opcion);
    clearInputBuffer();

    switch (opcion) {
        case 'a':
        case 'A':
            printf("Realizando Acci�n A...\n");
            // Aqu� puedes agregar el c�digo para la Acci�n A
            break;

        case 'b':
        case 'B':
            printf("Realizando Acci�n B...\n");
            // Aqu� puedes agregar el c�digo para la Acci�n B
            break;

        case 'c':
        case 'C':
            printf("Saliendo del programa...\n");
            exit(0);

        default:
            printf("Opci�n inv�lida. Int�ntalo de nuevo.\n");
            break;
    }
}

int main() {
    printf("<<<<WELCOME TO S T A T S M A R T>>>>\n");
    printf("\nA continucion vera los valores de los registros obtenidos entre 2021 y 2022 de nuestras energias.\nEstan separadas en a�os y meses.");
    printf("\n\nEstas energias son: ");
    printf("\n1.Hidraulica");
    printf("\n2.Turbinacion de bombeo");
    printf("\n3.Nuclear");
    printf("\n2.Carbon");
    printf("\n4.Motores diesel");
    printf("\n5.Turbina de gas");
    printf("\n6.Turbina de vapor");
    printf("\n7.Ciclo combinado");
    printf("\n8.Hidreolica");
    printf("\n9.Eolica");
    printf("\n10.Solar fotovoltaica");
    printf("\n11.Otras renovables");
    printf("\n12.Cogeneracion");
    printf("\n13.Residuos no renovables");
    printf("\n14.Residuos renovables");
    printf("\n15.Generacion total");
    printf("\\nPresiona Enter para continuar...");
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
