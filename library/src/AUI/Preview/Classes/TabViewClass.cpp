//
// Created by alex2 on 7/3/2021.
//

#include <AUI/Preview/Visitor/Layout/ViewVisitor.h>
#include "TabViewClass.h"

class_descriptor<ATabView>::class_descriptor() {

    registerFunction("addTab", [](const Runtime::CallArgs& args) {
        if (args.size() >= 1) {
            ViewVisitor uiBuilder;
            args[0]->acceptVisitor(uiBuilder);
            auto tab = uiBuilder.getView();
            if (tab) {
                if (args.size() >= 2) {
                    StringVisitor v;
                    args[1]->acceptVisitor(v);
                    if (v.getValue()) {
                        Class<ATabView>::runtimeThis()->addTab(tab, *v.getValue());
                        return;
                    }
                }
                Class<ATabView>::runtimeThis()->addTab(tab);
            }
        }
    });
}

