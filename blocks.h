#ifndef BLOCKS_H
#define BLOCKS_H

class Blocks
{
public:
    Blocks();
    void set_xy(int xcoor,int ycoor);//set position of blocks
    int get_x() const;//get X of blocks
    int get_y() const;//get Y of blocks
    int getType() const;//get type
    void setType(int);//set type
private:		
    int x;
    int y;
    int type;
}; 
#endif //BLOCKS_H
