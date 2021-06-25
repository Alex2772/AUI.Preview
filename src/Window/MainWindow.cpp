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

using namespace ass;

MainWindow::MainWindow():
    AWindow("Preview")
{
    setContents(Horizontal {
        Vertical {
            Horizontal {
                _new<ALabel>("Projects:"),
                _new<ASpacer>(),
                _new<AButton>("Open...").connect(&AView::clicked, me::openFileDialog),
            },
            mProjectsListView = _new<AListView>(AAdapter::make<Project>(ProjectsRepository::inst(),
                                                                           [](const Project& p) {
                return p.path.filename();
            })).connect(&AListView::selectionChanged, me::updatePreview),
            _new<ASpacer>(),
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
}

void MainWindow::openFileDialog() {
    ADesktop::browseForFile({}, {{"C++ source file", "cpp"}})->onDone([](const APath& p) {
        ProjectsRepository::inst().getModel() << Project{ p };
    });
}

void MainWindow::updatePreview() {
    if (mProjectsListView->getSelectionModel().empty()) {
        return;
    }
    _<Project> project = Autumn::put(_new<Project>(ProjectsRepository::inst().getModel()->at(mProjectsListView->getSelectionModel().one().getRow())));

    mDisplayWrapper->setStylesheet(nullptr);
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
        };
    };
}
