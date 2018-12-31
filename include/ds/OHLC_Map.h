//
// Created by alok on 28/11/18.
//

#ifndef LEARN_OHLC_MAP_H
#define LEARN_OHLC_MAP_H

#include <iostream>
#include <map>
#include "../schema/OHLC.h"

#define INTERVAL 1000 * 1000
#define SECOND_MULTIPLIER 1000 * 1000 * 1000
class OHLC_Map {
    static int64_t second_multiplier =  1000 * 1000 * 1000;
    std::map<int32_t , Order_Message> ohlc_map_prev;
    std::map<int32_t , Order_Message> ohlc_map_new;

    std::map<int32_t , Order_Message>::const_iterator it;

    void update(Trade_Message &trade_message){

    }

private:
    void convert_nano_to_floor_milli_second(int64_t timestamp) {
        // timestamp is in nanoseconds
        // first convert in seconds and then convert to milliseconds
        return (timestamp / second_multiplier) * 1000;
    }

};


#endif //LEARN_OHLC_MAP_H
