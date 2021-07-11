//
// Created by alex2 on 6/17/2021.
//

#pragma once


#include <AUI/Preview/Cpp/AST/INodeVisitor.h>
#include <AUI/ASS/AStylesheet.h>

class API_AUI_PREVIEW_LIBRARY StyleVisitor: public INodeVisitor {
private:
    _<AStylesheet> mStylesheet;

public:
    StyleVisitor();

    /**
     * struct Style { ... }
     * @param node
     */
    void visitNode(const StructClassDefinition& node) override;


    /**
     * Constructor
     * @param node
     */
    void visitNode(const ConstructorDeclarationNode& node) override;

    /**
     * AStylesheet::inst().
     * @param node
     */
    void visitNode(const MemberAccessOperatorNode& node) override;


    /**
     * ...addRules(...)
     * @param node
     */
    void visitNode(const OperatorCallNode& node) override;


    /**
     * The desired list
     * @param node
     */
    void visitNode(const ImplicitInitializerListCtorNode& node) override;

    [[nodiscard]]
    const _<AStylesheet>& getStylesheet() const {
        return mStylesheet;
    }
};


