//#include <iostream>
#include "view.h"
#include "view/ticks.h"
#include "core/globals.h"


ViewTicks::ViewTicks(MainWindow* mainWin) : Dialog(mainWin, tr("Ticks/Tick Labels"))
{  
    // make input fields
    editAxis = new QComboBox(this);
    editAxis->addItem("X axis");
    editAxis->addItem("Y axis");
    editAxis->addItem("Zero X axis");
    editAxis->addItem("Zero Y axis");
    editAxis->addItem("Alternate X axis");
    editAxis->addItem("Alternate Y axis");
    connect(editAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialog()));	
    
    // make line edits
    axisLabel = new QLineEdit();
    axisLabel->setMinimumWidth(300); 
    
    majTic = new QLineEdit();
    minTic = new QLineEdit();
    

    // make radio buttons
    QCheckBox* tickLabels = new QCheckBox("Tick labels");
    QCheckBox* tickMarks  = new QCheckBox("Tick marks");
    QCheckBox* axisBar    = new QCheckBox("Axis bar");
    tickLabels->setChecked(true);
    tickMarks->setChecked(true);
    
    QPushButton* axisProps = new QPushButton("Axis props...");	
    //connect(apply, SIGNAL(clicked()), this, SLOT(applyTicks()));
    
    labelPropsDialog = NULL;
    QPushButton* labelPropsButton = new QPushButton("Label props...");
    connect(labelPropsButton, SIGNAL(clicked()), this, SLOT(labelProps()));	
    
    QPushButton* markProps  = new QPushButton("Mark props...");
// 	connect(done, SIGNAL(clicked()), this, SLOT(doneTicks()));
    
    QPushButton* barProps = new QPushButton("Bar props");
// 	connect(apply, SIGNAL(clicked()), this, SLOT(applyTicks()));


    QGridLayout* layout = new QGridLayout();
	
    layout->addWidget(new QLabel("Edit:"),0,0);
    layout->addWidget(editAxis,0,1,1,2);
    layout->addWidget(axisProps,0,4,1,1);
    
    layout->addWidget(new QLabel(""),1,0);
    
    layout->addWidget(new QLabel("Axis label"),2,0);
    layout->addWidget(axisLabel,2,1,1,3);
    
    layout->addWidget(new QLabel(""),3,0);
    
    layout->addWidget(new QLabel("Major tics"),4,0);
    layout->addWidget(new QLabel("Minor tics"),5,0);
    layout->addWidget(majTic,4,1);
    layout->addWidget(minTic,5,1);
    
    layout->addWidget(new QLabel(""),6,0);
    
    layout->addWidget(tickLabels,7,0);
    layout->addWidget(tickMarks,8,0);
    layout->addWidget(axisBar,9,0);
    layout->addWidget(labelPropsButton,7,1);
    layout->addWidget(markProps,8,1);
    layout->addWidget(barProps,9,1);
    
    layout->setColumnMinimumWidth(0,80);
    layout->setColumnMinimumWidth(1,80);
    layout->setColumnMinimumWidth(2,80);
    layout->setColumnMinimumWidth(3,80);
    layout->setColumnMinimumWidth(4,80);

    this->setDialogLayout(layout);
  }
  
  
void ViewTicks::updateDialog()
{
    int gno,axis; 
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();
   
    majTic->setText(QString::number(g[gno].t[axis].tmajor,'g',9));
    minTic->setText(QString::number(g[gno].t[axis].tminor,'g',9));
    axisLabel->setText(QString::fromLocal8Bit(g[gno].t[axis].label.s));
    
    this->update();

}
  
void ViewTicks::applyDialog()
{
  
    int gno,axis; 
    char * label;
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();

    label = axisLabel->text().toAscii().data();

    strcpy(g[cg].t[axis].label.s, label);
    g[cg].t[axis].tmajor = majTic->text().toDouble();
    g[cg].t[axis].tminor = minTic->text().toDouble();
    
    drawgraph();  
    
    ViewMenu* viewMenu = (ViewMenu*) mainWindow->viewMenu;  // FIXME hack  
    viewMenu->updateWorld();
}

void ViewTicks::labelProps()
{
    if (labelPropsDialog) {
        printf("test\n");
        labelPropsDialog->setVisible(true);
    } else {
        printf("test1\n");
        labelPropsDialog = new QDialog(this);
        labelPropsDialog->setWindowTitle("QTGR: Edit tick labels");
        labelPropsDialog->setMaximumHeight(300);
        labelPropsDialog->setMinimumWidth(400);

        axisName = new QLabel(editAxis->currentText());

        // make input fields
        labelFormat = new QComboBox();
        labelFormat->addItem("Decimal");
        labelFormat->addItem("Exponential");
        labelFormat->addItem("Power");

        labelPrecision = new QComboBox;
        for (int i=0; i<10; i++) {
            labelPrecision->addItem(QString::number(i));
        }
        labelPrecision->setCurrentIndex(1);

        // buttons
        QPushButton* apply = new QPushButton("Apply");
        connect(apply, SIGNAL(clicked()), this, SLOT(applyLabelProps()));

        QPushButton* done  = new QPushButton("Done");
        connect(done, SIGNAL(clicked()), this, SLOT(doneLabelProps()));

        QGridLayout* layout = new QGridLayout();

        layout->addWidget(new QLabel("Axis: "),0,0);
        layout->addWidget(axisName,0,1);

        layout->addWidget(new QLabel(""),1,0);

        layout->addWidget(new QLabel("Font: "),2,0);

        layout->addWidget(new QLabel("Color"),3,0);
 	
        layout->addWidget(new QLabel("Width:"),4,0);
	
        layout->addWidget(new QLabel("Char size:"),5,0);
	
        layout->addWidget(new QLabel(""),6,0);
	
        layout->addWidget(new QLabel("Format:"),7,0);
        layout->addWidget(labelFormat,7,1);
	
        layout->addWidget(new QLabel("Stagger:"),8,0);
    //  layout->addWidget(legendX,7,1);
	
        layout->addWidget(new QLabel("Precision:"),9,0);
        layout->addWidget(labelPrecision,9,1);

        layout->addWidget(new QLabel("Skip every:"),10,0);
//      layout->addWidget(precision,9,1);

        layout->addWidget(new QLabel("Start labels at:"),11,0);
    // 	layout->addWidget(precision,9,1);
        layout->addWidget(new QLabel("         "),11,3);
	
        layout->addWidget(new QLabel("Stop labels at:"),12,0);
    // 	layout->addWidget(precision,9,1);
        layout->addWidget(new QLabel("         "),12,3);

        layout->addWidget(new QLabel(""),14,0);

        layout->addWidget(apply,15,1,Qt::AlignLeft);
        layout->addWidget(done,15,3,Qt::AlignLeft);

	
        labelPropsDialog->setLayout(layout);

        labelPropsDialog->show();

    } //labelPropsDialog != NULL
    updateLabelProps();

}

void ViewTicks::updateLabelProps()
{
    int axis,gno;
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();
  
    axisName->setText(editAxis->currentText());
    labelFormat->setCurrentIndex(get_format_index(g[gno].t[axis].tl_format));
    labelPrecision->setCurrentIndex(g[gno].t[axis].tl_prec);  
}

void ViewTicks::applyLabelProps()
{
    int gno,axis; 
    
    gno = cg; // current graph only 
    axis = editAxis->currentIndex();

    g[cg].t[axis].tl_format = format_types[labelFormat->currentIndex()];
    g[cg].t[axis].tl_prec   = labelPrecision->currentIndex();
    
    drawgraph();  
}

void ViewTicks::doneLabelProps()
{
  this->applyLabelProps();
  this->labelPropsDialog->setVisible(false);
}

