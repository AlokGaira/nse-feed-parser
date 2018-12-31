//
// Created by alok on 28/11/18.
//

#ifndef LEARN_OHLC_POOL_H
#define LEARN_OHLC_POOL_H

#include <boost/pool/pool.hpp>
#include "OHLC.h"
class OHLC_Pool{
    boost::object_pool<OHLC> pool;

};

#endif //LEARN_OHLC_POOL_H
