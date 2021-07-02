//
// Created by alex2 on 6/25/2021.
//

#pragma once

#include <AUI/View/ARulerArea.h>
#include <AUI/Image/IDrawable.h>

class MyBuildArea: public ARulerArea {
private:
    _<AView> mWrappedView;
    _<IDrawable> mCornerDrawable;
    glm::ivec2 mMouseDragPos;
    bool mMouseDragging = false;
    glm::ivec2 mPrevSize;

    glm::ivec2 getResizeCornerPos();
public:

    explicit MyBuildArea(const _<AView>& wrappedView);

    void render() override;

    void onMouseMove(glm::ivec2 pos) override;

    void onMousePressed(glm::ivec2 pos, AInput::Key button) override;

    void onMouseReleased(glm::ivec2 pos, AInput::Key button) override;
};


