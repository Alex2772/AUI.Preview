//
// Created by alex2 on 6/25/2021.
//

#include "AWithStyleOperatorNode.h"
#include <Cpp/AST/INodeVisitor.h>

void AWithStyleOperatorNode::acceptVisitor(INodeVisitor& v) {
    v.visitNode(*this);
}
