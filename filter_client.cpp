#include "filter_client.h"


filter_client::filter_client() : jack::client() {
}

filter_client::~filter_client() {
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
  memcpy (out, in, sizeof(sample_t)*nframes);
  return true;
}