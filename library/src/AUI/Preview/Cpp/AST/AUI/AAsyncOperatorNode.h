//
// Created by alex2 on 6/15/2021.
//

#pragma once

#include <AUI/Preview/Cpp/AST/ExpressionNode.h>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>

class AAsyncOperatorNode: public ExpressionNode {
private:
    AVector<_<INode>> mCode;

public:
    AAsyncOperatorNode(const AVector<_<INode>>& code): mCode(code) {}

    void acceptVisitor(INodeVisitor& v) override;
};




