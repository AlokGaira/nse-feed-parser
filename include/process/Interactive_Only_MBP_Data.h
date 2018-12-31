//
// Created by alok on 29/11/18.
//

#ifndef LEARN_INTERACTIVE_ONLY_MBP_DATA_H
#define LEARN_INTERACTIVE_ONLY_MBP_DATA_H

#include <arpa/inet.h>
#include <boost/endian/conversion.hpp>

#include "Types.h"
#include "MBP_Information.h"
#define INTERACTIVE_ONLY_MBP_DATA_LENGTH 211

// 7200
#pragma pack(2)
struct Interactive_Only_MBP_Data {
    SHORT token; // SHORT
    SHORT book_type; // SHORT
    SHORT trading_status; // SHORT
    LONG volume_traded_today; // LONG

    LONG last_traded_price; // LONG
    CHAR net_change_indicator; // CHAR
    LONG net_price_change_from_closing_price; // LONG
    LONG last_trade_quantity; // LONG

    LONG last_trade_time; // LONG
    LONG average_trade_price; // LONG
    SHORT auction_number; // SHORT
    SHORT auction_status; // SHORT

    SHORT initiator_type; // SHORT
    LONG initiator_price; // LONG
    LONG initiator_quantity; // LONG
    LONG auction_price; // LONG

    LONG auction_quantity; // LONG
    MBP_Information mbp_information[10];
    LONG close_price; // LONG
    LONG open_price; // LONG

    LONG high_price; // LONG
    LONG low_price; // LONG

    void big_to_little(){
        this->token = boost::endian::endian_reverse(this->token);
        this->book_type = boost::endian::endian_reverse(this->book_type);
        this->trading_status = boost::endian::endian_reverse(this->trading_status);
        this->volume_traded_today = boost::endian::endian_reverse(this->volume_traded_today);

        this->last_traded_price = boost::endian::endian_reverse(this->last_traded_price);
        this->net_price_change_from_closing_price = boost::endian::endian_reverse(this->net_price_change_from_closing_price);
        this->last_trade_quantity = boost::endian::endian_reverse(this->last_trade_quantity);

        this->last_trade_time = boost::endian::endian_reverse(this->last_trade_time);
        this->average_trade_price = boost::endian::endian_reverse(this->average_trade_price);
        this->auction_number = boost::endian::endian_reverse(this->auction_number);
        this->auction_status = boost::endian::endian_reverse(this->auction_status);

        this->auction_quantity = boost::endian::endian_reverse(this->auction_quantity);
        for(int16_t i = 0; i < 10; i++){
            mbp_information[i].big_to_little();
        }
        this->close_price = boost::endian::endian_reverse(this->close_price);
        this->open_price = boost::endian::endian_reverse(this->open_price);

        this->high_price = boost::endian::endian_reverse(this->high_price);
        this->low_price = boost::endian::endian_reverse(this->low_price);

    }
};


#endif //LEARN_INTERACTIVE_ONLY_MBP_DATA_H
