#include <math.h>
#define INPUT_SIZE 2
#define HIDDEN_SIZE 10
#define OUTPUT_SIZE 1

// Pesos y sesgos de la red neuronal
float W1[HIDDEN_SIZE][INPUT_SIZE] = {
    {0.0552504, 0.16712755},
    {-0.6825752, 0.13963714},
    {0.53459907, 1.2144818},
    {-0.26866814, -0.20400059},
    {-0.14121443, -0.8918965},
    {0.11530477, 0.09451997},
    {-0.8238475, -0.5127192},
    {-0.13560842, -0.11880038},
    {0.20746139, 0.5883256},
    {-0.38030693, -0.35533342}
};
float b1[HIDDEN_SIZE] = {-0.20443831, -0.05635213, 0.5525484, -0.1509982, 0.21910068, -0.18792123, -0.17175235, -0.13426319, 0.43787888, -0.27150592};
float W2[OUTPUT_SIZE][HIDDEN_SIZE] = {
    {0.08598058, 0.30728003, -0.379712, -0.62062854, 0.37021032, -0.14575838, -0.2596066, -0.45450103, -1.0234647, -0.41032442}
};
float b2[OUTPUT_SIZE] = {0.7189895};

void setup() {
  Serial.begin(9600);
  Serial.println("Red neuronal iniciada para clasificación binaria");
}

void loop() {
  if (Serial.available() > 0) {
    // Leer dos valores de entrada del puerto serie
    float inputValue1 = Serial.parseFloat();
    float inputValue2 = Serial.parseFloat();

    // Ignorar si los números no son válidos
    if (isnan(inputValue1) || isnan(inputValue2)) {
      Serial.println("Entrada no válida");
      return;
    }

    float input[INPUT_SIZE] = {inputValue1, inputValue2};
    float output[OUTPUT_SIZE];

    forwardPropagation(input, output);

    // Clasificar la salida como 0 o 1 basado en un umbral
    int classification = output[0] > 0.5 ? 1 : 0;

    // Enviar la clasificación al puerto serie
    Serial.print("Valores de entrada: ");
    Serial.print(inputValue1);
    Serial.print(", ");
    Serial.print(inputValue2);
    Serial.print(", Clasificación: ");
    Serial.println(classification);
  }
}

float relu(float x) {
  return x > 0 ? x : 0;
}

void forwardPropagation(float input[], float output[]) {
  float hidden[HIDDEN_SIZE];

  // Capa oculta
  for (int i = 0; i < HIDDEN_SIZE; i++) {
    hidden[i] = 0;
    for (int j = 0; j < INPUT_SIZE; j++) {
      hidden[i] += W1[i][j] * input[j];
    }
    hidden[i] += b1[i];
    hidden[i] = relu(hidden[i]);
  }

  // Capa de salida
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    output[i] = 0;
    for (int j = 0; j < HIDDEN_SIZE; j++) {
      output[i] += W2[i][j] * hidden[j];
    }
    output[i] += b2[i];
  }
}

//2.343876,-2.925000 = 1
