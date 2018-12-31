//
// Created by alok on 21/11/18.
//

#ifndef LEARN_TRADE_MESSAGE_H
#define LEARN_TRADE_MESSAGE_H

#include "./Stream_Header.h"

/*
 * CHAR (1 Bytes) --> char
 * SHORT (2 Bytes) --> int16_t
 * INT (4 Bytes) --> int32_t
 * LONG (8 Bytes) --> int64_t
 * DOUBLE (8 Bytes) --> double
 * */
#pragma pack(1)

struct Trade_Message {
    Stream_Header stream_header;

    /**
     * ‘T’ = Trade Message
     */
    char message_type; // CHAR

    /**
     * Time in nanoseconds from 01-Jan-1980
     * 00:00:00
     */

    int64_t timestamp; // LONG

    /**
     * Day Unique Order Reference Number for
     * Buy-Side Order
     */
    double buy_order_id; // DOUBLE


    /**
     * Day Unique Order Reference Number for
     * SELL-Side Order
     */
    double sell_order_id; // DOUBLE

    /**
     * Unique Contract Identifier
     */
    int32_t token; // INT

    /**
     * Price of the order (In
     * Paise)
     * This field contains the
     * price at which the order
     * is placed. The price is in
     * multiples of the tick
     * size. For FO and CM
     * segments this should be
     * divided by 100 for
     * converting into Rupees.
     * For CD segment this
     * should be divided by
     * 10^7
     * for converting into
     * Rupees.
     * For CO segment, this
     * should be divided by
     * 10^4
     * for converting into
     * rupees.
     */
    int32_t trade_price; // INT

    int32_t trade_quantity; // INT
};


#endif //LEARN_TRADE_MESSAGE_H
