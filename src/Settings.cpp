//
// Created by alex2 on 6/12/2021.
//

#include <AUI/IO/FileInputStream.h>
#include <AUI/Json/AJson.h>
#include <Model/Project.h>
#include <Repository/ProjectsRepository.h>
#include <AUI/Logging/ALogger.h>
#include "Settings.h"

Settings& Settings::inst() {
    static Settings s;
    return s;
}

Settings::Settings() {
    try {
        auto settings = AJson::read(_new<FileInputStream>("preview_settings.json"));

        for (auto& p : settings["projects"].asArray()) {
            Project project;
            project.readJson(p);
            ProjectsRepository::inst().getModel() << std::move(project);
        }
    } catch (...) {

    }
}

Settings::~Settings() {
    save();
}

void Settings::save() {
    try {
        AJsonObject settings;
        AJsonArray projects;
        for (Project& p : *ProjectsRepository::inst().getModel()) {
            projects << p.toJson();
        }
        settings["projects"] = projects;
        AJson::write(_new<FileOutputStream>("preview_settings.json"), settings);
    } catch (const AException& e) {
        ALogger::err("Could not save settings: " + e.getMessage());
    }
}
