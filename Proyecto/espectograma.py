import matplotlib.pyplot as plt
from scipy.io import wavfile

frequency, signalData = wavfile.read("C:\\Users\\andres\\Music\\rideofthevalkyries.wav")

plt.title('Espectograma')    
plt.specgram(signalData, Fs = frequency, NFFT = 512)
plt.xlabel('Tiempo [s]')
plt.ylabel('Frecuencia [Hz]')
plt.show()