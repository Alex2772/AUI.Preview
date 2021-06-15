//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include "ExpressionNode.h"

class OperatorLiteralNode: public ExpressionNode {
private:
    AString mLiteralName;
    _<ExpressionNode> mChild;

public:
    OperatorLiteralNode(const AString& literalName, const _<ExpressionNode>& child) : mLiteralName(literalName),
                                                                                      mChild(child) {}

    void acceptVisitor(INodeVisitor* v) override;

    const AString& getLiteralName() const {
        return mLiteralName;
    }

    const _<ExpressionNode>& getChild() const {
        return mChild;
    }
};


