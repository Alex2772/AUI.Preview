#pragma once

#include <AUI/View/AViewContainer.h>
#include <gtest/gtest.h>
#include <AUI/Reflect/AClass.h>
#include <AUI/Reflect/AReflect.h>
#include <AUI/Preview/Visitor/Style/MyDeclarationWrapper.h>

template<typename NodeType, typename InitialType, typename Consumer>
void assertType(const _<InitialType>& node, Consumer&& consumer) {
    if (auto c = _cast<NodeType>(node)) {
        if (typeid(NodeType) == typeid(*c.get())) {
            consumer(std::move(c));
            return;
        }
    }
    FAIL() << "expected value of type " << AClass<NodeType>::name() << ", got " << AReflect::name(node.get());
}

template<typename NodeType, typename InitialType, typename Consumer>
void assertType(InitialType* node, Consumer&& consumer) {
    if (auto c = dynamic_cast<NodeType*>(node)) {
        if (typeid(NodeType) == typeid(*c)) {
            consumer(c);
            return;
        }
    }
    FAIL() << "expected value of type " << AClass<NodeType>::name() << ", got " << AReflect::name(node);
}
template<typename ValueType, typename Consumer>
void assertAssDeclaration(ass::decl::IDeclarationBase* node, Consumer&& consumer) {
    if (auto wrapper = dynamic_cast<MyDeclarationWrapper*>(node)) {
        using declaration_t = ass::decl::Declaration<ValueType>;
        if (auto c = dynamic_cast<declaration_t*>(wrapper->getWrappedDeclaration())) {
            if (typeid(declaration_t) == typeid(*c)) {
                consumer(c->value());
                return;
            }
        }
        FAIL() << "expected declaration of type " << AClass<ValueType>::name() << ", got " << AReflect::name(wrapper->getWrappedDeclaration());
    } else {
        FAIL() << "expected declaration of type MyDeclarationWrapper first, got " << AReflect::name(node);
    }
}

template<typename LayoutType, typename Consumer>
void assertLayout(const _<AView>& node, Consumer&& consumer) {
    assertType<AViewContainer>(node, [consumer = std::forward<Consumer>(consumer)](const _<AViewContainer>& v) {
        ASSERT_TRUE(_cast<LayoutType>(v->getLayout())) << "got layout: " << AReflect::name(v->getLayout().get());
        consumer(v);
    });
}


