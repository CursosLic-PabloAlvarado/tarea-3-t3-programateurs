% Script para detectar todos los archivos .mat en el directorio actual
% y llamar a la función viewfreqresp para cada uno de ellos

% Obtener la lista de archivos .mat en el directorio actual
mat_files = glob('*.mat');

% Verificar si se encontraron archivos
if isempty(mat_files)
    disp('No se encontraron archivos .mat en el directorio actual.');
else
    disp('Archivos .mat encontrados:');

    output_dir = './figuras/';
    if ~exist(output_dir, 'dir')
        mkdir(output_dir);
    end

    for i = 1:length(mat_files)
        fprintf('Procesando: %s\n', mat_files{i});

        viewfreqresp(mat_files{i});

        % Guardar todas las figuras generadas
        figHandles = get(0, 'Children');  % Obtener handles de todas las figuras
        for j = 1:length(figHandles)
            % Asignar nombre según el número de figura
            if j == 1
                fig_name = 'poles_zeros_diagram';
            elseif j == 2
                fig_name = 'magnitude';
            else
                continue;  % No guardamos otras figuras
            end

            % Guardar cada figura en el directorio de salida
            saveas(figHandles(j), fullfile(output_dir, [mat_files{i}(1:end-4), '_', fig_name, '.png']));
        end

        close all;
    end
end

