#include "biquad.h"
#include <iostream>

biquad::biquad() {
  this->b0 = 0;
  this->b1 = 0;
  this->b2 = 0;
  this->a1 = 0;
  this->a2 = 0;
  this->x_minus_1 = 0;
  this->x_minus_2 = 0;
  this->y_minus_1 = 0;
  this->y_minus_2 = 0;

  this->w1 = 0;
  this->w1_minus_1 = 0;
  this->w2 = 0;
  this->w2_minus_1 = 0;
}

biquad::~biquad() {
}
  
void biquad::set_coefficients(std::vector< sample_t > filter_coefs){
  this->b0 = filter_coefs[0];
  this->b1 = filter_coefs[1];
  this->b2 = filter_coefs[2];
  // index 3 ignored on purpose
  this->a1 = filter_coefs[4];
  this->a2 = filter_coefs[5];
}

/**
 * First method with the First Direct form for the equation of the filter
 * 
*/
void biquad::process(jack_nframes_t nframes,
                     const sample_t *const in,
                     sample_t *const out) {
  const sample_t *const end_ptr = in + nframes;
  const sample_t *in_ptr = in;
  sample_t *out_ptr = out;

  for (; in_ptr != end_ptr;) {
    sample_t x = *in_ptr++;
    sample_t y = this->b0 * x + this->b1 * this->x_minus_1 + this->b2 * this->x_minus_2 - this->a1 * this->y_minus_1 - this->a2 * this->y_minus_2;

    *out_ptr++ = y;

    // Actualizar las variables de estado
    this->x_minus_2 = this->x_minus_1;
    this->x_minus_1 = x;
    this->y_minus_2 = this->y_minus_1;
    this->y_minus_1 = y;
  }
}

/**
 * Second method with the Second Direct Transpose form for the equation of the filter
 */
void biquad::process2(jack_nframes_t nframes,
                     const sample_t *const in,
                     sample_t *const out) {
  const sample_t *const end_ptr = in + nframes;
  const sample_t *in_ptr = in;
  sample_t *out_ptr = out;

  for (; in_ptr != end_ptr;) {
    sample_t x = *in_ptr++;
    sample_t y = this->b0 * x + this->w1_minus_1;

    this->w1_minus_1 = this->w1;
    this->w1 = this->b1 * x - this->a1 * y + this->w2_minus_1;
    this->w2_minus_1 = this->w2;
    this->w2 = this->b2 * x - this->a2 * y; 

    *out_ptr++ = y;
  }
}

void biquad::process3(jack_nframes_t nframes,
                      const sample_t * __restrict__ in,
                      sample_t * __restrict__ out) {
    const sample_t * const __restrict__ end_ptr = in + nframes;

    // Cargar los coeficientes y variables de estado en variables locales
    sample_t b0 = this->b0;
    sample_t b1 = this->b1;
    sample_t b2 = this->b2;
    sample_t a1 = this->a1;
    sample_t a2 = this->a2;
    sample_t w1 = this->w1;
    sample_t w1_minus_1 = this->w1_minus_1;
    sample_t w2 = this->w2;
    sample_t w2_minus_1 = this->w2_minus_1;

    for (; in != end_ptr; ++in, ++out) {
        sample_t x = *in;
        sample_t y = b0 * x + w1_minus_1;

        w1_minus_1 = w1;
        w1 = b1 * x - a1 * y + w2_minus_1;
        w2_minus_1 = w2;
        w2 = b2 * x - a2 * y; 

        *out = y;
    }

    // Guardar las variables de estado actualizadas de vuelta en la clase
    this->w1 = w1;
    this->w1_minus_1 = w1_minus_1;
    this->w2 = w2;
    this->w2_minus_1 = w2_minus_1;
}