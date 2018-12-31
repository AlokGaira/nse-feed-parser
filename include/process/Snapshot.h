//
// Created by alok on 29/11/18.
//

#ifndef LEARN_SNAPSHOT_H
#define LEARN_SNAPSHOT_H

#include <iostream>
#include <boost/endian/conversion.hpp>
#include <boost/endian/conversion.hpp>

#include "Types.h"
#include "Bcast_Pack_Data.h"
#include "Bcast_Header.h"
#include "Interactive_Only_MBP_Data.h"
#include <arpa/inet.h>
#include "../../third_party/lzo-1.07/include/lzo1z.h"

namespace Snapshot {

    void process_mbp(unsigned char *uncompressed_buffer, unsigned int uncompressed_offset) {
        SHORT number_of_packets;
        memcpy(&number_of_packets, uncompressed_buffer + uncompressed_offset, 2);
        boost::endian::endian_reverse(number_of_packets);
        std::cout << "number_of_packets :: " << number_of_packets << std::endl;

        uncompressed_offset += SHORT_BYTE_LENGTH;

        for (int16_t i = 0; i < number_of_packets; i++) {
            Interactive_Only_MBP_Data interactive_only_mbp_data;
            memcpy(&interactive_only_mbp_data, uncompressed_buffer + uncompressed_offset,
                   INTERACTIVE_ONLY_MBP_DATA_LENGTH);
            interactive_only_mbp_data.big_to_little();

            uncompressed_offset += INTERACTIVE_ONLY_MBP_DATA_LENGTH - SHORT_BYTE_LENGTH;

            std::cout << "number_of_packets :: " << interactive_only_mbp_data.token << std::endl;
            // TODO Print MBP
        }
    }

    void process(unsigned char * buffer, int16_t bytes_received) {


        int16_t offset = 0;

        Bcast_Pack_Data bcast_pack_data;
        memcpy(&bcast_pack_data, buffer, BCAST_PACKET_DATA_LENGTH);
        offset += BCAST_PACKET_DATA_LENGTH;
        bcast_pack_data.big_to_little();
        std::cout << sizeof(Bcast_Pack_Data);



        std::cout << "cNetId :: " << bcast_pack_data.cNetId[0] << std::endl;
        std::cout << "iNoPackets :: " << bcast_pack_data.iNoPackets << std::endl;


        for (int i = 0; i < bcast_pack_data.iNoPackets; i++) {
            SHORT compression_len;
            memcpy(&compression_len, buffer + offset, SHORT_BYTE_LENGTH);

            compression_len = boost::endian::endian_reverse(compression_len);

            std::cout << "compression_len :: " << compression_len << std::endl;

            offset += SHORT_BYTE_LENGTH;
            unsigned int size_uncompressed_buffer;
            unsigned char *uncompressed_buffer = new unsigned char[1024 * 10 * 10];

            if (compression_len == 0) {
                // Data is not compressed
            } else {
                unsigned int uncompressed_offset = 0;
//                const char* uncompress_start =
                lzo1z_decompress((buffer + offset), compression_len, uncompressed_buffer, &size_uncompressed_buffer,
                                 NULL);

                std::cout << "size_of_uncompressed_buffer :: " << size_uncompressed_buffer << std::endl;

                // market type (1 Byte)
                // '4 for cash market
                // '2' for future and options market
                CHAR market_type;
                memcpy(&market_type, uncompressed_buffer + uncompressed_offset, CHAR_BYTE_LENGTH);
                uncompressed_offset += CHAR_BYTE_LENGTH;

                // ignore next seven byte (7 Byte)
                uncompressed_offset += CHAR_BYTE_LENGTH
                                       * 7;

                Bcast_Header bcast_header;
                memcpy(&bcast_header, uncompressed_buffer + uncompressed_offset, BCAST_HEADER_LENGTH);
                bcast_header.big_to_little();
                uncompressed_offset += BCAST_HEADER_LENGTH;

                std::cout << "transcode :: " << bcast_header.transcode << std::endl;

                switch (bcast_header.transcode) {
                    // MBO MBP
                    case 7200:
                        break;
                        // Ticker and Market Index
                    case 7202:
                        break;
                        // multiple index broadcast
                    case 7207:
                        break;
                        // only MBP
                    case 7208:
                        process_mbp(uncompressed_buffer, uncompressed_offset);
                        break;
                        // spread contracts
                    case 7211:
                        //processSpreadContracts(buffer, newOffset, parsedData);     //TODO we are not handling spreadcontracts
                        break;
                        // broadcast messages - CM, FO and CDS
                    case 6511:
                    case 6521:
                    case 6531:
                    case 6571:
                    case 6522:
                    case 6583:
                    case 6584:
                        break;
                    case 7305:
                        //processCreditRating(buffer, newOffset, parsedData);
                        break;
                    default:
                        // "Ignoring NSE Feed Tx Code: " + transCode
                        break;
                }
                offset += compression_len;
            }

        }
    }

};






#endif //LEARN_SNAPSHOT_H
