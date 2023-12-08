#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Pipeline.h"
#include "Classifier.h"

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial.println("Started");

  // Iniciar el MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
}

void loop() {
  /* Leer los datos del acelerómetro y el giroscopio */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // realizar extracción de características
  float features[] = {a.acceleration.x, a.acceleration.y, a.acceleration.z, 
                      g.gyro.x, g.gyro.y, g.gyro.z};

  if (!pipeline.transform(features))
    return;

  // realizar clasificación
  Serial.print("Predicted gesture: ");
  Serial.print(forest.predictLabel(pipeline.X));
  Serial.print(" (DSP: ");
  Serial.print(pipeline.latencyInMicros());
  Serial.print(" micros, Classifier: ");
  Serial.print(forest.latencyInMicros());
  Serial.println(" micros)");
}
