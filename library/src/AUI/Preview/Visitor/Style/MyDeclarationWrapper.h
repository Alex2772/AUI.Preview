//
// Created by alex2772 on 7/7/21.
//

#pragma once

#include <AUI/ASS/Declaration/IDeclaration.h>
#include <AUI/Preview/Cpp/AST/ExplicitInitializerListCtorNode.h>

class MyDeclarationWrapper: public ass::decl::IDeclarationBase {
private:
    ass::decl::IDeclarationBase* mWrappedDeclaration;
    _<INode> mNode;

public:
    MyDeclarationWrapper(IDeclarationBase* wrappedDeclaration, _<INode> node)
            : mWrappedDeclaration(wrappedDeclaration), mNode(std::move(node)) {}

    [[nodiscard]]
    const _<INode>& getNode() const {
        return mNode;
    }

    IDeclarationBase* getWrappedDeclaration() const {
        return mWrappedDeclaration;
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
