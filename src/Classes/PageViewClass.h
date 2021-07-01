//
// Created by alex2 on 6/30/2021.
//

#pragma once


#include <AUI/View/APageView.h>
#include "ViewContainerClass.h"

template<>
struct class_descriptor<APageView>: public class_descriptor<AViewContainer>, public Runtime::Class<APageView> {
    class_descriptor();
};


