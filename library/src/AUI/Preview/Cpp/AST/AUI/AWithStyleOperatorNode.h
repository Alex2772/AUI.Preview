//
// Created by alex2 on 6/25/2021.
//

#pragma once


#include <AUI/Preview/Cpp/AST/ExpressionNode.h>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>

class AWithStyleOperatorNode: public ExpressionNode {
private:
    _<ExpressionNode> mTarget;
    AVector<_<ExpressionNode>> mArgs;

public:
    AWithStyleOperatorNode(const _<ExpressionNode>& target, const AVector<_<ExpressionNode>>& args) : mTarget(target),
                                                                                                      mArgs(args) {}

    void acceptVisitor(INodeVisitor& v) override;

    const _<ExpressionNode>& getTarget() const {
        return mTarget;
    }

    const AVector<_<ExpressionNode>>& getArgs() const {
        return mArgs;
    }
};


