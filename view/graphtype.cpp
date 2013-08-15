#include "view/graphtype.h"
#include "base/globals.h"

const int indx2type[] = { XY, LOGY, LOGX, LOGXY, BAR, STACKEDBAR, HBAR, STACKEDHBAR};
const char* opts[] = {"X Linear, Y Linear",
                        "X Linear, Y Logarithmic",
                        "X Logarithmic, Y Linear",
                        "X Logarithmic, Y Logarithmic",
                        "Vertical Bar",
                        "Vertical Bar Stacked",
                        "Horizontal Bar",
                        "Horizontal Bar Stacked"};

ViewGraphType::ViewGraphType(MainWindow* mainWin) :
    Dialog(mainWin, "Set Graph Type", true)
{
    printf("creating graph window");

    // items
    setNumbers = new QComboBox();
    setNumbers->addItem(QString::number(0));
    connect(setNumbers, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    graphTypes = new QComboBox();
    for (int k=0;k<8;k++) {
        graphTypes->addItem(tr(opts[k]));
    }

    autoHook(graphTypes);

    // layouting
    QGridLayout* primary = new QGridLayout();

    primary->addWidget(new QLabel(tr("Select Graph:"),0,0));
    primary->addWidget(setNumbers,0,1);

    // spacer
    primary->setRowMinimumHeight(1, 8);

    // if we really want to, use a nested, multilevel thingy.
    primary->addWidget(new QLabel(tr("Graph Type")), 2,0);
    primary->addWidget(graphTypes, 2, 1);

    this->setDialogLayout(primary);
}

void ViewGraphType::applyDialog() {
    // FIXME TODO: give this a warning when the world dimensions dip below 0

    printf("applying graph types\n");

    int cset = setNumbers->currentIndex();
    int t = graphTypes->currentIndex();

    int type = indx2type[t];
    g[cset].type = type;
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
