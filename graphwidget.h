/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

# ifdef __cplusplus 

#include <QtGui>
#include "mousecall.h"
#include "overlay.h"


//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
    //static const int maxcolors = 256;
    static GraphWidget *myGraphWidget;

public:
    GraphWidget(QGraphicsScene *, QWidget *parent = 0);
    static void paint(int x1, int y1, int x2, int y2); 
    static void linew(int w);
    static void lines(int s);
    static void linec(int s);
    static void text(int x, int y, int rot, char* c, int just);
    static void arc(int x, int y, int r, int fill);
    static void fillcolor (int n, int px[], int py[]);
    static void clear();
    static void update();
    static void getcanvas(int* win_w, int* win_h);
    QColor cmscolors[16];
    MouseCallBack *mouseClickCall;
    MouseCallBack *mouseDoubleCall;

    static void startRect(RectReceiver* r);

public slots:

protected:
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void resizeEvent(QResizeEvent* r);

private:
   Overlay* overlay;
   QPen *pen;
   void initialize_cms_data();  
   
};

#endif // __cplusplus

# ifdef __cplusplus 
extern "C"
{
#endif // __cplusplus
  void qtview_paint(int x1, int y1, int x2, int y2);
  void qtview_linew(int w);
  void qtview_lines(int s);
  void qtview_linec(int c);
  void qtview_text (int x, int y, int rot, char* c, int just);
  void qtview_arc (int x, int y, int r, int fill);
  void qtview_fillcolor (int n, int px[], int py[]);
  void qtview_clear();
  void qtview_update();
  void qtview_getcanvas(int* win_w, int* win_h);
  

# ifdef __cplusplus 
}
#endif // __cplusplus


#endif
