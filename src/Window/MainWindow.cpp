#include "MainWindow.h"
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/ASS/ASS.h>
#include <AUI/View/AListView.h>
#include <AUI/Model/AListModelAdapter.h>
#include <Repository/ProjectsRepository.h>
#include <AUI/View/AButton.h>
#include <AUI/Platform/ADesktop.h>
#include <Cpp/Cpp.h>
#include <Visitor/Layout/LayoutVisitor.h>
#include <AUI/Traits/strings.h>
#include <Visitor/Style/StyleVisitor.h>
#include <View/MyBuildArea.h>
#include <Model/ViewHierarchyTreeModel.h>
#include <AUI/Util/AViewProfiler.h>
#include <Visitor/Replicator.h>
#include <AUI/Model/AListModel.h>

using namespace ass;

MainWindow::MainWindow():
    AWindow("Preview", 1200_dp, 700_dp)
{
    setContents(Horizontal {
        Vertical {
            Horizontal {
                _new<ALabel>("Projects"),
                _new<ASpacer>(),
                _new<AButton>("Open...").connect(&AView::clicked, me::openFileDialog),
            },
            mProjectsListView = _new<AListView>(AAdapter::make<Project>(ProjectsRepository::inst(),
                                                                           [](const Project& p) {
                return p.path.filename();
            })).connect(&AListView::selectionChanged, me::updatePreview),
            _new<ALabel>("Твiя срака"),
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
            _new<MyBuildArea>( mDisplayWrapper = _new<StyleWrapperContainer>()),

            // bottom panel
            Horizontal {
                mPerformanceLabel = _new<ALabel>("Ready"),
            } with_style { BackgroundSolid { 0xeaeaea_rgb } },
        },
    });

    setCustomAss({ Padding { 0 } });

    connect(mViewHierarchyTree->itemMouseHover, this, [&](const ATreeIndex& x) {
        setTargetView((AView*)x.getUserData());
    });
    connect(mViewHierarchyTree->mouseLeave, this, [&]() {
        mTargetView = nullptr;
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
    setTargetView(nullptr);
    if (mProjectsListView->getSelectionModel().empty()) {
        return;
    }
    _<Project> project = Autumn::put(_new<Project>(ProjectsRepository::inst().getModel()->at(mProjectsListView->getSelectionModel().one().getRow())));

    mDisplayWrapper->setStylesheet(nullptr);
    mViewHierarchyTree->setModel(nullptr);
    async {
        // find src/ folder
        auto root = project->getRoot();
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
    redraw();

    if (targetView) {
        char ptr[0xff];
        sprintf(ptr, "0x%p", targetView);
        mTargetViewDescription->setContents(Vertical {
                _new<ALabel>(Replicator::prettyName(targetView)) with_style { FontSize {14_pt } },
                _new<ALabel>(ptr),
                _new<ALabel>("ASS classes:"),
                _new<AListView>(_new<AListModel<AString>>(targetView->getAssNames().begin(), targetView->getAssNames().end())),
        });
    } else {
        showNoViewSelected();
    }
    updateLayout();
}

void MainWindow::showNoViewSelected() const {
    mTargetViewDescription->setContents(Stacked {
        _new<ALabel>("No view selected") with_style { Opacity { 0.7f } }
    });
}
