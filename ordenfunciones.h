#include "funciones.h"
#include <stdio.h>
void Inicioprograma();


// Función para iniciar el programa
void Inicioprograma(){
    printf("Programa iniciado correctamente.\n");
    printf("Bienvenido al sistema de prediccion de contaminacion.\n");

    IngresoDatos();
    GuardarDatosCO();
    GuardarDatosPM10();
    GuardarDatosPM25();
    GuardarDatosNO2();
    GuardarDatosSO2();
    CalcProximas24Horas();
    GenerarReporte();
    MostrarReporte();
    MenuDeOpciones();
    
};