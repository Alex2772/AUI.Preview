//
// Created by alex2772 on 7/7/21.
//

#pragma once

#include <AUI/ASS/Declaration/IDeclaration.h>
#include <AUI/Preview/Cpp/AST/ExplicitInitializerListCtorNode.h>

class MyDeclarationWrapper: public ass::decl::IDeclarationBase {
private:
    ass::decl::IDeclarationBase* mWrappedDeclaration;
    ExplicitInitializerListCtorNode mNode;

public:
    MyDeclarationWrapper(IDeclarationBase* wrappedDeclaration, ExplicitInitializerListCtorNode&& node)
            : mWrappedDeclaration(wrappedDeclaration), mNode(std::forward<ExplicitInitializerListCtorNode>(node)) {}

    [[nodiscard]]
    const ExplicitInitializerListCtorNode& getNode() const {
        return mNode;
    }

    void setWrappedDeclaration(IDeclarationBase* wrappedDeclaration) {
        // TODO produces dangling pointers
        mWrappedDeclaration = wrappedDeclaration;
    }

    void applyFor(AView* view) override;
    void renderFor(AView* view) override;
    bool isNone() override;
    ass::decl::DeclarationSlot getDeclarationSlot() const override;
};
