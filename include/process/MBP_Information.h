//
// Created by alok on 29/11/18.
//

#ifndef LEARN_MBP_INFORMATION_H
#define LEARN_MBP_INFORMATION_H

#include <arpa/inet.h>
#include <boost/endian/conversion.hpp>

#include "Types.h"

#pragma pack(2)
struct MBP_Information {
    LONG quantity; // LONG
    LONG price; // LONG
    SHORT number_of_orders; // SHORT
    SHORT bb_buy_sell_flag; // SHORT

    void big_to_little(){

        this->quantity = boost::endian::endian_reverse(this->quantity);
        this->price = boost::endian::endian_reverse(this->price);
        this->number_of_orders = boost::endian::endian_reverse(this->number_of_orders);
        this->bb_buy_sell_flag = boost::endian::endian_reverse(this->bb_buy_sell_flag);

    }
};


#endif //LEARN_MBP_INFORMATION_H
