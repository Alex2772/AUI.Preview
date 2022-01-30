//
// Created by Alex2772 on 1/26/2022.
//


#include <gtest/gtest.h>
#include <AUI/Preview/Cpp/Cpp.h>
#include <AUI/Preview/Cpp/AST/ExplicitInitializerListCtorNode.h>
#include <AUI/Preview/Visitor/Layout/LayoutVisitor.h>
#include <AUI/View/AView.h>
#include <AUI/Layout/AStackedLayout.h>
#include <AUI/Preview/Visitor/Layout/ViewVisitor.h>
#include <AUI/View/AButton.h>
#include "TestHelper.h"

/**
 * Fixture.
 */
class LayoutTest : public testing::Test {
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


TEST_F(LayoutTest, Case1) {
    auto ast = Cpp::parseExpression(R"(
Stacked {
    _new<AButton>("Hello"),
    _new<ALabel>("World"),
}
)");
    ViewVisitor v;
    ast->acceptVisitor(v);
    assertLayout<AStackedLayout>(v.getView(), [](const _<AViewContainer>& n) {
        ASSERT_EQ(n->getViews().size(), 2);
        assertType<AButton>(n->getViews()[0], [](const _<AButton>& button) {
            ASSERT_EQ(button->getText(), "Hello");
        });
        assertType<ALabel>(n->getViews()[1], [](const _<ALabel>& v) {
            ASSERT_EQ(v->getText(), "World");
        });
    });
}
