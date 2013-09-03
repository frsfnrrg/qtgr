#include "choosers.h"
#include "base/globals.h"
#include "prop.h"
#include "base/patterns.h"

DoubleSpinBox::DoubleSpinBox() : QDoubleSpinBox() {}
IntegerSpinBox::IntegerSpinBox() : QSpinBox() {}

void DoubleSpinBox::setValue(double value, bool loud) {
    if (loud) {
        QDoubleSpinBox::setValue(value);
    } else {
        this->blockSignals(true);
        QDoubleSpinBox::setValue(value);
        this->blockSignals(false);
    }
}

void IntegerSpinBox::setValue(int value, bool loud) {
    if (loud) {
        QSpinBox::setValue(value);
    } else {
        this->blockSignals(true);
        QSpinBox::setValue(value);
        this->blockSignals(false);
    }
}

// SETS

/*
 Note: another level is to explicitly
 show _dead_, not _disabled_, sets as disabled
 on the combobox. This may lead to creating a model
 for the combobox, but that is fine...
 */
SetComboBox::SetComboBox(bool a) :
    QComboBox()
{
    add = a;
    if (add) {
        this->addItem("-- All live sets --");
    }
    for (int i=0;i<MAXPLOT;i++) {
        this->addItem("");
    }
    updateSets();

    SetsSender::add(this);
    this->setMinimumWidth(100);
}

void SetComboBox::updateSets() {
    for (int i=0;i<MAXPLOT;i++) {
        if (g[cg].p[i].active == OFF && g[cg].p[i].deact == 0) {
            this->setItemText(i+add, QString("~: ") + g[cg].l.str[i].s);
        } else {
            this->setItemText(i+add, QString::number(i) + ": " + g[cg].l.str[i].s);
        }
    }
}

// FONTS

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

// PATTERNS

typedef struct {
    int width;
    int height;
    unsigned char* bits;
} pattern;

const int MAX_PATTERN = 16;

const pattern patterns[MAX_PATTERN] = {
    {pat0_width, pat0_height, pat0_bits},
    {pat1_width, pat0_height, pat1_bits},
    {pat2_width, pat0_height, pat2_bits},
    {pat3_width, pat0_height, pat3_bits},
    {pat4_width, pat0_height, pat4_bits},
    {pat5_width, pat0_height, pat5_bits},
    {pat6_width, pat0_height, pat6_bits},
    {pat7_width, pat0_height, pat7_bits},
    {pat8_width, pat0_height, pat8_bits},
    {pat9_width, pat0_height, pat9_bits},
    {pat10_width, pat0_height, pat10_bits},
    {pat11_width, pat0_height, pat11_bits},
    {pat12_width, pat0_height, pat12_bits},
    {pat13_width, pat0_height, pat13_bits},
    {pat14_width, pat0_height, pat14_bits},
    {pat15_width, pat0_height, pat15_bits}
};

QPixmap* PatternComboBox::pxs[MAX_PATTERN] = {NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL, NULL};

PatternComboBox::PatternComboBox() :
    QComboBox()
{
    for (int i=0;i<MAX_PATTERN;i++) {
        addItem(QIcon(*pxs[i]),QString::number(i));
    }
}

QPixmap PatternComboBox::getPattern(int index) {
    return *pxs[index];
}

void PatternComboBox::initializePatterns() {
    for (int i=0;i<MAX_PATTERN;i++) {
        pattern pat = patterns[i];
        QPixmap* x = new QPixmap(pat.width, pat.height);
        pxs[i] = x;
    }
}

// COLORS

typedef struct {
    QColor color;
    const char* name;
} named_color;

named_color colors[MAXCOLORS] =
{{QColor(255,255,255), "White"},
 {QColor(0,5,0), "Black"},
 {QColor(255,0,0), "Red"},
 {QColor(0,255,0), "Green"},

 {QColor(0,0,255), "Blue"},
 {QColor(255,255,0), "Yellow"},
 {QColor(188,143,143), "Brown"},
 {QColor(220,220,220), "Gray"},

 {QColor(148,0,211), "Violet"},
 {QColor(0,255,255), "Cyan"},
 {QColor(255,0,211), "Magenta"},
 {QColor(255,138,0), "Orange"},

 {QColor(114,33,188), "Blue Violet"},
 {QColor(103,7,72), "Maroon"},
 {QColor(72,209,204), "Turquoise"},
 {QColor(85,192,52), "Mid Green"}};

ColorComboBox::ColorComboBox() {
    QIcon colorIcon;
    QPixmap colorPix(20, 20);
    for (int i=0;i<MAXCOLORS;i++) {
        named_color n = colors[i];
        colorPix.fill(n.color);
        colorIcon.addPixmap(colorPix);
        this->addItem(colorIcon, tr(n.name));
    }
}

QColor ColorComboBox::getColor(int index) {
    return colors[index].color;
}

// MISC

DoubleSpinBox* makeTextSizer() {
    DoubleSpinBox* f = new DoubleSpinBox();
    f->setMinimum(0.0);
    f->setDecimals(2);
    f->setSingleStep(0.1);
    return f;
}

QComboBox* makeWidthSelector() {
    QComboBox* f = new QComboBox();
    for (int i=0;i<MAX_LINEWIDTH;i++) {
        f->addItem(QString::number(i+1));
    }
    return f;
}

QComboBox* makeLineStyler() {
    QComboBox* f = new QComboBox();
    f->addItem("None");
    f->addItem("Solid");
    f->addItem("Dashed");
    f->addItem("Dotted");
    f->addItem("Dash-Dot");
    f->addItem("Dash-DotDot");
    return f;
}
