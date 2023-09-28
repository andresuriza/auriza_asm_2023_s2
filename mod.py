from fft import graphFFT
import numpy as np
import scipy.io.wavfile as wavfile

# ------------------------------ Inicio Funcionalidad ----------------------------

# Función para realizar la modulación AM
def modulationAM(signal, carrierFrequency, sampleRate):
    timeVector = np.arange(len(signal)) / sampleRate
    carrier = np.cos(2 * np.pi * carrierFrequency * timeVector)
    modulatedSignal = signal * carrier
    return modulatedSignal

# Función para realizar la demodulación AM
def am_demodulation(modulatedSignal, carrierFrequency, sampleRate):
    timeVector = np.arange(len(modulatedSignal)) / sampleRate
    carrier = np.cos(2 * np.pi * carrierFrequency * timeVector)
    demodulatedSignal = modulatedSignal * carrier
    return demodulatedSignal

# Función para guardar una señal en un archivo WAV
def saveWavFile (outputPath, sampleRate, signal):
    wavfile.write(outputPath, sampleRate, signal.astype(np.int16))
    return 1

#------------------------------ Fin Funcionalidad ---------------------------

# Ejemplo con un archivo de audio real 
filePath = "laser1.wav"
sampleRate, audioSignal = wavfile.read(filePath) # Cargar el archivo WAV

graphFFT(audioSignal, sampleRate, "Señal Original") # Graficar el sonido original con fft

# Parámetros para la modulación AM
carrierFrequency = 1000  # Frecuencia de la portadora en Hz

modulatedSignal = modulationAM(audioSignal, carrierFrequency, sampleRate) # Modular la señal de audio
demodulatedSignal = am_demodulation(modulatedSignal, carrierFrequency, sampleRate) # Demodular la señal modulada

# Crear un archivo .wav con el resultado
outputPath = "demodulated_audio.wav"
saveWavFile(outputPath, sampleRate, demodulatedSignal)

# Graficar la señal demodulada en función de la frecuencia con fft
graphFFT(demodulatedSignal, sampleRate, "Señal Demodulada")

print("Modulación y demodulación AM completadas. Se ha guardado la señal demodulada en", outputPath)


