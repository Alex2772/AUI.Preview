//
// Created by alex2 on 6/13/2021.
//

#pragma once

#include <Cpp/AST/ExpressionNode.h>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>

class ALetOperatorNode: public ExpressionNode {
private:
    _<ExpressionNode> mTarget;
    AVector<_<INode>> mCode;

public:
    ALetOperatorNode(const _<ExpressionNode>& target, const AVector<_<INode>>& code) : mTarget(target), mCode(code) {}

    void acceptVisitor(INodeVisitor* v) override;

    const _<ExpressionNode>& getTarget() const {
        return mTarget;
    }

    const AVector<_<INode>>& getCode() const {
        return mCode;
    }
};


