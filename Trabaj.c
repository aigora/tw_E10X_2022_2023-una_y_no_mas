#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define MAX_LINE_LENGTH 1000

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
    int mes,year;
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

            int columna = (year - 2021) * 12 + mes;

            printf("A continuación se muestra una lista de los datos en esta fecha %i-%i ordenados de mayor a menor.\n\n");
            printf("\nPulsa cualquier tecla para continuar.");
            getchar();
            fflush(stdin);
            system("cls");

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

            system("cls");
            printf("\nLa fecha elegida es %i-%i\n", mes, year);

            int columnaa = (year - 2021) * 12 + mes;

            printf("A continuación se muestra una lista de los datos en esta fecha %i-%i ordenados de mayor a menor.\n\n");
            printf("\nPulsa cualquier tecla para continuar.");
            getchar();
            fflush(stdin);
            system("cls");
            
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
