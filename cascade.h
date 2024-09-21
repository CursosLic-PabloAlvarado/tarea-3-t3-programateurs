#include <cstring>
using namespace std;

#include <cstring>

#ifndef _cascade_H
#define _cascade_H


#include "jack_client.h"

/**
 * Jack client class
 *
 * This class wraps some basic jack functionality.
 */
class cascade : public jack::client {
    
public:
  // typedef jack::client::sample_t sample_t;
  
  /**
   * The default constructor performs some basic connections.
   */
  cascade();
  ~cascade();

  /**
   * Passthrough functionality
   */
  virtual bool process(jack_nframes_t nframes,
                       const sample_t *const in,
                       sample_t *const out) override;
};


#endif
