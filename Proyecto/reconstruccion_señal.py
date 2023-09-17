import matplotlib.pyplot as plt
import numpy as np

dt = 0.001
t = np.arange(0, 1, dt)

wave = np.sin(2 * np.pi * 4 * t)

cleanWave = wave

wave = wave + 2 * np.random.randn(len(t)) # Ruido Gaussiano

n = len(t)
ffTransform = np.fft.fft(wave, n) # Transformada rápida de fourier
PSD = ffTransform * np.conj(ffTransform) / n # Power spectral density
freq = (1 / (dt * n)) * np.arange(n)
L = np.arange(1, np.floor(n / 2), dtype = 'int') # Dominio Fourier

fig, axs = plt.subplots(2, 1)
plt.subplots_adjust(None, None, None, None, None, 0.4)

plt.sca(axs[0])
plt.plot(t, wave, color = 'c', linewidth = 1.5, label = 'Ruido')
plt.plot(t, cleanWave, color = 'k', linewidth = 2, label = 'Limpia')
plt.xlim(t[0], t[-1])
plt.title('Gráfica onda + ruido Gaussiano')
plt.xlabel('Tiempo (s)') 
plt.ylabel('Amplitud')
plt.legend()

plt.sca(axs[1])
plt.plot(freq[L], PSD[L], color = 'c', linewidth = 2, label = 'Ruido')
plt.xlim(freq[L[0]], freq[L[-1]])
plt.title('Gráfica FFT')
plt.xlabel('Frecuencia (Hz)') 
plt.ylabel('Potencia')
plt.legend()

indices = PSD > 100  # Retorna boolean de si la potencia es muy alta
cleanPSD = PSD * indices    # Elimina las frecuencias comunes
ffTransform = indices * ffTransform
inverseFft = np.fft.ifft(ffTransform) # Transformada inversa

fig, axs = plt.subplots(2, 1)
plt.subplots_adjust(None, None, None, None, None, 0.4)

plt.sca(axs[0])
plt.plot(t, inverseFft, color = 'k', linewidth = 2, label = 'Filtrada')
plt.xlim(t[0], t[-1])
plt.title('Onda reconstruida')
plt.xlabel('Tiempo (s)') 
plt.ylabel('Amplitud')
plt.legend()

plt.sca(axs[1])
plt.plot(freq[L], PSD[L], color = 'c', linewidth = 2, label = 'Ruido')
plt.plot(freq[L], cleanPSD[L], color = 'k', linewidth = 1.5, label = 'Filtrada')
plt.xlim(freq[L[0]], freq[L[-1]])
plt.title('Gráfica FFT mostrando onda filtrada')
plt.xlabel('Frecuencia (Hz)') 
plt.ylabel('Potencia')
plt.legend()

plt.show()