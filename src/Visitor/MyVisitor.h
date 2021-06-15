//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>

class MyVisitor: public INodeVisitor {
private:
    class ViewContainer: public AViewContainer {
        friend class MyVisitor;
    };

    _<ViewContainer> mContainer;
public:
    MyVisitor();

    void visitNode(const ConstructorDeclarationNode& node) override;
    void visitNode(const OperatorCallNode& node) override;


    [[nodiscard]]
    const _<ViewContainer>& getContainer() const {
        return mContainer;
    }
};


