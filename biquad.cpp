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
}

biquad::~biquad() {
}
  
void biquad::set_coefficients(std::vector< sample_t > filter_coefs){
  this->b0 = filter_coefs[0];
  this->b1 = filter_coefs[1];
  this->b2 = filter_coefs[2];
  this->a1 = filter_coefs[4];
  this->a2 = filter_coefs[5];
}

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by 
   * the user (e.g. using Ctrl-C on a unix-ish operating system)
   */
void biquad::process(jack_nframes_t nframes,
                     const sample_t *const in,
                     sample_t *const out) {
  const sample_t *const end_ptr = in + nframes;
  const sample_t *in_ptr = in;
  sample_t *out_ptr = out;

  for (; in_ptr != end_ptr;) {
    sample_t x = *in_ptr++;
    sample_t y = this->b0 * x + this->b1 * this->x_minus_1 + this->b2 * this->x_minus_2- this->a1 * this->y_minus_1 - this->a2 * this->y_minus_2;

    *out_ptr++ = y;

    // Actualizar las variables de estado
    this->x_minus_2 = this->x_minus_1;
    this->x_minus_1 = x;
    this->y_minus_2 = this->y_minus_1;
    this->y_minus_1 = y;
  }
}