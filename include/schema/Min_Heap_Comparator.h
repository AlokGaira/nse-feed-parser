//
// Created by alok on 21/11/18.
//

#ifndef LEARN_MIN_HEAP_COMPARATOR_H
#define LEARN_MIN_HEAP_COMPARATOR_H

#include "Depth.h"


struct Min_Heap_Comparator {
    bool operator()(const Depth *a, const Depth *b) {
        return a->price < b->price;
    }
};


#endif //LEARN_MIN_HEAP_COMPARATOR_H
