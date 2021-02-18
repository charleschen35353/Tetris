#include <QApplication>
#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :  QWidget(parent), level(1), score(0)// make th UI
{
  playwindow = new Playwindow;
  previewwindow = new Previewwindow;
  levellabel = new QLabel;
  scorelabel = new QLabel;
  mainLayout = new QGridLayout;
  messagelabel = new QLabel;
  scorenumlabel = new QLabel;
  numlevel = new QLabel;

  timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updatescreen()));//connect timeout to updatescreen
  timer->start(50);
  
  //initialize level info
  levellabel->setText("Level:");
  numlevel->setNum(1);
  
  //initialize score info
  scorelabel->setText("Score:");
  scorenumlabel->setNum(0);
  
  //add widgets into layout with specific coordinate and display them all
  mainLayout->addWidget(previewwindow,20,40,32,20);
  mainLayout->addWidget(levellabel,60,40,4,20);
  mainLayout->addWidget(numlevel,59,48,6,6);
  mainLayout->addWidget(scorelabel,68,40,4,20);
  mainLayout->addWidget(playwindow,0,0,80,40);
  mainLayout->addWidget(scorenumlabel,67,48,6,6);
  mainLayout->addWidget(messagelabel,30,10,20,20);
  setLayout(mainLayout);

}
Mainwindow::~Mainwindow(){
  delete playwindow;
  delete previewwindow;
  delete levellabel;
  delete scorelabel;
  delete mainLayout;
  delete messagelabel;
  delete scorenumlabel;
  delete numlevel;
  delete timer;
  
}

void Mainwindow::updatescreen(){
  if (playwindow->isStart()%2 !=0){// if the return of isStart is odd, meaning that the game is in process
    messagelabel->setText("");//clean messagelabel
    playwindow->updatePlaywindow();
    previewwindow->loadnext(playwindow->getTetris()->getNexttype());//load the next type tetris into our preview window
    updateScore();
    updateLevel();
  }
  if(playwindow->isStart()%2 ==0 && playwindow->isStart()!=0 ){// if the return of isStart is even and not equal to 0, meaning that the game has ended at least one time
    messagelabel->setText("LOSE!\nPRESS UP\nTO START\nAGAIN");
    playwindow->Started(false);//see if the game is restarted
  }
  if(playwindow->isStart()==0 ){// this means the game has not started yey
    messagelabel->setText("PRESS\nup\nTO\nSTART");
    playwindow->Started(true) ;
  }
}


void Mainwindow::updateScore(){//update score
  scorelabel->setText("Score:");
  scorenumlabel->setNum(playwindow->getscore());
}

void Mainwindow::updateLevel(){//update level
  levellabel->setText("Level:");
  numlevel->setNum(playwindow->getlevel());
}

