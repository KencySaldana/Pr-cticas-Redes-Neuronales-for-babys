#include <math.h>
#define INPUT_SIZE 1
#define HIDDEN_SIZE 10
#define OUTPUT_SIZE 1

// Utiliza valores hipotéticos para los pesos y sesgos
float W1[HIDDEN_SIZE][INPUT_SIZE] = {
  {-0.6881267},
  {-0.35927361},
  {-0.31381777},
  {1.04817578},
  {0.23994406},
  {0.62808612},
  {-2.27849864},
  {0.81509633},
  {0.74601938},
  {1.93712111}
};
float b1[HIDDEN_SIZE] = {
  -1.15905571,
  0.83915819,
  -0.70751844,
  0.09178546,
  0.54097163,
  -0.01462036,
  0.35290278,
  -1.20707743,
  0.57419541,
  -0.51965628
};
float W2[OUTPUT_SIZE][HIDDEN_SIZE] = {
  {1.18365253, -0.87331633, 0.90095811, 0.35883521, 0.57842619, 0.03706513,
   0.02802357, -1.41371353, 0.62000477, -0.34031201}
};
float b2[OUTPUT_SIZE] = {0.01580466};

void setup() {
  Serial.begin(9600);
  while (!Serial); // Asegúrese de que la conexión serie esté activa
  Serial.println("Iniciando red neuronal...");
}

void loop() {
  for (float t = 0; t < 2 * PI; t += 0.1) {
    float senoInput = sin(t); // Simula la entrada con la función seno
    float input[INPUT_SIZE] = {senoInput};
    float output[OUTPUT_SIZE];

    forwardPropagation(input, output);

    // Enviar la función seno y la salida de la red neuronal al Serial Plotter en formato CSV
    Serial.print(senoInput);
    Serial.print(",");
    Serial.println(output[0]);
    
    delay(100); // Retraso para visualización, ajusta según sea necesario
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
