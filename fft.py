import matplotlib.pyplot as plt
import numpy as np
from scipy.io import wavfile

sampleRate, audioData = wavfile.read('laser1.wav')
def fastFourier (audioData):
    audioFFT = np.fft.fft(audioData) # Tranformada Rápida de Fourier
    return audioFFT

def graphFFT (audioData, sampleRate):

    audioDataFFT = fastFourier(audioData)

    # Calcular la frecuencia correspondiente a cada punto en la FFT
    frequencies = np.fft.fftfreq(len(audioData), 1 / sampleRate)

    # Tomar solo la mitad positiva de la FFT (frecuencias no negativas)
    positiveFrequencies = frequencies[:len(frequencies) // 2]
    audioFFTMagnitude = np.abs(audioDataFFT[:len(frequencies) // 2])

    # Crear la gráfica
    plt.figure(figsize=(12, 6))
    plt.plot(positiveFrequencies, audioFFTMagnitude)
    plt.title('Espectro de Frecuencia')
    plt.xlabel('Frecuencia (Hz)')
    plt.ylabel('Amplitud')
    plt.grid()
    plt.show()

    return 1

graphFFT(sampleRate, audioData)

