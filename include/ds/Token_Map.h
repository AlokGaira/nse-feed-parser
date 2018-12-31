//
// Created by alok on 28/11/18.
//

#ifndef LEARN_TOKEN_MAP_H
#define LEARN_TOKEN_MAP_H

#include <iostream>
#include <map>
#include "../schema/Trade_Message.h"
#include "../schema/Contract_Data.h"

class Token_Map {

    std::map<int32_t, Contract_Data> token_map;
    std::map<int32_t, Contract_Data>::const_iterator it;

private:
    void update(Trade_Message &trade_message) {
        if (exists(trade_message.token)) {
            // Update
            token_map.at(trade_message.token).update_contract_data(trade_message);
            return;
        }

        // Create new contract data
        token_map.insert(std::pair<int32_t, Contract_Data>
                                 (trade_message.token, new Contract_Data()));

        // Update contract data
        token_map.at(trade_message.token).update_contract_data(trade_message);
    }

    // TODO:: update from contract file or its map (al the map should get build during process bot becuase of contract file)

    bool exists(int32_t order_id) {
        it = order_map.find(order_id);
        return it != order_map.end();
    }
};


#endif //LEARN_TOKEN_MAP_H
