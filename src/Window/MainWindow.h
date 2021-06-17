#pragma once

#include <AUI/Platform/AWindow.h>
#include <AUI/View/AListView.h>
#include <AUI/View/ALabel.h>

class MainWindow: public AWindow {
private:
    _<AListView> mProjectsListView;
    _<AViewContainer> mDisplayWrapper;
    _<ALabel> mPerformanceLabel;

    void openFileDialog();

    void updatePreview();

public:
    MainWindow();
};