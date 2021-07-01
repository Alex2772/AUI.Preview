//
// Created by alex2 on 6/28/2021.
//

#include "ViewClass.h"
#include <Visitor/Replicator.h>

class_descriptor<AView>::class_descriptor() {
    registerMemberFunction("setExpanding", &AView::setExpanding);
    registerMemberFunction("addAssName", &AView::addAssName);
    registerFunction("setCustomAss", [](const Runtime::CallArgs& args) {
        Replicator::setCustomAss(runtimeThis(), args);
    });
}