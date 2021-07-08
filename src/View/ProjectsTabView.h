//
// Created by alex2772 on 7/7/21.
//

#pragma once

#include <AUI/View/AViewContainer.h>
#include <AUI/Model/AListModelObserver.h>
#include <AUI/View/ATabView.h>

class ProjectsTabView: public AViewContainer, public AListModelObserver<AString>::IListModelListener {
private:
    _<AListModelObserver<AString>> mObserver;
    _<ATabButtonView> mCurrentItem;

public:
    ProjectsTabView();
    void setModel(const _<IListModel<AString>>& model);

    void insertItem(size_t at, const AString& value) override;
    void updateItem(size_t at, const AString& value) override;
    void removeItem(size_t at) override;
    void onDataCountChanged() override;
    void onDataChanged() override;

signals:
    emits<size_t> selectionChanged;
};
