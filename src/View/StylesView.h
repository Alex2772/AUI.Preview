//
// Created by alex2772 on 7/7/21.
//

#pragma once


#include <AUI/View/AScrollArea.h>

class StylesView: public AScrollArea {
private:
    AView* mTargetView;
    _<AView> mPreviewerView;

public:
    explicit StylesView(AView* targetView);
    ~StylesView() override = default;

    void render() override;

signals:
    emits<> assUpdated;

    void
    displayApplicableRule(ADeque<ass::decl::IDeclarationBase*>& applicableDeclarations,
                          const RuleWithoutSelector* rule);
};
