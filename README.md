Command:

1.```qmake -o Makefile tetris.pro``` 

2. ```make```

3. ```./tetris```

We have six header files, seven cpp files.
			        tetris_main.cpp
blocks.h			blocks.cpp
coordinatemanager.h	coordinatemanager.cpp
mainwindow.h		mainwindow.cpp
playwindow.h		playwindow.cpp
preview.h		preview.cpp
tetris.h			tetris.cpp

For User Interface:
In mainwindow.cpp, We create one 'mainLayout' as a QGridLayout in QT, then we add six label on mainLayout 
to achieve displays of level,score,playwindow,and preview window. 

For implementation of Tetris:
	We create a 10*20 interger array to store the information of blocks, 0 for null, 1 for existence.
1. creat blocks in playwindow and preview window continuously. 
	In tetris.cpp, we overloaded constructor in class Tetris, Tetris() and Tetris(int,Tetris*),
	At the beginning, when a new class is created by Tetris() constructor, tetris_type and next_type are all created randomly, 
	tetris_type represents for blocks in playwindow and next_type represents for blocks in previewwindow.
	when stop of blocks is confirmed, we use Tetris(int,Tetris*) to creat new blocks in playwindow, similarily, next_type will be created again, then 
	it repeats Tetris(int,Tetris*) to create blocks, so it can achieve creating blocks in playwindow dnd preview window continuously. 	

2.blocks fall down and keypress event
	We use signal and slot to achieve displacement of blocks and update it in a certain time, and we use QKeyEvent to achieve conversion.
	The centers of blocks are set for rotation.

3.stop the blocks and prevent illegal conversion	
	We create functions called predictdown,predictleft,predictright,predictclockwiserorate,predictanticlockwiserotate. These functions can previously locate the
	blocks' changed positions, and we check if all the positions are in range and NULL, if yesthen we implement conversion.  So it can prevent illegal conversion.
	
	Similarily, we check if all positions of predictdown are NULL, if not , then we can stop it and create a new tetris.		

4.remove a full row
	When we find a full row, we just replace the row with the first upper row to achieve the remove of blocks.
	We check row by row from the bottom when the block stops, When we find that a row is full, then we store the number of row
	and check 3 rows above it, too. Since every time the maximum of removed rows if 4.
	
5.score and level
	Every time we check rows, initialize count =0; if there is one row removed, then count++; , after check is finished,
	score += 10*(count)*(count); then display it in scorenumlabel.

	Since the level will increase by 1 for every 100 mark, then we use equation level = ((score-score%100)/100)+1
	then display it in numlevel QLabel.
6.end of game and restart
	initialize gameStart = 0;	
	When we press Up at the beginning, gameStart will increase by 1,.
	We check the second row after active tetris stops, If there exists blocks, then let   gameStart increase by 1.
	if(gameStart%2 ==1), the game is processing,  if(gameStart%2==0),the game stops.
	It is a reasonable and simple way to implement it.

This is brief introduction of our project, you can see more details in codes.
Thanks
CHEN,Liang-yu

	
	 
