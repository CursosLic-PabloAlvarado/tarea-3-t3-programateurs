using namespace std;

#ifndef _biquad_H
#define _biquad_H


#include "jack_client.h"
#include <cstring>

/**
 * Jack client class
 *
 * This class wraps some basic jack functionality.
 */
class biquad : public jack::client {
    
public:
  // typedef jack::client::sample_t sample_t;
  
  /**
   * The default constructor performs some basic connections.
   */
  biquad();
  ~biquad();

  /**
   * Passthrough functionality
   */
  virtual bool process(jack_nframes_t nframes,
                       const sample_t *const in,
                       sample_t *const out) override;
};


#endif