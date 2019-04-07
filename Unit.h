#ifndef PROJECT3_UNIT_H
#define PROJECT3_UNIT_H

#include <iostream>

namespace ariel{
    enum class Unit: int {
        KM,    //0mod3
        HOUR,  //1mod3
        TON,   //2mod3

        M,     //0mod3
        MIN,   //1mod3
        KG,    //2mod3

        CM,    //0mod3
        SEC,   //1mod3
        G      //2mod3
    };
};

#endif //PROJECT3_UNIT_H
