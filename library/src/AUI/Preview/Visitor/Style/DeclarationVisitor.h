//
// Created by alex2 on 6/19/2021.
//

#pragma once


#include <AUI/Preview/Cpp/AST/INodeVisitor.h>
#include <AUI/ASS/ASS.h>

class DeclarationVisitor: public INodeVisitor {
private:
    _<ass::decl::IDeclarationBase> mRule;
    std::optional<ExplicitInitializerListCtorNode> mNode;
public:
    void visitNode(const ExplicitInitializerListCtorNode& node) override;

    ExplicitInitializerListCtorNode&& getNode() {
        return std::move(*mNode);
    }

    [[nodiscard]]
    const _<ass::decl::IDeclarationBase>& getDeclaration() const {
        return mRule;
    }

};


