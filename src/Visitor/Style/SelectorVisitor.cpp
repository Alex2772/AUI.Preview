//
// Created by alex2 on 6/18/2021.
//

#include "SelectorVisitor.h"
#include <AUI/ASS/Selector/AAssSelector.h>
#include <Factory/FactoryRegistry.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/ASS/Selector/class_of.h>
#include <Visitor/StringVisitor.h>
#include <typeinfo>

using namespace ass;

struct MyParentSubSelector: public IAssSubSelector {
private:
    _<IAssSubSelector> l;
    _<IAssSubSelector> r;

public:
    MyParentSubSelector(const _<IAssSubSelector>& l, const _<IAssSubSelector>& r) : l(l), r(r) {}

    bool isPossiblyApplicable(AView* view) override {
        if (r->isPossiblyApplicable(view)) {
            for (AView* v = view->getParent(); v; v = v->getParent()) {
                if (l->isPossiblyApplicable(v)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isStateApplicable(AView* view) override {
        if (r->isStateApplicable(view)) {
            for (AView* v = view->getParent(); v; v = v->getParent()) {
                if (l->isStateApplicable(v) && l->isPossiblyApplicable(v)) {
                    return true;
                }
            }
        }
        return false;
    }

    void setupConnections(AView* view, const _<AAssHelper>& helper) override {
        if (r->isPossiblyApplicable(view)) {
            for (AView* v = view->getParent(); v; v = v->getParent()) {
                if (l->isPossiblyApplicable(v)) {
                    l->setupConnections(v, helper);
                    r->setupConnections(view, helper);
                    return;
                }
            }
        }
        /**
         * you should never reach here because this function is called only in case isPossiblyApplicable returned
         * true
         */
        assert(0);
    }
};

namespace selector {
    struct Type : virtual ass::IAssSubSelector {
    private:
        const std::type_info& mReferenceTypeInfo;

    public:
        Type(const _<AObject>& o): mReferenceTypeInfo(typeid(*o.get())) {
        }

        bool isPossiblyApplicable(AView* view) override {
            return typeid(*view) == mReferenceTypeInfo;
        }

    };
}

void SelectorVisitor::visitNode(const ImplicitInitializerListCtorNode& node) {
    INodeVisitor::visitNode(node);

    for (auto& item : node.getElements()) {
        item->acceptVisitor(*this);
    }
}

void SelectorVisitor::visitNode(const TemplateOperatorCallNode& node) {
    // t<...>()
    if (node.getCallee() == "t" || node.getCallee() == "type_of") {
        auto objectType = node.getTemplateArg();
        try {
            auto referenceObject = Autumn::get<FactoryRegistry<AObject>>()->create(objectType, {});
            if (referenceObject) {
                mSelector.addSubSelector(selector::Type(referenceObject));
                return;
            }
        } catch (const AException& e) {
            ALogger::warn("Could not create temporary object of type {}: {}"_as.format(objectType, e.getMessage()));
        }
        /*
         * Unknown type may be a MainWindow class or some other class not provided by the user's project.
         * The workaround is use the classname as an prefix ASS class (ex.
         * MainWindow -> addAssName("preview_MainWindow"))
         */
        auto assName = "preview_" + objectType;
        mSelector.addSubSelector(ass::class_of(assName));
    } else {
        ALogger::warn("Unknown selector {}<{}> at {}"_as.format(node.getCallee(), node.getTemplateArg(), node.getLineNumber()));
    }
}

void SelectorVisitor::visitNode(const ArrayAccessOperatorNode& node) {
    INodeVisitor::visitNode(node);
}

void SelectorVisitor::visitNode(const RShiftOperatorNode& node) {
    SelectorVisitor c1;
    node.getLeft()->acceptVisitor(c1);
    node.getRight()->acceptVisitor(c1);

    mSelector.addSubSelector(MyParentSubSelector(c1.mSelector.getSubSelectors().at(0), c1.mSelector.getSubSelectors().at(1)));
}

void SelectorVisitor::visitNode(const OperatorCallNode& node) {
    if (node.getCallee() == "c" || node.getCallee() == "class_of") {
        try {
            StringVisitor v;
            node.getArgs().first()->acceptVisitor(v);
            mSelector.addSubSelector(ass::class_of(*v.getValue()));
        } catch (const AException&) {
            ALogger::warn("class_of does not accepts AString at {}"_as.format(node.getLineNumber()));
        }
    }
}

SelectorVisitor::SelectorVisitor():
    mSelector(nullptr)
{

}
