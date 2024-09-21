#ifndef _biquad_H
#define _biquad_H

using namespace std;
#include "jack_client.h"
#include <cstring>

/**
 * Jack client class
 *
 * This class wraps some basic jack functionality.
 */
class biquad {
    
public:
  typedef jack::client::sample_t sample_t;
  
  /**
   * The default constructor performs some basic connections.
   */
  biquad();
  ~biquad();

  sample_t b0, b1, b2, a1, a2;
  sample_t x_minus_1, x_minus_2, y_minus_1, y_minus_2;

  void set_coefficients(std::vector< sample_t > filter_coefs);

  /**
   * IIR
   */
  void process(jack_nframes_t nframes,
                const sample_t *const in,
                sample_t *const out);
};


#endif