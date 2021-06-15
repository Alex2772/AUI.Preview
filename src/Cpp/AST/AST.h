//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include <AUI/View/AViewContainer.h>
#include "INode.h"

class AST {
private:
    AVector<_<INode>> mNodes;

public:
    AST(const AVector<_<INode>>& nodes) : mNodes(nodes) {}

    void visit(INodeVisitor* visitor);

    _<AViewContainer> run();
};


