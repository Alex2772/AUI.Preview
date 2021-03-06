//
// Created by alex2 on 6/15/2021.
//

#include <AUI/View/AViewContainer.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/Preview/Factory/FactoryRegistry.h>
#include <AUI/Preview/Cpp/Runtime/Context.h>
#include <AUI/Preview/Classes/GetClassDescriptor.h>
#include "LayoutVisitor.h"
#include "AUI/Preview/Visitor/Replicator.h"
#include "ViewVisitor.h"


void LayoutVisitor::visitNode(const ConstructorDeclarationNode& node) {
    // SelectorVisitor.cpp:105
    auto assName = "__preview_clazz$" + node.getClassName();
    mContainer << assName;

    Runtime::Variable v(get_class_descriptor<AViewContainer>(), mContainer);
    Runtime::Context::PushThis t(&v);
    Autumn::get<Runtime::Context>()->executeCodeBlock(node.getCode());
}


void LayoutVisitor::visitNode(const OperatorCallNode& node) {

}
void LayoutVisitor::visitNode(const StructClassDefinition& node) {
    for (auto& i : node.getNodes()) {
        i->acceptVisitor(*this);
    }
}

LayoutVisitor::LayoutVisitor() {
    mContainer = _new<ViewContainer>();
}