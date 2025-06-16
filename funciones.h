void IngresoDatos() {
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
        float pendiente;
    };

    struct Zona zonas[5] = {
        {"Belisario", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.002}},
        {"Centro",    {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.00380303030303031}},
        {"El Camal",  {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.004893939}},
        {"Condado",   {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}},
        {"Turubamba", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}}
    };
    struct Zona zonas24[5] = {
        {"Belisario", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.002}},
        {"Centro",    {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.00380303030303031}},
        {"El Camal",  {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.004893939}},
        {"Condado",   {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}},
        {"Turubamba", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}}
    };

    int cantidad = 5; // Número de zonas

    struct registroFecha fecha;

    // Validación del año
    int valido = 0;
    while (valido == 0) {
        printf("Ingrese el año actual: ");
        scanf("%d", &fecha.year);
        if (fecha.year >= 2025 && fecha.year <= 2100) {
            valido = 1;
        } else {
            printf("Año invalido. Debe ser entre 2025 y 2100.\n");
        }
    }

    // Validación del mes
    valido = 0;
    while (valido == 0) {
        printf("Ingrese el mes actual: ");
        scanf("%d", &fecha.month);
        if (fecha.month >= 1 && fecha.month <= 12) {
            valido = 1;
        } else {
            printf("Mes invalido. Debe ser entre 1 y 12.\n");
        }
    }

    // Validación del día
    valido = 0;
    while (valido == 0) {
        int max_dia = 31;
        if (fecha.month == 2) {
            if ((fecha.year % 4 == 0 && fecha.year % 100 != 0) || (fecha.year % 400 == 0)) {
                max_dia = 29;
                printf("Febrero tiene 29 días en el año %d.\n", fecha.year);
            } else {
                max_dia = 28;
                printf("Febrero tiene 28 días en el año %d.\n", fecha.year);
            }
        } else if (fecha.month == 4 || fecha.month == 6 || fecha.month == 9 || fecha.month == 11) {
            max_dia = 30;
            printf("Este mes tiene 30 días.\n");
        } else {
            printf("Este mes tiene 31 días.\n");
        }
        printf("Ingrese el dia actual: ");
        scanf("%d", &fecha.day);
        if (fecha.day >= 1 && fecha.day <= max_dia) {
            valido = 1;
        } else {
            printf("Dia invalido. Debe ser entre 1 y %d.\n", max_dia);
        }
    }

    // Validación de la hora
    valido = 0;
    while (valido == 0) {
        printf("Ingrese la hora actual (0-23): ");
        scanf("%d", &fecha.hour);
        if (fecha.hour >= 0 && fecha.hour <= 23) {
            valido = 1;
        } else {
            printf("Hora invalida. Debe ser entre 0 y 23.\n");
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

/*
void CalcProximas24Horas(zonas, zonas24) {
    // Esta función se encarga de calcular los niveles de contaminación en las próximas 24 horas.
    for(int i = 0; i < 5; i++) {
        
        for(int j = 0; j < 5; j++) {
            // Aquí se implementaría la lógica para calcular los niveles de contaminación.
            // Por simplicidad, solo se imprime un mensaje.
            printf("Calculando niveles de %s en %s...\n", 
                   zonas[i].contaminantes[j].nom, zonas[i].nombre);
                   zonas24[i].contamDatos[j] = zonas[i].contamDatos[j] *zonas[i].pendiente; // Simulación de aumento del 10%
        }
        // Aquí se implementaría la lógica para calcular los niveles de contaminación.
        // Por simplicidad, solo se imprime un mensaje.
    }
}
*/