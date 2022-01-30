//
// Created by alex2 on 6/24/2021.
//

#pragma once


#include <AUI/View/AViewContainer.h>
#include <AUI/ASS/AStylesheet.h>

class StyleWrapperContainer: public AViewContainer {
private:
    _<AStylesheet> mStylesheet;

public:
    StyleWrapperContainer();
    void invalidateAllViewStyles();

    void setStylesheet(const _<AStylesheet>& stylesheet) {
        mStylesheet = stylesheet;
        updateLayout();
        invalidateAllViewStyles();
    }

    void setSize(int width, int height) override;

    void render() override;

    ~StyleWrapperContainer() override;

    void onMouseEnter() override;

    void onMouseMove(glm::ivec2 pos) override;

    void onMouseLeave() override;

    void onDpiChanged() override;

    int getContentMinimumWidth() override;

    int getContentMinimumHeight() override;

    void onMousePressed(glm::ivec2 pos, AInput::Key button) override;

    void onMouseDoubleClicked(glm::ivec2 pos, AInput::Key button) override;

    void onMouseReleased(glm::ivec2 pos, AInput::Key button) override;

protected:
    void recompileAss() override;

public:
    void onMouseWheel(const glm::ivec2& pos, const glm::ivec2& delta) override;

    bool consumesClick(const glm::ivec2& pos) override;

    void setEnabled(bool enabled) override;

    _<AView> getViewAt(glm::ivec2 pos, bool ignoreGone) override;

    void updateLayout() override;

protected:

    void updateParentsLayoutIfNecessary() override;
};


