pkg load symbolic

syms x               % Definir x como simbolo
f = x+2i;            % Número complejo a evaluar
int(f,x,0,2*pi)      % Función integrar, de 0 a pi 
