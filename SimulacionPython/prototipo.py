import numpy as np
import scipy.io.wavfile as wavfile
import matplotlib.pyplot as plt
from scipy.fftpack import fft, fftshift
    
# ------------------------------ Inicio Funcionalidad ----------------------------

# Función para la creación de la gráfica FFT
def ffTransform(audioSignal):
    X = fftshift(fft(audioSignal, NFFT))
    fig1, ax = plt.subplots(nrows=1, ncols=1)
    fVals=np.arange(start = -NFFT/2,stop = NFFT/2)*signalFrequency/NFFT
    ax.plot(fVals,np.abs(X),'b')
    ax.set_title('Transformada rápida de Fourier')
    ax.set_xlabel('Frecuencia (Hz)')         
    ax.set_ylabel('Amplitud')
    ax.set_xlim(-50, 50)
    ax.set_xticks(np.arange(-50, 50+10, 10))

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
sampleRate = 8000 # Total de Muestras por segundo
tiempoMuestreo = 1 / sampleRate  # Intervalo de tiempo entre muestras
tiempoTotal = 0.2  # Duración total de la señal
NFFT = 256  

# Generar la señal de mensaje (una onda senoidal)
t = np.arange(0, tiempoTotal, tiempoMuestreo)

audioSignal = signalAmplitude * np.sin(2 * np.pi * signalFrequency * t)

# Parámetros de la señal portadora
carrierFrequency = 1000  # Frecuencia de la portadora en Hz

# Parámetros para la modulación AM
modulatedSignal = modulationAM(audioSignal, carrierFrequency, sampleRate) # Modular la señal de audio
demodulatedSignal = am_demodulation(modulatedSignal, carrierFrequency, sampleRate) # Demodular la señal modulada
ffTransform(audioSignal)

# Graficar las señales moduladas
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