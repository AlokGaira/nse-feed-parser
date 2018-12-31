//
// Created by alok on 28/11/18.
//

#ifndef LEARN_OHLC_H
#define LEARN_OHLC_H
#include <iostream>
#include "Trade_Message.h"

class OHLC {
    static int32_t second_multiplier =  1000 * 1000 * 1000;
    static int32_t milli_second_multiplier =  1000 * 1000;

    int32_t interval = 1000;

    int32_t token;

    int32_t current_timestamp;
    int32_t prev_timestamp;

    int32_t open;
    int32_t high;
    int32_t low;
    int32_t close;
    int32_t volume;

    int32_t prev_open;
    int32_t prev_high;
    int32_t prev_low;
    int32_t prev_close;
    int32_t prev_volume;


    OHLC (Trade_Message& trade_message, int32_t interval){
        this->interval = interval * 1000;
        token = trade_message.token;

        current_timestamp = convert_nano_to_floor_milli_second(trade_message.timestamp);
        prev_timestamp = convert_nano_to_floor_milli_second(trade_message.timestamp);

        open = trade_message.trade_price;
        high = trade_message.trade_price;
        low = trade_message.trade_price;
        close = trade_message.trade_price;
        volume += trade_message.trade_quantity;

        prev_open = trade_message.trade_price;
        prev_high = trade_message.trade_price;
        prev_low = trade_message.trade_price;
        prev_close = trade_message.trade_price;
        prev_volume = 0;
    }

    void update_ohlc (Trade_Message& trade_message){
        int32_t timestamp = convert_nano_to_milli_second(trade_message.timestamp);

        if (timestamp >= (current_timestamp + interval)) {
            // This is a packet for the previous interval,
            // hence next interval candle should get created here

            // Swapping timestamp
            prev_timestamp = current_timestamp;
            current_timestamp = current_timestamp + interval;

            // Swapping OHLC
            prev_open = open;
            prev_high = high;
            prev_low = low;
            // Previous candle close will be next candle open
            prev_close = close;

            // Values for new candle
            prev_volume = volume;

            // Values for new candle
            open = prev_close;
            high = trade_message.trade_price;
            low = trade_message.trade_price;
            close = trade_message.trade_price;

            // Reset volume
            volume = 0;
            volume += trade_message.trade_quantity;

            // TODO:: send the new candle to OHLC queue
        } else {
            // This is the packet for the current interval

            if (trade_message.trade_price > high) {
                high = trade_message.trade_price;
            }

            if (trade_message.trade_price < low) {
                low = trade_message.trade_price;
            }

            close = trade_message.trade_price;
            volume += trade_message.trade_quantity;
        }

    }

private:
    void convert_nano_to_floor_milli_second(int64_t timestamp) {
        // timestamp is in nanoseconds
        // first convert in seconds and then convert to milliseconds
        return (timestamp / second_multiplier) * 1000;
    }

    int32_t convert_nano_to_milli_second(int64_t timestamp) {
        // timestamp is in nanoseconds
        // convert it in millisecond without decimal place
        return (timestamp / milli_second_multiplier);
    }
};


#endif //LEARN_OHLC_H
