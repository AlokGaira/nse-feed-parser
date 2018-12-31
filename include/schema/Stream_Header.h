//
// Created by alok on 16/11/18.
//

#ifndef LEARN_STREAM_HEADER_H
#define LEARN_STREAM_HEADER_H

#include <zconf.h>

#include <boost/asio/buffer.hpp>

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
struct Stream_Header {
public:

    /**This is the total size of the packet including Header and
     * Data i.e. Sum of length of STREAM_HEADER and STREAM_DATA.
     */
    int16_t message_length; //  SHORT

    /** This identifies a particular stream*/
    int16_t stream_id; //  SHORT

    /**
     * This is the sequence number of the packet for a particular
     * Stream Id
     */
    int64_t sequence_number; // INT

    static Stream_Header clone_stream_header(Stream_Header& stream_header){
        return Stream_Header {
                .message_length = stream_header.message_length,
                .stream_id = stream_header.stream_id,
                .sequence_number = stream_header.sequence_number
        };
    }
};


template<typename Archive>
void serialize(Archive &ar, Stream_Header &stream_header, const unsigned int version) {

    ar & stream_header.message_length;
    ar & stream_header.stream_id;
    ar & stream_header.sequence_number;

}


#endif //LEARN_STREAM_HEADER_H
