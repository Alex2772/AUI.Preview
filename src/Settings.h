//
// Created by alex2 on 6/12/2021.
//

#pragma once


class Settings {
private:
    Settings();
    ~Settings();
public:
    static Settings& inst();
    void save();
};


