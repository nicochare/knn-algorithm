typedef struct registro {
    int gender; // 0 = Hombre, 1 = Mujer
    float age;
    float hypertension;
    int heart_disease;
    int smoking_history;
    float bmi;
    float HbA1c_level;
    int blood_glucose_level;
    int diabetes; // 0 = No tiene, 1 = Tiene
} Registro;

FILE abrirArchivo(char*);

void cerrarArchivo(FILE);

void guardarRegistro(char*, Registro*, i);

Registro* leerDatos(FILE);
