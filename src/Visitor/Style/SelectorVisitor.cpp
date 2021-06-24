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

namespace selector {
    struct Type : virtual ass::IAssSubSelector {
    private:
        const std::type_info& mReferenceTypeInfo;

    public:
        Type(const _<AObject>& o): mReferenceTypeInfo(typeid(o.get())) {
        }

        bool isPossiblyApplicable(AView* view) override {
            return typeid(view) == mReferenceTypeInfo;
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
            } else {
                /*
                 * Unknown type may be a MainWindow class or some other class not provided by the user's project.
                 * The workaround is use the classname as an prefix ASS class (ex.
                 * MainWindow -> addAssName("preview_MainWindow"))
                 */
                auto assName = "preview_" + objectType;
                mSelector.addSubSelector(ass::class_of(assName));
            }
        } catch (const AException& e) {
            ALogger::warn("Could not create temporary object of type {}: {}"_as.format(objectType, e.getMessage()));
        }
    } else {
        ALogger::warn("Unknown selector {}<{}> at {}"_as.format(node.getCallee(), node.getTemplateArg(), node.getLineNumber()));
    }
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
