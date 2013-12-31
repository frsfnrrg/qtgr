#include "tools/status.h"
#include "base/globals.h"
#include "prop.h"

ToolsStatus* ToolsStatus::me = NULL;

const char* columns[] = {
    "n",
    "status",
    "type",
    "X/Y",
    "min",
    "at",
    "max",
    "at",
    "mean",
    "stdev",
    "comment"
};
const int numcols = sizeof columns / sizeof (char*);

void disable_item(QTableWidget* o, int row, int col) {
    o->item(row, col)->setFlags(Qt::NoItemFlags);
    o->item(row, col)->setBackgroundColor(QColor(220,220,220));
}

/*
 * This does not really fit in the "dialog" mold: this dialog only displays things
 */
ToolsStatus::ToolsStatus(MainWindow* mainWin) :
    Dialog(mainWin, "Status", true)
{
    output = new QTableWidget();
    output->setRowCount(MAXPLOT * 2);
    output->setColumnCount(numcols);

    QTableWidgetItem* it;

    for (int i=0;i<numcols;i++) {
        output->setHorizontalHeaderItem(i, new QTableWidgetItem(tr(columns[i])));
        for (int j=0;j<MAXPLOT * 2;j++) {
            it = new QTableWidgetItem();
            it->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            output->setItem(j, i, it);
        }
    }
    for (int j=0;j<MAXPLOT;j++) {
        output->setVerticalHeaderItem(j*2, new QTableWidgetItem(QString::number(j)));
        output->setVerticalHeaderItem(j*2+1, new QTableWidgetItem());
        disable_item(output, j*2+1, 0);
        disable_item(output, j*2+1, 1);
        disable_item(output, j*2+1, 2);
    }

    // perhaps, hook up row selection so selecting one row on the lhs selects all the items for that set

    QPushButton* updateButton = makeButton("Update", SLOT(updateDialog()));
    setButtonBold(updateButton);

    QPushButton* copyButton = makeButton("Copy Selected", SLOT(copySelected()));
    setButtonBold(copyButton);
    copyButton->setShortcut(QKeySequence::Copy);

    QHBoxLayout* top = new QHBoxLayout();
    top->addWidget(updateButton, 0);
    top->addStrut(12);
    top->addWidget(copyButton, 0);
    top->addStretch(1);

    QVBoxLayout* s = new QVBoxLayout();
    s->addLayout(top);
    s->addStrut(6);
    s->addWidget(output);

    this->setDialogLayout(s);

    me = this;

    SetsSender::add(this);
}

void set_num(QTableWidget* o, int row, int col, double val) {
    o->item(row, col)->setText(QString::number(val));
}

void set_num(QTableWidget* o, int row, int col, int val) {
    o->item(row, col)->setText(QString::number(val));
}

void set_text(QTableWidget* o, int row, int col, const QString &text) {
    o->item(row, col)->setText(text);
}

void clear_row(QTableWidget* o, int row) {
    for (int i=0;i < o->columnCount();i++) {
        o->item(row, i)->setText(QString());
    }
}

void ToolsStatus::update_set_status(int, int setno) {
    if (!me) return;

    QTableWidget* o = me->output;

    double x1, y1, x2, y2, xbar, ybar, xsd, ysd, dx1, dx2, dy1, dy2, dxbar, dybar, dxsd, dysd;
    int ix1, ix2;
    int iy1, iy2;

    const char* type;

    clear_row(o, 2 * setno);
    clear_row(o, 2 * setno + 1);
    if (isactive(cg, setno)) {

        minmax(getx(cg, setno), getsetlength(cg, setno), &x1, &x2, &ix1, &ix2);
        minmax(gety(cg, setno), getsetlength(cg, setno), &y1, &y2, &iy1, &iy2);

        xbar = 0.0;
        ybar = 0.0;
        xsd = 0.0;
        ysd = 0.0;
        dxbar = 0.0;
        dybar = 0.0;
        dxsd = 0.0;
        dysd = 0.0;

        stasum(getx(cg, setno), getsetlength(cg, setno), &xbar, &xsd, 0);
        stasum(gety(cg, setno), getsetlength(cg, setno), &ybar, &ysd, 0);

        switch (dataset_type(cg, setno)) {
        case XY:
            type = "XY";
            break;
        case XYZ:
            type = "XY Z";
            stasum(getdx(cg, setno), getsetlength(cg, setno), &dxbar, &dxsd, 0);
            break;
        case XYDX:
            type = "XY DX";
            break;
        case XYDY:
            type = "XY DY";
            break;
        case XYDXDX:
            type = "XY DXDX";
            break;
        case XYDYDY:
            type = "XY DYDY";
            break;
        case XYDXDY:
            type = "XY DXDY";
            break;
        case XYZW:
            type = "XY ZW";
            break;
        case XYRT:
            type = "XY R";
            break;
        case XYX2Y2:
            type = "XY X2Y2";
            break;
        case XYSEG:
            type = "XY SEG";
            break;
        case XYBOX:
            type = "XY BOX";
            break;
        case XYARC:
            type = "XY ARC";
            break;
        case XYYY:
            type = "XY Y1 Y2";
            break;
        case XYXX:
            type = "XY X1 X2";
            break;
        case XYHILO:
            type = "XY HILO";
            break;
        case XYUV:
            type = "XY UV";
            break;
        }

        int r = setno*2;

        set_num(o, r, 0, getsetlength(cg, setno));
        set_text(o, r, 1, on_or_off(g[cg].p[setno].active));
        set_text(o, r, 2, type);

        set_text(o, r, 3, "X");
        set_num(o, r, 4, x1);
        set_num(o, r, 5, ix1);
        set_num(o, r, 6, x2);
        set_num(o, r, 7, ix2);
        set_num(o, r, 8, xbar);
        set_num(o, r, 9, xsd);
        set_text(o, r, 10, getcomment(cg, setno));

        r++;

        set_text(o, r, 3, "Y");
        set_num(o, r, 4, y1);
        set_num(o, r, 5, iy1);
        set_num(o, r, 6, y2);
        set_num(o, r, 7, iy2);
        set_num(o, r, 8, ybar);
        set_num(o, r, 9, ysd);


    } else if (g[cg].p[setno].deact) {
        set_text(o, setno*2, 0, tr("De-activated"));
    } else {
        set_text(o, setno*2, 0, tr("Undefined"));
    }

    o->resizeColumnsToContents();
}

void ToolsStatus::updateDialog() {
    for (int i=0;i<MAXPLOT;i++) {
        update_set_status(cg, i);
    }
}

void ToolsStatus::updateSets() {
    updateDialog();
}


void ToolsStatus::applyDialog() {

}

class CellComparator {
public:
    bool operator()(const QTableWidgetItem* left, const QTableWidgetItem* right) const {
        if (left->row() == right->row()) {
            return left->column() < right->column();
        }
        return left->row() < right->row();
    }
} cell_comp;

void ToolsStatus::copySelected() {
    QString text = QString();
    int lastrow = -1;
    QList<QTableWidgetItem*> o = output->selectedItems();
    qSort(o.begin(), o.end(), cell_comp);
    for (int i=0;i<o.count();i++) {
        QTableWidgetItem* g = o.at(i);
        if (g->row() != lastrow) {
            lastrow = g->row();
            if (!text.isEmpty()) text += "\n";
        } else {
            text += " ";
        }

        text += g->text();
    }

    QApplication::clipboard()->setText(text);
}

void qt_update_set_status(int graphno, int setno) {
    ToolsStatus::update_set_status(graphno, setno);
}
