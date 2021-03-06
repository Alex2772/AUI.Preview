//
// Created by alex2 on 7/1/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include <AUI/Model/ITreeModel.h>
#include <AUI/View/AViewContainer.h>

class API_AUI_PREVIEW_LIBRARY ViewHierarchyTreeModel: public ITreeModel<AString> {
private:
    _<AViewContainer> mRoot;

public:
    ViewHierarchyTreeModel(const _<AViewContainer>& root) : mRoot(root) {}

    ~ViewHierarchyTreeModel() override = default;

    size_t childrenCount(const ATreeIndex& parent) override;
    AString itemAt(const ATreeIndex& index) override;
    ATreeIndex indexOfChild(size_t row, size_t column, const ATreeIndex& parent) override;

protected:
    void *rootUserData() override;
};


