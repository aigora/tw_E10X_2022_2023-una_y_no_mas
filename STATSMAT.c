#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include <windows.h>
#define N 1000



void menu(char nombre[]);
void menu2(char nombre[]);
void energias(char nombre[]);
void menuenergias(char nombreenergia[], int energia,char nombre[]);
void imprimir_fichero_texto_antiguos();
void calculomediaporenergias(const char *nombreArchivoCSV, const char *nombreArchivo4TXT, int fil, int energia);
void yearymesdemasgasto(const char *nombreArchivoCSV, const char *nombreArchivo5TXT, int fil, int energia);
void ordenarmayoramenor(const char *nombreArchivoCSV, const char *nombreArchivoTXT, int col);
void masgasta(const char *nombreArchivoCSV, const char *nombreArchivo2TXT, int col);
void calculomedia(const char *nombreArchivoCSV, const char *nombreArchivo3TXT, int col);


int main(void){


     char nombre[30];
     printf("Bienvenido a STATSMAT.\nEsta aplicación está comprometida a brindarle servicios de estadística confiables y personalizados que impulsen su éxito.\n");
     printf("Para comenzar a usar esta aplicación, lo primero que necesitaríamos sería el nombre del usuario:\n");
     scanf("%29[^\n]", nombre);

     printf("\nPulsa el teclado para continuar.");
     getchar();
     fflush(stdin);
     system("cls");

     menu( nombre);
     return 0;
}



void imprimir_fichero_texto_antiguos() {
    // Lee los antiguos ficheros
    char *fichero_antiguos[] = {"calculomediaporenergias.txt","yearymesdemasgasto.txt","energiasmayoramenorporfechas.txt","energiasmayorporfechas.txt","calculomediaporfechas.txt"};
    int num_dato= sizeof(fichero_antiguos) / sizeof(fichero_antiguos[0]);
    int encontrado =0;
    for (int i = 0; i < num_dato; i++) {
        FILE *dato = fopen(fichero_antiguos[i], "r");
        if (dato) {
            printf("\nContenido anterior de %s:\n\n", fichero_antiguos[i]);

            char linea[10000];
            while (fgets(linea, sizeof(linea), dato) != NULL) {
                printf("%s", linea);
            }

            printf("\n\n\n\n\n");
            fclose(dato);
         } else if (strstr(fichero_antiguos[i], ".txt") != NULL) {
            printf("No se ha buscado informacion sobre %s todavía.\n", fichero_antiguos[i]);
        }
    }

    if (!encontrado) {
        printf("No se encontraron archivos .txt para mostrar.\n");
    }
}

typedef struct {
    char energia1[N];
    double numeros1[24];
} Dato1;
int fila;

void calculomediaporenergias(const char *nombreArchivoCSV, const char *nombreArchivo4TXT, int fil, int energia) {

    FILE *archivoCSV = fopen(nombreArchivoCSV, "r"); // Lee el archivo CSV
    FILE *archivo4TXT = fopen(nombreArchivo4TXT, "w"); // Escribe el archivo de texto resultante

    if (archivoCSV == NULL || archivo4TXT == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    Dato1 datos[N];
    char linea[N];
    int indice = 0;

    while (fgets(linea, N, archivoCSV) != NULL) {
        char *token = strtok(linea, ",");
        strncpy(datos[indice].energia1, token, N);

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros1[i] = atof(token);
        }

        indice++;
    }

    int numRegistros = indice;
    fila=fil;

    int fila;
fila = energia;

    if (fila < 1 || fila > numRegistros) {

        return 1;//verifica que el numero de fila es valido
    }

    double suma = 0.0;//almacena la suma de los numeros de la fila seleccionada

    for (int i = 0; i < 24; i++) {
        suma += datos[fila - 1].numeros1[i];

    }

    double media = suma / 24;//divide suma entre el numero de columnas

    printf("Media de la energía seleccionada durante los años 2021 y 2022: %.2lf\n GWh",media);
    fprintf(archivo4TXT, "Media de la energía seleccionada durante los años 2021 y 2022: %.2lf\n GWh",media);

    fclose(archivoCSV);
    fclose(archivo4TXT);

    return 0;
}
void yearymesdemasgasto(const char *nombreArchivoCSV, const char *nombreArchivo5TXT, int fil, int energia) {
    FILE *archivoCSV = fopen(nombreArchivoCSV, "r"); // Lee el archivo CSV
    FILE *archivo5TXT = fopen(nombreArchivo5TXT, "w"); // Escribe el archivo de texto resultante

    if (archivoCSV == NULL || archivo5TXT == NULL) {

        return 1;
    }

    Dato1 datos[N];
    char linea[N];
    int indice = 0;

    while (fgets(linea, N, archivoCSV) != NULL) {
        char *token = strtok(linea, ",");
        strncpy(datos[indice].energia1, token, N);

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros1[i] = atof(token);
        }

        indice++;
    }

    int numRegistros = indice;
    fila=fil;

    int fila;
    fila = energia;
//    printf("Ingrese el número de fila para comparar las columnas (1-%d): ", numRegistros);
//    scanf("%d", &fila);

    if (fila < 1 || fila > numRegistros) {

        return 1;
    }

    double maximo = datos[fila - 1].numeros1[0]; // Asignamos el primer valor de la fila como máximo
    int columnaMaxima = 1; // Almacenamos el índice de la columna con el máximo valor

    for (int i = 1; i < 24; i++) {
        if (datos[fila - 1].numeros1[i] > maximo) {
            maximo = datos[fila - 1].numeros1[i];
            columnaMaxima = i + 1; // Sumamos 1 para obtener el número de columna correspondiente
        }
    }
    if (columnaMaxima > 1 && columnaMaxima < 12) {
        printf("El dato mayor de la energía elegida es %.2lf, que corresponde a : %i-2021\n ", maximo, columnaMaxima);
    } else if (columnaMaxima > 12 && columnaMaxima < 24) {
        printf("El dato mayor de la energía elegida es %.2lf, que corresponde a : %i-2022\n ", maximo, columnaMaxima-12);
    }

  if (columnaMaxima > 1 && columnaMaxima < 12) {
        fprintf(archivo5TXT,"El dato mayor de la energía elegida es %.2lf, que corresponde a : %i-2021\n ", maximo, columnaMaxima);
    } else if (columnaMaxima > 12 && columnaMaxima < 24) {
        fprintf(archivo5TXT,"El dato mayor de la energía elegida es %.2lf, que corresponde a : %i-2022\n ", maximo, columnaMaxima-12);
    }



    fclose(archivoCSV);
    fclose(archivo5TXT);

    return 0;
}

void menuenergias(char nombreenergia[], int energia, char nombre[]){
    char opcion;
    const char *nombreArchivoCSV = "re.csv";
    const char *nombreArchivo4TXT = "calculomediaporenergias.txt";
    const char *nombreArchivo5TXT = "yearymesdemasgasto.txt";
    printf("Pulsa el número de lo que desee buscar:\n\na)Información sobre esta %s\nb)Hacer la media de todos los datos obtenidos de %s\nc)Año con más gasto\nd)Salir",nombreenergia,nombreenergia);
    do {
        scanf(" %c", &opcion);
        if (opcion != 'a' && opcion != 'b' && opcion != 'c' && opcion != 'd') {
            printf("Escribe una de las letras indicadas, por favor.\n");
        }
        while (getchar() != '\n');
    }
    while (opcion != 'a' && opcion != 'b' && opcion != 'c' && opcion != 'd');// no sale del bucle hasta que no ponga la letra indicada

    switch (opcion) {

        case 'a':
            system("cls");
            printf("Has elegido consultar información sobre la energía %s.\n",nombreenergia);

                if (strcmp(nombreenergia, "Hidráulica") == 0){
            printf("La energía hidráulica es una forma de energía renovable que se obtiene del movimiento del agua, aprovechando su caudal y altura \n");
            printf("Se utiliza a través de la construcción de presas y embalses, donde la energía potencial del agua almacenada se convierte en energía cinética al ser liberada y hacer girar turbinas hidráulicas \n");
            printf(" Esta energía se transforma en electricidad mediante generadores acoplados a las turbinas. \n");
            printf("La energía hidráulica es una fuente limpia y sostenible, ya que el agua es un recurso natural abundante y no se emiten gases de efecto invernadero durante su producción, lo que contribuye a la reducción de la contaminación y el impacto ambiental. \n");
                }
               else if (strcmp(nombreenergia, "Turbinación bombeo") == 0){
            //TURBINACIÓN BOMBEO
            printf("La energía de turbinación de bombeo es un método de almacenamiento de energía que implica utilizar dos embalses de agua a diferentes alturas.\n");
            printf("Durante los períodos de baja demanda energética, el exceso de electricidad se utiliza para bombear agua desde un embalse inferior al embalse superior. \n");
            printf("Luego, cuando se necesita energía adicional, el agua se deja fluir hacia abajo a través de turbinas, generando electricidad mediante la conversión de la energía cinética del agua en energía eléctrica.\n");
            printf("Este proceso permite almacenar energía cuando hay un exceso y liberarla cuando se requiere, proporcionando una solución eficiente para el equilibrio de la demanda y la oferta de electricidad en el sistema de energía. \n");
            printf("Además, puede ayudar a integrar energías renovables intermitentes en la red eléctrica. \n");
                }
                else if (strcmp(nombreenergia, "Nuclear") == 0){
            //NUCLEAR
            printf("La energía nuclear es una forma de energía que se obtiene mediante reacciones nucleares, específicamente la fisión o fusión de átomos. \n");
            printf("En la fisión nuclear, los núcleos de átomos pesados, como el uranio, se dividen en fragmentos más pequeños, liberando una gran cantidad de energía en forma de calor./n");
            printf("Esta energía se utiliza para generar vapor y accionar turbinas, produciendo electricidad en centrales nucleares. Aunque la energía nuclear es una fuente potente y eficiente, también plantea desafíos en términos de seguridad, gestión de residuos radiactivos y proliferación nuclear. \n");
            printf("Además, existen preocupaciones sobre el impacto ambiental y los riesgos asociados a los accidentes nucleares. \n");
                }
                else if (strcmp(nombreenergia, "Carbón") == 0){
            //CARBÓN
            printf("La energía del carbón es una forma de energía obtenida mediante la quema de carbón mineral. \n");
            printf("Este proceso libera energía térmica que se utiliza para generar vapor y accionar turbinas, produciendo electricidad en centrales térmicas de carbón.\n");
            printf("El carbón ha sido una fuente de energía tradicional y ampliamente utilizada debido a su abundancia y bajo costo.\n");
            printf("Sin embargo, la combustión del carbón también conlleva desafíos ambientales, como la emisión de grandes cantidades de dióxido de carbono y otros contaminantes atmosféricos, lo que contribuye al cambio climático y la contaminación del aire. \n");
            printf("A medida que se busca reducir las emisiones de gases de efecto invernadero, se está impulsando la transición hacia fuentes de energía más limpias y sostenibles. \n");
                }
                else if (strcmp(nombreenergia, "Motores diésel") == 0){
            //MOTORES DIESEL
            printf("Los motores diésel son motores de combustión interna que funcionan según el ciclo diésel.\n");
            printf("Utilizan la compresión del aire en el cilindro para encender el combustible diésel, en lugar de utilizar una chispa como en los motores de gasolina. \n");
            printf(" Estos motores son conocidos por su eficiencia y durabilidad, lo que los hace populares en aplicaciones que requieren un alto torque, como vehículos pesados, barcos y generadores.\n");
            printf("Sin embargo, los motores diésel también emiten más partículas y óxidos de nitrógeno en comparación con los motores de gasolina, lo que ha llevado a regulaciones más estrictas para controlar su impacto ambiental. \n");
            printf("En los últimos años, ha habido un creciente interés en desarrollar y adoptar tecnologías diésel más limpias, como filtros de partículas y sistemas de reducción catalítica selectiva.\n");
                }
                else if (strcmp(nombreenergia, "Turbina de gas") == 0){
            //TURBINA DE GAS
            printf("La energía de turbina de gas es una forma de generación de electricidad que utiliza la combustión de gas natural o combustibles líquidos en una turbina de gas.\n");
            printf("En este proceso, el aire se comprime y se mezcla con el combustible, generando una explosión controlada que impulsa las palas de la turbina.\n");
            printf("La energía cinética resultante se convierte en electricidad a través de un generador acoplado a la turbina.\n");
            printf("La energía de turbina de gas es conocida por su alta eficiencia, respuesta rápida y menor emisión de contaminantes en comparación con otras tecnologías de generación de electricidad basadas en combustibles fósiles.\n");
            printf("Además, los ciclos combinados, que combinan la turbina de gas con una caldera de vapor, pueden mejorar aún más la eficiencia del sistema.\n");
                }
                else if (strcmp(nombreenergia, "Turbina de vapor") == 0){
            //TURBINA DE VAPOR
            printf("La energía de turbina de vapor es una forma de generación de electricidad que utiliza el vapor de agua como medio para impulsar una turbina.\n");
            printf("En este proceso, el agua se calienta y se convierte en vapor en una caldera mediante la combustión de combustibles fósiles, biomasa o energía nuclear. \n");
            printf("El vapor de alta presión se dirige a través de la turbina, haciendo girar las palas y generando energía mecánica. \n");
            printf("Luego, esta energía se convierte en electricidad mediante un generador acoplado a la turbina.\n");
            printf("La energía de turbina de vapor es ampliamente utilizada debido a su eficiencia, flexibilidad y capacidad para operar con diferentes tipos de combustibles.\n");
            printf("Además, puede integrarse con tecnologías de captura de carbono para reducir las emisiones de gases de efecto invernadero.\n");
            }
            else if (strcmp(nombreenergia, "Ciclo combinado") == 0){
            //CICLO COMBINADO
            printf("La energía del ciclo combinado es un tipo de generación de electricidad que combina la tecnología de la turbina de gas y la turbina de vapor en un sistema integrado.\n");
            printf("En este proceso, el combustible, como gas natural, se quema en una turbina de gas para generar energía mecánica.\n");
            printf("Luego, los gases de escape calientes de la turbina de gas se utilizan para producir vapor en una caldera, que impulsa una turbina de vapor adicional para generar electricidad adicional. \n");
            printf("Este enfoque aumenta la eficiencia general del sistema al aprovechar el calor residual de la turbina de gas.\n");
            printf("Los ciclos combinados son valorados por su alta eficiencia, menor emisión de contaminantes y capacidad de respuesta rápida a la demanda de energía.\n");
            }
            else if (strcmp(nombreenergia, "Eolica") == 0){
            //EOLICA
            printf("La energía eólica es una forma de energía renovable que se obtiene del viento. \n");
            printf("Se utiliza mediante la instalación de aerogeneradores que capturan la energía cinética del viento y la convierten en energía eléctrica.\n");
            printf("Estos aerogeneradores constan de aspas giratorias conectadas a un generador que produce electricidad. \n");
            printf("La energía eólica es una fuente limpia y sostenible, ya que no produce emisiones de gases de efecto invernadero ni contamina el aire o el agua. \n");
            printf("Además, es una fuente de energía abundante y renovable, ya que el viento es un recurso natural inagotable. \n");
            printf("La energía eólica desempeña un papel importante en la transición hacia una matriz energética más limpia y en la reducción de la dependencia de los combustibles fósiles.\n");
            }
            else if (strcmp(nombreenergia, "Solar fotovoltaica") == 0){
            //SOLAR FOTOVOLTAICA
            printf("La energía solar fotovoltaica es una forma de energía renovable que se obtiene directamente del sol mediante la conversión de la luz solar en electricidad.\n");
            printf("Utiliza paneles solares compuestos por células fotovoltaicas que absorben la radiación solar y generan corriente eléctrica. \n");
            printf("Estas células están compuestas principalmente de silicio y, al recibir la luz solar, generan un flujo de electrones que produce electricidad de corriente continua (DC). \n");
            printf("Esta electricidad se convierte en corriente alterna (AC) mediante un inversor y puede utilizarse para alimentar equipos eléctricos y abastecer redes eléctricas. \n");
            printf("La energía solar fotovoltaica es una fuente limpia, sostenible y silenciosa, que no emite gases de efecto invernadero ni produce contaminantes durante su operación.\n");
            printf("Además, los avances tecnológicos han reducido los costos y aumentado la eficiencia de los paneles solares, lo que ha impulsado su adopción en todo el mundo.\n");
            }
            else if (strcmp(nombreenergia, "Solar Térmica") == 0){
            //SOLAR TÉRMICA
            printf("La energía solar térmica es una forma de energía renovable que aprovecha el calor del sol para generar calor o agua caliente. Se utiliza a través de colectores solares que capturan la radiación solar y la convierten en calor.\n");
            printf("Este calor se utiliza para calentar agua, tanto para uso doméstico como industrial, o para generar vapor que impulsa turbinas para generar electricidad. \n");
            printf("La energía solar térmica es una opción eficiente y limpia para reducir el consumo de combustibles fósiles en aplicaciones de calefacción y agua caliente.\n");
            printf("Además, puede integrarse con sistemas de almacenamiento térmico para utilizar el calor generado incluso en momentos de poca radiación solar.\n");
            }
            else if (strcmp(nombreenergia, "Otras renovables") == 0){
            //OTRAS RENOVABLES
            printf("Hay otras formas de energías renovables que no hemos mencionado. \n");
            printf("La energía hidroeléctrica aprovecha la fuerza del agua en movimiento para generar electricidad a través de turbinas hidráulicas. \n");
            printf("La biomasa utiliza materia orgánica, como residuos agrícolas o forestales, para generar calor o electricidad. \n");
            printf("La energía geotérmica se basa en el calor natural del interior de la Tierra para generar electricidad o proporcionar calefacción.\n");
            printf("Por último, la energía de las olas y las mareas aprovecha el movimiento de las olas y el flujo de las mareas para generar electricidad mediante tecnologías específicas.\n");
            printf("Estas fuentes renovables diversifican el mix energético y contribuyen a la transición hacia un sistema más sostenible y menos dependiente de los combustibles fósiles.\n");
            }
            else if (strcmp(nombreenergia, "Cogeneración") == 0){
            //COGENERACIÓN
            printf("La energía de cogeneración, también conocida como producción combinada de calor y energía (CHP, por sus siglas en inglés), es un proceso eficiente que permite generar simultáneamente electricidad y calor útil a partir de una fuente de energía primaria, como gas natural, biomasa o residuos.\n");
            printf(" En este proceso, el calor residual producido durante la generación de electricidad se recupera y se utiliza para calefacción, agua caliente o procesos industriales, maximizando el rendimiento energético.\n");
            printf("La cogeneración ofrece beneficios significativos, como la reducción de emisiones de gases de efecto invernadero, el aumento de la eficiencia energética y la mejora de la autonomía energética de instalaciones industriales, hospitales o complejos residenciales. \n");
            printf("Además, puede integrarse con sistemas de almacenamiento de energía para una mayor flexibilidad y resiliencia.\n");
            }
            else if (strcmp(nombreenergia, "Residuos no renovables") == 0){
            //RESIDIUS NO RENOVABLES
            printf("Las energías no renovables son aquellas que provienen de fuentes agotables y no se regeneran a una velocidad significativa.\n");
            printf("Los combustibles fósiles, como el petróleo, el gas natural y el carbón, son ejemplos de fuentes no renovables.\n");
            printf("Estas energías se formaron a lo largo de millones de años a partir de materia orgánica y su uso intensivo ha llevado a la emisión de grandes cantidades de gases de efecto invernadero y la degradación del medio ambiente. \n");
            printf("La energía nuclear también se considera no renovable, ya que depende de la fisión nuclear de átomos de uranio o plutonio, recursos limitados y sujetos a preocupaciones de seguridad y gestión de residuos. \n");
            printf("La transición hacia fuentes de energía renovable es fundamental para reducir la dependencia de las energías no renovables y mitigar los impactos ambientales asociados.\n");
            }
            else if (strcmp(nombreenergia, "Residuos renovables") == 0){
            //RESIDIUS RENOVABLES
            printf("La energía renovable es aquella que se obtiene de fuentes naturales que son inagotables o se regeneran rápidamente. \n");
            printf("stas fuentes de energía no generan emisiones de gases de efecto invernadero y contribuyen a la reducción del cambio climático. \n");
            printf("Además, son sostenibles a largo plazo y ayudan a diversificar la matriz energética, reduciendo la dependencia de los combustibles fósiles. \n");
            printf("La adopción de energías renovables fomenta la creación de empleos verdes, impulsa la innovación tecnológica y promueve la seguridad energética.\n");
            printf("Su desarrollo y utilización son fundamentales para una transición hacia un futuro más limpio y sostenible.\n");
            }
             else if (strcmp(nombreenergia, "Hidroeolica") == 0){
             printf("La energía hidroeléctrica es una forma de energía renovable que se obtiene mediante la combinación de energía hidráulica y eólica \n");
            printf("Se aprovecha el movimiento del agua en ríos o embalses para accionar turbinas, generando electricidad.\n ");
            printf("Este sistema combina la confiabilidad y constancia de los flujos de agua con la variabilidad y disponibilidad del viento.");
            printf("Es una fuente de energía limpia, no emite gases de efecto invernadero y contribuye a la reducción de la dependencia de combustibles fósiles.\n");
            printf("Sin embargo, su implementación requiere considerar impactos ambientales y sociales, así como la disponibilidad de recursos hídricos y eólicos.\n");
            }
            printf("\nPulsa el teclado para continuar.");
            getchar();
            fflush(stdin);
            system("cls");
            return menu(nombre);
            break;

        case 'b':
            system("cls");
            printf("Has elegido hacer la media de todos los datos obtenidos.\n");
            calculomediaporenergias(nombreArchivoCSV, nombreArchivo4TXT, fila, energia);
            printf("\nPulsa el teclado para continuar.");
            getchar();
            fflush(stdin);
            system("cls");
            return menu(nombre);

            break;

        case 'c':
            system("cls");
            printf("Has elegido buscar el año y mes con más gasto\n");
            yearymesdemasgasto(nombreArchivoCSV, nombreArchivo5TXT, fila,energia);
            printf("\nPulsa el teclado para continuar.");
            getchar();
            fflush(stdin);
            system("cls");
            return menu(nombre);

            break;


        case 'd':
            system("cls");
            printf("Vuelva pronto a consultar nuestros datos.\n");
            return 0;
            break;

    }
}

void energias(char nombre[]){
    int energia;
    char nombreenergia[20];

     printf("Elige el tipo de energía del que quieras buscar información:\n");
     printf("Te ofrecemos una lista de las energías:\n\n1)Hidráulica\n2)Turbinación bombeo\n3)Nuclear\n4)Carbón\n5)Motores diésel\n6)Turbina de gas\n");
     printf("7)Turbina de vapor\n8)Ciclo combinado\n 9)Hidroeolica\n10)Eolica\n11)Solar fotovoltaica\n12)Solar térmica\n13)Otras renovables\n14)Cogeneración\n15)Residuos no renovables\n16)Residuos renovables\n");
     scanf("%i",&energia);
     switch (energia){

     case 1:
        system("cls");
        strcpy(nombreenergia, "Hidráulica");
        printf("Ha elegido la energía Hidráulica.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 2:
        system("cls");
        strcpy(nombreenergia, "Turbinación bombeo");
        printf("Ha elegido la energía Turbinación bombeo.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 3:
        system("cls");
        strcpy(nombreenergia, "Nuclear");
        printf("Ha elegido la energía Nuclear.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 4:
        system("cls");
        strcpy(nombreenergia, "Carbón");
        printf("Ha elegido la energía Carbón.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 5:
        system("cls");
        strcpy(nombreenergia, "Motores diésel");
        printf("Ha elegido la energía Motores diésel.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 6:
        system("cls");
        strcpy(nombreenergia, "Turbina de gas");
        printf("Ha elegido la energía Turbina de gas.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 7:
        system("cls");
        strcpy(nombreenergia, "Turbina de vapor");
        printf("Ha elegido la energía Turbina de vapor.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 8:
        system("cls");
        strcpy(nombreenergia, "Ciclo combinado");
        printf("Ha elegido la energía Ciclo combinado.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 9:
        system("cls");
        strcpy(nombreenergia, "Hidroeolica");
        printf("Ha elegido la energía Hidroeolica.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 10:
        system("cls");
        strcpy(nombreenergia, "Eolica");
        printf("Ha elegido la energía Eolica.");
        menuenergias(nombreenergia,energia, nombre);
        break;
     case 11:
        system("cls");
        strcpy(nombreenergia, "Solar fotovoltaica");
        printf("Ha elegido la energía Solar fotovoltaica.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 12:
        system("cls");
        strcpy(nombreenergia, "Solar Térmica");
        printf("Ha elegido la energía Solar térmica.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 13:
        system("cls");
        strcpy(nombreenergia, "Otras renovables");
        printf("Ha elegido la energía Otras renovables.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 14:
        system("cls");
        strcpy(nombreenergia, "Cogeneración");
        printf("Ha elegido la energía Cogeneración.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 15:
        system("cls");
        strcpy(nombreenergia, "Residuos no renovables");
        printf("Ha elegido la energía Residuos no renovables.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     case 16:
        system("cls");
        strcpy(nombreenergia, "Residuos renovables");
        printf("Ha elegido la energía Residuos renovables.");
        menuenergias(nombreenergia,energia,nombre);
        break;
     default:
        printf("Opción inválida.\n");
        break;





     }
}

typedef struct {
    char energia[N];//cadena de caracteres
    double numeros[24];  // vector de números para las 24 columnas
} Dato;//estructura llamada datos, que contiene dos campos: nombre y numero

  int columna;  // Variable global para almacenar la columna a ordenar

int comparardatos(const void *a, const void *b) {//la utiliza la funcion qsort para ordenar los datos
    const Dato *datoA = (const Dato *)a;//punteros a datos
    const Dato *datoB = (const Dato*)b;

    double numeroA = datoA->numeros[columna - 1];//se obtienen valores numericos de la columna especificada
    double numeroB = datoB->numeros[columna - 1];

    if (numeroA < numeroB) return 1;//si el valor del dato a es menor q el del dato b devuelve 1
    if (numeroA > numeroB) return -1;
    return 0;
}

//la siguiente funcion se encarga de abrir los archivos, leer los registros del csv y ordenarlos por la columna especificada
void ordenarmayoramenor(const char *nombreArchivoCSV, const char *nombreArchivoTXT, int col) {
    FILE *archivoCSV = fopen(nombreArchivoCSV, "r");//lee el csv
    FILE *archivoTXT = fopen(nombreArchivoTXT, "w");//escribe el .txt resultante

    if (archivoCSV == NULL || archivoTXT == NULL) {
        printf("Error al abrir los archivos.\n");;//por si alguno de los archivos no se puede abrir
        return;
    }

    Dato datos[N];//vector de la estructura registro que se utiliza para almacenar lo leido en el .csv
    char linea[N];//almacena temporalmente lo leidoen una linea
    int indice = 0;//realiza el seguimiento del numero de datos leidos en .csv

    // Leer el archivo CSV y guardar los datos en un vector de datos
    while (fgets(linea, N, archivoCSV) != NULL) {//fgets lee una linea completa del .csv lo almacena en el vector linea, y si no es nula sigue
        char *token = strtok(linea, ",");//la funcion strtok nos divide la linea en tokens separados por comas
        strncpy(datos[indice].energia, token, N);//el primer token corresponde a energia y se copia en el campo energia

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros[i] = atof(token);//recorre las 24 columnas y convierten los tokens siguientes en numeros y se almacenan en la variable numeros
        }

        indice++;//se incrementa para leer mas datos
    }

    int numDatos = indice;//guarda el numero total en una variable
    // Asignar la columna especificada
    columna = col;
    // Ordenar los datos por número de mayor a menor
    qsort(datos, numDatos, sizeof(Dato), comparardatos);

    // Mostrar los datos ordenados en la salida estándar
    printf("Energías de ese año ordenadas de mayor a menor:\n\n");
    for (int i = 0; i < numDatos; i++) {
        printf("%s,%.2lf\n", datos[i].energia, datos[i].numeros[columna - 1]);
    }
    // Escribir los datos ordenados en el archivo de texto
    for (int i = 0; i < numDatos; i++) {
        fprintf(archivoTXT, "%s,%.2lf\n", datos[i].energia, datos[i].numeros[columna - 1]);
    }

    fclose(archivoCSV);
    fclose(archivoTXT);
}


void masgasta(const char *nombreArchivoCSV, const char *nombreArchivo2TXT, int col) {
    FILE *archivoCSV = fopen(nombreArchivoCSV, "r");//lee el csv
    FILE *archivo2TXT = fopen(nombreArchivo2TXT, "w");//escribe el .txt resultante

    if (archivoCSV == NULL || archivo2TXT == NULL) {
        printf("Error al abrir los archivos.\n");;//por si alguno de los archivos no se puede abrir
        return;
    }

    Dato datos[N];//vector de la estructura registro que se utiliza para almacenar lo leido en el .csv
    char linea[N];//almacena temporalmente lo leidoen una linea
    int indice = 0;//realiza el seguimiento del numero de datos leidos en .csv

    // Leer el archivo CSV y guardar los datos en un vector de datos
    while (fgets(linea, N, archivoCSV) != NULL) {//fgets lee una linea completa del .csv lo almacena en el vector linea, y si no es nula sigue
        char *token = strtok(linea, ",");//la funcion strtok nos divide la linea en tokens separados por comas
        strncpy(datos[indice].energia, token, N);//el primer token corresponde a energia y se copia en el campo energia

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros[i] = atof(token);//recorre las 24 columnas y convierten los tokens siguientes en numeros y se almacenan en la variable numeros
        }

        indice++;//se incrementa para leer mas datos
    }

    int numDatos = indice;//guarda el numero total en una variable

    // Asignar la columna especificada
    columna = col;

    // Ordenar los datos por número de mayor a menor
    qsort(datos, numDatos, sizeof(Dato), comparardatos);

    // Mostrar los datos en la salida estándar
    printf("Este es la energía mas gastada de ese año:\n\n");

    printf("%s,%.2lf\n", datos[1].energia, datos[1].numeros[columna - 1]);

   //Mostrar los datos en el .txt
    fprintf(archivo2TXT, "Esta es la energía más gastada de ese año:\n\n");
    fprintf(archivo2TXT, "%s,%.2lf\n", datos[0].energia, datos[0].numeros[col - 1]);

    fclose(archivoCSV);
    fclose(archivo2TXT);
}


void calculomedia(const char *nombreArchivoCSV, const char *nombreArchivo3TXT, int col) {
    FILE *archivoCSV = fopen(nombreArchivoCSV, "r"); // Lee el archivo CSV
    FILE *archivo3TXT = fopen(nombreArchivo3TXT, "w"); // Escribe el archivo de texto resultante

    if (archivoCSV == NULL || archivo3TXT == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1; // Por si alguno de los archivos no se puede abrir
    }
    Dato datos[N]; // Vector de la estructura Dato que se utiliza para almacenar lo leído en el archivo .csv
    char linea[N]; // Almacena temporalmente lo leído en una línea
    int indice = 0; // Realiza el seguimiento del número de registros leídos en el archivo .csv

    while (fgets(linea, N, archivoCSV) != NULL) { // fgets lee una línea completa del archivo .csv, la almacena en el vector linea y, si no es nula, sigue
        char *token = strtok(linea, ","); // La función strtok divide la línea en tokens separados por comas
        strncpy(datos[indice].energia, token, N); // El primer token corresponde al energia y se copia en el campo energia

        for (int i = 0; i < 24; i++) {
            token = strtok(NULL, ",");
            datos[indice].numeros[i] = atof(token); // Recorre las 24 columnas y convierte los tokens siguientes en números y los almacena en la variable numeros
        }

        indice++; // Se incrementa para leer más datos
    }

    int numDatos = indice; // Guarda el número total en una variable
    columna = col;

    // Calcular la media de los datos en la columna seleccionada, excepto la última fila
    double suma = 0.0;
    for (int i = 0; i < numDatos - 1; i++) {
        suma += datos[i].numeros[columna - 1];
    }
    double media = suma / (numDatos - 1);

    // Mostrar la media en la salida del compilador
    printf("Media de las energías de ese año : %.2lf\n", media);

    // Escribir la media en el archivo de texto
    fprintf(archivo3TXT, "Media de las energías de ese año : %.2lf\n", media);

    fclose(archivoCSV);
    fclose(archivo3TXT);

    return 0;
}


void menu2(char nombre[]) {

    char opcion,opcion2;
    int mes, year, year2,k;
    const char* archivoCSV = "re.csv";
    const char* archivoTXT = "energiasmayoramenorporfechas.txt";
    const char* archivo2TXT = "energiasmayorporfechas.txt";
    const char *nombreArchivoCSV = "re.csv";
    const char *nombreArchivo3TXT = "calculomediaporfechas.txt";
    int columna = 4;
    printf("Elige de qué forma quieres comparar los datos:\n\n");
    printf("a) Por fecha\nb) Por tipo de energía\nc) Salir\n");

    do {
        scanf(" %c", &opcion);
        if (opcion != 'a' && opcion != 'b' && opcion != 'c' && opcion != 'd') {
            printf("Escribe una de las letras indicadas, por favor.\n\n");
        }
        while (getchar() != '\n');
    }
    while (opcion != 'a' && opcion != 'b' && opcion != 'c' && opcion != 'd');// no sale del bucle hasta que no ponga la letra indicada

    switch (opcion) {

        case 'a':
            system("cls");
            printf("Has elegido consultar los datos por las fechas.\n");
            printf("Elija la fecha de la que quiere buscar datos entre los años 2021-2022:\n\n");
            printf("Introduzca el mes\n");

            do {
             scanf("%i",&mes);
             if(mes<0 || mes>13)
                {
                 printf("\nMes incorrecto, intentelo de nuevo.\n");
                }

              } while (mes<0 || mes>13);

            printf("Introduzca el año\n");
            do{
             scanf("%i",&year);
             if( year != 2021 && year != 2022)
                {
                 printf("El año introducido no esta en nuestro registro de datos, intentelo de nuevo\n");
                }

              } while( year != 2021 && year != 2022);

             system("cls");
             printf("\nLa fecha elegida es %i-%i\n", mes, year);

             if(year == 2021)
                {
                  k=0;
                }
             else if (year == 2022)
                {
                  k=12;
                }
                columna= k + mes;

                printf("\nQue desea saber de esta fecha:\n\nA)Ordenar los datos de mayor a menor.\n\nB)Media de todos los datos de esa fecha.\n\nC)Mostrar que energía gasto más en esa fecha.\n\nD)Salir\n");
                 do {
                 scanf(" %c", &opcion2);
                 if (opcion2 != 'A' && opcion2 != 'B' && opcion2 != 'C' && opcion2 != 'D') {
                 printf("Escribe una de las letras indicadas, por favor. Quizas no la este poniendo en mayuscula.\n");
                   }
                   while (getchar() != '\n');
                   }
                   while (opcion2 != 'A' && opcion2 != 'B' && opcion2 != 'C' && opcion2 != 'D');// no sale del bucle hasta que no ponga la letra indicada
                   switch (opcion2) {

                       case 'A':
                           system("cls");
                           printf("A continuación le mostramos una lista de los datos en esta fecha %i-%i ordenados de mayor a menor.\n\n",mes, year);
                           ordenarmayoramenor(archivoCSV,archivoTXT,columna);
                           printf("\nPulsa el teclado para continuar.");
                           getchar();
                           fflush(stdin);
                           system("cls");
                           return menu(nombre);
                       break;
                       case 'B':
                           system("cls");
                           printf("A contunación le mostraremos la media de los datos en esta fecha %i-%i.\n\n",mes,year);
                           calculomedia(nombreArchivoCSV, nombreArchivo3TXT, columna);
                           printf("\nPulsa el teclado para continuar.");
                           getchar();
                           fflush(stdin);
                           system("cls");
                           return menu(nombre);

                           break;
                       case 'C':
                           system("cls");
                           printf("A continuación le mostraremos la energía que más gasta en esta fecha %i-%i\n\n",mes,year);
                           masgasta(archivoCSV,archivo2TXT,columna);
                           printf("\nPulsa el teclado para continuar.");
                           getchar();
                           fflush(stdin);
                           system("cls");
                           return menu(nombre);
                           break;
                        case 'D':
                           system("cls");
                           printf("\nVuelva pronto a consultar nuestros datos.\n");
                           return 0;
                           break;
                   }
            break;

        case 'b':
            system("cls");
            printf("Has elegido consultar los datos por el tipo de energía.\n");
            energias(nombre);
            break;

        case 'c':
            system("cls");
            printf("Vuelva pronto a consultar nuestros datos.\n");
            return 0;
            break;

    }
}


void menu(char nombre[]) {
    int aux;

    system("cls");
    printf("A continuación elija lo que desea hacer, %s (Pulse el número deseado):\n\n", nombre);
    printf("1.- GWh consumidos\n");
    printf("2.- Ver usuarios anteriores\n");
    printf("3.- Ultimos datos buscados\n");
    printf("Pulsa 0 si quieres salir\n");

do {
        while (scanf("%i", &aux) != 1 || (aux != 0 && aux != 1 && aux != 2 && aux !=3))
            {
            while (getchar() != '\n');
            printf("Elige un número entre 1, 2 y 3, por favor.\n");
            system("pause");
            }

        while (getchar() != '\n');

        if (aux == 0){

            system("cls");
            printf("Vuelve cuando quieras, esperamos haberle ayudado.\n");
            return 0;
            }


        else if (aux == 1) {
            system("cls");
            printf("Has elegido buscar datos sobre GWh.\n");
            printf("\nPulsa el teclado para continuar.");
            getchar();
            fflush(stdin);
            system("cls");
            menu2(nombre);
            }
     else if (aux == 2) {
             system("cls");
            printf("Ver usuarios anteriores.\n");
                  // Leer el archivo de registro de usuarios
                FILE *archivo = fopen("usuarios.txt", "a+");

                // Mostrar los nombres de usuarios previamente utilizados
                printf("Usuarios previos:\n");
                rewind(archivo); // Volver al inicio del archivo
                char linea[30];
                while (fgets(linea, sizeof(linea), archivo) != NULL) {
                linea[strcspn(linea, "\n")] = '\0'; // Eliminar el salto de línea del final
                printf("%s\n", linea);
                }
                printf("\n");


               // Para ver si esta  registrado el nombre
               rewind(archivo); // Volver al inicio del archivo
               char nombreEnRegistro[30];
               int nombreEncontrado = 0;
               while (fgets(nombreEnRegistro, sizeof(nombreEnRegistro), archivo) != NULL) {
               nombreEnRegistro[strcspn(nombreEnRegistro, "\n")] = '\0'; // Eliminar el salto de línea del final
               if (strcmp(nombreEnRegistro, nombre) == 0) {
               nombreEncontrado = 1;
               break;

        }
    }
             if (!nombreEncontrado) {
             fprintf(archivo, "%s\n", nombre);
              }

              fclose(archivo);
              return 0;

            }
            else if(aux == 3){
                printf("Ultimos datos buscados.\n");
                imprimir_fichero_texto_antiguos();
                printf("\nPulsa el teclado para continuar.");
                getchar();
                fflush(stdin);
                system("cls");
                return menu(nombre);
            }

    } while (aux != 0);
}



