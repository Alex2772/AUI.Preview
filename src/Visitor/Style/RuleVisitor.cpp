//
// Created by alex2 on 6/19/2021.
//

#include <AUI/Common/AException.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/Autumn/Autumn.h>
#include <Factory/FactoryRegistry.h>
#include "RuleVisitor.h"
#include <AUI/ASS/ASS.h>

void RuleVisitor::visitNode(const ExplicitInitializerListCtorNode& node) {
    try {
        auto rule = Autumn::get<FactoryRegistry<ass::decl::IDeclarationBase>>()->create(node.getClassName(), node.getArgs());
        if (!rule) {
            throw AException("no such rule");
        }
        mRule = rule;
    } catch (const AException& e) {
        ALogger::warn("Style.cpp:{} Failed to replicate rule {}: {}"_as.format(node.getLineNumber(),
                                                                                   node.getClassName(),
                                                                                   e.getMessage()));
    }
}
