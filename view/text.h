#ifndef TEXT_H
#define TEXT_H

#include "dialog.h"
#include "base/defines.h"

class ViewTextElement;

class ViewText : public Dialog
{
    Q_OBJECT
public:
    explicit ViewText(MainWindow* mainWin);

    void addText(float x, float y);

    void setText(int id, float x, float y);
private:
    QPushButton* placeTextButton;

    ViewTextElement* texts[MAXSTR];

    QVBoxLayout* textsLayout;

public slots:
    void updateDialog();

    void relocateText(int id);

private slots:
    void applyDialog();

    void placeText();
};

class ViewTextElement : public QFrame
{
    Q_OBJECT
public:
    explicit ViewTextElement(ViewText* parent, int id);
    ~ViewTextElement();

    DoubleSpinBox* xCoord;
    DoubleSpinBox* yCoord;

    void applyValues();
    void updateValues();
private:
    QPushButton* relocateButton;
    QPushButton* moreButton;

    QGridLayout* layout;

    LongTextEdit* textArea;

    ViewText* par;
    int num;

    QLabel* xLabel;
    QLabel* yLabel;

private slots:
    void reloc();
};

#endif // TEXT_H
