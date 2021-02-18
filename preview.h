#ifndef PREVIEW_H
#define PREVIEW_H
#include <QWidget>
#include <QtGui>
#include <QApplication>
#include "tetris.h"
class Previewwindow : public QLabel
{
Q_OBJECT
 public:
  Previewwindow(QLabel *parent = 0);
  void loadnext(int);
  
private:
  QImage myImage;
} ;
#endif // PREVIEW_H
