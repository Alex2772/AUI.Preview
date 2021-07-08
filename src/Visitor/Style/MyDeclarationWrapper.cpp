//
// Created by alex2772 on 7/7/21.
//

#include "MyDeclarationWrapper.h"

void MyDeclarationWrapper::applyFor(AView* view) {
    mWrappedDeclaration->applyFor(view);
}

void MyDeclarationWrapper::renderFor(AView* view) {
    mWrappedDeclaration->renderFor(view);
}

bool MyDeclarationWrapper::isNone() {
    return mWrappedDeclaration->isNone();
}

ass::decl::DeclarationSlot MyDeclarationWrapper::getDeclarationSlot() const {
    return mWrappedDeclaration->getDeclarationSlot();
}
