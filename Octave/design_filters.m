% Este archivo contiene los 16 filtros requeridos.
% 4 metodos: ellip, butter, cheby1, cheby2
% 4 tipos de filtros: paso bajo, paso alto, pasa banda, rechaza banda
% Guarda los coeficientes de los filtros en archivos .mat

pkg load signal

% Parámetros comunes
Fs = 48000;  % Frecuencia de muestreo en Hz
n = 3;       % Orden del filtro
rp = 1;      % Rizado en la banda de paso (dB)
rs = 50;     % Atenuación en la banda de rechazo (dB)

% Frecuencia de corte normalizada para filtro paso bajo/alto
Wp = 2 * 440 / Fs;

% Frecuencias para el pasa banda y rechaza banda
Wl = 2 * 220 / Fs;
Wh = 2 * 1000 / Fs;

% ------------------------ FILTROS ELIPTICOS ------------------------

% Filtro eliptico paso bajo
[b, a] = ellip(n, rp, rs, Wp, 'low');
SOS = tf2sos(b, a);
save('ellip_lowpass.mat', 'SOS');

% Filtro eliptico paso alto
[b, a] = ellip(n, rp, rs, Wp, 'high');
SOS = tf2sos(b, a);
save('ellip_highpass.mat', 'SOS');

% Filtro eliptico pasa banda
[b, a] = ellip(n, rp, rs, [Wl, Wh]);
SOS = tf2sos(b, a);
save('ellip_bandpass.mat', 'SOS');

% Filtro eliptico rechaza banda
[b, a] = ellip(n, rp, rs, [Wl, Wh], 'stop');
SOS = tf2sos(b, a);
save('ellip_stopband.mat', 'SOS');

% ------------------------ FILTROS BUTTER ------------------------

% Filtro butter paso bajo
[b, a] = butter(n, Wp);
SOS = tf2sos(b, a);
save('butter_lowpass.mat', 'SOS');

% Filtro butter paso alto
[b, a] = butter(n, Wp, 'high');
SOS = tf2sos(b, a);
save('butter_highpass.mat', 'SOS');

% Filtro butter pasa banda
[b, a] = butter(n, [Wl, Wh]);
SOS = tf2sos(b, a);
save('butter_bandpass.mat', 'SOS');

% Filtro butter rechaza banda
[b, a] = butter(n, [Wl, Wh], 'stop');
SOS = tf2sos(b, a);
save('butter_stopband.mat', 'SOS');

% ------------------------ FILTROS CHEBY 1 ------------------------

% Filtro cheby1 paso bajo
[b, a] = cheby1(n, rp, Wp);
SOS = tf2sos(b, a);
save('cheby1_lowpass.mat', 'SOS');

% Filtro cheby1 paso alto
[b, a] = cheby1(n, rp, Wp, 'high');
SOS = tf2sos(b, a);
save('cheby1_highpass.mat', 'SOS');

% Filtro cheby1 pasa banda
[b, a] = cheby1(n, rp, [Wl, Wh]);
SOS = tf2sos(b, a);
save('cheby1_bandpass.mat', 'SOS');

% Filtro cheby1 rechaza banda
[b, a] = cheby1(n, rp, [Wl, Wh], 'stop');
SOS = tf2sos(b, a);
save('cheby1_stopband.mat', 'SOS');

% ------------------------ FILTROS CHEBY 2 ------------------------

% Filtro cheby2 paso bajo
[b, a] = cheby2(n, rs, Wp);
SOS = tf2sos(b, a);
save('cheby2_lowpass.mat', 'SOS');

% Filtro cheby2 paso alto
[b, a] = cheby2(n, rs, Wp, 'high');
SOS = tf2sos(b, a);
save('cheby2_highpass.mat', 'SOS');

% Filtro cheby2 pasa banda
[b, a] = cheby2(n, rs, [Wl, Wh]);
SOS = tf2sos(b, a);
save('cheby2_bandpass.mat', 'SOS');

% Filtro cheby2 rechaza banda
[b, a] = cheby2(n, rs, [Wl, Wh], 'stop');
SOS = tf2sos(b, a);
save('cheby2_stopband.mat', 'SOS');