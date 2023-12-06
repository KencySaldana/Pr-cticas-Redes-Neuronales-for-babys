import pandas as pd
import tensorflow as tf
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense

# Carga de datos
data = pd.read_csv('/content/gdrive/MyDrive/Colab Notebooks/MLParaArduino/simple_binary.csv')
y = data.pop('Output')

# Creación del dataset TensorFlow
tf_dataset = tf.data.Dataset.from_tensor_slices((data.values, y.values)).batch(32)

# Definición del modelo
model = Sequential([
    Dense(10, activation='relu', input_shape=(data.shape[1],)),  # Capa oculta con 10 neuronas
    Dense(1, activation='sigmoid')  # Capa de salida
])

# Compilación del modelo
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# Entrenamiento del modelo
history = model.fit(tf_dataset, epochs=50)

# Predicciones (opcional)
predictions = model.predict([
    [2.703007, -3.003042],
    [2.503735, -3.004376],
    [5.210248, -3.616640],
    [3.684824, 2.362308],
    [2.009693, 3.786094],
    [4.604840, 1.405890]
])
print("Predicciones:", predictions)

# Extracción de pesos y sesgos
for i, layer in enumerate(model.layers):
    weights, biases = layer.get_weights()
    print(f"Capa {i} - {layer.name}")
    print("Pesos:\n", weights)
    print("Sesgos:\n", biases)