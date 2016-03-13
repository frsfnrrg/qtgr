#include "transform/regression.h"
#include "choosers.h"
#include "base/globals.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"
#include "mainwindow.h"
#include "util.h"

#include <QGridLayout>
#include <QLabel>

TransformRegression* TransformRegression::me = NULL;

TransformRegression::TransformRegression(MainWindow* mainWin) :
    Dialog(mainWin, "Regression")
{
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    output = new QPlainTextEdit();
    output->setReadOnly(true);
    output->setTabStopWidth(80);

    const char* degrees[] = {
        "Linear",
        "Quadratic",
        "Cubic",
        "4th Degree",
        "5th Degree",
        "6th Degree",
        "7th Degree",
        "8th Degree",
        "9th Degree",
        "10th Degree",
        "1 - 10",
        "Power",
        "Exponential",
        "Logarithmic",
        "Inverse"
    };
    const int degrees_len = sizeof degrees / sizeof degrees[0];

    degree = makeQComboBox(this, degrees, degrees_len);
    load = new QComboBox();
    load->addItem(tr("Fitted Values"));
    load->addItem(tr("Residuals"));

    outputLabel = makeLabel("Output");
    loadLabel = makeLabel("Load");
    degreeLabel = makeLabel("Degree");

    QGridLayout* layout = new QGridLayout();
    addPair(layout, 0, makeLabel("Set"), setNumber);
    layout->setRowMinimumHeight(2, 12);
    addPair(layout, 2, degreeLabel, degree);
    addPair(layout, 3, loadLabel, load);
    layout->setRowMinimumHeight(4, 12);

    layout->setColumnStretch(0, 0);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 3);
    layout->setColumnMinimumWidth(1, 180);

    layout->addWidget(outputLabel, 5, 0);
    layout->addWidget(output, 5, 1, 1, 2);

    this->setDialogLayout(layout);

    if (!me) me = this;
}

void TransformRegression::updateDialog() {
    int setno = setNumber->currentIndex();
    bool isnull = g[cg].p[setno].active == FALSE && g[cg].p[setno].deact == 0;

    outputLabel->setDisabled(isnull);
    loadLabel->setDisabled(isnull);
    degreeLabel->setDisabled(isnull);

    output->setDisabled(isnull);
    load->setDisabled(isnull);
    degree->setDisabled(isnull);
}

void TransformRegression::applyDialog() {
    int setno = setNumber->currentIndex();
    if (g[cg].p[setno].active == FALSE && g[cg].p[setno].deact == 0) {
        return;
    }

//    do_regress(setno, degree->currentIndex()+1, load->currentIndex());//fixme

    if (ToolsOptions::isRescaleOnTransform()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }
    SetsSender::send();
}

void TransformRegression::stufftext(char* s) {
    if (me) {
        me->output->moveCursor(QTextCursor::End);
        me->output->insertPlainText(QString(s));
    }
}

void qt_stufftext(char* s) {
    TransformRegression::stufftext(s);
}
