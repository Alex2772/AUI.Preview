//
// Created by alex2 on 6/19/2021.
//

#pragma once


#include <AUI/Preview/Cpp/AST/INodeVisitor.h>
#include <AUI/ASS/ASS.h>
#include <optional>

class API_AUI_PREVIEW_LIBRARY DeclarationVisitor: public INodeVisitor {
private:
    _<ass::decl::IDeclarationBase> mRule;
    _<INode> mNode;

public:
    void visitNode(const ExplicitInitializerListCtorNode& node) override;

    // handles BackgroundCropping::H4_1()
    void visitNode(const StaticMemberAccessOperatorNode& node) override;

    const _<INode>& getNode() {
        return mNode;
    }

    [[nodiscard]]
    const _<ass::decl::IDeclarationBase>& getDeclaration() const {
        return mRule;
    }

};


