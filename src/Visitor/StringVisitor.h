//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/Common/AException.h>
#include "UnsetWrapVisitor.h"

class StringVisitor: public UnsetWrapVisitor<AString> {
public:
    void visitNode(const StringNode& node) override;

    /**
     * << "..." let { ... } workaround
     * @param node
     */
    void visitNode(const ALetOperatorNode& node) override;
};


