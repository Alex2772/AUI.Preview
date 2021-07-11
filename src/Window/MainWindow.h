#pragma once

#include <AUI/Platform/AWindow.h>
#include <AUI/View/AListView.h>
#include <AUI/View/ALabel.h>
#include <View/StyleWrapperContainer.h>
#include <AUI/View/ATreeView.h>
#include <AUI/Preview/Visitor/Layout/LayoutVisitor.h>
#include <View/ProjectsTabView.h>

class MainWindow: public AWindow {
private:
    _<ProjectsTabView> mProjectsTabView;
    _<StyleWrapperContainer> mDisplayWrapper;
    _<ALabel> mPerformanceLabel;
    _<ATreeView> mViewHierarchyTree;
    AView* mTargetView = nullptr;
    _<LayoutVisitor::ViewContainer> mTargetViewDescription;
    size_t mCurrentProjectId = -1;

    void openFileDialog();

    void updatePreview();

public:
    MainWindow();

    void render() override;

    void setTargetView(AView* targetView);

    void showNoViewSelected() const;
};