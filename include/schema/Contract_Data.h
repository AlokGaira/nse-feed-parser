//
// Created by alok on 21/11/18.
//

#ifndef LEARN_CONTRACT_DATA_H
#define LEARN_CONTRACT_DATA_H

#include <iostream>
#include "Trade_Message.h"

/*
 *     "timestamp": 1494837991000,
    "exchange": "NSE_FO",
    "symbol": "NIFTY17MAYFUT",
    "ltp": 9446.8,
    "open": 9448,
    "high": 9454.4,
    "low": 9437,
    "close": 9414.8,
    "vtt": 2802525,
    "atp": 9446.71,
    "oi": 21256725,
    "spot_price": 9442.15,
    "total_buy_qty": 830925,
    "total_sell_qty": 858375,
    "lower_circuit": 8473.35,
    "upper_circuit": 10356.3,
    "bids": [
      {
        "quantity": 900,
        "price": 9446.7,
        "orders": 2
      },
      {
        "quantity": 75,
        "price": 9446.65,
        "orders": 1
      },
      {
        "quantity": 1050,
        "price": 9446.6,
        "orders": 4
      },
      {
        "quantity": 150,
        "price": 9446.55,
        "orders": 1
      },
      {
        "quantity": 75,
        "price": 9446.1,
        "orders": 1
      }
    ],
    "asks": [
      {
        "quantity": 450,
        "price": 9447,
        "orders": 1
      },
      {
        "quantity": 450,
        "price": 9447.3,
        "orders": 1
      },
      {
        "quantity": 900,
        "price": 9447.4,
        "orders": 1
      },
      {
        "quantity": 75,
        "price": 9447.45,
        "orders": 1
      },
      {
        "quantity": 75,
        "price": 9447.55,
        "orders": 1
      }
    ],
     "ltt": 1494837991000
 * */
class Contract_Data {
public:

/**
     * Unique Contract
     * Identifier
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
    int32_t last_traded_price; // INT

    int32_t open; // INT
    int32_t high; // INT
    int32_t low; // INT
    int32_t close; // INT


    int64_t volume_traded_today;
    /**
     * Total buy quantity available.
     * For FO Market this value = Quantity * LotSize
     */
    int32_t total_buy_quantity;

    /**
     * Total sell quantity available
     * For FO Market this value = Quantity * LotSize
     */
    int32_t total_sell_quantity;

    /**
     * Open interest can't be calculated from TBT feed.
     */
//    int32_t open_interest;

    /**
     * Should be calculated from our side
     * */
    double average_traded_price;

    /*
     * Values fetched from contract information file
     * */
    int32_t lower_circuit_limit;
    int32_t upper_circuit_limit;

    /**
     * Time in nanoseconds from 01-Jan-1980
     * 00:00:00
     */
    int64_t last_traded_timestamp; // LONG

    /**
     * Flag to check first packet
     */
    bool first_packet;


    Contract_Data(int32_t token, int32_t last_traded_price, int32_t open, int32_t high, int32_t close, int32_t low,
                  int64_t volume_traded_today, int32_t total_buy_quantity, int32_t total_sell_quantity,
                  double average_traded_price, int32_t lower_circuit_limit, int64_t last_traded_timestamp,
                  int32_t upper_circuit_limit, bool first_packet, int64_t total_traded_value) : token(token),
                                                                                                last_traded_price(
                                                                                                        last_traded_price),
                                                                                                open(open), high(high),
                                                                                                close(close), low(low),
                                                                                                volume_traded_today(
                                                                                                        volume_traded_today),
                                                                                                total_buy_quantity(
                                                                                                        total_buy_quantity),
                                                                                                total_sell_quantity(
                                                                                                        total_sell_quantity),
                                                                                                average_traded_price(
                                                                                                        average_traded_price),
                                                                                                lower_circuit_limit(
                                                                                                        lower_circuit_limit),
                                                                                                last_traded_timestamp(
                                                                                                        last_traded_timestamp),
                                                                                                upper_circuit_limit(
                                                                                                        upper_circuit_limit),
                                                                                                first_packet(
                                                                                                        first_packet),
                                                                                                total_traded_value(
                                                                                                        total_traded_value) { }

    /**
     * lower_circuit and upper_circuit should be updated from contract file or feed
     */
    void update_circuits(int32_t lower_circuit_limit, int32_t upper_circuit_limit) {
        this->lower_circuit_limit = lower_circuit_limit;
        this->upper_circuit_limit = upper_circuit_limit;
    }

    /**
     * close price is the previous day close price which should get updated via contract file
     */
    void update_close(int32_t close) {
        this->close = close;
    }

    /**
     * Update contract data from trade update
     */
    void update_contract_data(Trade_Message &trade_message) {

        if (first_packet) {
            open = trade_message.trade_price;
            high = trade_message.trade_price;
            low = trade_message.trade_price;

            // Setting first packet as false
            first_packet = false;
            return;
        } else {
            if (trade_message.trade_price > high) {
                high = trade_message.trade_price;
            }

            if (trade_message.trade_price < low) {
                low = trade_message.trade_price;
            }

        }

        volume_traded_today += trade_message.trade_quantity;
        total_traded_value += trade_message.trade_quantity * trade_message.trade_price;
        average_traded_price = total_traded_value / volume_traded_today;

        last_traded_price = trade_message.trade_price;
        last_traded_timestamp = trade_message.timestamp;
    }

private:
    int64_t total_traded_value;
};


#endif //LEARN_CONTRACT_DATA_H
