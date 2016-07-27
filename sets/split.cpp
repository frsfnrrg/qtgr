#include "sets/split.h"
#include "choosers.h"
#include "prop.h"
#include "base/globals.h"

#include <QButtonGroup>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QSlider>

SetsSplit::SetsSplit(MainWindow* mainWin) :
    Dialog(mainWin, "Split")
{
    setNumber = new SetComboBox();
    connect(setNumber, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));

    position = new IntegerSpinBox();
    connect(position, SIGNAL(valueChanged(int)), this, SLOT(spinChange()));
    position->setFocusPolicy(Qt::WheelFocus);

    preview = new QTableWidget();
    preview->setRowCount(2);// or 3, for Dx, etc.
    preview->setColumnCount(5);
    preview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    preview->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    preview->setVerticalHeaderLabels(QStringList() << "X "<< "Y");
    preview->setSelectionMode(QAbstractItemView::NoSelection);
    preview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    preview->setShowGrid(true);
    preview->horizontalHeader()->hide();
    preview->setMinimumWidth(400);
#if QT_VERSION >= 0x050000
    preview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    preview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    preview->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    preview->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
    // set a bunch of lfloating point items...
    for (int j=0;j<preview->rowCount();j++) {
        for (int i=0;i<preview->columnCount();i++) {
            preview->setItem(j,i,new QTableWidgetItem(""));
        }
    }

    slider = new Slider(Qt::Horizontal);
    slider->setPageStep(20);
    slider->setSingleStep(1);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slideChange()));

    QGridLayout* layout = new QGridLayout();

    QHBoxLayout* topRow = new QHBoxLayout();
    topRow->addWidget(makeLabel("Set"));
    topRow->addWidget(setNumber);
    topRow->addStretch(1);
    topRow->addWidget(makeLabel("Pos"));
    topRow->addWidget(position);
    layout->addLayout(topRow, 0, 0);

    layout->addWidget(preview, 1, 0);
    layout->addWidget(slider, 2, 0);

    this->setDialogLayout(layout);

    SetsSender::addViaDialog(this);
}

void SetsSplit::updateDialog() {
    int setno = setNumber->currentIndex();
    int len = g[cg].p[setno].len;
    if (!isactive_set(cg, setno) || len <= 0) {
        deactivate(true);
        slider->setDisabled(true);
        position->setDisabled(true);
        // wipe preview
        for (int j=0;j<preview->rowCount();j++) {
            for (int i=0;i<preview->columnCount();i++) {
                QTableWidgetItem* t = preview->item(j,i);
                t->setText("");
                t->setBackgroundColor(QColor(220,220,220));
            }
            preview->item(j, 2)->setBackgroundColor(Qt::black);
        }
        return;
    }

    deactivate(false);
    slider->setDisabled(false);
    position->setDisabled(false);

    slider->setRange(1,len-1);
    position->setRange(1,len-1);

    setupPreview();
}

void SetsSplit::spinChange() {
    slider->setValue(position->value());
    setupPreview();
}

void SetsSplit::slideChange() {
    position->setValue(slider->value());
    setupPreview();
}

void SetsSplit::setupPreview() {
    int setno = setNumber->currentIndex();
    int len = g[cg].p[setno].len;
    for (int j=0;j<preview->rowCount();j++) {
         for (int i=0;i<4;i++) {
            int d = i - 2 + position->value();
            QTableWidgetItem* t = preview->item(j,i >= 2 ? i+1 : i);
            if (d < 0 || d >= len) {
                t->setText("");
                t->setBackgroundColor(QColor(220,220,220));
            }  else {
                double v = g[cg].p[setno].ex[j][d];
                t->setText(QString::number(v,'g',4));
                t->setBackgroundColor(Qt::white);
            }
        }
        preview->item(j, 2)->setBackgroundColor(Qt::black);
    }
}



void SetsSplit::applyDialog() {
    int setno = setNumber->currentIndex();
    int splitpo = position->value();
    do_breakset(cg, setno, splitpo);
    drawgraph();
    SetsSender::send();
}
