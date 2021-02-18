#include <QtGui>
#include <QWidget>
#include"mainwindow.h"
using namespace std;

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  Mainwindow window; // create a new game window
  window.show();
  return app.exec();
}