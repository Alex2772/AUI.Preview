//
// Created by alex2 on 6/13/2021.
//

#include "BinaryOperatorNode.h"
#include "INodeVisitor.h"

void LShiftOperatorNode::acceptVisitor(INodeVisitor* v) {
    v->visitNode(*this);
}

void RShiftOperatorNode::acceptVisitor(INodeVisitor* v) {
    v->visitNode(*this);
}

void MemberAccessOperatorNode::acceptVisitor(INodeVisitor* v) {
    v->visitNode(*this);
}

void AssignmentOperatorNode::acceptVisitor(INodeVisitor* v) {
    v->visitNode(*this);
}
