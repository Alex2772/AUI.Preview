//
// Created by alex2 on 6/30/2021.
//

#pragma once


#include <AUI/View/APageView.h>
#include "ViewContainerClass.h"

template<>
struct class_descriptor<APageView>: class_descriptor<AViewContainer>, Runtime::Class<APageView> {
    class_descriptor();
    ~class_descriptor() override = default;
};


