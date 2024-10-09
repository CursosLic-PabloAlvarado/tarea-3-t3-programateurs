#include <cstring>
using namespace std;

#ifndef _cascade_H
#define _cascade_H


#include "biquad.h"
#include <vector>

/**
 * Jack client class
 *
 * This class wraps some basic jack functionality.
 */
class cascade {
    
public:
  typedef jack::client::sample_t sample_t;
  
  /**
   * The default constructor performs some basic connections.
   */
  cascade();
  ~cascade();

  biquad first_stage;
  biquad second_stage;
  biquad third_stage; // use for stop band and pass band

  std::vector<biquad*> stages;


  void set_coefficients(std::vector< std::vector< sample_t > > filter_coefs_matrix);

  /**
   * Cascade functionality
   */
  void process(jack_nframes_t nframes,
                       const sample_t *const in,
                       sample_t *const out);

  void process2(jack_nframes_t nframes,
                       const sample_t *const in,
                       sample_t *const out);
  void process3(jack_nframes_t nframes,
                      const sample_t * __restrict__ in,
                      sample_t * __restrict__ out);
};


#endif
