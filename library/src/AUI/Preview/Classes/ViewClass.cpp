//
// Created by alex2 on 6/28/2021.
//

#include "ViewClass.h"
#include <AUI/Preview/Visitor/Replicator.h>

class_descriptor<AView>::class_descriptor() {
    registerFunction("setExpanding", member(&AView::setExpanding));
    registerFunction("addAssName", member(&AView::addAssName));
    registerFunction("setCustomAss", [](const Runtime::CallArgs& args) {
        Replicator::setCustomAss(runtimeThis(), args);
    });
}

