#include "MainWindow.h"
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/ASS/ASS.h>
#include <AUI/View/AListView.h>
#include <AUI/Model/AListModelAdapter.h>
#include <Repository/ProjectsRepository.h>
#include <AUI/View/AButton.h>
#include <AUI/Platform/ADesktop.h>
#include <AUI/Preview/Cpp/Cpp.h>
#include <AUI/Preview/Visitor/Layout/LayoutVisitor.h>
#include <AUI/Traits/strings.h>
#include <AUI/Preview/Visitor/Style/StyleVisitor.h>
#include <View/MyBuildArea.h>
#include <AUI/Preview/Model/ViewHierarchyTreeModel.h>
#include <AUI/Util/AViewProfiler.h>
#include <AUI/Preview/Visitor/Replicator.h>
#include <AUI/Model/AListModel.h>
#include <View/ProjectsTabView.h>
#include <View/StylesView.h>
#include <AUI/Platform/Dll.h>
#include <AUI/Common/Plugin.h>
#include <AUI/Preview/APreview.h>

using namespace ass;

MainWindow::MainWindow():
    AWindow("Preview", 1200_dp, 700_dp)
{
    setContents(Horizontal {
        Vertical {
            (mViewHierarchyTree = _new<ATreeView>() let {
                it->setViewFactory([](const _<ITreeModel<AString>>& model, const ATreeIndex& index) {
                    auto name = model->itemAt(index);
                    auto label = _new<ALabel>(name);
                    _<IDrawable> drawable;
                    try {
                        drawable = AImageLoaderRegistry::inst().loadDrawable(":icon/{}.svg"_as.format(name));
                    } catch (...) {}
                    if (drawable == nullptr) {
                        drawable = AImageLoaderRegistry::inst().loadDrawable(":icon/unknown.svg");
                    }
                    label->setIcon(drawable);
                    return label;
                });
            }) with_style { Expanding {2, 2} },

            mTargetViewDescription = _new<LayoutVisitor::ViewContainer>() with_style { FixedSize { {}, 200_dp } },

        } << ".side_panel",
        Vertical {
            Horizontal {
                mProjectsTabView = _new<ProjectsTabView>() let {
                    it->setModel(AAdapter::make<Project>(ProjectsRepository::inst(),
                                                         [](const Project& p) {
                                                             return p.path.filename();
                                                         }));
                },
                _new<AButton>("+").connect(&AView::clicked, me::openFileDialog) with_style {
                    BackgroundSolid { nullptr },
                    BoxShadow { nullptr },
                    Padding { 4_dp },
                    MinSize { 0 },
                },
                _new<ASpacer>(),
            },

            _new<MyBuildArea>( mDisplayWrapper = _new<StyleWrapperContainer>()),

            // bottom panel
            Horizontal {
                mPerformanceLabel = _new<ALabel>("Ready"),
            } with_style { BackgroundSolid { 0xeaeaea_rgb } },
        },
    });

    setCustomAss({ Padding { 0 } });

    connect(mViewHierarchyTree->itemMouseHover, this, [&](const ATreeIndex& x) {
        setTargetView((AView*) x.getUserData());
    });
    connect(mViewHierarchyTree->mouseLeave, this, [&]() {
        mTargetView = nullptr;
    });
    connect(mProjectsTabView->selectionChanged, [&](size_t index) {
        mCurrentProjectId = index;
        updatePreview();
    });

    showNoViewSelected();
}

void MainWindow::openFileDialog() {
    ADesktop::browseForFile({}, {{"C++ source file", "cpp"}})->onDone([](const APath& p) {
        if (p.empty()) return;
        ProjectsRepository::inst().getModel() << Project{ p };
    });
}

void MainWindow::updatePreview() {
    if (mCurrentProjectId >= ProjectsRepository::inst().getModel()->size()) {
        return;
    }

    setTargetView(nullptr);

    _<Project> project = Autumn::put(_new<Project>(ProjectsRepository::inst().getModel()->at(mCurrentProjectId)));

    mDisplayWrapper->setStylesheet(nullptr);
    mViewHierarchyTree->setModel(nullptr);
    async {
        // find src/ folder
        auto root = project->getRoot();
        APreview::setProject(project);

        // check if we can load plugins
        AString extension = "." + Dll::getDllExtension();
        static ASet<AString> loadedPlugins;
        for (auto& path : root.listDir(ListFlags::RECURSIVE | ListFlags::REGULAR_FILES)) {
            auto filename = path.filename();
            if (!loadedPlugins.contains(filename)) {
                if (filename.endsWith(extension) &&
                    (filename.startsWith("libpreview.") || filename.startsWith("preview."))) {
                    ALogger::info("Loading plugin {}"_as.format(path));
                    AStylesheet::inst().setIgnoreRules(true);
                    aui::importPluginPath(path);
                    loadedPlugins << filename;
                    AStylesheet::inst().setIgnoreRules(false);
                }
            }
        }

        auto styleSheetCpp = root["src"]["Style.cpp"];
        if (styleSheetCpp.isRegularFileExists()) {
            // stylesheets
            async {
                StyleVisitor v;
                auto ast = Cpp::parseCode(styleSheetCpp);
                ast->visit(v);
                auto s = v.getStylesheet();
                ui {
                    mDisplayWrapper->setStylesheet(s);
                };
            };
        }

        using namespace std::chrono;
        auto before1 = high_resolution_clock::now().time_since_epoch();
        auto ast = Cpp::parseCode(project->path);
        auto after1 = high_resolution_clock::now().time_since_epoch();
        ui {
            auto before2 = high_resolution_clock::now().time_since_epoch();
            LayoutVisitor v;
            ast->visit(v);
            auto after2 = high_resolution_clock::now().time_since_epoch();
            mPerformanceLabel->setText("Parse: {}ms"_as.format((duration_cast<milliseconds>(after1 - before1 + after2 - before2)).count()));
            mDisplayWrapper->setLayout(_new<AStackedLayout>());
            auto view = v.getContainer();
            mDisplayWrapper->addView(view);
            view->setExpanding({ 2, 2 });
            updateLayout();
            flagRedraw();
            mViewHierarchyTree->setModel(_new<ViewHierarchyTreeModel>(mDisplayWrapper));
        };
    };
}

void MainWindow::render() {
    AViewContainer::render();

    if (mTargetView) {
        AViewProfiler::displayBoundsOn(*mTargetView);
    }
}

void MainWindow::setTargetView(AView* targetView) {
    mTargetView = targetView;

    if (targetView) {
        mTargetViewDescription->setContents(Vertical {
            _new<StylesView>(targetView) let {
                connect(it->assUpdated, [&]{
                    mDisplayWrapper->invalidateAllViewStyles();
                    mDisplayWrapper->updateLayout();
                });
            },
        });
        mTargetView->getParent()->updateLayout();
    } else {
        showNoViewSelected();
    }
    flagRedraw();
}

void MainWindow::showNoViewSelected() const {
    mTargetViewDescription->setContents(Stacked {
        _new<ALabel>("No view selected") with_style { Opacity { 0.7f } }
    });
}
