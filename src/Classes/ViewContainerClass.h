//
// Created by alex2 on 6/29/2021.
//

#pragma once


#include "ViewClass.h"
#include <AUI/View/AViewContainer.h>

template<>
struct class_descriptor<AViewContainer>: public class_descriptor<AView>, public Runtime::Class<AViewContainer> {
public:
    class_descriptor();
};


