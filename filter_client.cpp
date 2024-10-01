#include "filter_client.h"
#include <iostream>

filter_client::filter_client() : jack::client() {
  set_test_coefficients();
}

filter_client::~filter_client() {
}

void filter_client::set_coefficients(std::vector< std::vector< sample_t > > filter_coefs_matrix){
  cascade_filter.set_coefficients(filter_coefs_matrix);
}

void filter_client::set_test_coefficients(){
  std::vector< sample_t > filter_coefs;
  // Paso bajo
  filter_coefs.push_back(0.00016822f);
  filter_coefs.push_back(0.00033645f);
  filter_coefs.push_back(0.00016822f);
  filter_coefs.push_back(1.0f);
  filter_coefs.push_back(-1.96298009f);
  filter_coefs.push_back(0.96365298f);
  
  test_filter.set_coefficients(filter_coefs);
}


void filter_client::passThrough(jack_nframes_t nframes,
                   const sample_t *const in,
                   sample_t *const out){
  memcpy (out, in, sizeof(sample_t)*nframes);
}
  
/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by 
   * the user (e.g. using Ctrl-C on a unix-ish operating system)
   */
bool filter_client::process(jack_nframes_t nframes,
                                 const sample_t *const in,
                                 sample_t *const out) {

  if (this->is_passthrough){
    this->passThrough(nframes, in, out);

  }else if (this->is_test_filter){
    test_filter.process(nframes, in, out);

  // You can use process or process2  (process2 is more efficient)
  }else if (this->is_cascade){
    cascade_filter.process(nframes, in, out);
  }
  
  return true;
}