
// This program allows two functions to have a Gomoku battle.
// The program expects the files to be called

// "Player1.h", "Player1.cpp", "Player2.h", "Player2.cpp"

// and for the functions in those files to be defined as 

// void playerOne(int &roW, int &coL); 
// void playerTwo(int &roW, int &coL);

// roW and coL (above) perform two jobs. 
//
// 1.)	record the players move and return it to playGomoku(). 
//
//		These vars are shared by both players so when they are 
//		passed to playerOne() (for example) they already contain 
//		the move that playerTwo() just made.
//
// 2.)	record the move that the opponent just made

// Both players need their own 19x19 array to record the game.

// --- Program Controls ---
//
// spacebar	- start playing gomoku 
// x		- press at beginning of game to view one move for
//			  each player at a time.  Now each time spacebar 
//			  is pressed only two dots will appear on the board
//			  until 5 in a row is reached or all squares are 
//			  filled
// up (dir.)- fullscreen
// down		- exit full screen
// b		- make game grid disappear
// s		- player 1 smiley face
// esc		- exit program
// backspace- exit program

#ifndef MAIN_CPP
#define MAIN_CPP

#define _WIN32_WINNT 0x0500		//hide terminal window
#include <windows.h>			//hide terminal window
#include <glew.h>
#include <glut.h>
#include <math.h>
#include <algorithm>
#include <assert.h>
#include "Ares.h"
#include "Player1.h"	// a player needs one .cpp and one .h file
#include "PlayerDaybreak.h"
#include "Board.h"

using namespace std;

bool oneMove = true; // toggle to view one move at a time 
bool gameStart = false;	// start playing gomoku
bool gameWon = false;	// exit condition for playGomoku()

bool smiles = false;	// show smiley face
bool board = true;		// show green 19x19 gameboard
bool game = false;		// show 2D array of moves 

char moveColor = 'P';	// = purple, 'T' = tan
Board gameBoard; // current game board

// ai classes - Player1, PlayerDaybreak, Ares (Player1 renamed)

// --- moves first------
Ares player1;				// best attack + best block
//Player1 player1;			// good attack + very little block
//PlayerDaybreak player1;	// no attack   + limited block

// --- moves second ----
Ares player2;				// best attack + best block
//Player1 player2;			// good attack + very little block
//PlayerDaybreak player2;	// no attack   + limited block


Player *currentPlayer = &player1; // Who's current turn
Player *otherPlayer = &player2;

int smileyFace[2][8] = { -4, -2, 0, 2, 4, -2, 2, 0,
						  2,  0, 0, 0, 2,  6, 6, 0};

//--------------------------------------------------------------


void init ( GLvoid )     // Create Some Everyday Functions
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//--------------------------------------------------------------

void triangleFan(char color, float row, float col)
{
	int sections = 30; // # of triangles used to estimate a circle
    float hoffset = col;	// should be changed 
	float voffset = row;	// from display

    GLfloat radius = 0.8f; //radius
    GLfloat twoPi = 2.0f * 3.14159f;

//--game colors

	if (color == 'P') // purple
	{
		glColor3f(0.65f, 0.44f, 0.75f);
	}
	else if (color == 'T') // dark tan
	{
		glColor3f(0.58f, 0.41f, 0.3f); //Dark Tan	151;105;79
	}

//--

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(hoffset, voffset, 0.0); // origin
       
	for(int i = 0; i <= sections; i++)  // make section number of circles 
	{	     	 
		glVertex2f(radius * cos(i *  twoPi / sections) + hoffset, 
                   radius* sin(i * twoPi / sections) + voffset);
	}
          
	glEnd();
}


//-------------------------------------------------------------------


void drawSmileyFace(char faceColor)
{
	int tempRow, tempCol;

	for (int b = 0; b < 8; b++)
	{
		tempCol = smileyFace[0][b];
		tempRow = smileyFace[1][b];
		triangleFan(faceColor, tempRow, tempCol); 
	}
}

//-------------------------------------------------------------------


void drawGrid (void) 
{
	float vertical, horizon;

	glColor3f(0.0, 0.5, 0.0);
	glLineWidth(3);

	glBegin (GL_LINES);		// BEGIN LINES

	vertical = horizon = -19;

	for (int a = 0; a < 20; a++)
	{
		glVertex2i( horizon, -19.0);		
		glVertex2i( horizon,  19.0);
		horizon += 2;

		glVertex2i( -19.0, vertical);		
		glVertex2i( 19.0, vertical);
		vertical += 2;
	}

	glEnd();				// END LINES
}

//--------------------------------------------------------------


void drawGameMoves()
{
	int newRow, newCol;
	
	for (int d = 0; d < 19; d++)		// row
	{
		for (int e = 0; e < 19; e++)	// col
		{
			if (gameBoard.GetPiece(d, e) == PiecePlayer1)
			{
				moveColor = 'P';
				
				newRow = d - (18 - d); // gameBoard[][] to OGL screen
				newRow *= -1;
				newCol = e - (18 - e);

				triangleFan(moveColor, newRow, newCol);
			}
			if (gameBoard.GetPiece(d, e) == PiecePlayer2)
			{
				moveColor = 'T';
				
				newRow = d - (18 - d); // gameBoard[][] to OGL screen
				newRow *= -1;
				newCol = e - (18 - e);
				
				triangleFan(moveColor, newRow, newCol);
			}
		}
	}
}


//--------------------------------------------------------------


void swapPlayers() 
{
	Player *tmp = currentPlayer;
	currentPlayer = otherPlayer;
	otherPlayer = tmp;
}

Piece pieceForPlayer(Player *player) 
{
	return (player == &player1) ? PiecePlayer1 : PiecePlayer2;
}


//--------------------------------------------------------------


void playGomoku()
{
	Winner winner;
	
	while (!gameWon) 
	{
		// get move from player 1 & update gameBoard
		int ROW, COL;	// record player 1 moves and player 2 moves
		currentPlayer->GetMove(ROW, COL);

		assert(gameBoard.GetPiece(ROW, COL) == PieceNone); // Make sure this is a valid move
		gameBoard.SetPiece(ROW, COL, pieceForPlayer(currentPlayer));

		otherPlayer->OpponentDidMove(ROW, COL);
		
		drawGameMoves();
		gameWon = gameBoard.IsSolved(ROW, COL, winner); // check for win

		swapPlayers();

		if (oneMove) break;
	}
	if (gameWon)
		drawGameMoves();

}


//--------------------------------------------------------------


void display ( void )   // Create The Display Function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glTranslatef(-1.5f,0.0f,-30.0f);						// Move Left 1.5 Units And Into The Screen 6.0
    
	if (board) drawGrid();		// draws matrix / game board
	//if (game) drawGameMoves();	// fills all squares w/ circles
	if (smiles) drawSmileyFace(moveColor);
	if (gameStart) playGomoku();

    glutSwapBuffers ( );  // To Not Be Left With A Clear Screen
}


//--------------------------------------------------------------


void reshape ( int w, int h )   // Create The Reshape Function (the viewport)
{
    glViewport     ( 0, 0, w, h );
    glMatrixMode   ( GL_PROJECTION );  // Select The Projection Matrix
    glLoadIdentity ( );                // Reset The Projection Matrix
    
	if ( h==0 )  // Calculate The Aspect Ratio Of The Window
        gluPerspective ( 80, ( float ) w, 1.0, 5000.0 );
    else
        gluPerspective ( 80, ( float ) w / ( float ) h, 1.0, 5000.0 );
   
	glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
    glLoadIdentity ( );    // Reset The Model View Matrix
}


//--------------------------------------------------------------


void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
    switch ( key )
    {
    case 8: exit (0);	// BACKSPACE key = 8 (ascii)	
			break;	
	case 27: exit ( 0 );		// Exit The Program
        break;  
	case 32: gameStart = true;	// space starts gomoku
        break;   
	case 98: board = !board;	// lower b. toggle board
        break;
	case 103: game = !game;		// lower s. toggle game moves
        break;
	case 115: smiles = !smiles; // lower s. toggle smiley face
        break;
	case 120: oneMove = !oneMove; // lower x. toggle to view one
	    break;					  // move at a time per player
    
	default: break;
    }

    glutPostRedisplay(); // makes it all happen
}


//--------------------------------------------------------------


void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
    switch ( a_keys )
    {
    case GLUT_KEY_UP: glutFullScreen ( ); 
        break;
    case GLUT_KEY_DOWN: glutReshapeWindow ( 500, 500 ); 
        break;
    
	default: break;
    }
}


//--------------------------------------------------------------


int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
	//HWND hWnd = GetConsoleWindow();		//hide terminal window
	//ShowWindow( hWnd, SW_HIDE );

    glutInit            ( &argc, argv ); // Erm Just Write It =)
    init ();
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE ); // Display Mode
    glutInitWindowSize  ( 600, 600 ); // If glutFullScreen wasn't called this is the window size
    glutInitWindowPosition (200, 150); // Set the position of the window
	glutCreateWindow    ( "GLomoku" ); // Window Title (argv[0] for current directory as title)
    //glutFullScreen      ( );          // Put Into Full Screen
    glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc     ( reshape );
    glutKeyboardFunc    ( keyboard );
    glutSpecialFunc     ( arrow_keys );
    glutMainLoop        ( );          // Initialize The Main Loop

    return 0;
}

#endif