import matplotlib.pyplot as plt
import numpy as np
from scipy.io import wavfile

# ------------------------------ Inicio Funcionalidad ----------------------------

# Función que le aplica la transformada rápida de Fourier a un archivo de sonido
def getFastFourier (audioData):
    audioFFT = np.fft.fft(audioData) # Tranformada Rápida de Fourier
    return audioFFT

# Función que obtiene las frecuencias de los armónicos del archivo de audio
def getFreqFFT (audioData, sampleRate):
    freqFFT = np.fft.fftfreq(len(audioData), 1 / sampleRate)
    return freqFFT

# Función que grafica el resultado de aplicar la FFT a una señal de audio
def graphFFT (audioData, sampleRate, titleGraph):

    audioDataFFT = getFastFourier(audioData)

    freqFFT = getFreqFFT(audioData, sampleRate) # Calcular la frecuencia correspondiente a cada punto en la FFT
    
    positiveFrequencies = freqFFT[:len(freqFFT) // 2] # Tomar solo la mitad positiva de la FFT (frecuencias no negativas)

    audioFFTMagnitude = np.abs(audioDataFFT[:len(freqFFT) // 2])

    # Creación de la gráfica
    plt.figure(figsize=(12, 6))
    plt.plot(positiveFrequencies, audioFFTMagnitude)
    plt.title(titleGraph)
    plt.xlabel('Frecuencia (Hz)')
    plt.ylabel('Amplitud')
    plt.grid()
    plt.show()
    return 1 

#------------------------------ Fin Funcionalidad ---------------------------

# Ejemplo con un archivo de audio
sampleRate, audioData = wavfile.read('laser1.wav') # Lectura del archivo de audio
#graphFFT(audioData, sampleRate, "Espectro de Frecuencia")

