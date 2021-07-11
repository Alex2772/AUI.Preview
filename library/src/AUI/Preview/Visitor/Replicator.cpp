//
// Created by alex2 on 6/17/2021.
//

#include "Replicator.h"
#include <AUI/Preview/Factory/FactoryRegistry.h>
#include <AUI/Autumn/Autumn.h>
#include <AUI/Preview/Visitor/Style/DeclarationVisitor.h>
#include <AUI/Preview/Visitor/Style/StyleRuleBlockVisitor.h>
#include <AUI/Preview/Util/ICustomViewName.h>
#include <AUI/Reflect/AReflect.h>

_<ALayout> Replicator::layout(const AString& layoutName) {
    return _cast<ALayout>(Autumn::get<FactoryRegistry<AObject>>()->create(layoutName, {})->getValue());
}

void Replicator::setCustomAss(AView* target, const Runtime::CallArgs& args) {
    for (auto& i : args) {

        class MyVisitor: public INodeVisitor {
        private:
            RuleWithoutSelector r;

        public:
            void visitNode(const ImplicitInitializerListCtorNode& node) override {
                INodeVisitor::visitNode(node);

                for (auto& i : node.getElements()) {
                    i->acceptVisitor(*this);
                }
            }

            void visitNode(const ExplicitInitializerListCtorNode& node) override {
                INodeVisitor::visitNode(node);
                DeclarationVisitor v;
                v.visitNode(node);

                if (auto rule = v.getDeclaration()) {
                    r.addDeclaration(rule.get());
                    StyleRuleBlockVisitor::ourDeclarationStorage << rule;
                }
            }

            const RuleWithoutSelector& getRules() const {
                return r;
            }
        } v;
        i->acceptVisitor(v);

        target->setCustomAss(v.getRules());

    }
}

AString Replicator::prettyName(AView* view) {
    AString name;
    if (auto i = dynamic_cast<ICustomViewName*>(view)) {
        name = i->getCustomViewName();
    } else {
        if (auto c = dynamic_cast<AViewContainer*>(view)) {
            name = AReflect::name(c->getLayout().get());
        } else {
            name = AReflect::name(view);
        }

        // remove 'class '
        if (name.startsWith("class ")) {
            name = name.mid(6);
        }
        if (name.startsWith("LayoutVisitor::")) {
            name = "A" + name.mid(15);
        }
    }
    return name;
}
