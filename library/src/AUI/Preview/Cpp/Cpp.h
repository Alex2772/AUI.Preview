//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include <AUI/View/AViewContainer.h>
#include <AUI/Preview/Cpp/AST/AST.h>
#include <AUI/Preview/Cpp/AST/ExpressionNode.h>
#include <AUI/IO/IInputStream.h>

namespace Cpp {
    API_AUI_PREVIEW_LIBRARY _<AST> parseCode(_<IInputStream> p);
    API_AUI_PREVIEW_LIBRARY _<ExpressionNode> parseExpression(const AString& text);
};


