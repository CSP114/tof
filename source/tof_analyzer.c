#include <stdio.h>
#include "tof_analyzer.h"

void trigger_data_init(trigger_index_t* trigger_data){
    trigger_data->tl = -1;
    trigger_data->tr = -1;
    trigger_data->bl = -1;
    trigger_data->br = -1;
}

#define DEAD_ZONE_OFFSET 220
#define TOP_LEFT_CHANNEL  0
#define TOP_RIGHT_CHANNEL  3
#define BOTTOM_LEFT_CHANNEL  1
#define BOTTOM_RIGHT_CHANNEL  2

void find_object_distance(const uint16_t* interleaved_signal, int total_length, uint16_t treshold,  trigger_index_t* trigger_data){
    int signal_length = total_length/4;
    int trigger_index[] = {-1, -1, -1, -1};
    trigger_data_init(trigger_data);

    for(int sample_index = 0; sample_index < signal_length; sample_index++){
        for(int channel = 0; channel < 4; channel++){
            int interleaved_index = (sample_index*4) + channel;
            uint16_t sample_value = interleaved_signal[interleaved_index];
            if((sample_index > DEAD_ZONE_OFFSET) && (trigger_index[channel] < 0) && (sample_value > treshold)){
                trigger_index[channel] = sample_index;
            }
        }
    }

    trigger_data->tl  = trigger_index[TOP_LEFT_CHANNEL];
    trigger_data->tr  = trigger_index[TOP_RIGHT_CHANNEL];
    trigger_data->bl  = trigger_index[BOTTOM_LEFT_CHANNEL];
    trigger_data->br  = trigger_index[BOTTOM_RIGHT_CHANNEL];
}

#define DIRECTIONAL_TRESHOLD 10

char estimate_direction(trigger_index_t* trigger_data){
    int bl = trigger_data->bl;
    int br = trigger_data->br;
    int tl = trigger_data->tl;
    int tr = trigger_data->tr;

    int left = -1;
    int right = -1;

    if(bl >= 0 && tl >= 0){
        left = (bl < tl) ? bl : tl;
    }else if(bl >= 0 || tl >= 0){
        left = (bl >= 0) ? bl : tl;
    }

    if(br >= 0 && tr >= 0){
        right = (br < tr) ? br : tr;
    }else if(br >= 0 || tr >= 0){
        right = (br >= 0) ? br : tr;
    }

    if(right < 0 && left < 0){
        return 'x';
    }else if(right < 0){
        return 'l';
    }else if(left < 0){
        return 'r';
    }

    int tof_diference = (left - right);

    if(tof_diference >= DIRECTIONAL_TRESHOLD){
        return 'r';
    }else if(tof_diference <= -DIRECTIONAL_TRESHOLD){
        return 'l';
    }else{
        return 'c';
    }

}
