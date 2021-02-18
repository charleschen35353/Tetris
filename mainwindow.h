#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qtimer.h>
#include "playwindow.h"
#include "preview.h"
class Mainwindow : public QWidget
{
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = 0);// to add all widgets into main layout
    ~Mainwindow();
public slots: void updatescreen();//update screen info every 50 msec
    
private:
    Playwindow *playwindow; //create a gameboard
    Previewwindow *previewwindow; //create a window to preview next Tetris
    QLabel *levellabel; // level: 
    QLabel *scorelabel;// score:
    QLabel *messagelabel;//used to print insturctive message
    QLabel *scorenumlabel;//print my score
    QLabel *numlevel;//print store level
    QGridLayout *mainLayout;//Layout to store all widgets 
    QTimer *timer;//timer event
    int level;//store level
    int score;//store score
    void updateScore();
    void updateLevel();
};
 
#endif // PLAYWINDOW_H
