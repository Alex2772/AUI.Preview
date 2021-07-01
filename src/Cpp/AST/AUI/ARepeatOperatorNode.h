//
// Created by alex2 on 6/30/2021.
//

#pragma once

#include <Cpp/AST/ExpressionNode.h>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>

class ARepeatOperatorNode: public ExpressionNode {
private:
    unsigned mTimes;
    AVector<_<INode>> mCode;

public:
    ARepeatOperatorNode(unsigned int times, const AVector<_<INode>>& code) : mTimes(times), mCode(code) {}

    void acceptVisitor(INodeVisitor& v) override;

    unsigned int getTimes() const {
        return mTimes;
    }

    const AVector<_<INode>>& getCode() const {
        return mCode;
    }
};

