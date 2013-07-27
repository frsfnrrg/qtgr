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

ViewGraphType::ViewGraphType(MainWindow* mainWin) : Dialog(mainWin, tr("Set Graph Type"))
{
    printf("creating graph window");

    // items

    QPushButton* apply = new QPushButton(tr("Apply"));
    connect(apply, SIGNAL(clicked()), this, SLOT(applyDialog()));

    QPushButton* done = new QPushButton(tr("Done"));
    connect(done, SIGNAL(clicked()), this, SLOT(doneDialog()));

    QPushButton* cancel = new QPushButton(tr("Cancel"));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelDialog()));

    setNumbers = new QComboBox();
    setNumbers->addItem(QString::number(0));
    connect(setNumbers, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    graphTypes = new QComboBox();
    for (int k=0;k<4;k++) {// FIXME: find out why bar charts fail (and others are skewed)
        graphTypes->addItem(tr(opts[k]));
    }

    // layouting
    QGridLayout* primary = new QGridLayout();

    primary->addWidget(new QLabel(tr("Select Graph:"),0,0));
    primary->addWidget(setNumbers,0,1);

    // spacer
    primary->addWidget(new QLabel(""),1,0,1,3);

    // if we really want to, use a nested, multilevel thingy.
    primary->addWidget(new QLabel(tr("Graph Type")), 2,0);
    primary->addWidget(graphTypes, 2, 1);

    this->setDialogLayout(primary);
}

void ViewGraphType::applyDialog() {
    printf("applying graph types\n");

    int cset = setNumbers->currentIndex();
    int t = graphTypes->currentIndex();

    g[cset].type = indx2type[t];
    printf("%i %i\n", g[cset].type, t);

    // & show it too
    drawgraph();
}

void ViewGraphType::updateDialog() {
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
        printf("type not implemented\n");
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
        printf("Unsupported graph type...\n");
    }
}
