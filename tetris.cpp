#include"tetris.h"

void Tetris :: createPrototype(int type){//create center blocks and two other blocks next to it
  if (type == 1 || type == 5 || type == 6 || type == 7){
      block[0].set_xy(5,2);
      block[1].set_xy(block[0].get_x(),block[0].get_y()+1);
      block[2].set_xy(block[0].get_x(),block[0].get_y()-1);
  }
  else{
      block[0].set_xy(5,2);
      block[1].set_xy(block[0].get_x(),block[0].get_y()-1);
      block[2].set_xy(block[0].get_x()+1,block[0].get_y());   
  }
}

void Tetris :: createTetris(int type){//create the fourth block
  switch(type){
    case 1:
      createPrototype(type);  
      block[3].set_xy(block[0].get_x(),block[0].get_y()-2);
      for (int i=0 ; i<4; i++) block[i].setType(type);  
      break;
    case 2:
      createPrototype(type); 
      block[3].set_xy(block[0].get_x()+1,block[0].get_y()-1); 
      for (int i=0 ; i<4; i++) block[i].setType(type); 
      for(int i= 0 ;i < 2; i++){rotate_anticlockwise(2,rotationflag); rotationflag ++;}
      break;
    case 3:
      createPrototype(type); 
      block[3].set_xy(block[0].get_x()+1,block[0].get_y()+1);
      for (int i=0 ; i<4; i++) block[i].setType(type); 
      break;
    case 4:
      createPrototype(type);  
      block[3].set_xy(block[0].get_x()-1,block[0].get_y()-1);
      for (int i=0 ; i<4; i++) block[i].setType(type); 
      for(int i= 0 ;i < 3 ; i++){rotate_anticlockwise(4,rotationflag); rotationflag ++;}
      break;
    case 5:
      createPrototype(type);   
      block[3].set_xy(block[0].get_x()+1,block[0].get_y()+1); 
      for (int i=0 ; i<4; i++) block[i].setType(type); ;
      break;
    case 6:
      createPrototype(type); 
      block[3].set_xy(block[0].get_x()-1,block[0].get_y()+1);
      for (int i=0 ; i<4; i++) block[i].setType(type); 
      break;
    case 7:
      createPrototype(type); 
      block[3].set_xy(block[0].get_x()-1,block[0].get_y());
      for (int i=0 ; i<4; i++) block[i].setType(type); 
      for(int i= 0 ;i < 3 ; i++){rotate_anticlockwise(7,rotationflag); rotationflag ++;}
      break;
  }
}
Tetris::Tetris() : rotationflag(0){
  previous = NULL;
  srand (time(NULL));
  tetris_type = rand()%7+1;// assign random type to tetris 
  next_type = rand()%7+1;//assign random type to next tetris
  createTetris(tetris_type);
}

Tetris::Tetris(int type ,Tetris* pre) :rotationflag(0) {
  previous = pre;
  tetris_type = type;
  srand (time(NULL));
  next_type = rand()%7+1;//assign random type to next tetris
  createTetris(tetris_type);//create active tetris
}
int Tetris::getNexttype()const{//get next type
  return next_type;
}

Blocks *Tetris :: getBlockadress(int i){//get block address
  return &block[i];
}

void Tetris :: rotate_anticlockwise(int type, int rotationflag){//rotate tetris in anticlockwise according to type
    //change the position of all 4 block in a single tetris
    if (type == 1 || type == 5 || type == 6 || type == 7){
      if ((rotationflag%4+4) % 4 ==  0){
	block[1].set_xy(block[1].get_x()+1, block[1].get_y()-1); 
	block[2].set_xy(block[2].get_x()-1, block[2].get_y()+1);
	
	if (type ==1) block[3].set_xy(block[3].get_x()-2, block[3].get_y()+2);
	else if(type == 5) block[3].set_xy(block[3].get_x(), block[3].get_y()-2);
	else if(type == 6) block[3].set_xy(block[3].get_x()+2, block[3].get_y());
	else if(type == 7)block[3].set_xy(block[3].get_x()+1, block[3].get_y()+1);
      }
      else if ((rotationflag%4+4) % 4 == 1){
	block[1].set_xy(block[1].get_x()-1, block[1].get_y()-1); 
	block[2].set_xy(block[2].get_x()+1, block[2].get_y()+1);
	
	if (type ==1) block[3].set_xy(block[3].get_x()+2, block[3].get_y()+2);
	else if(type == 5) block[3].set_xy(block[3].get_x()-2, block[3].get_y());
	else if(type == 6) block[3].set_xy(block[3].get_x(), block[3].get_y()-2);
	else if(type == 7)block[3].set_xy(block[3].get_x()+1, block[3].get_y()-1);
      }
      else if ((rotationflag%4+4) % 4 == 2){
	block[1].set_xy(block[1].get_x()-1, block[1].get_y()+1); 
	block[2].set_xy(block[2].get_x()+1, block[2].get_y()-1);
	
	if (type ==1) block[3].set_xy(block[3].get_x()+2, block[3].get_y()-2);
	else if(type == 5) block[3].set_xy(block[3].get_x(), block[3].get_y()+2);
	else if(type == 6) block[3].set_xy(block[3].get_x()-2, block[3].get_y());
	else if(type == 7)block[3].set_xy(block[3].get_x()-1, block[3].get_y()-1);
      }
      else if ((rotationflag%4+4) % 4 == 3){
	block[1].set_xy(block[1].get_x()+1, block[1].get_y()+1); 
	block[2].set_xy(block[2].get_x()-1, block[2].get_y()-1);
	
	if (type ==1) block[3].set_xy(block[3].get_x()-2, block[3].get_y()-2);
	else if(type == 5) block[3].set_xy(block[3].get_x()+2, block[3].get_y());
	else if(type == 6) block[3].set_xy(block[3].get_x(), block[3].get_y()+2);
	else if(type == 7)block[3].set_xy(block[3].get_x()-1, block[3].get_y()+1);
      }
    }
   
   else if (type == 2 || type == 3 || type == 4 ){
      if ((rotationflag%4+4) % 4 == 0){
	block[1].set_xy(block[1].get_x()-1, block[1].get_y()+1); 
	block[2].set_xy(block[2].get_x()-1, block[2].get_y()-1);
	
	
	if (type == 2) block[3].set_xy(block[3].get_x()-2, block[3].get_y());
	else if(type == 3) block[3].set_xy(block[3].get_x(), block[3].get_y()-2);
	else if(type == 4)block[3].set_xy(block[3].get_x(), block[3].get_y()+2);
	
      }
      else if ((rotationflag%4+4) % 4 == 1){
	block[1].set_xy(block[1].get_x()+1, block[1].get_y()+1); 
	block[2].set_xy(block[2].get_x()-1, block[2].get_y()+1);
    
	if (type == 2) block[3].set_xy(block[3].get_x(), block[3].get_y()+2); 
	else if(type == 3) block[3].set_xy(block[3].get_x()-2, block[3].get_y());
	else if(type == 4)block[3].set_xy(block[3].get_x()+2, block[3].get_y());
	
      }
      else if ((rotationflag%4+4) % 4 == 2){
	block[1].set_xy(block[1].get_x()+1, block[1].get_y()-1); 
	block[2].set_xy(block[2].get_x()+1, block[2].get_y()+1);
	
	if (type == 2) block[3].set_xy(block[3].get_x()+2, block[3].get_y());
	else if(type == 3) block[3].set_xy(block[3].get_x(), block[3].get_y()+2);
	else if(type == 4)block[3].set_xy(block[3].get_x(), block[3].get_y()-2);
	
      }
      else if ((rotationflag%4+4) % 4 == 3){
	block[1].set_xy(block[1].get_x()-1, block[1].get_y()-1); 
	block[2].set_xy(block[2].get_x()+1, block[2].get_y()-1);
	
	if (type == 2) block[3].set_xy(block[3].get_x(), block[3].get_y()-2);
	else if(type == 3) block[3].set_xy(block[3].get_x()+2, block[3].get_y());
	else if(type == 4)block[3].set_xy(block[3].get_x()-2, block[3].get_y());
      }
   }
}
void Tetris :: move_up(){//let blocks move up
  for (int i=0 ; i<4; i++)
    block[i].set_xy(block[i].get_x(), block[i].get_y()-1);
}

void Tetris :: move_down(){//let blocks move down
  for (int i=0 ; i<4; i++)
    block[i].set_xy(block[i].get_x(), block[i].get_y()+1);
}

void Tetris :: move_left(){//let blocks move left
  for (int i=0 ; i<4; i++)
    block[i].set_xy(block[i].get_x()-1, block[i].get_y());
}

void Tetris :: move_right(){//let blocks move right
  for (int i=0 ; i<4; i++)
    block[i].set_xy(block[i].get_x()+1, block[i].get_y());
}

int Tetris::getType()const{//get type
  return tetris_type;
}

int Tetris::getRotationflag()const{
  return rotationflag;
}

int Tetris::getBlock_x (int i)const{if (i>=0 && i <4)return block[i].get_x(); else return -1;}//get X of block

int Tetris::getBlock_y (int i)const{if (i>=0 && i <4)return block[i].get_y(); else return -1;}//get Y of block

void Tetris::setRotationflag(int num){
  rotationflag = num;
}
void Tetris :: setprevious(Tetris* pre){previous = pre;}//set previous blocks

Tetris* Tetris::getprevious() const{return previous;}//get previous blocks



