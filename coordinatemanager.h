#ifndef COORDINATEMANAGER_H
#define COORDINATEMANAGER_H

#include "tetris.h"

 
class CoorMngr
{

public:
    CoorMngr();
    Blocks* pointedblock(int,int)const;
    void occupycoor(Tetris*);//fill the array
    bool checkend()const;//check whether there is block in first and second row
    void checkrow();//check whether there is a full row
    void zero();//set all position to NULL
    int getscore() const;//get score
    int getlevel() ;//get level

private:
    Blocks* myCoor[20][10];//create interger array to store blocks
    void remove(int);//remove a full row
    int score;
    int level;

};
 
#endif//COORDINATEMANAGER_H

