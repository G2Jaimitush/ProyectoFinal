#include "funciones.h"
#include <stdio.h>
void Inicioprograma();


// Función para iniciar el programa
void Inicioprograma(){
    printf("Programa iniciado correctamente.\n");
    
    IngresoDatos();
    GuardarDatosCO2();
    CalcProximas24Horas();
    GenerarReporte();
    MostrarReporte();

    
};