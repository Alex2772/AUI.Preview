//
// Created by alex2 on 6/30/2021.
//

#include <Visitor/Layout/ViewVisitor.h>
#include "PageViewClass.h"


class_descriptor<APageView>::class_descriptor() {
    registerFunction("addPage", [](const Runtime::CallArgs& args) {
        if (args.size() == 1) {
            ViewVisitor v;
            args.first()->acceptVisitor(v);
            if (v.getView()) {
                Class<APageView>::runtimeThis()->addPage(v.getView());
            }
        }
    });

    assert(getFunction("addPage"));
}

