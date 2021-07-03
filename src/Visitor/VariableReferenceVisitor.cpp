//
// Created by alex2 on 7/3/2021.
//

#include "VariableReferenceVisitor.h"

void VariableReferenceVisitor::visitNode(const VariableReferenceNode& node) {
    INodeVisitor::visitNode(node);
    mName = node.getVariableName();
}
