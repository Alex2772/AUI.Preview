//
// Created by alex2 on 7/1/2021.
//

#include <Visitor/Replicator.h>
#include "ViewHierarchyTreeModel.h"

size_t ViewHierarchyTreeModel::childrenCount(const ATreeIndex& parent) {
    AView* v = reinterpret_cast<AView*>(parent.getUserData());
    if (auto c = dynamic_cast<AViewContainer*>(v)) {
        return c->getViews().size();
    }
}

AString ViewHierarchyTreeModel::itemAt(const ATreeIndex& index) {
    auto c = (AView*)index.getUserData();
    return Replicator::prettyName(c);
}

ATreeIndex ViewHierarchyTreeModel::indexOfChild(size_t row, size_t column, const ATreeIndex& parent) {
    AViewContainer* c = dynamic_cast<AViewContainer*>((AView*)parent.getUserData());
    return {(AView*)c->getViews()[row].get(), row, column};
}

void* ViewHierarchyTreeModel::getUserDataForRoot() {
    return (AView*)mRoot.get();
}
