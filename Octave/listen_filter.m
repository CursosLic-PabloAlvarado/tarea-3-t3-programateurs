function listen_filter(filter_file, wav_file, Fs = 48000)
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
