#include "view_graphtype.h"

#include "globals.h"

const int indx2type[] = { XY, LOGY, LOGX, LOGXY, BAR, STACKEDBAR, HBAR, STACKEDHBAR};
const char* opts[] = {"X Linear, Y Linear",
                        "X Linear, Y Logarithmic",
                        "X Logarithmic, Y Linear",
                        "X Logarithmic, Y Logarithmic",
                        "Vertical Bar",
                        "Vertical Bar Stacked",
                        "Horizontal Bar",
                        "Horizontal Bar Stacked"};

ViewGraphType::ViewGraphType(MainWindow* mainWin) : QDialog(mainWin)
{
    printf("creating graph window");
    this->mainWindow = mainWin;
    this->setWindowTitle(tr("QTGR: Set Graph Type"));

    // items

    QPushButton* apply = new QPushButton(tr("Apply"));
    connect(apply, SIGNAL(clicked()), this, SLOT(applyType()));

    QPushButton* done = new QPushButton(tr("Done"));
    connect(done, SIGNAL(clicked()), this, SLOT(doneType()));

    QPushButton* cancel = new QPushButton(tr("Cancel"));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelType()));

    // FIXME: abstract this out; view symbols has the exact
    // same mess.
    setNumbers = new QComboBox();
    setNumbers->addItem(QString::number(0));
    connect(setNumbers, SIGNAL(currentIndexChanged(int)), this, SLOT(updateType()));

    graphTypes = new QComboBox();
    for (int k=0;k<4;k++) {
        graphTypes->addItem(tr(opts[k]));
    }

    // layouting

    QVBoxLayout* layout = new QVBoxLayout();

    QGridLayout* primary = new QGridLayout();
    layout->addLayout(primary);

    primary->addWidget(new QLabel(tr("Select Set:"),0,0));
    primary->addWidget(setNumbers,0,1);

    // spacer
    primary->addWidget(new QLabel(""),1,0,1,3);

    // if we really want to, use a nested, multilevel thingy.
    primary->addWidget(new QLabel(tr("Graph Type")), 2,0);
    primary->addWidget(graphTypes, 2, 1);

    QHBoxLayout* finals = new QHBoxLayout();
    layout->addLayout(finals);

    finals->addWidget(cancel);
    finals->addStretch();
    finals->addWidget(apply);
    finals->addWidget(done);

    this->setLayout(layout);
}

void ViewGraphType::applyType() {
    printf("applying graph types\n");

    int cset = setNumbers->currentIndex();
    int t = graphTypes->currentIndex();

    g[cset].type = indx2type[t];
    printf("%i %i\n", g[cset].type, t);

    // & show it too
    drawgraph();
}

void ViewGraphType::doneType() {
    printf("done setting graph types\n");
    this->applyType();
    this->setVisible(false);
}

void ViewGraphType::updateType() {
    printf("updating graph types\n");

    int cset = setNumbers->currentIndex();
    int g_type = g[cset].type;

    // darn, need a good solution to unite
    // the graph display types and #enums.
    // too hacky
    int vk = -1;
    switch (g_type) {

    case POLAR:
    case PIE:
    case STACKEDLINE:
        printf("type not implemented");
        break;

    case XY:
        vk = 0;
        break;
    case LOGY:
        vk = 1;
        break;
    case LOGX:
        vk = 2;
        break;
    case LOGXY:
        vk = 3;
        break;
    case BAR:
        vk = 4;
        break;
    case STACKEDBAR:
        vk = 5;
        break;
    case HBAR:
        vk = 6;
        break;
    case STACKEDHBAR:
        vk = 7;
        break;
    }

    if (vk != -1) {
        graphTypes->setCurrentIndex(vk);
    } else {
        printf("Unsupported graph type...");
    }
}

void ViewGraphType::cancelType() {
    printf("cancelling graph types\n");
    this->setVisible(false);
}
