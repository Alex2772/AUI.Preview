//
// Created by alex2 on 6/15/2021.
//

#include <AUI/View/AViewContainer.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <Factory/FactoryRegistry.h>
#include "MyVisitor.h"
#include "StringVisitor.h"


class ViewVisitor: public INodeVisitor {
protected:
    _<AView> mView;

public:
    [[nodiscard]]
    const _<AView>& getView() const {
        return mView;
    }

    /**
     * ASS class assignment
     * @param node
     */
    void visitNode(const LShiftOperatorNode& node) override {
        StringVisitor c;
        node.getRight()->acceptVisitor(&c);
        auto assName = c.getString();
        node.getLeft()->acceptVisitor(this);
        if (mView != nullptr) {
            mView << assName;
        }
    }

    /**
     * Handle _new<...>().connect case
     * @param node
     */
    void visitNode(const MemberAccessOperatorNode& node) override {
        node.getLeft()->acceptVisitor(this);
    }

    void visitNode(const ALetOperatorNode& node) override {
        node.getTarget()->acceptVisitor(this);
    }

    /**
     * _new<?>(?)
     * @param node
     */
    void visitNode(const TemplateOperatorCallNode& node) override {
        if (node.getCallee() == "_new") {
            assert(mView == nullptr);

            try {
                for (auto& factory : Autumn::get<FactoryRegistry>()->getFactoriesForTypeName(node.getTemplateArg())) {
                    try {
                        mView = _cast<AView>(factory->create(node.getArgs()));
                    } catch (...) {
                        break;
                    }
                }
            } catch (...) {

            }
            if (mView == nullptr) {
                ALogger::warn("Replicate error for " + node.getTemplateArg());
                mView = _new<ALabel>("<replicate error " + node.getTemplateArg() + ">");
            }
        }
    }




    void visitNode(const ExplicitInitializerListCtorNode& node) override {
        assert(mView == nullptr);
        _<AViewContainer> view;
        if (node.getClassName() == "Stacked") {
            view = Stacked{};
        } else if (node.getClassName() == "Vertical") {
            view = Vertical{};
        } else if (node.getClassName() == "Horizontal") {
            view = Horizontal{};
        } else {
            return;
        }

        for (auto& x : node.getArgs()) {
            ViewVisitor v;
            x->acceptVisitor(&v);
            if (v.getView()) {
                view->addView(v.getView());
            }
        }
        mView = view;
    }
};

void MyVisitor::visitNode(const ConstructorDeclarationNode& node) {
    for (auto& n : node.getCode()) {
        n->acceptVisitor(this);
    }
}

void MyVisitor::visitNode(const OperatorCallNode& node) {
    if (node.getCallee() == "setContents") {
        for (auto& x : node.getArgs()) {
            ViewVisitor uiBuilder;
            x->acceptVisitor(&uiBuilder);
            if (auto container = _cast<AViewContainer>(uiBuilder.getView())) {
                mContainer->setContents(container);
            }
        }
    }
}

MyVisitor::MyVisitor() {
    mContainer = _new<ViewContainer>();
}
