//
// Created by alex2 on 6/17/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/View/AViewContainer.h>

/**
 * _container<...>({...})
 *                 ^^^^^
 */
class ContainerListVisitor: public INodeVisitor {
private:
    _<AViewContainer> mContainer;

public:
    ContainerListVisitor();

    const _<AViewContainer>& getContainer() const {
        return mContainer;
    }

    void visitNode(const ImplicitInitializerListCtorNode& node) override;
};


