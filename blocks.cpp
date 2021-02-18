#include"blocks.h"

Blocks::Blocks():x(0),y(0) {}

void Blocks::set_xy(int xcoor, int ycoor){//set position of blocks
  x = xcoor;
  y = ycoor;
}

int Blocks::get_x() const {//get X of blocks
    return x;
}

int Blocks::get_y()const {//get Y of blocks
    return y;
}
void Blocks::setType(int t){// set type
    type = t;
}
int Blocks::getType() const{// get type
    return type;
}
