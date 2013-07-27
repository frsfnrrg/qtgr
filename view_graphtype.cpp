#include "view_graphtype.h"

#include "globals.h"

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
    for (int i=0;i<maxsets;i++) {
        setNumbers->addItem(QString::number(i));
    }
    //connect(setNumbers, SIGNAL(currentIndexChanged(int)), this, SLOT(updateType()));

    // add icons?
    graphTypes = new QComboBox();
    graphTypes->addItem("X Lin, Y Lin");
    graphTypes->addItem("X Lin, Y Log");
    graphTypes->addItem("X Log, Y Lin");
    graphTypes->addItem("X Log, Y Log");
    graphTypes->addItem("X Log, Y Log");
    graphTypes->addItem("Vertical Bar");
    graphTypes->addItem("Vertical Bar Stacked");
    graphTypes->addItem("Horizontal Bar");
    graphTypes->addItem("Horizontal Bar Stacked");

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
    printf("applying graph types");

    // & show it too
    drawgraph();
}

void ViewGraphType::doneType() {
    printf("done setting graph types\n");
    this->applyType();
    this->setVisible(false);
}

void ViewGraphType::updateType() {
    printf("updating graph types");
}

void ViewGraphType::cancelType() {
    printf("cancelling graph types");
    this->setVisible(false);
}
