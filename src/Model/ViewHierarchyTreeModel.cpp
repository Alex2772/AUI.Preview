//
// Created by alex2 on 7/1/2021.
//

#include <Visitor/Replicator.h>
#include "ViewHierarchyTreeModel.h"

size_t ViewHierarchyTreeModel::childrenCount(const ATreeIndex& parent) {
    AView* v = reinterpret_cast<AView*>(parent.getUserData());
    auto c = dynamic_cast<AViewContainer *>(v);
    if (c) {
        return c->getViews().size();
    } else {
        return 0;
    }
}

AString ViewHierarchyTreeModel::itemAt(const ATreeIndex& index) {
    auto c = (AView*) index.getUserData();
    return Replicator::prettyName(c);
}

void *ViewHierarchyTreeModel::rootUserData() {
    return mRoot.get();
}

ATreeIndex ViewHierarchyTreeModel::indexOfChild(size_t row, size_t column, const ATreeIndex& parent) {
    AViewContainer* c = dynamic_cast<AViewContainer*>((AView*) parent.getUserData());
    assert(c);
    return ATreeIndex{ (void *) c->getViews()[row].get() };
}
