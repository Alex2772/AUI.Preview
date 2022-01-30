//
// Created by Alex2772 on 1/26/2022.
//


#include <gtest/gtest.h>
#include <AUI/Preview/Cpp/Cpp.h>
#include <AUI/Reflect/AClass.h>
#include <AUI/Reflect/AReflect.h>
#include <AUI/Preview/Cpp/AST/ExplicitInitializerListCtorNode.h>
#include <AUI/Preview/Visitor/Layout/LayoutVisitor.h>
#include <AUI/View/AView.h>
#include <AUI/Layout/AStackedLayout.h>
#include <AUI/Preview/Visitor/Layout/ViewVisitor.h>
#include <AUI/View/AButton.h>
#include <AUI/Preview/Visitor/Style/StyleVisitor.h>
#include <AUI/IO/AStringStream.h>
#include <AUI/ASS/Selector/class_of.h>
#include <AUI/Preview/Visitor/Style/MyDeclarationWrapper.h>
#include <AUI/ASS/Declaration/TextColor.h>
#include <AUI/ASS/Declaration/FontSize.h>
#include <AUI/ASS/Declaration/LineHeight.h>
#include "TestHelper.h"

/**
 * Fixture.
 */
class StylesheetTest : public testing::Test {
public:
    /**
     * Run once per test case before body.
     */
    void SetUp() override {
        Test::SetUp();
    }

    /**
     * Run once per test case after body.
     */
    void TearDown() override {
        Test::TearDown();
    }
};


TEST_F(StylesheetTest, Case1) {
    auto ast = Cpp::parseCode(_new<AStringStream>(R"(
using namespace ass;

class Style1234891489128 {
public:
    Style1234891489128() {
        AStylesheet::inst().addRules({
            {
                 t<AView>(),
                 BackgroundCropping::H4_1,
            },

            // talk
            {
                t<UI::Dialog>() >> t<ALabel>(),
                TextColor { 0xff00ff_rgb },
                FontSize { 9_pt },
                LineHeight { 1.5 },
            },
        });
    }
} style1234891489128;
)"));
    StyleVisitor v;
    const_cast<AVector<Rule>&>(v.getStylesheet()->getRules()).clear();
    ast->visit(v);
    ASSERT_TRUE(v.getStylesheet() != nullptr);
    auto& rules = v.getStylesheet()->getRules();
    ASSERT_EQ(rules.size(), 2);

    // first rule
    {
        auto& rule = rules[0];
        auto selector = rule.getSelector().getSubSelectors().first();
        ASSERT_EQ(IStringable::toString(selector), R"(ass::class_of("__preview_clazz$AView"))");

        auto& declarations = rule.getDeclarations();
        ASSERT_EQ(declarations.size(), 1);
        assertAssDeclaration<ass::BackgroundCropping>(declarations[0], [](const ass::BackgroundCropping& info) {
            ASSERT_EQ(info.offset, (glm::vec2{0.f, 0.f}));
            ASSERT_EQ(info.size, (glm::vec2{1.f / 4.f, 1.f}));
            ASSERT_NE(info.size, (glm::vec2{1.f / 5.f, 1.f}));
        });
    }
    // second rule
    {
        auto& rule = rules[1];
        auto selector = rule.getSelector().getSubSelectors().first();
        ASSERT_EQ(IStringable::toString(selector), R"(ass::class_of("__preview_clazz$UI::Dialog") >> ass::class_of("__preview_clazz$ALabel"))");

        auto& declarations = rule.getDeclarations();
        ASSERT_EQ(declarations.size(), 3);

        assertAssDeclaration<ass::TextColor>(declarations[0], [](const ass::TextColor& info) {
            ASSERT_EQ(info.color, 0xff00ff_rgb);
            ASSERT_NE(info.color, 0xff10ff_rgb);
        });
        assertAssDeclaration<ass::FontSize>(declarations[1], [](const ass::FontSize& info) {
            ASSERT_EQ(info.size, 9_pt);
        });
        assertAssDeclaration<ass::LineHeight>(declarations[2], [](const ass::LineHeight& info) {
            ASSERT_EQ(info.spacing, 1.5);
        });
    }
}
