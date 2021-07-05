//
// Created by alex2 on 7/3/2021.
//

#pragma once

#include <AUI/View/ATabView.h>
#include <Cpp/Runtime/Class.h>
#include "GetClassDescriptor.h"

template<>
struct class_descriptor<ATabView>: public class_descriptor<AView>, public Runtime::Class<ATabView> {
public:
    class_descriptor();
};


