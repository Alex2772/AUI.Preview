//
// Created by alex2 on 6/30/2021.
//

#include "ARepeatOperatorNode.h"
#include <AUI/Preview/Cpp/AST/INodeVisitor.h>

void ARepeatOperatorNode::acceptVisitor(INodeVisitor& v) {
    v.visitNode(*this);
}
