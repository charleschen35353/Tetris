#include "coordinatemanager.h"

CoorMngr :: CoorMngr(){//set all position NULL
  this->zero();
}
void CoorMngr :: zero(){//set all position NULL
  score = 0;
  for(int i=0;i<20;i++)
    for(int j=0;j<10;j++)
      myCoor[i][j]=NULL;
}

void CoorMngr :: occupycoor(Tetris* mytetris){//fill the array
  for(int i = 0 ; i < 4 ; i++)
    myCoor[mytetris->getBlock_y(i)][mytetris->getBlock_x(i)] = mytetris->getBlockadress(i);
}

void CoorMngr :: remove(int r){//remove a full row
  for(int row=r; row >0 ; row--)
    for(int i=9; i >=0;i--)
      myCoor[row][i] = myCoor[row-1][i];
}

void CoorMngr :: checkrow(){
  int rowtocheck = 0;
  bool isrowfull = true;
  int rowchecked = 0;
  
  for(int row=19; row >=0 ; row--){//check whether there is a full row
    isrowfull = true;
    for(int i=9; i >=0;i--)if(myCoor[row][i]==NULL) isrowfull = false;
      if(isrowfull) {rowtocheck = row; break;}
  }
    int count = 0;
    while(rowchecked <=4 && rowtocheck !=0){//Starting from the full row, check it and 3 more rows above it
      isrowfull = true;
      for(int i=9; i >=0;i--)if(myCoor[rowtocheck][i]==NULL) isrowfull = false;
      if(isrowfull) {remove(rowtocheck); count++;}//remove a full row
      else --rowtocheck;
      rowchecked++;
  }
  score += 10*(count)*(count);//compute score
}
Blocks* CoorMngr :: pointedblock(int y, int x) const{
   return myCoor[y][x];
}

bool CoorMngr::checkend()const{//check whether there is block in first and second row
  bool gameend= false;
  for(int i=0 ; i<2 ; i++)
    for(int j=0; j < 10 ; j++)
      if (myCoor[i][j]!=NULL) gameend = true; 
  return gameend;
}

int CoorMngr::getscore()const{return score;}//get score
int CoorMngr::getlevel(){//compute and get level
  if(score <1000) level = ((score-score%100)/100)+1;
  else level = 10;  
  return level;
  
}