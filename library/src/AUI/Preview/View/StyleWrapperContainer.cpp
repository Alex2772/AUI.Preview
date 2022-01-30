//
// Created by alex2 on 6/24/2021.
//

#include "StyleWrapperContainer.h"
#include <AUI/ASS/ASS.h>

using namespace ass;

struct Replace {
private:
    _<AStylesheet> mPrev;
    
public:
    Replace(const _<AStylesheet>& x) {
        mPrev = AStylesheet::instStorage();
        if (x) {
            AStylesheet::instStorage() = x;
        }
    }
    
    ~Replace() {
        AStylesheet::instStorage() = mPrev;
    }
};


void StyleWrapperContainer::setSize(int width, int height) {
    Replace r(mStylesheet);
    AViewContainer::setSize(width, height);
}

void StyleWrapperContainer::render() {
    Replace r(mStylesheet);
    AViewContainer::render();
}

void StyleWrapperContainer::invalidateAllViewStyles() {
    // dpi update ensures that all styles will be invalidated
    onDpiChanged();
}

StyleWrapperContainer::~StyleWrapperContainer() {

}

void StyleWrapperContainer::onMouseEnter() {
    Replace r(mStylesheet);
    AViewContainer::onMouseEnter();
}

void StyleWrapperContainer::onMouseMove(glm::ivec2 pos) {
    Replace r(mStylesheet);
    AViewContainer::onMouseMove(pos);
}

void StyleWrapperContainer::onMouseLeave() {
    Replace r(mStylesheet);
    AViewContainer::onMouseLeave();
}

void StyleWrapperContainer::onDpiChanged() {
    Replace r(mStylesheet);
    AViewContainer::onDpiChanged();
}

int StyleWrapperContainer::getContentMinimumWidth() {
    Replace r(mStylesheet);
    return AViewContainer::getContentMinimumWidth();
}

int StyleWrapperContainer::getContentMinimumHeight() {
    Replace r(mStylesheet);
    return AViewContainer::getContentMinimumHeight();
}

void StyleWrapperContainer::onMousePressed(glm::ivec2 pos, AInput::Key button) {
    Replace r(mStylesheet);
    AViewContainer::onMousePressed(pos, button);
}

void StyleWrapperContainer::onMouseDoubleClicked(glm::ivec2 pos, AInput::Key button) {
    Replace r(mStylesheet);
    AViewContainer::onMouseDoubleClicked(pos, button);
}

void StyleWrapperContainer::onMouseReleased(glm::ivec2 pos, AInput::Key button) {
    Replace r(mStylesheet);
    AViewContainer::onMouseReleased(pos, button);
}

bool StyleWrapperContainer::consumesClick(const glm::ivec2& pos) {
    Replace r(mStylesheet);
    return AViewContainer::consumesClick(pos);
}

void StyleWrapperContainer::setEnabled(bool enabled) {
    Replace r(mStylesheet);
    AViewContainer::setEnabled(enabled);
}

_<AView> StyleWrapperContainer::getViewAt(glm::ivec2 pos, bool ignoreGone) {
    return AViewContainer::getViewAt(pos, ignoreGone);
}

void StyleWrapperContainer::updateLayout() {
    Replace r(mStylesheet);
    AViewContainer::updateLayout();
}


void StyleWrapperContainer::updateParentsLayoutIfNecessary() {
    Replace r(mStylesheet);
    AViewContainer::updateParentsLayoutIfNecessary();
}

StyleWrapperContainer::StyleWrapperContainer() {
    setCustomAss({
        BoxShadow{0, 4_dp, 17_dp, 0x40000000_argb},
        MinSize{10_dp, 10_dp},
        BackgroundSolid{0xf0f0f0_rgb},
        Overflow::HIDDEN,
    });
}

void StyleWrapperContainer::onMouseWheel(const glm::ivec2& pos, const glm::ivec2& delta) {
    Replace r(mStylesheet);
    AViewContainer::onMouseWheel(pos, delta);
}

void StyleWrapperContainer::recompileAss() {
    Replace r(mStylesheet);
    AViewContainer::recompileAss();
}
