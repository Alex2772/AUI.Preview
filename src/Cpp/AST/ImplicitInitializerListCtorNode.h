//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>
#include "ExpressionNode.h"

class ImplicitInitializerListCtorNode: public ExpressionNode {
private:
    AVector<_<ExpressionNode>> mArgs;

public:
    ImplicitInitializerListCtorNode(const AVector<_<ExpressionNode>>& args) : mArgs(args) {}

    void acceptVisitor(INodeVisitor* v) override;
};


