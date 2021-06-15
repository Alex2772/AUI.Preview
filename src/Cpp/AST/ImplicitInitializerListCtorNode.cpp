//
// Created by alex2 on 6/15/2021.
//

#include "ImplicitInitializerListCtorNode.h"
#include "INodeVisitor.h"

void ImplicitInitializerListCtorNode::acceptVisitor(INodeVisitor* v) {
    v->visitNode(*this);
}
