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
    printf("a) Ordenadar de mayor a menor las engerias\n");
    printf("b) Dependiendo de la energia: Hacer promedio o mes mas significativo de esa energia\n");
    printf("c) Salir del programa\n");

    printf("\nEscribe tu opcion: ");
    scanf(" %c", &opcion);

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

            printf("A continuación se muestra una lista de los datos en esta fecha %i-%i ordenados de mayor a menor.\n\n");
            printf("\nPulsa cualquier tecla para continuar.");
            getchar();
            fflush(stdin);
            system("cls");

            break;

        case 'b':
        case 'B':
            system("cls");
            printf("\nHas elegido calcular el valor más significativo o promedio de una energia.\n");
            printf("Elige una energía (1-16):\n");
            printf("1. Hidráulica\n");
            printf("2. Turbinación de bombeo\n");
            printf("3. Nuclear\n");
            printf("4. Carbón\n");
            printf("5. Motores diesel\n");
            printf("6. Turbina de gas\n");
            printf("7. Turbina de vapor\n");
            printf("8. Ciclo combinado\n");
            printf("9. Hidreolica\n");
            printf("10. Eólica\n");
            printf("11. Solar fotovoltaica\n");
            printf("12. Otras renovables\n");
            printf("13. Cogeneración\n");
            printf("14. Residuos no renovables\n");
            printf("15. Residuos renovables\n");
            printf("16. Generación total\n");

            int energia;
            scanf("%d", &energia);
            if (energia < 1 || energia > 16) {
                printf("Energía inválida. Inténtalo de nuevo.\n");
                break;
            }
            system("cls");
            int anio;
            do {
                printf("Elige el año:\n");
                printf("1. 2021\n");
                printf("2. 2022\n");
                scanf("%d", &anio);
                if (anio != 2021 && anio != 2022) {
                    printf("Año invalido. Intentalo de nuevo.\n");
                }
            } while (anio != 2021 && anio != 2022);
            system("cls");
            printf("Elige el tipo de calculo:\n");
            printf("1. Mes mas significativo\n");
            printf("2. Promedio\n");
            int tipoCalculo;
            scanf("%d", &tipoCalculo);
            if (tipoCalculo != 1 && tipoCalculo != 2) {
                printf("Tipo de calculo invalido. Intentalo de nuevo.\n");
                break;
            }
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
