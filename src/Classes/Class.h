//
// Created by alex2 on 6/30/2021.
//

#pragma once

#include "ViewClass.h"
#include "ViewContainerClass.h"

template<class T>
class_descriptor<T>& get_class_descriptor() {
    static class_descriptor<T>* s = new class_descriptor<T>;
    return *s;
}
