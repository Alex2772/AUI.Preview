//
// Created by alex2 on 6/17/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/View/AView.h>

class ViewVisitor: public INodeVisitor {
protected:
    _<AView> mView;

public:
    [[nodiscard]]
    const _<AView>& getView() const {
        return mView;
    }

    /**
     * ASS class assignment
     * @param node
     */
    void visitNode(const LShiftOperatorNode& node) override;

    /**
     * Handle _new<...>().connect case
     * @param node
     */
    void visitNode(const MemberAccessOperatorNode& node) override;

    /**
     * Handle view let { ... }
     * @param node
     */
    void visitNode(const ALetOperatorNode& node) override;

    /**
     * Handle view with_style { ... }
     * @param node
     */
    void visitNode(const AWithStyleOperatorNode& node) override;

    /**
     * Handle ... = _new<...>() case
     * @param node
     */
    void visitNode(const AssignmentOperatorNode& node) override;


    /**
     * _new<?>(?)
     * _container<Layout?>({?})
     * @param node
     */
    void visitNode(const TemplateOperatorCallNode& node) override;



    /**
     * Stacked { ... }, Vertical { ... }, Horizontal { ... }
     * @param node
     */
    void visitNode(const ExplicitInitializerListCtorNode& node) override;

    void visitNode(const VariableReferenceNode& node) override;
};