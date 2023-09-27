import matplotlib.pyplot as plt
import numpy as np
from scipy.io import wavfile

plt.rcParams['figure.dpi'] = 100

sampleRate, sound = wavfile.read('laser1.wav')

sound = sound / 2.0**15 # Potencia de 2 para 44kHz

fft_spectrum = np.fft.rfft(sound)
freq = np.fft.rfftfreq(sound.size, d=1./sampleRate)

fft_spectrum_abs = np.abs(fft_spectrum) # Obtener amplitudes y no la parte imaginaria

plt.plot(freq, fft_spectrum_abs)
plt.xlabel("Frecuencia (Hz)")
plt.ylabel("Amplitud")
plt.show()