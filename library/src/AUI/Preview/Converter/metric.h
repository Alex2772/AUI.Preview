//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<ass::unset_wrap<AMetric>> {
        static ass::unset_wrap<AMetric> from_vm(const _<ExpressionNode>& n) {
            class MetricVisitor: public UnsetWrapVisitor<AMetric> {
            public:
                void visitNode(const IntegerNode& node) override {
                    if (node.getNumber() != 0) {
                        auto str = ":{} metric can be only zero without unit"_as.format(node.getNumber());
                        ALogger::warn(str);
                        throw AException(str);
                    }
                    mIsValid = true;
                    mValue = 0;
                }


                void visitNode(const OperatorLiteralNode& node) override {
                    // _dp, _px, _pt
                    AMetric::Unit unit;
                    auto& name = node.getLiteralName();

                    if (name == "_dp") {
                        unit = AMetric::T_DP;
                    } else if (name == "_px") {
                        unit = AMetric::T_PX;
                    } else if (name == "_pt") {
                        unit = AMetric::T_PT;
                    } else {
                        auto str = ":{} invalid literal {}"_as.format(node.getLineNumber(), name);
                        ALogger::warn(str);
                        throw AException(str);
                    }

                    class NumberVisitor: public INodeVisitor {
                    private:
                        AMetric::Unit& mUnit;
                        AMetric& mMetric;


                    public:
                        NumberVisitor(AMetric::Unit& unit, AMetric& metric) : mUnit(unit), mMetric(metric) {}

                        void visitNode(const IntegerNode& node) override {
                            mMetric = AMetric(node.getNumber(), mUnit);
                        }
                    };
                    AMetric v;
                    NumberVisitor numberVisitor(unit, v);
                    node.getChild()->acceptVisitor(numberVisitor);
                    mValue = v;
                    mIsValid = true;
                }
            };
            MetricVisitor v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };

    template<>
    struct converter<AMetric>: unset_wrap_converter<AMetric> {};
}