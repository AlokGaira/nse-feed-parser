//
// Created by alok on 29/11/18.
//

#ifndef LEARN_BCAST_HEADER_H
#define LEARN_BCAST_HEADER_H

#include "Types.h"
#define BCAST_HEADER_LENGTH 40

#pragma pack(2)
struct Bcast_Header {
    CHAR reserved[4];
    LONG log_time;
    CHAR alpha_char[2];
    SHORT transcode;
    SHORT error_code;
    LONG bcseq_no;
    CHAR reserved_2[4];
    CHAR time_stamp_2[8];
    CHAR filler_2[8];
    SHORT message_length;

    void big_to_little(){
        this->log_time = boost::endian::endian_reverse(this->log_time);
        this->transcode = boost::endian::endian_reverse(this->transcode);
        this->error_code = boost::endian::endian_reverse(this->error_code);
        this->bcseq_no = boost::endian::endian_reverse(this->bcseq_no);

        this->message_length = boost::endian::endian_reverse(this->message_length);
    }
};


#endif //LEARN_BCAST_HEADER_H
