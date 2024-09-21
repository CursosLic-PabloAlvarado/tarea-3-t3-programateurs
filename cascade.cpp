#include "cascade.h"

cascade::cascade(){
}

cascade::~cascade(){
}

void cascade::set_coefficients(std::vector< std::vector< sample_t > > filter_coefs_matrix){
    // First stage
    stages.clear();
    stages.push_back(&first_stage);
    stages.push_back(&second_stage);
    this->first_stage.set_coefficients(filter_coefs_matrix[0]);
    this->second_stage.set_coefficients(filter_coefs_matrix[1]);

    // Third stage
    if (filter_coefs_matrix.size() > 2){
        this->third_stage.set_coefficients(filter_coefs_matrix[2]);
        stages.push_back(&third_stage);
    }
}

void cascade::process(jack_nframes_t nframes,
                    const sample_t *const in,
                    sample_t *const out){
  sample_t temp_in[nframes];
  sample_t temp_out[nframes];

  memcpy(temp_in, in, sizeof(sample_t) * nframes); // Copia la entrada inicial en temp_in

  // Procesar cada etapa
  for (long unsigned int i = 0; i < stages.size(); i++){
      stages[i]->process(nframes, temp_in, temp_out);
      memcpy(temp_in, temp_out, sizeof(sample_t) * nframes); // El resultado de una etapa es la entrada de la siguiente
  }

  // Copiar la salida final al buffer de salida
  memcpy(out, temp_out, sizeof(sample_t) * nframes);
}