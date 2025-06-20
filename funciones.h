#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LIM_PM25 15
#define LIM_PM10 45
#define LIM_NO2 25
#define LIM_SO2 40
#define LIM_CO 4

//Se definenn los limites de contamacion segun la OMS para así tener la restriccion


//Estructuras
struct Contaminante {
        char nom[20];
    };
    struct registroFecha {
        int day;
        int month;
        int year;
        int hour;   
    };
    typedef struct registroFecha Fecha;
    struct Zona {
        char nombre[20];
        struct Contaminante contaminantes[5];
        float contamDatos[5];
        float pendiente[5];
    };

    struct Zona zonas[5] = {
        {"Belisario",  {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.16809, -0.277532929, 0.154716942, -0.007614, 0.01113441}},
        {"Centro",     {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, { 0.0554,   0.964459,    -0.072728931, -0.0739445, 0.00633295}},
        {"Cotocollao", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, { 0.107786, 0.047835,     0.033273232, -0.0051026, 0.004077135}},
        {"Los Chillos",{{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, { 0.254448, -1.14707,     0.343161221,  0.00399695, 0.00917739}},
        {"Tumbaco",    {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.0696,   0.346828,     0.243433055,  0.01567613, -0.00264876}}
    };

    struct Zona zonas24[5] = {
        {"Belisario", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.002}},
        {"Centro",    {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.00380303030303031}},
        {"Cotocollao",  {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.004893939}},
        {"Los Chillos",   {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}},
        {"Tumbaco", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}}
    };

    int cantidad = 5; // Número de zonas

    struct registroFecha fecha;



void IngresoDatos(){

 // Validación del año
    int valido = 0;
    float valido2 = 0;

    REPETIR:
        while (valido == 0) {
        printf("Ingrese el periodo actual entre 2025 - 2100: ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero, ingrese de nuevo.\n");
            while (getchar() != '\n'); // Limpia el buffer
            goto REPETIR;
        }

        // Validación de que el número ingresado sea un entero
        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero, ingrese de nuevo.\n");
            while (getchar() != '\n'); // Limpia el buffer
            goto REPETIR;
        }

        fecha.year = (int)valido2; // Convertir float a int

        if (fecha.year >= 2025 && fecha.year <= 2100) {
            valido = 1;
        } else {
            printf("Periodo invalido. Debe ser entre 2025 y 2100.\n");
            goto REPETIR;
        }
    }

    // Validación del mes
    valido = 0;
    valido2 = 0;

    REPETIR_MES:
    while (valido == 0) {
        printf("Ingrese el mes actual (1 - 12): ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_MES;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_MES;
        }

        fecha.month = (int)valido2;

        if (fecha.month >= 1 && fecha.month <= 12) {
            valido = 1;
        } else {
            printf("Mes invalido. Debe estar entre 1 y 12.\n");
            goto REPETIR_MES;
        }
    }

    // Validación del día
    valido = 0;
    valido2 = 0;

    REPETIR_DIA:
    while (valido == 0) {
        int max_dia = 31;

        // Determinar la cantidad de días del mes
        if (fecha.month == 2) {
            if ((fecha.year % 4 == 0 && fecha.year % 100 != 0) || (fecha.year % 400 == 0)) {
                max_dia = 29;
                printf("Febrero tiene 29 dias en el periodo %d.\n", fecha.year);
            } else {
                max_dia = 28;
                printf("Febrero tiene 28 dias en el periodo %d.\n", fecha.year);
            }
        } else if (fecha.month == 4 || fecha.month == 6 || fecha.month == 9 || fecha.month == 11) {
            max_dia = 30;
            printf("Este mes tiene 30 dias.\n");
        } else {
            max_dia = 31;
            printf("Este mes tiene 31 dias.\n");
        }

        printf("Ingrese el dia actual (1 - %d): ", max_dia);

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_DIA;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_DIA;
        }

        fecha.day = (int)valido2;

        if (fecha.day >= 1 && fecha.day <= max_dia) {
            valido = 1;
        } else {
            printf("Dia invalido. Debe ser entre 1 y %d.\n", max_dia);
            goto REPETIR_DIA;
        }
    }

    // Validación de la hora
    valido = 0;
    valido2 = 0;

    REPETIR_HORA:
    while (valido == 0) {
        printf("Ingrese la hora actual (0 - 23): ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_HORA;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_HORA;
        }

        fecha.hour = (int)valido2;

        if (fecha.hour >= 0 && fecha.hour <= 23) {
            valido = 1;
        } else {
            printf("Hora invalida. Debe estar entre 0 y 23.\n");
            goto REPETIR_HORA;
        }
    }

    printf("Fecha y hora de registro: %02d/%02d/%04d %02d:00\n",
        fecha.day, fecha.month, fecha.year, fecha.hour);


    // Ingreso de datos de contaminación
    printf("Ingrese los niveles de contaminacion para las siguientes zonas:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < 5; j++) {
            float contaminacion;
            int valido = 0;
            while (valido == 0) {
                printf("Ingrese la concentracion de %s: ", zonas[i].contaminantes[j].nom);
                if (scanf("%f", &contaminacion) != 1) {
                    printf("Nivel de concentracion invalido. Debe ser un numero flotante. Intente nuevamente:\n");
                    while (getchar() != '\n'); // Limpia el buffer
                } else {
                    zonas[i].contamDatos[j] = contaminacion;
                    valido = 1;
                }
            }
        }
    }
}

void CalcProximas24Horas() {
    // Esta función se encarga de calcular los niveles de contaminación en las próximas 24 horas.
    for(int i = 0; i < 5; i++) {
        
        for(int j = 0; j < 5; j++) {
            // Aquí se implementaría la lógica para calcular los niveles de contaminación.
            // Por simplicidad, solo se imprime un mensaje.
            printf("Calculando niveles de %s en %s...\n", zonas[i].contaminantes[j].nom, zonas[i].nombre);
                   zonas24[i].contamDatos[j] = zonas[i].contamDatos[j] *zonas[i].pendiente[j]; 
            
        }
        
    }
}

void GenerarReporte() {
    FILE *reporte = fopen("reporte_contaminacion.txt", "w");
    if (reporte == NULL) {
        printf("No se pudo crear el archivo de reporte.\n");
        return;
    }
    fprintf(reporte, "Fecha y hora de registro: %02d/%02d/%04d %02d:00\n\n", 
            fecha.day, fecha.month, fecha.year, fecha.hour);
    fprintf(reporte, "Zona\t\tContaminante\tActual\tPredicción 24h\tPendiente\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fprintf(reporte, "%-12s\t%-12s\t%.2f\t%.2f\t%.6f\n",
                zonas[i].nombre,
                zonas[i].contaminantes[j].nom,
                zonas[i].contamDatos[j],
                zonas24[i].contamDatos[j],
                zonas[i].pendiente[j]);
        }
        //AQUÍ FALTA IMRIMIR ALERTAS Y RECOMENDACIONES
        

    }
    fclose(reporte);
    printf("Reporte generado correctamente.\n");
}


//Datos de CO
void GuardarDatosCO (){
    //Abre el archivo CSV para guardar los datos de CO2
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosCO.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[4]);  // Índice 4 = CO
    }

    fclose(archivo);
    printf("Datos de CO guardados correctamente en el archivo historico.\n");
}


//Datos de SO2
void GuardarDatosSO2 (){
    //Abre el archivo CSV para guardar los datos de SO2
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosSO2.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[3]);  // Índice 3 = SO2
    }

    fclose(archivo);
    printf("Datos de SO2 guardados correctamente en el archivo historico.\n");
}



//Datos de NO2
void GuardarDatosNO2 (){
    //Abre el archivo CSV para guardar los datos de NO2
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosNO2.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d,%02d:00,%s,%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[2]);  // Índice 2 = NO2
    }

    fclose(archivo);
    printf("Datos de NO2 guardados correctamente en el archivo historico.\n");
}


//Datos de PM10
void GuardarDatosPM10 (){
    //Abre el archivo CSV para guardar los datos de PM10
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosPM10.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d,%02d:00,%s,%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[1]);  // Índice 1 = PM10
    }

    fclose(archivo);
    printf("Datos de PM10 guardados correctamente en el archivo historico.\n");
}

//Datos de PM2.5
void GuardarDatosPM25 (){
    //Abre el archivo CSV para guardar los datos de PM2.5
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosPM25.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d,%02d:00,%s,%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[0]);  // Índice 0 = PM2.5
    }

    fclose(archivo);
    printf("Datos de PM2.5 guardados correctamente en el archivo historico.\n");
}

void MostrarReporte(){
    printf("================================ REPORTE DE CONTAMINACIÓN ================================\n");
    printf("Fecha y hora de registro: %02d/%02d/%04d %02d:00\n\n", 
           fecha.day, fecha.month, fecha.year, fecha.hour);

    printf("%-12s | %-12s | %-10s | %-15s | %-10s\n", 
           "Zona", "Contaminante", "Actual", "Prediccion 24h", "Pendiente");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%-12s | %-12s | %-10.2f | %-15.2f | %-10.6f\n",
                   zonas[i].nombre,
                   zonas[i].contaminantes[j].nom,
                   zonas[i].contamDatos[j],
                   zonas24[i].contamDatos[j],
                   zonas[i].pendiente[j]);
        }
    }

    printf("==========================================================================================\n");
}


void MenuDeOpciones (){

    int opc;
    printf ("\n=== Prediccion de Contaminacion ===\n");
    printf ("1. Ingresar datos de contaminacion\n");
    printf ("2. Calcular niveles de contaminacion en las proximas 24 horas\n");
    printf ("3. Generar reporte de contaminacion\n");
    printf ("4. Salir\n");
    printf ("Ingrese una opcion: ");
    scanf ("%d", &opc);

}


void PredecirCOPendienteCalculada() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[4];     // CO actual
        float pendiente = zonas[i].pendiente[4];          // Pendiente de CO
        float prediccion = valor_actual + pendiente * 1;  // Para 1 unidad de tiempo (día)

        zonas24[i].contamDatos[4] = prediccion;

        printf("Prediccion CO (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionCO24Horas() {
    printf("\n========= PREDICCION DE CO PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Promedio CO");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[4];
        float pendiente = zonas[i].pendiente[4];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("============================================================================\n");
}


void PredecirSO2Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[3];     // SO2 actual
        float pendiente = zonas[i].pendiente[3];          // Pendiente de SO2
        float prediccion = valor_actual + pendiente * 1;  // Para 1 unidad de tiempo (1 día)

        zonas24[i].contamDatos[3] = prediccion;

        printf("Prediccion SO2 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionSO2_24Horas() {
    printf("\n========= PROMEDIO DE PREDICCION DE SO2 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Promedio SO2");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[3];  // SO2 actual
        float pendiente = zonas[i].pendiente[3];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}

void PredecirNO2Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[2];     // NO2 actual
        float pendiente = zonas[i].pendiente[2];          // Pendiente de NO2
        float prediccion = valor_actual + pendiente * 1;  // Para 1 día

        zonas24[i].contamDatos[2] = prediccion;

        printf("Prediccion NO2 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionNO2_24Horas() {
printf("\n========= PREDICCION DE NO2 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Promedio NO2");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[2];  // NO2 actual
        float pendiente = zonas[i].pendiente[2];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}


void PredecirPM10Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[1];     // PM10 actual
        float pendiente = zonas[i].pendiente[1];          // Pendiente de PM10
        float prediccion = valor_actual + pendiente * 1;  // Para 1 día

        zonas24[i].contamDatos[1] = prediccion;

        printf("Prediccion PM10 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionPM10_24Horas() {
    printf("\n========= PREDICCION DE PM10 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Promedio PM10");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[1];
        float pendiente = zonas[i].pendiente[1];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}


void PredecirPM25Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[0];     // PM2.5 actual
        float pendiente = zonas[i].pendiente[0];          // Pendiente PM2.5
        float prediccion = valor_actual + pendiente * 1;

        zonas24[i].contamDatos[0] = prediccion;

        printf("Prediccion PM2.5 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionPM25_24Horas() {
    printf("\n========= PREDICCION DE PM2.5 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Promedio PM2.5");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[0];     // PM2.5
        float pendiente = zonas[i].pendiente[0];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}

