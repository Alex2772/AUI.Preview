#include "MainWindow.h"
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/ASS/ASS.h>
#include <AUI/View/AListView.h>
#include <AUI/Model/AListModelAdapter.h>
#include <Repository/ProjectsRepository.h>
#include <AUI/View/AButton.h>
#include <AUI/Platform/ADesktop.h>
#include <Cpp/Cpp.h>
#include <Visitor/MyVisitor.h>

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
        Stacked {
            mDisplayWrapper = _new<AViewContainer>() << ".build_area"
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
    Project project = ProjectsRepository::inst().getModel()->at(mProjectsListView->getSelectionModel().one().getRow());
    async {
        auto ast = Cpp::parseCode(project.path);
        ui {
            MyVisitor v;
            ast->visit(&v);
            mDisplayWrapper->setLayout(_new<AStackedLayout>());
            auto view = v.getContainer();
            mDisplayWrapper->addView(view);
            view->setExpanding({ 2, 2 });
            updateLayout();
            flagRedraw();
        };
    };
}
