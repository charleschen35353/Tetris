#include <QApplication>
#include <unistd.h>
#include "playwindow.h"
Playwindow::Playwindow(QLabel *parent) : QLabel(parent), timecount(0)
{   
    gameStart= 0; //the game is waiting for users tp press start button
    previousTetris  = NULL; //clean the temporary storer
    setFocusPolicy(Qt::StrongFocus); //make playwindow listen to keyPressEvent
    myImage.load("background.bmp"); //load backgournd into my image
    this->setPixmap(QPixmap::fromImage(myImage)); //set background
    activeTetris = new Tetris; //create the first tetris
}
Playwindow :: ~Playwindow()
{
    cleanTetris();  
}
void Playwindow::updatePlaywindow(){
    timecount ++;

    if(gameStart >1 && started == false){// if the user lose, restart the game into initialized situation 
                         //if the game has not started yet, create default situation
      myImage.load("background.bmp"); //load backgournd into my image
      this->setPixmap(QPixmap::fromImage(myImage)); //set background
      coormg.zero();//clean all coordinate of my game board and zero all the score and level
      activeTetris = new Tetris; //create the first tetris
      started = true;
    }
    
    if (isStop(activeTetris) && (timecount%(22-2*getlevel()) == 0 || isoverlapped(activeTetris))){ // check if the active tetris is stop
      coormg.occupycoor(activeTetris);//record the stablized tetris coordinate
      if(coormg.checkend()) {gameStart++;cleanTetris();return;}
      coormg.checkrow();
      previousTetris = activeTetris;// put the stop Tetris into a temporary pointer
      activeTetris = new Tetris(activeTetris->getNexttype(),previousTetris);//create a new tetris and put my last active tetris into its previous pointer in case of memory leakage
      activeTetris -> move_up();// put the Tetris one step back for the next move down
    }
    
    if (timecount%(22-2*getlevel()) == 0 && inrange(predictdown(activeTetris))) activeTetris->move_down();// move down the tetris in every time interval respect to the level
    
    drawTetris();//draw my game board

}

void Playwindow::drawTetris() {
    myImage.load("background.bmp");
    this->setPixmap(QPixmap::fromImage(myImage));
    QPainter qPainter(&myImage);// set qpainter to background
    qPainter.setPen(Qt::black);//use black pen to draw the margin of the blocks
    
    switch (activeTetris->getType()){//change paint color of my tetris depends on their types
      case 1: qPainter.setBrush(Qt::red); break;
      case 2: qPainter.setBrush(Qt::green); break;
      case 3: qPainter.setBrush(Qt::blue); break;
      case 4: qPainter.setBrush(Qt::yellow); break;
      case 5: qPainter.setBrush(Qt::cyan); break;
      case 6: qPainter.setBrush(Qt::darkYellow); break;
      case 7: qPainter.setBrush(Qt::magenta); break;}
    for (int i = 0; i < 4 ; i++) qPainter.drawRect(activeTetris->getBlock_x(i)*20, activeTetris->getBlock_y(i)*20,20,20);//draw my activeTetris
    
    
    for (int row = 19 ; row >=0 ; row --)
      for (int col = 9 ; col>=0 ; col-- )
	if(coormg.pointedblock(row,col)!= NULL){//paint only if the coordinate is occupied
	  switch (coormg.pointedblock(row,col)->getType()){
	    case 1: qPainter.setBrush(Qt::red); break;
	    case 2: qPainter.setBrush(Qt::green); break;
	    case 3: qPainter.setBrush(Qt::blue); break;
	    case 4: qPainter.setBrush(Qt::yellow); break;
	    case 5: qPainter.setBrush(Qt::cyan); break;
	    case 6: qPainter.setBrush(Qt::darkYellow); break;
	    case 7: qPainter.setBrush(Qt::magenta); break;}
	  qPainter.drawRect(col*20,row*20,20,20);//draw stop tetris
	}
    this->setPixmap(QPixmap::fromImage(myImage));//print out the result of all draw events
}

void Playwindow :: cleanTetris(){// using linked list to clean momory
    Tetris* dptr = activeTetris; //point at the tetris we are goning to delete
    Tetris* nptr;//point at the next tetris to be delete

    while(dptr->getprevious() != NULL){
      nptr = dptr->getprevious();
      delete dptr;
      dptr = nptr;
    }
    delete dptr;
}

void Playwindow :: keyPressEvent( QKeyEvent* event){
    switch (event->key()){
      
      case Qt::Key_Left:
	if(gameStart%2 !=0){
	  if(inrange(predictleft(activeTetris))&& !isoverlapped(predictleft(activeTetris))) activeTetris->move_left();}
	break;//go left if the next step is in range and will not overlap with stop tetris
	
      case Qt::Key_Right:
	if(gameStart%2 !=0){
	  if(inrange(predictright(activeTetris))&& !isoverlapped(predictright(activeTetris))) activeTetris->move_right();}
	break;//go right if the next step is in range and will not overlap with stop tetris
      
      case Qt::Key_Up:
	if(gameStart%2 ==0)gameStart ++;
	break; // press up to start the game
      
      case Qt::Key_Down:
	if(gameStart%2 !=0){ 
	if(inrange(predictdown(activeTetris)) && !isoverlapped(predictdown(activeTetris)))activeTetris->move_down();//go down if the next step is in range and will not overlap with stop tetris
	else timecount = -1;}//The case tetris can not move anymore. This will caause the tetris to stop immediately and a new active tetris will be created
	break;
      
      case Qt::Key_X:
	if(gameStart%2 !=0){// rotate anticlockwise
	  if (!isoverlapped(predictanticlockwiserotate(activeTetris))&&inrange(predictanticlockwiserotate(activeTetris)))
	  {
	    activeTetris->rotate_anticlockwise(activeTetris->getType(),activeTetris->getRotationflag()); 
	    activeTetris->setRotationflag(activeTetris->getRotationflag()+1);}
	}
	break;
      
      case Qt::Key_Z://rotate clockwise
	if(gameStart%2 !=0){
	  if(!isoverlapped(predictclockwiserotate(activeTetris))&&inrange(predictclockwiserotate(activeTetris)))
	  for(int i=0 ; i<3 ; i++){ // rotate clockwise means do anticlockwise rotation 3 times
	    activeTetris->rotate_anticlockwise(activeTetris->getType(),activeTetris->getRotationflag()); 
	    activeTetris->setRotationflag(activeTetris->getRotationflag()+1);}
	}
	break;
    }
}
void Playwindow::Started(bool q){started = q;}//see if the game has been restarted or not

Tetris* Playwindow::getTetris()const{return activeTetris;}

Tetris* Playwindow::predictleft(const Tetris* const mytetris){ // predict the next coordinate of the left move
  cacuTetris = *mytetris;
  cacuTetris.move_left();
  return &cacuTetris;
}
Tetris* Playwindow::predictright(const Tetris* const mytetris){// predict the next coordinate of the right move
  cacuTetris = *mytetris;
  cacuTetris.move_right();
  return &cacuTetris;
}
Tetris* Playwindow::predictdown(const Tetris* const mytetris){// predict the next coordinate of the down move
  cacuTetris = *mytetris;
  cacuTetris.move_down();
  return &cacuTetris;
}
Tetris* Playwindow::predictanticlockwiserotate(const Tetris* const mytetris){// predict the next coordinate of the anticlockwise rotation
  cacuTetris = *mytetris;
  cacuTetris.rotate_anticlockwise(cacuTetris.getType(),cacuTetris.getRotationflag());
  return &cacuTetris;
}
Tetris* Playwindow::predictclockwiserotate(const Tetris* const mytetris){// predict the next coordinate of the clockwise rotation
  cacuTetris = *mytetris;
  for (int i = 0; i<3 ; i++){
  cacuTetris.rotate_anticlockwise(cacuTetris.getType(),cacuTetris.getRotationflag());
  cacuTetris.setRotationflag(cacuTetris.getRotationflag()+1);}
  return &cacuTetris;
}

int Playwindow::isStart() const {return gameStart;}// see if the game is in progress or not.ODD means not in progress,EVEN means is in progress

int Playwindow::getscore()const {return coormg.getscore();}

int Playwindow::getlevel(){return coormg.getlevel();}

bool Playwindow::isStop(const Tetris* const mytetris){
    if(!inrange(predictdown(mytetris)) || isoverlapped(predictdown(mytetris))) return true;// this function is used to determine whether the tetris must to stop and create a new one
    else return false;
}

bool Playwindow::inrange(const Tetris* const mytetris) // this function check if the tetris is in board coordinate or not. Usually used with predict funcitons
{
  bool isinrange = true;
  for (int i=0 ; i<4; i++)
    if(mytetris->getBlock_x(i) < 0 || mytetris->getBlock_x(i)>=10 || mytetris->getBlock_y(i)>19) isinrange = false;
  return isinrange;
}

bool Playwindow :: isoverlapped(const Tetris* const mytetris){// this function check if the tetris is overlapped with stop tetris or not. Usually used with predict funcitons
  bool isoverlapped = false;
  for (int i=0 ; i<4; i++)
    if(coormg.pointedblock(mytetris->getBlock_y(i),mytetris->getBlock_x(i)) != NULL) {isoverlapped = true;}
  return isoverlapped;
}


