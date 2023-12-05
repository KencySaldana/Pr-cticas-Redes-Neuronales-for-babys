int tree(float petalLength, float petalWidth, float sepalLength, float sepalWidth) {
    if (petalLength <= 2.45) {
        return 0; // Setosa
    } else if (petalLength > 2.45 && petalWidth <= 1.75) {
        if (petalLength <= 4.95) {
            if (petalWidth <= 1.65) {
                return 1; // Versicolor
            } else {
                return 2; // Virginica
            }
        } else if (petalWidth <= 1.55) {
            return 2; // Virginica
        } else {
            if (sepalLength <= 6.95) {
                return 1; // Versicolor
            } else {
                return 2; // Virginica
            }
        }
    } else if (petalWidth > 1.75) {
        if (petalLength <= 4.85) {
            if (sepalWidth <= 3.10) {
                return 2; // Virginica
            } else {
                return 1; // Versicolor
            }
        } else {
            return 2; // Virginica
        }
    }
    return -1; // Caso no cubierto
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        // Leer las características
        float petalLength = Serial.parseFloat();
        while (Serial.available() == 0) {}
        float petalWidth = Serial.parseFloat();
        while (Serial.available() == 0) {}
        float sepalLength = Serial.parseFloat();
        while (Serial.available() == 0) {}
        float sepalWidth = Serial.parseFloat();

        // Obtener la predicción del árbol
        int clase = tree(petalLength, petalWidth, sepalLength, sepalWidth);

        // Enviar la clase predicha
        if (clase == 0) {
            Serial.println("Es una Setosa");
        } else if (clase == 1) {
            Serial.println("Es una Versicolor");
        } else if (clase == 2) {
            Serial.println("Es una Virginica");
        } else {
            Serial.println("Clase desconocida");
        }
    }
}
