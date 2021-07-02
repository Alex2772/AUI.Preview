//
// Created by alex2 on 6/18/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/ASS/Selector/AAssSelector.h>

class SelectorVisitor: public INodeVisitor {
private:
    ass::AAssSelector mSelector;

public:
    SelectorVisitor();

    /**
     * t<...>(...)
     * type_of<...>(...)
     * @param node
     */
    void visitNode(const TemplateOperatorCallNode& node) override;

    /**
     * c(...)
     * class_of(...)
     * @param node
     */
    void visitNode(const OperatorCallNode& node) override;

    /**
     * { selector1, selector2, ... }
     * @param node
     */
    void visitNode(const ImplicitInitializerListCtorNode& node) override;

    [[nodiscard]]
    ass::AAssSelector& getSelector() {
        return mSelector;
    }

    void visitNode(const RShiftOperatorNode& node) override;

    void visitNode(const ArrayAccessOperatorNode& node) override;

    void visitNode(const GreaterOperatorNode& node) override;
};


