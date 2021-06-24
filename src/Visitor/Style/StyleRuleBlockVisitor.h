//
// Created by alex2 on 6/18/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/ASS/ASS.h>

/**
 * Parses
 * {
 *     selector,
 *     rule1,
 *     rule2,
 *     ...
 * }
 */
class StyleRuleBlockVisitor: public INodeVisitor {
private:
    _unique<Rule> mRule;
    static AVector<_<ass::decl::IDeclarationBase>> ourDeclarationStorage;


public:
    void visitNode(const ImplicitInitializerListCtorNode& node) override;


    [[nodiscard]] const _unique<Rule>& getRule() const {
        return mRule;
    }
};


