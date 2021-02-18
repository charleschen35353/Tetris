#include "preview.h"

Previewwindow :: Previewwindow(QLabel *parent) : QLabel(parent){
  this->setFixedSize(100,160);
  this->setStyleSheet("background-color:white;");
}

void Previewwindow :: loadnext(int type){//load next type in previewwindow
  switch(type){
    case 1:
      myImage.load("Tetris1.png");
      break;
    case 2:      
      myImage.load("Tetris2.png");
      break;
    case 3:  
      myImage.load("Tetris3.png");
      break;
    case 4:
      myImage.load("Tetris4.png");
      break;
    case 5:
      myImage.load("Tetris5.png");
      break;
    case 6:
      myImage.load("Tetris6.png");
      break;
    case 7:     
      myImage.load("Tetris7.png");
      break;
  }
   this->setPixmap(QPixmap::fromImage(myImage));
}