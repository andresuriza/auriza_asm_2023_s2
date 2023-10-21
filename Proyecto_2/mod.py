import numpy as np
import scipy.io.wavfile as wavfile
import matplotlib.pyplot as plt

# ------------------------------ Inicio Funcionalidad ----------------------------

# Función para realizar la modulación AM
def modulationAM(signal, carrierFrequency, sampleRate):
    timeVector = np.arange(len(signal)) / sampleRate
    carrier = np.sin(2 * np.pi * carrierFrequency * timeVector)
    modulatedSignal = signal * carrier
    return modulatedSignal

# Función para realizar la demodulación AM
def am_demodulation(modulatedSignal, carrierFrequency, sampleRate):
    timeVector = np.arange(len(modulatedSignal)) / sampleRate
    carrier = np.sin(2 * np.pi * carrierFrequency * timeVector)
    demodulatedSignal = modulatedSignal * carrier
    return demodulatedSignal

#------------------------------ Fin Funcionalidad ---------------------------

# Ejemplo con una señal senoidal
signalFrequency = 100  # Frecuencia de la portadora (Hz)
signalAmplitude = 1.0 # Amplitud de la portadora

# Tiempo de muestreo
tiempoMuestreo = 0.001  # Intervalo de tiempo entre muestras
tiempoTotal = 0.2  # Duración total de la señal
sampleRate = 4000

# Generar la señal de mensaje (una onda senoidal)
t = np.arange(0, tiempoTotal, 1 / sampleRate)

audioSignal = signalAmplitude * np.sin(2 * np.pi * signalFrequency * t)

# Parámetros de la señal portadora
carrierFrequency = 1000  # Frecuencia de la portadora en Hz

# Parámetros para la modulación AM
modulatedSignal = modulationAM(audioSignal, carrierFrequency, sampleRate) # Modular la señal de audio
demodulatedSignal = am_demodulation(modulatedSignal, carrierFrequency, sampleRate) # Demodular la señal modulada

# Graficar las señales
plt.figure(figsize=(12, 6))

plt.subplot(3, 1, 1)
plt.plot(t, audioSignal)
plt.title('Señal de Mensaje')

plt.subplot(3, 1, 2)
plt.plot(t, modulatedSignal)
plt.title('Señal Modulada (AM)')

plt.subplot(3, 1, 3)
plt.plot(t, demodulatedSignal)
plt.title('Señal Demodulada')

plt.tight_layout()
plt.show()



