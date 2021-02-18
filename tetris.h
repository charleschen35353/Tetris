#ifndef TETRIS_H
#define TETRIS_H
#include <time.h>
#include <stdlib.h>
#include "blocks.h"
class Tetris
{
 
public:
    Tetris();
    Tetris(int,Tetris*);//two constructor
    Tetris* getprevious()const;//return previous blocks
    void setprevious(Tetris*);//set previous blocks
    void rotate_anticlockwise(int,int);//rotate
    void move_up();
    void move_down();
    void move_left();
    void move_right();//move in a certain direction
    int getType()const;//get type of active tetris
    int getNexttype()const;//get type of next tetris
    int getRotationflag() const;
    int getBlock_x(int)const;//get x of blocks
    int getBlock_y(int)const;// get y of blocks
    void setRotationflag(int);
    Blocks* getBlockadress(int) ;
private:		

    Tetris *previous;
    Blocks block[4];
    int tetris_type;//type of active tetris
    int next_type;//type of next tetris
    int rotationflag;
    void createPrototype(int);//create center blocks and two other blocks next to it
    void createTetris(int);//create the fourth blocks
}; 
#endif //TETRIS_H

