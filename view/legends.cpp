#include "view/legends.h"
#include "core/globals.h"

ViewLegends::ViewLegends(MainWindow* mainWin) :
    Dialog(mainWin, tr("Legends"))
{
    //this->setWindowTitle(tr("QTGR: Legends"));
    legendsEditDialog = NULL;


    // make input fields
    locType = new QComboBox;
    locType->addItem(tr("Viewport coordinates"));
    locType->addItem(tr("World coordinates"));
//	connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTicks()));

// 	// make line edits
    legendX = new QLineEdit();
    legendY = new QLineEdit();
    legendX->setMaximumWidth(100);
    legendY->setMaximumWidth(100);

    showLegend = new QCheckBox("Show Legend");
    //connect(apply, SIGNAL(clicked()), this, SLOT(applyTicks()));

    QPushButton* editLegend = new QPushButton("Edit...");
    connect(editLegend, SIGNAL(clicked()), this, SLOT(legendsEdit()));

    QPushButton* place  = new QPushButton("Place");
    connect(place, SIGNAL(clicked()), this, SLOT(placeLegends()));

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(showLegend,0,0,1,2,Qt::AlignLeft);
    layout->addWidget(editLegend,0,4,1,1);

    layout->addWidget(new QLabel(""),1,0);

    layout->addWidget(new QLabel("Legend location: "),2,0);
    layout->addWidget(locType,2,1,1,3);

    layout->addWidget(new QLabel(""),3,0);

    layout->addWidget(new QLabel("Color:"),4,0);
    layout->addWidget(new QLabel("Char size:"),5,0);
// 	layout->addWidget(majTic,4,1);
// 	layout->addWidget(minTic,5,1);

    layout->addWidget(new QLabel(""),6,0);

    layout->addWidget(new QLabel("Legend x:"),7,0);
    layout->addWidget(new QLabel("Legend y:"),8,0);
    layout->addWidget(legendX,7,1);
    layout->addWidget(legendY,8,1);

    layout->addWidget(place,7,3,Qt::AlignHCenter);


    layout->addWidget(new QLabel(""),10,0);

    layout->setColumnMinimumWidth(0,80);
    layout->setColumnMinimumWidth(1,80);
    layout->setColumnMinimumWidth(2,80);
    layout->setColumnMinimumWidth(3,80);
    layout->setColumnMinimumWidth(4,80);

    this->setDialogLayout(layout);
}

void ViewLegends::updateDialog() {
    int gno;
     legend leg;

    gno = cg; // current graph only

    get_graph_legend(gno,&leg);

//     printf("UpdateLegends %i %f %f %i\n",leg.active == ON, leg.legx, leg.legy, leg.loctype);

    showLegend->setChecked(g[gno].l.active == ON);
    if (g[gno].l.loctype == VIEW) {
        locType->setCurrentIndex(0);
    } else {
        locType->setCurrentIndex(1);
    }
    legendX->setText(QString::number(g[gno].l.legx,'g',9));
    legendY->setText(QString::number(g[gno].l.legy,'g',9));

    update();
}

void ViewLegends::applyDialog() {
    int gno,axis;
    legend leg;

      gno = cg; // current graph only

      get_graph_legend(gno,&leg);

  //     printf("ApplyLegends %i %f %f\n",leg.active == ON, leg.legx, leg.legy);

      if (showLegend->isChecked()) {
      g[gno].l.active = ON;
      } else {
      g[gno].l.active = OFF;
      }

      if (locType->currentIndex() == 0) {
      g[gno].l.loctype = VIEW;
      } else {
      g[gno].l.loctype = WORLD;
      }

      g[gno].l.legx = legendX->text().toDouble();
      g[gno].l.legy = legendY->text().toDouble();

      drawgraph();
}


class MouseClickCall : public MouseCallBack
{
public:
    ViewLegends* view;

    void mouse( int x, int y, int w, int h )
    {
    printf("mouse_callback %f %f \n" ,double(x)/w,1.0-double(y)/h);
    view->mainWindow->gwidget->mouseClickCall = NULL;
    view->mainWindow->gwidget->unsetCursor();
    view->mainWindow->statusBar()->clearMessage();

    view->legendX->setText(QString::number(double(x)/w,'g',3));
    view->legendY->setText(QString::number(1.0-double(y)/h,'g',3));
    view->applyDialog();

    }
} mouseClick;

void ViewLegends::placeLegends()
{
    mouseClick.view = this;
    mainWindow->gwidget->mouseClickCall =  &mouseClick;
    mainWindow->gwidget->setCursor(Qt::CrossCursor);
    mainWindow->statusBar()->showMessage(tr("Click to place legend"));
}

void ViewLegends::legendsEdit()
{
    if (legendsEditDialog) {
        legendsEditDialog->setVisible(true);
    } else {
        // TODO: eventually, abstract this out..
        legendsEditDialog = new QDialog(this->mainWindow);
        legendsEditDialog->setWindowTitle("QTGR: Edit legend labels");
        legendsEditDialog->setMaximumHeight(300);
        legendsEditDialog->setMinimumWidth(400);

        // buttons
        QPushButton* apply = new QPushButton("Apply");
        connect(apply, SIGNAL(clicked()), this, SLOT(applyLegendsEdit()));

        QPushButton* done  = new QPushButton("Done");
        connect(done, SIGNAL(clicked()), this, SLOT(doneLegendsEdit()));

        // central widget for legend labels
        QScrollArea* scrollArea = new QScrollArea;
        QWidget* widget = new QWidget();
        QGridLayout* layout = new QGridLayout();

        for (int i=0; i<MAXPLOT; i++) {
            setLabels[i] = new QLineEdit();
            setLabels[i]->setMinimumWidth(240);
            layout->addWidget(new QLabel(QString("Set ")+QString::number(i)),i,0);
            layout->addWidget(setLabels[i],i,1);
        }

        widget->setLayout(layout);
        scrollArea->setWidget(widget);

        // put everything together
        QGridLayout* lay = new QGridLayout();
        lay->addWidget(scrollArea,0,0,1,5);

        layout->addWidget(new QLabel(""),1,0);

        lay->addWidget(apply,2,1);
        lay->addWidget(done,2,3);

        layout->setColumnMinimumWidth(0,80);
        layout->setColumnMinimumWidth(1,80);
        layout->setColumnMinimumWidth(2,80);
        layout->setColumnMinimumWidth(3,80);
        layout->setColumnMinimumWidth(4,80);

        legendsEditDialog->setLayout(lay);

        legendsEditDialog->show();
    }

    updateLegendsEdit();
}

void ViewLegends::updateLegendsEdit()
{
    int gno;

    gno = cg; // current graph only

//     printf("updateLegendEdit  max %i s %s\n",g[gno].maxplot,g[gno].l.str[0].s);

    for (int i=0; i<MAXPLOT; i++) {
//        printf("updateLegendEdit   %i s %s\n",i,g[gno].l.str[i].s);
       setLabels[i]->setText(QString::fromLocal8Bit(g[gno].l.str[i].s));
    }
    legendsEditDialog->update();
}

void ViewLegends::applyLegendsEdit()
{
    int gno;

    gno = cg; // current graph only

    for (int i=0; i<MAXPLOT; i++) {
    strcpy((char*)g[gno].l.str[i].s,setLabels[i]->text().toAscii().data());
    }
}

void ViewLegends::doneLegendsEdit()
{
  this->applyLegendsEdit();
  this->legendsEditDialog->setVisible(false);
}


