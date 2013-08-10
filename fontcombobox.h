#ifndef FONTCOMBOBOX_H
#define FONTCOMBOBOX_H

#include <QtGui>

class FontComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit FontComboBox();
    
    QFont getCurrentFont();

    static QFont getFont(int index);

    static void initializeFonts();
private:
    static int serif;
    static int sans;
    static int mono;
signals:
    
public slots:
    
};

#endif // FONTCOMBOBOX_H
