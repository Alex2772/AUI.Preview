//
// Created by alex2 on 6/15/2021.
//

#include "AAsyncOperatorNode.h"
#include <AUI/Preview/Cpp/AST/INodeVisitor.h>

void AAsyncOperatorNode::acceptVisitor(INodeVisitor& v) {
    v.visitNode(*this);
}
