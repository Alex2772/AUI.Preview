//
// Created by alex2 on 6/11/2021.
//

#include "ProjectsRepository.h"

ProjectsRepository::ProjectsRepository() {
    mModel = _new<AListModel<Project>>();
}

ProjectsRepository& ProjectsRepository::inst() {
    static ProjectsRepository r;
    return r;
}
