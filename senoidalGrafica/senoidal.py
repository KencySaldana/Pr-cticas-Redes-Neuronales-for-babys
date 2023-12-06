import numpy as np
import matplotlib.pyplot as plt

# Definir funciones necesarias
def relu(x):
    return np.maximum(0, x)

def train(X, Y, hidden_size, learning_rate, epochs):
    input_size = X.shape[0]
    output_size = Y.shape[0]

    W1, b1, W2, b2 = initialize_parameters(input_size, hidden_size, output_size)

    for i in range(epochs):
        Z1, A1, Z2, A2 = forward_propagation(X, W1, b1, W2, b2)
        loss = compute_loss(Y, A2)
        dW1, db1, dW2, db2 = backward_propagation(X, Y, Z1, A1, Z2, A2, W2)
        W1, b1, W2, b2 = update_parameters(W1, b1, W2, b2, dW1, db1, dW2, db2, learning_rate)

        if i % 1000 == 0:
            print(f"Epoch {i}, Loss: {loss}")

    _, _, _, predictions = forward_propagation(X, W1, b1, W2, b2)
    r2 = calculate_r2(Y.flatten(), predictions.flatten())
    print(f"Coeficiente de determinación (R^2): {r2 * 100}%")

    return W1, b1, W2, b2

def compute_loss(Y, A2):
    m = Y.shape[1]
    loss = np.mean((Y - A2) ** 2)
    return loss

def linear(x):
    return x

def initialize_parameters(input_size, hidden_size, output_size):
    W1 = np.random.randn(hidden_size, input_size) * np.sqrt(2 / input_size)
    b1 = np.zeros((hidden_size, 1))
    W2 = np.random.randn(output_size, hidden_size) * np.sqrt(2 / hidden_size)
    b2 = np.zeros((output_size, 1))
    return W1, b1, W2, b2

def forward_propagation(X, W1, b1, W2, b2):
    Z1 = np.dot(W1, X) + b1
    A1 = relu(Z1)
    Z2 = np.dot(W2, A1) + b2
    A2 = linear(Z2)
    return Z1, A1, Z2, A2

def backward_propagation(X, Y, Z1, A1, Z2, A2, W2):
    m = Y.shape[1]
    dZ2 = A2 - Y
    dW2 = np.dot(dZ2, A1.T) / m
    db2 = np.sum(dZ2, axis=1, keepdims=True) / m
    dZ1 = np.dot(W2.T, dZ2) * (Z1 > 0)
    dW1 = np.dot(dZ1, X.T) / m
    db1 = np.sum(dZ1, axis=1, keepdims=True) / m
    return dW1, db1, dW2, db2

def update_parameters(W1, b1, W2, b2, dW1, db1, dW2, db2, learning_rate):
    W1 -= learning_rate * dW1
    b1 -= learning_rate * db1
    W2 -= learning_rate * dW2
    b2 -= learning_rate * db2
    return W1, b1, W2, b2


def calculate_r2(y_true, y_pred):
    y_mean = np.mean(y_true)
    ss_total = np.sum((y_true - y_mean) ** 2)
    ss_residual = np.sum((y_true - y_pred) ** 2)
    r2 = 1 - (ss_residual / ss_total)
    return r2

# Cargar datos desde un archivo .npz
with np.load('seno_ruidoso.npz') as data:
    X = data['x'].reshape(1, -1)
    Y = data['y_ruidoso'].reshape(1, -1)

# Entrenamiento (asegúrate de que la función train esté definida)
hidden_size = 10
learning_rate = 0.01
epochs = 50000
W1, b1, W2, b2 = train(X, Y, hidden_size, learning_rate, epochs)

# Generar predicciones
_, _, _, predictions = forward_propagation(X, W1, b1, W2, b2)

# Graficar la función del seno y la predicción
plt.figure(figsize=(10, 5))
plt.plot(X.flatten(), Y.flatten(), label='Función del Seno', color='blue')
plt.plot(X.flatten(), predictions.flatten(), label='Predicción de la Red Neuronal', color='red')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Función del Seno vs. Predicción de la Red Neuronal')
plt.legend()
plt.grid(True)
plt.show()


# Entrenamiento
hidden_size = 10
learning_rate = 0.01
epochs = 50000
W1, b1, W2, b2 = train(X, Y, hidden_size, learning_rate, epochs)

# pesos y sesgos entrenados
print("Pesos de la capa oculta (W1):")
print(W1)
print("Sesgos de la capa oculta (b1):")
print(b1)
print("Pesos de la capa de salida (W2):")
print(W2)
print("Sesgos de la capa de salida (b2):")
print(b2)