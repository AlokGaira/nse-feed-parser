//
// Created by alok on 28/11/18.
//

#ifndef LEARN_CONTRACT_FILE_RECORD_H
#define LEARN_CONTRACT_FILE_RECORD_H

#include <iostream>
class Contract_File_Record {

    /**
     * Contract Information
     */
    char message_type; // CHAR

    /**
     * Stream ID
     */
    int16_t stream_id; // SHORT

    /**
     * Token Number
     */
    int32_t  token_number; // INT

    /**
     *FO & CD:
     *Security Instrument.
     *Eg. FUTIDX
     *CM:
     *Set to “EQUITY”.
     *CO:
     *Commodity Instrument.
     *Eg. FUTENR, FUTBLN
     */
    char instrument[6];

    /**
     * Security Symbol
     */
    char symbol[10];

    /**
     *FO & CD:
     *Expiry date of contract in
     *seconds from 01-Jan1980
     *00:00:00
     *CM:
     *Not used, set to 0.
     */
    int32_t expiry_date; // INT

    /**
     *FO & CD:
     *Strike Price Of Contract
     *(In Paise).
     *For FO segment this
     *should be divided by 100
     *for converting into
     *Rupees.
     *For CD segment this
     *should be divided by 10^7
     *for converting into
     *Rupees.
     *This will be zero in case
     *of futures contract.
     *CM:
     *Not used, set to 0.
     *CO:
     *This will be zero in case
     *of futures commodity
     *contract.
     */


    int32_t strike_price; // INT

    /**
     * FO & CD
     * Option Type for the
     * contract
     * CM:
     * Series of the security.
     * CO:
     * Not used currently
     */
    char option_type[2]; // CHAR

    Contract_File_Record(std::string csv){

    }
};


#endif //LEARN_CONTRACT_FILE_RECORD_H
