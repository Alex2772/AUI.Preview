//
// Created by alex2 on 6/28/2021.
//

#include "IClass.h"

using namespace Runtime;

bool IClass::isClass() {
    return true;
}

IClass* IClass::asClass() {
    return this;
}
