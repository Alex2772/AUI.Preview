#pragma once

#include <AUI/Platform/AWindow.h>
#include <AUI/View/AListView.h>

class MainWindow: public AWindow {
private:
    _<AListView> mProjectsListView;
    _<AViewContainer> mDisplayWrapper;

    void openFileDialog();

    void updatePreview();

public:
    MainWindow();
};