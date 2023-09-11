import matplotlib.pyplot as plt
import sounddevice as sd
import librosa

y, sr = librosa.load('C:\\Users\\andres\\Music\\rideofthevalkyries.wav')
            
sd.play(y[0:600000], sr)

plt.specgram(y[0:600000], NFFT = 5000, Fs = sr, noverlap = 400, cmap='jet_r')
plt.xlabel('Tiempo (s)') 
plt.ylabel('Frecuencia (Hz)')
plt.colorbar()
plt.show()