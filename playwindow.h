#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include <QWidget>
#include <QtGui>
#include "tetris.h"
#include "coordinatemanager.h"
 
class Playwindow: public QLabel
{
    Q_OBJECT
public:
    Playwindow(QLabel *parent = 0);//initialize my gameboard
    ~Playwindow();
    Tetris* getTetris() const;//return the tetris active now
    void updatePlaywindow(); 
    void Started(bool);//change game situation
    int isStart() const;//return the game processing situation
    int getscore() const;//return the score of users
    int getlevel();//return the level of users

    
  
private:
    QImage myImage;//store background
    Tetris cacuTetris;//used to predict next move of active tetris
    Tetris *activeTetris;
    Tetris *previousTetris;//a temporary pointer to store my stop tetris
    CoorMngr coormg;//a coordinate manager to store and manage the coordinate data of the tetris blocks
    int gameStart;//0 means game has not started yet. odd means in process even means not in process
    int timecount;//counter plus one evry time when the screen is updated, used to determin when the tetris should move down
    void drawTetris();
    void cleanTetris();//clean memory used to store newed tetris
    void keyPressEvent(QKeyEvent* );
    bool started;//used to store restart data (T:restarted F: have not restarted yet)
    bool isStop(const Tetris* const);// determine if the active tetris needs to stop moving down or not
    bool inrange(const Tetris* const);// determine the tetris is in window or not
    bool isoverlapped(const Tetris* const );// determine whether the tetris is overlapped with existing ones
    Tetris* predictleft(const Tetris* const);
    Tetris* predictright(const Tetris* const);
    Tetris* predictdown(const Tetris* const);
    Tetris* predictanticlockwiserotate(const Tetris* const);
    Tetris* predictclockwiserotate(const Tetris* const);
};
 
#endif//PLAYWINDOW_H
