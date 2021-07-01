//
// Created by alex2 on 6/17/2021.
//

#include "Replicator.h"
#include <Factory/FactoryRegistry.h>
#include <AUI/Autumn/Autumn.h>
#include <Visitor/Style/RuleVisitor.h>
#include <Visitor/Style/StyleRuleBlockVisitor.h>

_<ALayout> Replicator::layout(const AString& layoutName) {
    return _cast<ALayout>(Autumn::get<FactoryRegistry<AObject>>()->create(layoutName, {})->getValue());
}

void Replicator::setCustomAss(AView* target, const Runtime::CallArgs& args) {
    for (auto& i : args) {
        RuleVisitor v;
        i->acceptVisitor(v);
        RuleWithoutSelector r;
        if (auto rule = v.getRule()) {
            r.addDeclaration(rule.get());
            StyleRuleBlockVisitor::ourDeclarationStorage << rule;
            target->setCustomAss(r);
        }
    }
}
