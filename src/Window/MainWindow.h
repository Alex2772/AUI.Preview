#pragma once

#include <AUI/Platform/AWindow.h>
#include <AUI/View/AListView.h>
#include <AUI/View/ALabel.h>
#include <View/StyleWrapperContainer.h>
#include <AUI/View/ATreeView.h>
#include <Visitor/Layout/LayoutVisitor.h>

class MainWindow: public AWindow {
private:
    _<AListView> mProjectsListView;
    _<StyleWrapperContainer> mDisplayWrapper;
    _<ALabel> mPerformanceLabel;
    _<ATreeView> mViewHierarchyTree;
    AView* mTargetView = nullptr;
    _<LayoutVisitor::ViewContainer> mTargetViewDescription;

    void openFileDialog();

    void updatePreview();

public:
    MainWindow();

    void render() override;

    void setTargetView(AView* targetView);

    void showNoViewSelected() const;
};