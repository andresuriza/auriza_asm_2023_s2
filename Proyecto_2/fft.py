import matplotlib.pyplot as plt
import numpy as np
from scipy.fftpack import fft, fftshift

# ------------------------------ Inicio Funcionalidad ----------------------------
# Función que genera una onda seno
def sine_wave(f,overSampRate,phase,nCyl):
	fs = overSampRate*f # sampling frequency
	t = np.arange(0,nCyl*1/f-1/fs,1/fs) # time base
	g = np.sin(2*np.pi*f*t+phase) # replace with cos if a cosine wave is desired
	return (t,g) # return time base and signal g(t) as tuple

# Función que grafica el resultado de aplicar la FFT a una señal seno
def graphFFT(f, overSampRate, fs, phase, nCycl):
    (t,x) = sine_wave(f,overSampRate,phase,nCyl) #function call

    NFFT = 256  
    X = fftshift(fft(x, NFFT))

    # Creación de la gráfica
    fig4, ax = plt.subplots(nrows=1, ncols=1) #create figure handle
    fVals=np.arange(start = -NFFT/2,stop = NFFT/2)*fs/NFFT
    ax.plot(fVals,np.abs(X),'b')
    ax.set_title('Transformada rápida de Fourier')
    ax.set_xlabel('Frecuencia (Hz)')         
    ax.set_ylabel('Amplitud')
    ax.set_xlim(-50, 50)
    ax.set_xticks(np.arange(-50, 50+10, 10))
    plt.show()
#------------------------------ Fin Funcionalidad ---------------------------

f = 100 
overSampRate = 30 
fs = 400
phase = 0
nCyl = 5

graphFFT(f, overSampRate, fs, phase, nCyl)