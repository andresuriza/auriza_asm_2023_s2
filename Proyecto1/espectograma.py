import matplotlib.pyplot as plt
import sounddevice as sd
import librosa

y, sr = librosa.load('C:\\Users\\andres\\Music\\rideofthevalkyries.wav')

#sd.play(y[0:600000], sr)

y_harmonic, y_percussive = librosa.effects.hpss(y)

plt.specgram(y[0:600000], NFFT = 5000, Fs = sr, noverlap = 400, cmap='jet_r')
plt.xlabel('Tiempo (s)') 
plt.ylabel('Frecuencia (Hz)')
plt.title("Espectograma")
plt.colorbar()

plt.figure()
plt.specgram(y_harmonic[0:600000], NFFT = 5000, Fs = sr, noverlap = 400, cmap='jet_r')
plt.xlabel('Tiempo (s)') 
plt.ylabel('Frecuencia (Hz)')
plt.title("Espectograma harmónicos extraídos")
plt.colorbar()

plt.figure()
plt.specgram(y_percussive[0:600000], NFFT = 5000, Fs = sr, noverlap = 400, cmap='jet_r')
plt.xlabel('Tiempo (s)') 
plt.ylabel('Frecuencia (Hz)')
plt.title("Espectograma percusión extraída")
plt.colorbar()
plt.show()