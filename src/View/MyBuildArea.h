//
// Created by alex2 on 6/25/2021.
//

#pragma once


#include <AUI/View/AViewContainer.h>

class MyBuildArea: public AViewContainer {
public:
    explicit MyBuildArea(const _<AView>& wrappedView);
};


