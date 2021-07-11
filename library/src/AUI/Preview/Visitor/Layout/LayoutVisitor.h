//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Preview/Cpp/AST/INodeVisitor.h>
#include <AUI/Traits/strings.h>
#include <AUI/View/AViewContainer.h>
#include <AUI/Preview/Util/ICustomViewName.h>

class ViewContainerClass;

class API_AUI_PREVIEW_LIBRARY LayoutVisitor: public INodeVisitor {
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



