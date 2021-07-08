//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include <AUI/View/AViewContainer.h>
#include <Cpp/AST/AST.h>
#include <Cpp/AST/ExpressionNode.h>

namespace Cpp {
    _<AST> parseCode(const APath& p);
    _<ExpressionNode> parseExpression(const AString& text);
};


