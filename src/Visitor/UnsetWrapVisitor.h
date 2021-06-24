//
// Created by alex2 on 6/23/2021.
//

#pragma once


#include <AUI/ASS/ASS.h>
#include <AUI/Logging/ALogger.h>
#include <Cpp/AST/INodeVisitor.h>

template<typename T>
class UnsetWrapVisitor: public INodeVisitor {
protected:
    bool mIsValid = false;
    ass::unset_wrap<T> mValue;

public:

    void visitNode(const ImplicitInitializerListCtorNode& node) override {
        mIsValid = true;
    }

    [[nodiscard]]
    const ass::unset_wrap<T>& getValue() const {
        if (mIsValid) {
            return mValue;
        }
        throw AException("not a valid unset_wrap<{}>"_as.format(AClass<T>::name()));
    }
};