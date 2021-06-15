//
// Created by alex2 on 6/12/2021.
//

#include "NumberNode.h"
#include "INodeVisitor.h"

void NumberNode::acceptVisitor(INodeVisitor* v) {
    v->visitNode(*this);
}
