#include <cstring>

#ifndef _filter_client_H
#define _filter_client_H


#include "jack_client.h"

/**
 * Jack client class
 *
 * This class wraps some basic jack functionality.
 */
class filter_client : public jack::client {
    
public:
  // typedef jack::client::sample_t sample_t;
  
  /**
   * The default constructor performs some basic connections.
   */
  filter_client();
  ~filter_client();

  /**
   * Passthrough functionality
   */
  virtual bool process(jack_nframes_t nframes,
                       const sample_t *const in,
                       sample_t *const out) override;
};


#endif
