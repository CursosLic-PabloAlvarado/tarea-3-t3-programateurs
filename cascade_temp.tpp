#include <cascade_temp.h>

#include <cstring>

template <size_t N>
cascade_temp<N>::cascade_temp() : stages(N) { // Inicializar el vector de biquad con N elementos
}

template <size_t N>
cascade_temp<N>::~cascade_temp() {
}

template <size_t N>
void cascade_temp<N>::set_coefficients(std::vector<std::vector<sample_t>> filter_coefs_matrix) {
    // Establecer coeficientes para las etapas
    for (size_t i = 0; i < filter_coefs_matrix.size(); ++i) {
        stages[i].set_coefficients(filter_coefs_matrix[i]);
    }
}



template <size_t N>
void cascade_temp<N>::process2(jack_nframes_t nframes, const sample_t * __restrict__ in, sample_t * __restrict__ out) {
    sample_t temp_in[nframes];
    sample_t temp_out[nframes] = {0};

    memcpy(temp_in, in, sizeof(sample_t) * nframes); 

    // Procesar cada etapa
    for (size_t i = 0; i < stages.size(); i++) {
        stages[i].process2(nframes, temp_in, temp_out);
        memcpy(temp_in, temp_out, sizeof(sample_t) * nframes); 
    }

    // Copiar la salida final al buffer de salida
    memcpy(out, temp_out, sizeof(sample_t) * nframes);
}

template <size_t N>
void cascade_temp<N>::process3(jack_nframes_t nframes, const sample_t * __restrict__ in, sample_t * __restrict__ out) {
    sample_t temp_in[nframes];
    sample_t temp_out[nframes] = {0};

    memcpy(temp_in, in, sizeof(sample_t) * nframes); 

    // Procesar cada etapa
    for (size_t i = 0; i < stages.size(); i++) {
        stages[i].process3(nframes, temp_in, temp_out);
        memcpy(temp_in, temp_out, sizeof(sample_t) * nframes); 
    }

    // Copiar la salida final al buffer de salida
    memcpy(out, temp_out, sizeof(sample_t) * nframes);
}

