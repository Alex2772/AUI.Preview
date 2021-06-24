//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/Traits/strings.h>

class LayoutVisitor: public INodeVisitor {
private:
    class ViewContainer: public AViewContainer {
        friend class LayoutVisitor;
    };

    _<ViewContainer> mContainer;
public:
    LayoutVisitor();

    void visitNode(const ConstructorDeclarationNode& node) override;
    void visitNode(const OperatorCallNode& node) override;


    [[nodiscard]]
    const _<ViewContainer>& getContainer() const {
        return mContainer;
    }
};


