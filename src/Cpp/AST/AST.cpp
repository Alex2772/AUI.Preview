//
// Created by alex2 on 6/12/2021.
//

#include "AST.h"
#include <AUI/Util/UIBuildingHelpers.h>

_<AViewContainer> AST::run() {
    return Stacked {
        _new<ALabel>("ты лох")
    };
}

void AST::visit(INodeVisitor& visitor) {
    for (auto& v : mNodes) {
        v->acceptVisitor(visitor);
    }
}
