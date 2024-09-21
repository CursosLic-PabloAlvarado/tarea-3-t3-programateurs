#ifndef _filter_client_H
#define _filter_client_H

#include <cstring>
#include "jack_client.h"
#include "biquad.h"

typedef jack::client::sample_t sample_t;

/**
 * Jack client class
 *
 * This class wraps some basic jack functionality.
 */
class filter_client : public jack::client {
    
public:
  
  /**
   * The default constructor performs some basic connections.
   */
  filter_client();
  ~filter_client();

  sample_t b0, b1, b2, a1, a2;
  biquad test_filter;

  bool is_passthrough = true;
  bool is_test_filter = false;
  bool is_cascade = false;

  /**
   * Function to passthorugh
   */
  void passThrough(jack_nframes_t nframes,
                   const sample_t *const in,
                   sample_t *const out);


  void set_coefficients(std::vector< std::vector< sample_t > > filter_coefs_matrix);

  void set_test_coefficients();


  /**
   * process callback
   */
  virtual bool process(jack_nframes_t nframes,
                       const sample_t *const in,
                       sample_t *const out) override;
};


#endif
