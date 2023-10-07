import numpy
import matplotlib.pyplot as plt

t = numpy.linspace(0, 100, 1000 * 20) # Espacios uniformes entre 0 y 20
x = numpy.sin(2 * numpy.pi * 1000 * t) # Funcion seno

plt.specgram(x, Fs=200, cmap='plasma') # Espectograma
plt.xlabel('Tiempo (s)') 
plt.ylabel('Frecuencia (Hz)')
plt.colorbar(label='Intesidad (dB)')
plt.show()
