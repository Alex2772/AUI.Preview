//
// Created by alex2 on 6/17/2021.
//

#include "ContainerListVisitor.h"
#include "ViewVisitor.h"

ContainerListVisitor::ContainerListVisitor() {
    mContainer = _new<AViewContainer>();
}

void ContainerListVisitor::visitNode(const ImplicitInitializerListCtorNode& node) {
    for (auto& element : node.getElements()) {
        ViewVisitor v;
        element->acceptVisitor(&v);
        if (v.getView()) {
            mContainer->addView(v.getView());
        }
    }
}
