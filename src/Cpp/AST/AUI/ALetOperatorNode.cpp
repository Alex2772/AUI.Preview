//
// Created by alex2 on 6/13/2021.
//

#include "ALetOperatorNode.h"
#include <Cpp/AST/INodeVisitor.h>

void ALetOperatorNode::acceptVisitor(INodeVisitor& v) {
    v.visitNode(*this);
}
