#include "funciones.h"
#include <stdio.h>
void Inicioprograma();


// Función para iniciar el programa
void Inicioprograma(){
printf("Programa iniciado correctamente.\n");
    
    IngresoDatos();
    CalcProximas24Horas();
    GenerarReporte();
    CargarDatosHistoricosCO2("datos_historicos_CO2.txt");
};