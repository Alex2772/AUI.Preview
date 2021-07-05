//
// Created by alex2 on 6/28/2021.
//

#pragma once

#include "ClassDescriptor.h"
#include <Cpp/Runtime/Class.h>
#include <AUI/View/AView.h>

template<>
struct class_descriptor<AView>: Runtime::Class<AView>, Runtime::IClass {
public:
    class_descriptor();
    ~class_descriptor() override = default;
};




