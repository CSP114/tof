#ifndef TOF_ANALYZER_H_INCLUDED
#define TOF_ANALYZER_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int tl;
    int tr;
    int bl;
    int br;
} trigger_index_t;

void find_object_distance(const uint16_t* interleaved_signal, int size, uint16_t treshold, trigger_index_t* trigger_data);
char estimate_direction(trigger_index_t* trigger_data);

#ifdef __cplusplus
}
#endif

#endif
