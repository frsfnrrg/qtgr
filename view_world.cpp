#include <iostream>
#include "view.h"
#include "view_world.h"
#include "globals.h"


ViewWorld::ViewWorld(MainWindow* mainWin) : QDialog(mainWin) {
        this->mainWindow = mainWin;
	this->setWindowTitle("QTGR: Define World");
      
	// make combo box
	QComboBox* fileType = new QComboBox;
	fileType->addItem("X Y");
	fileType->addItem("X Y1 Y2");
	
	// make input fields 
	xMin = new QLineEdit();
	xMax = new QLineEdit();
	yMin = new QLineEdit();
	yMax = new QLineEdit();
	xMajTic = new QLineEdit();
	xMinTic = new QLineEdit();
	yMajTic = new QLineEdit();
	yMinTic = new QLineEdit();
	xMin->setMaximumWidth(100); 
	xMax->setMaximumWidth(100); 
	yMin->setMaximumWidth(100); 
	yMax->setMaximumWidth(100); 
	xMajTic->setMaximumWidth(100); 
	xMinTic->setMaximumWidth(100); 
	yMajTic->setMaximumWidth(100); 
	yMinTic->setMaximumWidth(100); 

	// make buttons
    QPushButton* apply = new QPushButton(tr("Apply"));
 	connect(apply, SIGNAL(clicked()), this, SLOT(applyWorld()));
	
    QPushButton* done  = new QPushButton(tr("Done"));
 	connect(done, SIGNAL(clicked()), this, SLOT(doneWorld()));

	QGridLayout* layout = new QGridLayout();
	    
	layout->addWidget(new QLabel("World coordinates"),0,0,1,2);
	layout->addWidget(new QLabel("Xmin"),1,0);
	layout->addWidget(new QLabel("Xmax"),2,0);
	layout->addWidget(new QLabel("Ymin"),3,0);
	layout->addWidget(new QLabel("Ymax"),4,0);
	
	layout->addWidget(xMin,1,1);
	layout->addWidget(xMax,2,1);
	layout->addWidget(yMin,3,1);
	layout->addWidget(yMax,4,1);
	
	layout->addWidget(new QLabel(" "),1,2);
	layout->addWidget(new QLabel(" "),2,2);
	layout->addWidget(new QLabel(" "),3,2);
	layout->addWidget(new QLabel(" "),4,2);
	
	layout->addWidget(new QLabel("Tickmarks"),0,3,1,2);
	layout->addWidget(new QLabel("X-major"),1,3);
	layout->addWidget(new QLabel("X-minor"),2,3);
	layout->addWidget(new QLabel("Y-major"),3,3);
	layout->addWidget(new QLabel("Y-minor"),4,3);
	
	layout->addWidget(xMajTic,1,4);
	layout->addWidget(xMinTic,2,4);
	layout->addWidget(yMajTic,3,4);
	layout->addWidget(yMinTic,4,4);
	
	layout->addWidget(new QLabel(""),5,0);
	
	layout->addWidget(new QLabel("Apply to"),6,0);
	

	layout->addWidget(fileType,6,1,1,1);
	
	layout->addWidget(new QLabel(""),7,0);

	layout->addWidget(apply,8,1);
	layout->addWidget(done,8,4);

	this->setLayout(layout);
  }
  
  
void ViewWorld::updateWorld()
{
    int gno; 
    
    printf("updateWorld \n");
    gno = cg; // current graph only 

    xMin->setText(QString::number(g[gno].w.xg1,'g',9));
    xMax->setText(QString::number(g[gno].w.xg2,'g',9));
    yMin->setText(QString::number(g[gno].w.yg1,'g',9));
    yMax->setText(QString::number(g[gno].w.yg2,'g',9));
    xMajTic->setText(QString::number(g[gno].t[0].tmajor,'g',9));
    xMinTic->setText(QString::number(g[gno].t[0].tminor,'g',9));
    yMajTic->setText(QString::number(g[gno].t[1].tmajor,'g',9));
    yMinTic->setText(QString::number(g[gno].t[1].tminor,'g',9));
    
    update();

}
  
void ViewWorld::applyWorld()
{
    int i, which, ming, maxg;

    which = 0; //current graph only at this time
    
    ming = cg;
    maxg = cg;

    if (ming == cg && maxg == cg) {
	if (!isactive_graph(cg)) {
	    errwin("Current graph is not active!");
	    return;
	}
    }
    for (i = ming; i <= maxg; i++) {
	if (isactive_graph(i)) {
	    if (which <= 1 || which == 2) {
		g[i].w.xg1 = xMin->text().toDouble();
		g[i].w.xg2 = xMax->text().toDouble();
		g[i].t[0].tmajor = xMajTic->text().toDouble();
		g[i].t[0].tminor = xMinTic->text().toDouble();
	    }
	    if (which <= 1 || which == 3) {
		g[i].w.yg1 = yMin->text().toDouble();
		g[i].w.yg2 = yMax->text().toDouble();
		g[i].t[1].tmajor = yMajTic->text().toDouble();
		g[i].t[1].tminor = yMinTic->text().toDouble();
	    }
	}
    }
    drawgraph();  
    
    ViewMenu* viewMenu = (ViewMenu*) mainWindow->viewMenu;  // FIXME hack  
    viewMenu->updateTicks();
}

void ViewWorld::doneWorld()
{
  printf("done\n");
  this->applyWorld();
  this->setVisible(false);
}
