//
// Created by alok on 29/11/18.
//

#ifndef LEARN_BCAST_PACK_DATA_H
#define LEARN_BCAST_PACK_DATA_H

#include "arpa/inet.h"
#include <boost/endian/conversion.hpp>
#include "Types.h"
#define BCAST_PACKET_DATA_LENGTH 4
#pragma pack(2)
struct Bcast_Pack_Data {
    CHAR cNetId [2];
    SHORT iNoPackets;

    void big_to_little(){
        this->iNoPackets = boost::endian::endian_reverse(this->iNoPackets);
    }
};


#endif //LEARN_BCAST_PACK_DATA_H
