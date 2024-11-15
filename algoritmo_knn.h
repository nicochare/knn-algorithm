typedef struct registro {
    float gender; // 0 = Hombre, 1 = Mujer
    float age;
    float hypertension;
    float heart_disease;
    float smoking_history;
    float bmi;
    float HbA1c_level;
    float blood_glucose_level;
    float diabetes; // 0 = No tiene, 1 = Tiene
} Registro;

void normalizar_registro(Registro*);
float calcular_distancia_registros(Registro, Registro);