#include "fontcombobox.h"


// These groups are fonts all have the same metrics; this makes
// them interchangable, so scaling issues never occur.
const QString names[4][3] = {
    {"Liberation Serif","Liberation Sans","Liberation Mono"},// Liberation
    {"Times New Roman","Arial","Courier New"},// Monotype
    {"Tinos","Arimo","Cousine"},// Croscore
    {"","",""}// default
};

int FontComboBox::serif = -1;
int FontComboBox::sans = -1;
int FontComboBox::mono = -1;

FontComboBox::FontComboBox() :
    QComboBox()
{    
    this->addItem("Serif");
    this->addItem("Serif Bold");
    this->addItem("Serif Italic");
    this->addItem("Serif Bold/Italic");

    this->addItem("Sans");
    this->addItem("Sans Bold");
    this->addItem("Sans Italic");
    this->addItem("Sans Bold/Italic");

    this->addItem("Mono");
    this->addItem("Mono Bold");
    this->addItem("Mono Italic");
    this->addItem("Mono Bold/Italic");
}

void FontComboBox::initializeFonts() {
    serif = 3;
    sans = 3;
    mono = 3;
    QFontDatabase q;
    QString t;
    QStringList l = q.families();
    for (int i=0;i<l.length();i++) {
        for (int j=0;j<3;j++) {
            t = l.at(i);
            if (t == names[j][0] && j < serif) serif = j;
            if (t == names[j][1] && j < sans) sans = j;
            if (t == names[j][2] && j < mono) mono = j;
        }
    }
}

QFont FontComboBox::getCurrentFont() {
    return getFont(this->currentIndex());
}

QFont FontComboBox::getFont(int index) {
    QFont font;
    int mode = index % 4;
    switch(mode) {
    case 0:
        font.setWeight(QFont::Normal);
        font.setItalic(false);
        break;
    case 1:
        font.setWeight(QFont::Bold);
        font.setItalic(false);
        break;
    case 2:
        font.setWeight(QFont::Normal);
        font.setItalic(true);
        break;
    case 3:
        font.setWeight(QFont::Bold);
        font.setItalic(true);
        break;
    }

    switch ((index - mode) / 4) {
    case 0:
        font.setFamily(names[serif][0]);
        break;
    case 1:
        font.setFamily(names[sans][1]);
        break;
    case 2:
        font.setFamily(names[mono][2]);
        break;
    }

    return font;
}
