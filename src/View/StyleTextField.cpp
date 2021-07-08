//
// Created by alex2772 on 7/8/21.
//

#include "StyleTextField.h"
#include <AUI/View/AViewContainer.h>

int StyleTextField::getContentMinimumWidth() {
    prerenderStringIfNeeded();
    return mPrerenderedString.length;
}

void StyleTextField::typeableErase(size_t begin, size_t end) {
    AAbstractTextField::typeableErase(begin, end);
    getParent()->updateLayout();
}

void StyleTextField::typeableInsert(size_t at, const AString& toInsert) {
    AAbstractTextField::typeableInsert(at, toInsert);
    getParent()->updateLayout();
}

void StyleTextField::typeableInsert(size_t at, wchar_t toInsert) {
    AAbstractTextField::typeableInsert(at, toInsert);
    getParent()->updateLayout();
}

void StyleTextField::setText(const AString& t) {
    AAbstractTextField::setText(t);
    if (getParent()) {
        getParent()->updateLayout();
    }
}
