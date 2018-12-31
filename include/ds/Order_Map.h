//
// Created by alok on 21/11/18.
//

#ifndef LEARN_ORDER_MAP_H
#define LEARN_ORDER_MAP_H

#include <map>
#include "../schema/Order_Message.h"
#include "../schema/Trade_Message.h"

class Order_Map {

    std::map<double, Order_Message> order_map;
    std::map<double, Order_Message>::const_iterator it;
public:
    Order_Map() {

    }

private:
    void insert(Order_Message &order_message) {
        if (exists(order_message.order_id)) {
            order_map.insert(std::pair<double, Order_Message>
                                     (order_message.order_id, Order_Message::clone_order_message(order_message)));
        }
    }

    bool modify_order(Order_Message &order_message) {
        if (exists(order_message.order_id)) {
            // Order exists in map
            Order_Message::copy_order_message(order_message, order_map.at(order_message.order_id));
        }

        // TODO: What if order doesn't exist
    }

    bool cancel_order(Order_Message &order_message) {
        if (exists(order_message.order_id)) {
            // Order exists in map
            delete_order(order_message.order_id);
            int num = order_map.erase(order_message.order_id);
        }

        // TODO: What if order doesn't exist
    }

    bool delete_order(double order_id) {
        if (exists(order_id)) {
            // Order exists in map
            int num = order_map.erase(order_id);
        }

        // TODO: What if order doesn't exist
    }

    /**
     * order_id can be a "buy_order_id" or a "sell_order_id" from Trade_Message
     */
    Order_Message* update_order_from_trade(Trade_Message &trade_message, double order_id) {

        // Buy Order
        if (exists(order_id)) {
            Order_Message& order_message = order_map.at(order_id);
            Order_Message::update_order_from_trade(order_message, trade_message);
            if (order_message.quantity <= 0) {
                // Order is complete hence delete it from map
                delete_order(order_message.order_id);
                return NULL;
            }
            return &order_message;
        }

        return NULL;

        // TODO: What if order doesn't exist
    }

    bool exists(int32_t order_id) {
        it = order_map.find(order_id);
        return it != order_map.end();
    }

};


#endif //LEARN_ORDER_MAP_H
