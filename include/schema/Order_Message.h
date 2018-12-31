//
// Created by alok on 16/11/18.
//

#ifndef LEARN_ORDERMESSAGE_H
#define LEARN_ORDERMESSAGE_H

#include <iostream>
#include <boost/asio.hpp>
#include "./Stream_Header.h"
#include "./Trade_Message.h"
#include "./Depth.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/*
 * CHAR (1 Bytes) --> char
 * SHORT (2 Bytes) --> int16_t
 * INT (4 Bytes) --> int32_t
 * LONG (8 Bytes) --> int64_t
 * DOUBLE (8 Bytes) --> double
 * */
#pragma pack(1)
struct Order_Message {
    Stream_Header stream_header;
    /**
     * ‘N’ - New Order
     * ‘M’ - Order Modification
     * ‘X’ - Order Cancellation
     */
    char message_type; // CHAR

    /**
     * Time in nanoseconds
     * from 01-Jan-1980 00:00:00
     */
    int64_t timestamp; // LONG

    /**
     * Day Unique Order
     * Reference Number
     */
    double order_id; // DOUBLE

    /**
     * Unique Contract
     * Identifier
     */
    int32_t token; // INT

    /**
     * ‘B’ - Buy Order
     * ‘S’ - Sell Order
     */
    char order_type; // CHAR

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
    int32_t price; // INT

    int32_t quantity; // INT

    /**
     * Update Order From Trade Message
     */
    static void update_order_from_trade(Order_Message& order_message, Trade_Message& trade_message){
        order_message.quantity -= trade_message.trade_quantity;
    }

    static Depth get_depth_from_order(Order_Message& order_message){
        return Depth{
                .price = order_message.price,
                .quantity = order_message.quantity
        };
    }

    static Order_Message clone_order_message(Order_Message& order_message){
        Order_Message new_order_message = {
                .stream_header = Stream_Header::clone_stream_header(order_message.stream_header),
                .message_type = order_message.message_type,
                .timestamp = order_message.timestamp,
                .order_id = order_message.order_id,
                .token = order_message.token,
                .order_type = order_message.order_type,
                .price = order_message.price,
                .quantity = order_message.quantity
        };
        return new_order_message;
    }


    /**
     * Copy A to B
     */
    static void copy_order_message(Order_Message& a, Order_Message& b){
        b.order_id = a.order_id;
        b.message_type = a.message_type;
        b.order_type = a.order_type;
        b.price = a.price;
        b.quantity = a.quantity;
        b.timestamp = a.timestamp;
        b.token = a.token;

        b.stream_header.message_length = a.stream_header.message_length;
        b.stream_header.sequence_number = a.stream_header.sequence_number;
        b.stream_header.stream_id = a.stream_header.stream_id;
    }


};

template<typename Archive>
void serialize(Archive &ar, Order_Message &order_message, const unsigned int version) {

//    ar & boost::serialization::base_object<Stream_Header>(order_message);

    ar & order_message.stream_header;

    ar & order_message.message_type;
    ar & order_message.timestamp;
    ar & order_message.order_id;

    ar & order_message.token;
    ar & order_message.order_type;
    ar & order_message.price;

    ar & order_message.quantity;
}


#endif //LEARN_ORDERMESSAGE_H
