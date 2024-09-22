function viewfreqresp(filename, Fs = 48000)
  % Esta funcion permite visualizar la respuesta y la fase del filtro especificado.
  % Y el diagrama de polos y ceros.
  %
  % Entradas:
  %
  % filename = string con el path del archivo que contiene 
  %           la matriz con los coeficientes del filtro.
  % Fs = frecuencia de muestreo (por defecto 48 kHz)

  close all;

  %TODO: guardar las img en una carpeta mediante un for
  
  % Cargar la matriz SOS desde el archivo
  Data = load(filename, "SOS");
  SOS = Data.SOS;
  
  % Convertir SOS a los coeficientes del filtro (b, a)
  [b, a] = sos2tf(SOS);

  % Diagrama de polos y ceros
  figure;
  zplane(b, a);
  title('Diagrama de Polos y Ceros');
  xlabel('Real');
  ylabel('Imaginario');
  grid on;

  % Frecuencia de analisis
  f = logspace(0, log10(Fs / 2), 1000);  % Frecuencias desde 1 Hz hasta Fs/2 en escala logarítmica
  w = 2 * pi * f / Fs;  % Frecuencia angular normalizada

  % Respuesta en frecuencia
  H = polyval(b, exp(1j * w)) ./ polyval(a, exp(1j * w));

  % Magnitud en dB
  magnitude = 20 * log10(abs(H));

  % Fase en grados
  phase = angle(H) * 180 / pi;
  phase = mod(phase + 360, 360) - 360;  % Normalizar fase a -360° a 0°

  % Plot de la magnitud
  figure;
  subplot(2, 1, 1);
  semilogx(f, magnitude, 'LineWidth', 2); 
  xlabel('F [Hz]');
  ylabel('|H(F)| [dB]');
  title('Respuesta en Magnitud');
  axis([1 Fs/2 -100 5]); 
  grid on;

  % Plot de la fase
  subplot(2, 1, 2);
  semilogx(f, phase, 'LineWidth', 2); 
  xlabel('F [Hz]');
  ylabel('∠H(F) [°]');
  title('Respuesta en Fase');
  axis([1 Fs/2 -360 0]);  
  grid on;
end
