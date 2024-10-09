#ifndef _cascade_temp_H
#define _cascade_temp_H

#include <cstring>
#include <vector>
using namespace std;
#include "biquad.h"

/**
 * Jack client template class
 *
 * This class wraps some basic jack functionality and supports a variable
 * number of biquad stages.
 */
template <size_t N>
class cascade_temp {
public:
    typedef jack::client::sample_t sample_t;

    /**
     * The default constructor performs some basic connections.
     */
    cascade_temp();
    ~cascade_temp();

    std::vector<biquad> stages; // Usar std::vector para almacenar biquads

    void set_coefficients(std::vector<std::vector<sample_t>> filter_coefs_matrix);

    /**
     * Cascade functionality
     */
    void process2(jack_nframes_t nframes, const sample_t * __restrict__ in, sample_t * __restrict__ out);
    void process3(jack_nframes_t nframes, const sample_t * __restrict__ in, sample_t * __restrict__ out);
};

#include "cascade_temp.tpp"
#endif
