//
// Created by alex2 on 6/19/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/ASS/ASS.h>

class RuleVisitor: public INodeVisitor {
private:
    _<ass::decl::IDeclarationBase> mRule;
public:
    void visitNode(const ExplicitInitializerListCtorNode& node) override;

    [[nodiscard]]
    const _<ass::decl::IDeclarationBase>& getRule() const {
        return mRule;
    }
};


