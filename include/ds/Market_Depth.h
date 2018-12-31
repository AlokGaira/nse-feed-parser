//
// Created by alok on 21/11/18.
//

#ifndef LEARN_MARKET_DEPTH_H
#define LEARN_MARKET_DEPTH_H

#define DEPTH_LEVEL 20

#include <iostream>
#include <boost/heap/priority_queue.hpp>
#include "../schema/Order_Message.h"
#include "../schema/Depth.h"
#include "../schema/Min_Heap_Comparator.h"
#include "../schema/Max_Heap_Comparator.h"

class Market_Depth {
    // Priority queue clears memory by itself
    boost::heap::priority_queue<Depth, std::vector<Depth>, Min_Heap_Comparator> buy_market_depth;
    boost::heap::priority_queue<Depth, std::vector<Depth>, Max_Heap_Comparator> sell_market_depth;

public:
    Market_Depth() { }

    void insert_from_order(Order_Message &order_message) {

        if (order_message.order_type == 'B') {

            // Buy Order
            buy_market_depth.push(Order_Message::get_depth_from_order(order_message));
            if (buy_market_depth.size() > DEPTH_LEVEL) {
                buy_market_depth.pop();
            }
        } else {

            // Sell Order
            sell_market_depth.push(Order_Message::get_depth_from_order(order_message));
            if (sell_market_depth.size() > DEPTH_LEVEL) {
                sell_market_depth.pop();
            }

        }

    }

    std::vector<Depth> get_asks() {
        //if you want to provide a size
        std::vector<Depth> asks(DEPTH_LEVEL);
        // One by one extract items from min heap
        std::for_each(buy_market_depth.begin(), buy_market_depth.end(),
                      [](const Depth &depth) {
                          asks.push_back(Depth{
                                  .price = depth.price,
                                  .quantity = depth.quantity
                          });
                      });

        return asks;
    }
};


#endif //LEARN_MARKET_DEPTH_H
