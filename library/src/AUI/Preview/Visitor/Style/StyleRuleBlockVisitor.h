//
// Created by alex2 on 6/18/2021.
//

#pragma once


#include <AUI/Preview/Cpp/AST/INodeVisitor.h>
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
class API_AUI_PREVIEW_LIBRARY StyleRuleBlockVisitor: public INodeVisitor {
private:
    _unique<Rule> mRule;


public:
    void visitNode(const ImplicitInitializerListCtorNode& node) override;
    static AVector<_<ass::decl::IDeclarationBase>> ourDeclarationStorage;


    [[nodiscard]] const _unique<Rule>& getRule() const {
        return mRule;
    }
};


