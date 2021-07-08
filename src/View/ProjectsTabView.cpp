//
// Created by alex2772 on 7/7/21.
//

#include <AUI/Layout/AHorizontalLayout.h>
#include "ProjectsTabView.h"

class Item: public ATabButtonView {
public:
    using ATabButtonView::ATabButtonView;
};

ProjectsTabView::ProjectsTabView() {
}

void ProjectsTabView::setModel(const _<IListModel<AString>>& model) {
    setLayout(_new<AHorizontalLayout>());
    if (!mObserver) {
        mObserver = _new<AListModelObserver<AString>>(this);
    }
    mObserver->setModel(model);
}

void ProjectsTabView::insertItem(size_t at, const AString& value) {
    auto item = _new<Item>(value);
    addView(at, item);

    connect(item->mousePressed, [&, item]() {
        if (mCurrentItem) {
            mCurrentItem->setCurrent(false);
        }
        item->setCurrent(true);
        mCurrentItem = item;
        emit selectionChanged(getViews().indexOf(item));
    });
}

void ProjectsTabView::updateItem(size_t at, const AString& value) {
    _cast<Item>(mViews[at])->setText(value);
}

void ProjectsTabView::removeItem(size_t at) {
    removeView(at);
}

void ProjectsTabView::onDataCountChanged() {
    updateLayout();
}

void ProjectsTabView::onDataChanged() {
    redraw();
}

