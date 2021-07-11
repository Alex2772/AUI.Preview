/**
 * =====================================================================================================================
 * Copyright (c) 2021 Alex2772
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * Original code located at https://github.com/Alex2772/aui
 * =====================================================================================================================
 */

//
// Created by alex2772 on 7/7/21.
//

#include <AUI/Layout/AVerticalLayout.h>
#include "StylesView.h"
#include "StyleTextField.h"
#include <AUI/ASS/AAssHelper.h>
#include <AUI/ASS/Rule.h>
#include <AUI/Common/IStringable.h>
#include <AUI/View/ALabel.h>
#include <AUI/Traits/iterators.h>
#include <AUI/View/AHDividerView.h>
#include <AUI/Traits/strings.h>

#include <AUI/ASS/ASS.h>
#include <AUI/Preview/Visitor/Style/MyDeclarationWrapper.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/Util/AViewProfiler.h>
#include <AUI/Preview/Visitor/Replicator.h>
#include <AUI/View/ATextField.h>
#include <AUI/Preview/Visitor/SimpleNodeVisitor.h>
#include <AUI/Preview/Cpp/AST/AST.h>
#include <AUI/Preview/Cpp/Cpp.h>
#include <AUI/Preview/Visitor/Style/DeclarationVisitor.h>
#include <AUI/Preview/Visitor/Style/StyleRuleBlockVisitor.h>

using namespace ass;


StylesView::StylesView(AView* targetView) : mTargetView(targetView) {
    setCustomAss({
        Border {
            1_px,
            0x505050_rgb,
        },
        Padding { 1_px },
        Margin { 4_dp },
    });
    getContentContainer()->setLayout(_new<AVerticalLayout>());
    getContentContainer()->addView(_new<ALabel>(Replicator::prettyName(targetView)) with_style { FontSize {14_pt } });

    ADeque<ass::decl::IDeclarationBase*> applicableDeclarations;

    // element style
    this->getContentContainer()->addView(Horizontal {
            _new<ALabel>("view's custom style"),
            _new<ALabel>("{") << ".declaration_br",
    });

    displayApplicableRule(applicableDeclarations, &targetView->getCustomAss());

    for (auto r : aui::reverse_iterator_wrap(targetView->getAssHelper()->getPossiblyApplicableRules())) {
        if (r->getSelector().isStateApplicable(targetView)) {
            AStringVector sl;
            for (auto& ss : r->getSelector().getSubSelectors()) {
                if (auto classOf = _cast<class_of>(ss)) {
                    sl << "ass::class_of(\"{}\")"_as.format(classOf->getClasses().join(", "));
                } else {
                    sl << IStringable::toString(ss);
                }
            }
            if (sl.size() == 1) {
                this->getContentContainer()->addView(_new<ALabel>(sl.join(',') + ","));
            } else {
                this->getContentContainer()->addView(_new<ALabel>("{" + sl.join(',') + "},"));
            }
            displayApplicableRule(applicableDeclarations, r);
        }
    }

    // previewer
    {
        RuleWithoutSelector previewerRule;
        for (auto& d: applicableDeclarations) {
            previewerRule.addDeclaration(d);
        }
        mPreviewerView = _new<ALabel>("content area");
        mPreviewerView->setCustomAss(previewerRule);
        getContentContainer()->addView(Stacked {
            mPreviewerView
        });
    }



    getContentContainer()->updateLayout();
}

void StylesView::displayApplicableRule(ADeque<ass::decl::IDeclarationBase*>& applicableDeclarations,
                                       const RuleWithoutSelector* rule) {

    for (auto& decl : rule->getDeclarations()) {
        applicableDeclarations.push_front(decl);
        if (auto myDeclaration = dynamic_cast<MyDeclarationWrapper*>(decl)) {
            this->getContentContainer()->addView(Horizontal {
                _new<ALabel>(myDeclaration->getNode().getClassName()) << ".declaration_name",
                _new<ALabel>("{") << ".declaration_br",
            });

            // parse arguments
            size_t argIndex = 0;
            for (auto& arg : myDeclaration->getNode().getArgs()) {
                if (auto s = _cast<IStringable>(arg)) {
                    this->getContentContainer()->addView(Horizontal {
                        _new<StyleTextField>() let {
                            it->setText(s->toString());
                            auto node = &myDeclaration->getNode();
                            this->connect(it->textChanging, [&, myDeclaration, node, argIndex](const AString& text) {
                                // reparse it as an expression using AST
                                try {
                                    auto expr = Cpp::parseExpression(text);
                                    if (!expr) return;

                                    // inject it
                                    auto& args = const_cast<AVector<_<ExpressionNode>>&>(node->getArgs());
                                    args[argIndex] = expr;

                                    DeclarationVisitor dv;
                                    const_cast<ExplicitInitializerListCtorNode&>(myDeclaration->getNode()).acceptVisitor(dv);
                                    auto newDecl = dv.getDeclaration();
                                    if (!newDecl) return;

                                    StyleRuleBlockVisitor::ourDeclarationStorage << newDecl;
                                    myDeclaration->setWrappedDeclaration(newDecl.get());
                                    emit this->assUpdated;
                                } catch (...) {}
                            });
                        },
                        _new<ALabel>(",") << ".declaration_br",
                        _new<ASpacer>(),
                    } << ".declaration_entry");
                } else {
                    this->getContentContainer()->addView(_new<ALabel>("<n/a>") << ".declaration_entry" << ".declaration_br");
                }
                ++argIndex;
            }
        } else {
            this->getContentContainer()->addView(_new<ALabel>("<internal {}>"_as.format(AReflect::name(decl))) with_style{Opacity {0.7f } });
        }
    }
    this->getContentContainer()->addView(Horizontal {
            _new<ALabel>("},") << ".declaration_br",
    });
    this->getContentContainer()->addView(_new<AHDividerView>() with_style{BackgroundSolid {0x505050_rgb }, Margin {5_dp, 0 }, MinSize {{}, 10_dp } });
}

void StylesView::render() {
    AViewContainer::render();
}
