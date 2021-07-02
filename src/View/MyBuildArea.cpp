//
// Created by alex2 on 6/25/2021.
//

#include "MyBuildArea.h"
#include <AUI/ASS/ASS.h>
#include <AUI/Util/UIBuildingHelpers.h>

using namespace ass;

MyBuildArea::MyBuildArea(const _<AView>& wrappedView):
        ARulerArea(wrappedView),
        mWrappedView(wrappedView),
        mCornerDrawable(AImageLoaderRegistry::inst().loadDrawable(":svg/resize.svg"))
{
}

void MyBuildArea::render() {
    ARulerArea::render();

    RenderHints::PushMatrix m;
    Render::inst().translate(getResizeCornerPos());

    mCornerDrawable->draw({16_dp, 16_dp});
}

void MyBuildArea::onMouseMove(glm::ivec2 pos) {
    ARulerArea::onMouseMove(pos);
    if (mMouseDragging) {
        auto delta = pos - mMouseDragPos;
        mWrappedView->setFixedSize(glm::max(mPrevSize + delta * 2, glm::ivec2{mWrappedView->getContentMinimumWidth(), mWrappedView->getContentMinimumHeight()} ));
    }
}

void MyBuildArea::onMousePressed(glm::ivec2 pos, AInput::Key button) {
    AViewContainer::onMousePressed(pos, button);
    auto delta = pos - getResizeCornerPos();
    if (delta.x >= 0 && delta.y >= 0 && delta.x <= 16_dp && delta.y <= 16_dp) {
        mPrevSize = mWrappedView->getSize();
        mMouseDragPos = pos;
        mMouseDragging = true;
    }
}

void MyBuildArea::onMouseReleased(glm::ivec2 pos, AInput::Key button) {
    AViewContainer::onMouseReleased(pos, button);

    mMouseDragging = false;
}

glm::ivec2 MyBuildArea::getResizeCornerPos() {
    return (mWrappedView->getPositionInWindow() - getPositionInWindow()) + mWrappedView->getSize();
}
