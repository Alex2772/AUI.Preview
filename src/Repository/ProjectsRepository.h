//
// Created by alex2 on 6/11/2021.
//

#pragma once


#include <AUI/Model/AListModel.h>
#include <AUI/Preview/Model/Project.h>

class ProjectsRepository {
private:
    _<AListModel<Project>> mModel;

public:
    explicit ProjectsRepository();

    [[nodiscard]]
    operator _<IListModel<Project>>() const {
        return mModel;
    }

    [[nodiscard]]
    const _<AListModel<Project>>& getModel() const {
        return mModel;
    }

    static ProjectsRepository& inst();
};


