//
// Created by alex2 on 6/13/2021.
//

#pragma once


#include "ExpressionNode.h"
#include <AUI/Common/SharedPtrTypes.h>

class BinaryOperatorNode: public ExpressionNode {
private:
    _<ExpressionNode> mLeft;
    _<ExpressionNode> mRight;

public:
    BinaryOperatorNode(const _<ExpressionNode>& left, const _<ExpressionNode>& right) : mLeft(left), mRight(right) {}


    const _<ExpressionNode>& getLeft() const {
        return mLeft;
    }

    const _<ExpressionNode>& getRight() const {
        return mRight;
    }
};


class LShiftOperatorNode: public BinaryOperatorNode {
public:
    using BinaryOperatorNode::BinaryOperatorNode;

    void acceptVisitor(INodeVisitor* v) override;
};

class RShiftOperatorNode: public BinaryOperatorNode {
public:
    using BinaryOperatorNode::BinaryOperatorNode;

    void acceptVisitor(INodeVisitor* v) override;
};

class MemberAccessOperatorNode: public BinaryOperatorNode {
public:
    using BinaryOperatorNode::BinaryOperatorNode;

    void acceptVisitor(INodeVisitor* v) override;
};

class AssignmentOperatorNode: public BinaryOperatorNode {
public:
    using BinaryOperatorNode::BinaryOperatorNode;

    void acceptVisitor(INodeVisitor* v) override;
};
