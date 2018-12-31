//
// Created by alok on 22/11/18.
//

#ifndef LEARN_MARKET_DEPTH_MAP_H
#define LEARN_MARKET_DEPTH_MAP_H

#include <map>
#include <iostream>
#include "../schema/Order_Message.h"
#include "../schema/Trade_Message.h"
#include "Market_Depth.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <boost/unordered_map.hpp>     //boost::unordered_map
#include <functional>                  //std::equal_to
#include <boost/functional/hash.hpp>   //boost::hash

class Market_Depth_Map {
private:
    std::map<int32_t, Market_Depth> market_depth_map;
    std::map<int32_t, Market_Depth>::const_iterator it;
public:
    Market_Depth_Map() { }

    void insert(Order_Message &order_message) {
        if (exists(order_message.token)) {
            Market_Depth &market_depth = market_depth_map.at(order_message.token);
            market_depth.insert_from_order(order_message);
        } else {
            market_depth_map.insert(std::pair<int32_t, Market_Depth>(order_message.token, Market_Depth()));
        }
    }

    bool exists(int32_t token) {
        it = market_depth_map.find(token);
        return it != market_depth_map.end();
    }
};


#endif //LEARN_MARKET_DEPTH_MAP_H
