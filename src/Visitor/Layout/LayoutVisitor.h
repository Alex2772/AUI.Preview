//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/Traits/strings.h>
#include <AUI/View/AViewContainer.h>
#include <Util/ICustomViewName.h>

class ViewContainerClass;

class LayoutVisitor: public INodeVisitor {
public:
    class ViewContainer: public AViewContainer {
        friend class LayoutVisitor;
        friend class ViewContainerClass;
        friend class MainWindow;

    };

private:

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



