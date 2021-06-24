#pragma once

#include <AUI/Platform/AWindow.h>
#include <AUI/View/AListView.h>
#include <AUI/View/ALabel.h>
#include <View/StyleWrapperContainer.h>

class MainWindow: public AWindow {
private:
    _<AListView> mProjectsListView;
    _<StyleWrapperContainer> mDisplayWrapper;
    _<ALabel> mPerformanceLabel;

    void openFileDialog();

    void updatePreview();

public:
    MainWindow();
};