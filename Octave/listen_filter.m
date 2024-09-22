function listen_filter(filter_file, wav_file, Fs = 48000)
  % Esta funcion permite aplica un filtro dado a un archivo .wav
  % y posteriormente escuchar este audio filtrado.
  %
  % Entradas:
  %
  % filter_file = string con el path del archivo que contiene 
  %            los coeficientes del filtro.
  % wav_file = archivo de audio al cual se le aplicara el filtro.
  % Fs = frecuencia de muestreo (por defecto 48 kHz)

  % Cargar el filtro desde el archivo .mat
  Data = load(filter_file, "SOS");
  SOS = Data.SOS;
  
  % Convertir SOS a los coeficientes del filtro
  [b, a] = sos2tf(SOS);

  % Leer el archivo .wav
  [audio, wav_Fs] = audioread(wav_file);

  % Verificar si la frecuencia de muestreo del wav es distinta a Fs
  if wav_Fs ~= Fs
    fprintf('Frecuencia de muestreo del archivo wav: %d Hz\n', wav_Fs);
    fprintf('Re-muestreando el audio a %d Hz...\n', Fs);
    audio = resample(audio, Fs, wav_Fs);
  end

  % Aplicar el filtro al archivo de audio
  filtered_audio = filter(b, a, audio);

  % Reproducir el audio filtrado
  fprintf('Reproduciendo el audio filtrado...\n');
  sound(filtered_audio, Fs);
end
