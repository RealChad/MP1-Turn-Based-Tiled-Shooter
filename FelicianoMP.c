/******************************************************************************
This is to certify that this project is my own work, based on my personal
efforts in studying and applying the concepts learned. I have constructed
the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I
further certify that I have not copied in part or whole or otherwise
plagiarized the work of other students and/or persons.
<-------------> - <--------> - <S19A>
******************************************************************************/
/*   
     Description:      <Turn-based Tiled Shooter>
     Programmed by:    <------------------->   <S19A>
     Last modified:    <December 4, 2022>
     Version:          <2.0>
    [Acknowledgements: <C Library - <stdlib.h>. (2022, November 20). Retrieved from https://www.tutorialspoint.com/c_standard_library/stdlib_h.htm#>
                       <Windows API Reference (Windows). (2022, December 04). Retrieved from https://learn.microsoft.com/en-us/previous-versions//aa383749(v=vs.85)?redirectedfrom=MSDN>
                       <FAQ - UTF-8, UTF-16, UTF-32 & BOM. (2022, October 20). Retrieved from https://unicode.org/faq/utf_bom.html>]
                       
*/
/*
    Compile:    gcc -Wall FelicianoMP.c -o FelicianoExe.exe
    Execution:  FelicianoExe.exe or ./FelicianoExe.exe
*/
#include <stdio.h>
#include <stdlib.h> //for use of the rand() function to receive a random number
#include <windows.h> //for use of the SetConsoleOutputCP function to print the expected border and divider in terminal

#define ENEMY_ICON '$' // to easily manipulate the enemy's appearance in the game
#define PLAYER_ICON 'P' // to easily manipulate the player's appearance in the game
#define SCORE_FOR_ENEMY_DOWN 10 //to easily manipulate the score added for whenever an enemy is downed by fireLaser
#define SCORE_FOR_PLAYER_WIN 100 //to easily manipulate the score needed for the player to win

#define TRUE 1 //defines the boolean value of true
#define FALSE 0 //defines the boolean value of false

/* <This function prints a divider>
Precondition: <none>
@param <none>
@return <none>
*/
void printDivider() {
    printf("\n———————————————————————————————————————————————————————————————————\n\n"); //prints a divider
}

/* <This function prints the game's start menu>
Precondition: <none>
@param <none>
@return <none>
*/
void printMenu() {
    int nShowScoreNeeded = SCORE_FOR_PLAYER_WIN;
    char cShowEnemyIcon = ENEMY_ICON; 
    int nInputStart;
    printDivider();
    printf("\nCLOUT CHASER\n");
    printf("Goal: Get to %d points before the enemies (%c) reach you.\n\n", nShowScoreNeeded, cShowEnemyIcon);
    printf("made by: Jan Robee Feliciano\n\n");
    printf("\nEnter any number to start.\n\n");
    printDivider();
    scanf("%d", &nInputStart);
    printDivider();
    /******************************************************************************
    EXPECTED OUTPUT
    ———————————————————————————————————————————————————————————————————


    CLOUT CHASER
    Goal: Get to 100 points before the enemies ($) reach you.

    made by: Jan Robee Feliciano


    Enter any number to start.


    ———————————————————————————————————————————————————————————————————

    ******************************************************************************/
}

/* <This function prints flavor text>
Precondition: <none>
@param <none>
@return <none>
*/
void printFlavorText() {
    int nFlavorText;

    nFlavorText = rand() % 10 + 1; //outputs a random flavor text from 10 choices

    switch (nFlavorText) {
        case 1:
            printf("\nYou bought a new car!\n\n");
            break;
        case 2:
            printf("\nYou bought a new condo!\n\n");
            break;
        case 3:
            printf("\nYou bought a new sink(?)\n\n");
            break;
        case 4:
            printf("\nYou bought a new PS5!\n\n");
            break;    
        case 5:
            printf("\nYou bought a new piano!\n\n");
            break;
        case 6:
            printf("\nYou bought a soya beancurd pareh SHEEEEESH!\n\n");
            break;
        case 7:
            printf("\nYou bought a train ticket to BGC pareh!\n\n");
            break;   
        case 8:
            printf("\nYou bought a starbs pareh!\n\n");
            break; 
        case 9:
            printf("\nYou bought a new personal fountain!\n\n");
            break;
        case 10:
            printf("\nYou bought a personal valet!\n\n");
            break;
    }
}

/* <This function respawns the enemy>
Precondition: <*nEnemy_X, *nEnemy_Y, and *nEnemy_AI are non-negative values>
@param <*nEnemy_X> holds the enemy's X-coordinate in the game
@param <*nEnemy_Y> holds the enemy's Y-coordinate in the game
@param <*nEnemy_AI> is the personal AI of the enemy
@return <none>
*/
void respawnEnemy(int *nEnemy_X, int *nEnemy_Y, int *nEnemy_AI) {
    printf("\a"); //plays a sound whenever the player scores points (which happens when an enemy respawns)
    printFlavorText(); //prints flavor text whenever an enemy is killed (which happens when an enemy respawns) (Note: this function outputs twice when two enemies are killed, and thrice when three enemies are killed)
    if (*nEnemy_Y == 1) { //if the enemy is killed in the top row, they will respawn at the leftmost column
        *nEnemy_X = 1;
    } else {
        *nEnemy_X = rand() % 3 + 1; //this is so the enemy will respawn randomly between the first 3 columns
    }
    *nEnemy_Y = 1; //this is so the enemy respawns at the top row  
    *nEnemy_AI = 1; //moves the enemy to the right

    //Note: No collision detection is utilized for this function. When two enemies are killed at the same time, they will randomly respawn at any slot (meaning they could also potentially respawn at the same spot).
    //Note: The enemy will move immediately upon respawning. If an enemy is assumed to respawn at the leftmost column but actually appears in the same column, it means they moved right immediately and should move down in the next turn.
    //Note: "Power Up: Fire Actual Laser" and "Power Up: ONE PUNCH!" will specify where killed enemies will respawn.
    }

/* <This function fires a laser which downs enemies with the same X-coordinate as the player>
Precondition: <*nEnemy1_X, *nEnemy1_Y, *nEnemy2_X, *nEnemy2_Y, *nEnemy3_X, *nEnemy3_Y, *nEnemy1_AI, *nEnemy2_AI, *nEnemy3_AI are non-negative values; nPlayer_X is a value between 1-4; *nScore is a non-negative value.>
@param <*nEnemy1_X> holds enemy 1's X-coordinate in the game
@param <*nEnemy1_Y> holds enemy 1's Y-coordinate in the game
@param <*nEnemy2_X> holds enemy 2's X-coordinate in the game
@param <*nEnemy2_Y> holds enemy 2's Y-coordinate in the game
@param <*nEnemy3_X> holds enemy 3's X-coordinate in the game
@param <*nEnemy3_Y> holds enemy 3's Y-coordinate in the game
@param <nPlayer_X> holds the player's X-coordinate in the game
@param <*nScore> holds the value of the player's score
@param <*nEnemy1_AI> is the personal AI of enemy 1
@param <*nEnemy2_AI> is the personal AI of enemy 2
@param <*nEnemy3_AI> is the personal AI of enemy 3
@return <none>
*/
void fireLaser(int *nEnemy1_X, int *nEnemy1_Y, int *nEnemy2_X, int *nEnemy2_Y, int *nEnemy3_X, int *nEnemy3_Y, int nPlayer_X, int *nScore, int *nEnemy1_AI, int *nEnemy2_AI, int *nEnemy3_AI) {
//This version of the code has collision detection for whenever there are multiple enemies in the same column. In this case, the bottommost enemy in the column is prioritized and the others retain their movement.
    if ((nPlayer_X == *nEnemy1_X) && (nPlayer_X == *nEnemy2_X) && (nPlayer_X == *nEnemy3_X)) { //all enemies are in the same column
        if ((*nEnemy1_Y >= *nEnemy2_Y) && (*nEnemy1_Y >= *nEnemy3_Y)) { //Enemy 1 is bottommost 
            respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        }
        if ((*nEnemy2_Y >= *nEnemy1_Y) && (*nEnemy2_Y >= *nEnemy3_Y)) { //Enemy 2 is bottommost 
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        }
        if ((*nEnemy3_Y >= *nEnemy1_Y) && (*nEnemy3_Y >= *nEnemy1_Y)) { //Enemy 3 is bottommost 
            respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        }
        *nScore += SCORE_FOR_ENEMY_DOWN;
    } else if ((nPlayer_X == *nEnemy1_X) && (nPlayer_X == *nEnemy2_X)) { //Enemy 1 and Enemy 2 are in the same column
        if ((*nEnemy1_Y >= *nEnemy2_Y)){ //Enemy 1 is bottommost 
            respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        }
        if (*nEnemy2_Y >= *nEnemy1_Y){ //Enemy 2 is bottommost 
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        }
        *nScore += SCORE_FOR_ENEMY_DOWN;
    } else if ((nPlayer_X == *nEnemy1_X) && (nPlayer_X == *nEnemy3_X)) { //Enemy 1 and Enemy 3 are in the same column
        if ((*nEnemy1_Y >= *nEnemy3_Y)){ //Enemy 1 is bottommost 
            respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        }
        if (*nEnemy3_Y >= *nEnemy1_Y){ //Enemy 3 is bottommost 
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        }
        *nScore += SCORE_FOR_ENEMY_DOWN;
    } else if ((nPlayer_X == *nEnemy2_X) && (nPlayer_X == *nEnemy3_X)) { //Enemy 2 and Enemy 3 are in the same column
        if ((*nEnemy2_Y >= *nEnemy3_Y)){ //Enemy 2 is bottommost 
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        }
        if (*nEnemy3_Y >= *nEnemy2_Y){ //Enemy 3 is bottommost 
            respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        }
        *nScore += SCORE_FOR_ENEMY_DOWN;
    } else if ((nPlayer_X == *nEnemy1_X) || (nPlayer_X == *nEnemy2_X) || (nPlayer_X == *nEnemy3_X)) { //only one enemy is in the column
        if (nPlayer_X == *nEnemy1_X) {
            respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        }
        if (nPlayer_X == *nEnemy2_X) {
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        }
        if (nPlayer_X == *nEnemy3_X) {
            respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        }
        *nScore += SCORE_FOR_ENEMY_DOWN;
    } else { //no enemies are in the same column as the player
        printf("\nYou didn't hit anything.\n\n");
    } 
}

/* <This function moves player to the left>
Precondition: <*nPlayer_X is a value between 1-4>
@param <*nPlayer_X> holds the player's X-coordinate in the game
@return <none>
*/
void movePlayerLeft(int *nPlayer_X) {
    if (*nPlayer_X > 1) { //If the Player is not in first column, movePlayerLeft reduces its value by 1 so the Player is printed to the previous column
        --*nPlayer_X;
    }
}

/* <This function moves player to the right>
Precondition: <*nPlayer_X is a value between 1-4>
@param <*nPlayer_X> holds the player's X-coordinate in the game
@return <none>
*/
void movePlayerRight(int *nPlayer_X) {
    if (*nPlayer_X < 4) { //If the Player is not in fourth column, movePlayerRight reduces its value by 1 so the Player is printed to the next column
        ++*nPlayer_X;
    }
}

/* <This function fires an actual laser which downs ALL enemies with the same X-coordinate as the player>
Precondition: <*nEnemy1_X, *nEnemy1_Y, *nEnemy2_X, *nEnemy2_Y, *nEnemy3_X, *nEnemy3_Y, *nEnemy1_AI, *nEnemy2_AI, *nEnemy3_AI are non-negative values; nPlayer_X is a value between 1-4; *nScore is a non-negative value.>
@param <*nEnemy1_X> holds enemy 1's X-coordinate in the game
@param <*nEnemy1_Y> holds enemy 1's Y-coordinate in the game
@param <*nEnemy2_X> holds enemy 2's X-coordinate in the game
@param <*nEnemy2_Y> holds enemy 2's Y-coordinate in the game
@param <*nEnemy3_X> holds enemy 3's X-coordinate in the game
@param <*nEnemy3_Y> holds enemy 3's Y-coordinate in the game
@param <nPlayer_X> holds the player's X-coordinate in the game
@param <*nScore> holds the value of the player's score
@param <*nEnemy1_AI> is the personal AI of enemy 1
@param <*nEnemy2_AI> is the personal AI of enemy 2
@param <*nEnemy3_AI> is the personal AI of enemy 3
@return <none>
*/
void fireActualLaser(int *nEnemy1_X, int *nEnemy1_Y, int *nEnemy2_X, int *nEnemy2_Y, int *nEnemy3_X, int *nEnemy3_Y, int nPlayer_X, int *nScore, int *nEnemy1_AI, int *nEnemy2_AI, int *nEnemy3_AI) {
    if ((nPlayer_X == *nEnemy1_X) && (nPlayer_X == *nEnemy2_X) && (nPlayer_X == *nEnemy3_X)) { //all enemies are in the same column
        respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        *nEnemy1_X = 1;
        respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        *nEnemy2_X = 2;
        respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        *nEnemy3_X = 3;
        *nScore += SCORE_FOR_ENEMY_DOWN * 3; //gives the corresponding score for killing three enemies
    } else if ((nPlayer_X == *nEnemy1_X) && (nPlayer_X == *nEnemy2_X)) { //Enemy 1 and Enemy 2 are in the same column
        respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        *nEnemy1_X = 1;
        respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        *nEnemy2_X = 2;
        *nScore += SCORE_FOR_ENEMY_DOWN * 2; //gives the corresponding score for killing two enemies
    } else if ((nPlayer_X == *nEnemy2_X) && (nPlayer_X == *nEnemy3_X)) { //Enemy 2 and Enemy 3 are in the same column
        respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        *nEnemy2_X = 1;
        respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        *nEnemy3_X = 2;
        *nScore += SCORE_FOR_ENEMY_DOWN * 2; //gives the corresponding score for killing two enemies
    } else if ((nPlayer_X == *nEnemy1_X) && (nPlayer_X == *nEnemy3_X)) { //Enemy 1 and Enemy 3 are in the same column
        respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        *nEnemy2_X = 1;
        respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        *nEnemy3_X = 2;
        *nScore += SCORE_FOR_ENEMY_DOWN * 2; //gives the corresponding score for killing two enemies
    } else if ((nPlayer_X == *nEnemy1_X) || (nPlayer_X == *nEnemy2_X) || (nPlayer_X == *nEnemy3_X)) { //only one enemy is in the column
        if(nPlayer_X == *nEnemy1_X) {
            respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
        }
        if(nPlayer_X == *nEnemy2_X) {
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
        }
        if(nPlayer_X == *nEnemy3_X) {
            respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
        }
        *nScore += SCORE_FOR_ENEMY_DOWN; //gives the corresponding score for killing one enemy
    } else { //no enemies are in the same column as the player
        printf("\nBut you didn't hit anything! :(\n\n");
    }
}

/* <This function displays the player's console and does all calculations concerning player action>
Precondition: <*nEnemy1_X, *nEnemy1_Y, *nEnemy2_X, *nEnemy2_Y, *nEnemy3_X, *nEnemy3_Y, *nEnemy1_AI, *nEnemy2_AI, *nEnemy3_AI are non-negative values; nPlayer_X is a value between 1-4; *nScore is a non-negative value; nOnePunchRequirement is non-negative value; *nOnePunchUsed is a boolean value (TRUE/FALSE);  nFireActualLaserRequirement is non-negative value; *nFireActualLaserUsed is a boolean value (TRUE/FALSE); nInput is a non-negative value>
@param <*nEnemy1_X> holds enemy 1's X-coordinate in the game
@param <*nEnemy1_Y> holds enemy 1's Y-coordinate in the game
@param <*nEnemy2_X> holds enemy 2's X-coordinate in the game
@param <*nEnemy2_Y> holds enemy 2's Y-coordinate in the game
@param <*nEnemy3_X> holds enemy 3's X-coordinate in the game
@param <*nEnemy3_Y> holds enemy 3's Y-coordinate in the game
@param <nPlayer_X> holds the player's X-coordinate in the game
@param <*nScore> holds the value of the player's score
@param <*nEnemy1_AI> is the personal AI of enemy 1
@param <*nEnemy2_AI> is the personal AI of enemy 2
@param <*nEnemy3_AI> is the personal AI of enemy 3
@param <nOnePunchRequirement> dictates the score required for player to use "Power Up: ONE PUNCH!"
@param <*nOnePunchUsed> if FALSE - the player can still use "Power Up: ONE PUNCH!"; if TRUE - the player can no longer use "Power Up: ONE PUNCH!"
@param <nFireActualLaserRequirement> dictates the score required for player to use "Power Up: Fire Actual Laser"
@param <*nFireActualLaserUsed> if FALSE - the player can still use "Power Up: Fire Actual Laser"; if TRUE - the player can no longer use "Power Up: Fire Actual Laser"
@param <nInput> holds the player's input
@return <none>
*/
void printPlayerConsole(int *nEnemy1_X, int *nEnemy1_Y, int *nEnemy2_X, int *nEnemy2_Y, int *nEnemy3_X, int *nEnemy3_Y, int *nPlayer_X, int *nScore, int *nEnemy1_AI, int *nEnemy2_AI, int *nEnemy3_AI, int nOnePunchRequirement, int *nOnePunchUsed, int nFireActualLaserRequirement, int *nFireActualLaserUsed, int nInput) {
	
	do { //continuously asks for player input until the player enters a valid input
        printf("Actions:\n");
	    printf(" 1 - Move Left\n");
	    printf(" 2 - Move Right\n");
	    printf(" 3 - Fire Laser\n");
        if (*nFireActualLaserUsed == FALSE){
            if (*nScore < nFireActualLaserRequirement) {
                printf(" 4 - Power Up: Fire Actual Laser (Available after reaching %d points)\n", nFireActualLaserRequirement);  
            } else {
                printf(" 4 - Power Up: Fire Actual Laser (Ready to fire!)\n"); 
            }
        } else {
            printf(" 4 - Power Up: Fire Actual Laser (No longer available)\n"); 
        }       
        if (*nOnePunchUsed == FALSE){
            if (*nScore < nOnePunchRequirement) {
                printf(" 5 - Power Up: ONE PUNCH! (Available after reaching %d points)\n", nOnePunchRequirement);  
            } else {
                printf(" 5 - Power Up: ONE PUNCH! (Ready to fire!)\n"); 
            }
        } else {
            printf(" 5 - Power Up: ONE PUNCH! (No longer available)\n");  
        }
		printf("Input Action: ");
		scanf("%d", &nInput);
        
        if((nInput > 5 || nInput < 1) || ((nInput == 1 && *nPlayer_X == 1)) || (nInput == 2 && *nPlayer_X == 4) || (nInput == 4 && (*nScore < nFireActualLaserRequirement)) || (nInput == 4 && (*nFireActualLaserUsed== TRUE)) || (nInput == 5 && (*nScore < nOnePunchRequirement)) || (nInput == 5 && (*nOnePunchUsed == TRUE))) {
            if ((nInput > 5 || nInput < 1)) { //INVALID if the player inputs a number not within 1-4
                printf("\nINVALID INPUT\n\n");
            }
            if ((nInput == 1) && (*nPlayer_X == 1)) { // INVALID if player inputs left while at leftmost column
                printf("\nINVALID ACTION (move left unavailable)\n\n");
            }
            if((nInput == 2) && (*nPlayer_X == 4)) { // INVALID if player inputs right while at rightmost column
                printf("\nINVALID ACTION (move right unavailable)\n\n");
            }
            if ((nInput == 4) && (*nScore < nFireActualLaserRequirement)) {  //INVALID if the player tries to use "Fire Actual Laser" while it is unavailable
                printf("\nINVALID ACTION (Fire Actual Laser is not yet available!)\n\n");
            }
            if ((nInput == 4) && (*nFireActualLaserUsed == TRUE)) { //INVALID if the player tries to use "Fire Actual Laser" while it has already been used
                printf("\nINVALID ACTION (Fire Actual Laser has already been used!)\n\n");
            }
            if ((nInput == 5) && (*nScore < nOnePunchRequirement)) {  //INVALID if the player tries to use "ONE PUNCH!" while it is unavailable
                printf("\nINVALID ACTION (One Punch is not yet available!)\n\n");
            }
            if ((nInput == 5) && (*nOnePunchUsed == TRUE)) { //INVALID if the player tries to use "ONE PUNCH!" while it has already been used
                printf("\nINVALID ACTION (One Punch has already been used!)\n\n");
            }
        } else {
            printDivider(); //prints a divider when the input is valid
        }
	} while ((nInput > 5 || nInput < 1) || ((nInput == 1 && *nPlayer_X == 1)) || (nInput == 2 && *nPlayer_X == 4) || (nInput == 4 && (*nScore < nFireActualLaserRequirement)) || (nInput == 4 && (*nFireActualLaserUsed == TRUE)) || (nInput == 5 && (*nScore < nOnePunchRequirement)) || (nInput == 5 && (*nOnePunchUsed == TRUE)));
    
	switch (nInput) {
		case 1: //moves left
			movePlayerLeft(nPlayer_X);
			break;
        case 2: //moves right
			movePlayerRight(nPlayer_X);
			break;
        case 3: //fires laser
			fireLaser(nEnemy1_X, nEnemy1_Y, nEnemy2_X, nEnemy2_Y, nEnemy3_X, nEnemy3_Y, *nPlayer_X, nScore, nEnemy1_AI, nEnemy2_AI, nEnemy3_AI);
			break;
        case 4: //uses "Power Up: Fire Actual Laser"
            printf("\nYou fired an actual laser.\n\n");
            fireActualLaser(nEnemy1_X, nEnemy1_Y, nEnemy2_X, nEnemy2_Y, nEnemy3_X, nEnemy3_Y, *nPlayer_X, nScore, nEnemy1_AI, nEnemy2_AI, nEnemy3_AI);
            *nFireActualLaserUsed = TRUE; //removes the player's ability to use "Power Up: Fire Actual Laser" again
            break;
        case 5: //uses "Power Up: ONE PUNCH!"
            printf("\nONE PUUUUUUUUUUUNCH!!!!!!!!!!!\n\n");
            respawnEnemy(nEnemy1_X, nEnemy1_Y, nEnemy1_AI);
            *nEnemy1_X = 1;
            respawnEnemy(nEnemy2_X, nEnemy2_Y, nEnemy2_AI);
            *nEnemy2_X = 2;
            respawnEnemy(nEnemy3_X, nEnemy3_Y, nEnemy3_AI);
            *nEnemy3_X = 3;
            *nScore += SCORE_FOR_ENEMY_DOWN * 3; //gives the corresponding score for killing three enemies
            *nOnePunchUsed = TRUE; //removes the player's ability to use "Power Up: ONE PUNCH!" again
            break;
    }
}

/* <This function cycles the enemy's movement>
Precondition: <*nEnemy_X, *nEnemy_Y, and *nEnemy_AI are non-negative values>
@param <*nEnemy_X> holds the enemy's X-coordinate in the game
@param <*nEnemy_Y> holds the enemy's Y-coordinate in the game
@param <*nEnemy_AI> is the personal AI of the enemy
@return <none>
*/
void cycleEnemyMovement(int *nEnemy_X, int *nEnemy_Y, int *nEnemy_AI) {   
    switch (*nEnemy_AI) {
		case 1: //enemy moves right
			++*nEnemy_X;
			break;
		case 2: //enemy moves down
			++*nEnemy_Y;
			break;
		case 3: //enemy moves left
			--*nEnemy_X;
			break;
		case 4: //enemy moves down
			++*nEnemy_Y;
			break;
    }
    *nEnemy_AI = *nEnemy_AI % 4 + 1;  //cycles the enemy's actions
}

/* <This function displays the game>
Precondition: <nEnemy1_X, nEnemy1_Y, nEnemy2_X, nEnemy2_Y, nEnemy3_X, and nEnemy3_Y are non-negative values; nPlayer_X is a value between 1-4; nScore is a non-negative value.>
@param <nEnemy1_X> holds enemy 1's X-coordinate in the game
@param <nEnemy1_Y> holds enemy 1's Y-coordinate in the game
@param <nEnemy2_X> holds enemy 2's X-coordinate in the game
@param <nEnemy2_Y> holds enemy 2's Y-coordinate in the game
@param <nEnemy3_X> holds enemy 3's X-coordinate in the game
@param <nEnemy3_Y> holds enemy 3's Y-coordinate in the game
@param <nPlayer_X> holds the player's X-coordinate in the game
@param <nScore> holds the value of the player's score
@return <none>
*/
void printGame(int nEnemy1_X, int nEnemy1_Y, int nEnemy2_X, int nEnemy2_Y, int nEnemy3_X, int nEnemy3_Y, int nPlayer_X, int nScore) {
    int nRow; //to be used to print the rows 
    int nCol; //to be used to print the columns
    char cEnemyIcon = ENEMY_ICON; //variable that will hold the enemy's icon as defined in the preprocessor directive
    char cPlayerIcon = PLAYER_ICON; //variable that will hold the player's icon as defined in the preprocessor directive

    SetConsoleOutputCP(CP_UTF8); //this is so we can use unicode for the game border
    printf("┌─┬─┬─┬─┐*\n"); //prints the top border

    //this section is to print the enemy's area
    for (nRow = 1; nRow <= 5; nRow++){ //Prints the rows. nRow <= 5 is the condition because there are 5 rows
       if ((nRow == nEnemy1_Y) || (nRow == nEnemy2_Y) || (nRow == nEnemy3_Y)) { //prints the columns with enemies if there are any
            for (nCol = 1; nCol <= 4; nCol++) {
                printf("│"); //leftmost and inner borders
				if ((nCol == nEnemy1_X && nRow == nEnemy1_Y) || (nCol == nEnemy2_X && nRow == nEnemy2_Y) || (nCol == nEnemy3_X && nRow == nEnemy3_Y)) {
					printf("%c", cEnemyIcon);
                } else {
					printf(" ");	
                }
            }
            printf("│"); //rightmost border
       } else {
            printf("│ │ │ │ │"); //prints a blank row
       }
       printf("%d\n", nRow); //prints the row number (starts at 1 and ends with 5)     
    }
    printf("├─┼─┼─┼─┤*\n");

    //this section is to print the player's area
	for (nCol = 1; nCol <= 4; nCol++) {
		printf("│"); //leftmost and inner borders
		if (nCol == nPlayer_X) {
			printf("%c", cPlayerIcon);
        } else {
			printf(" ");
        }
	}
	printf("│*\n"); //rightmost border
	printf("└─┴─┴─┴─┘*\n"); //prints the bottom border
	printf("Score: %d\n", nScore);
    /******************************************************************************
    EXPECTED OUTPUT
    ┌─┬─┬─┬─┐*
    │ │ │ │ │1
    │ │ │ │ │2
    │ │ │ │ │3
    │ │ │ │ │4
    │ │ │ │ │5
    ├─┼─┼─┼─┤*
    │ │ │ │ │*
    └─┴─┴─┴─┘*
    Score: 000
    ******************************************************************************/
}

/* <This function gives the player a chance in the scenario when the player fires laser in the same turn an enemy is supposed to move down>
Precondition: <nPlayer_X is a value between 1-4; nEnemy_X, nEnemy_Y, and nEnemy_AI are non-negative values;  nInput is a non-negative value>
@param <nPlayer_X> holds the player's X-coordinate in the game
@param <*nEnemy_X> holds the enemy's X-coordinate in the game
@param <*nEnemy_Y> holds the enemy's Y-coordinate in the game
@param <*nEnemy_AI> is the personal AI of the enemy
@param <nInput> holds the player's input
@return <none>
*/
void givePlayerChance(int nPlayer_X, int *nEnemy_X, int *nEnemy_Y, int *nEnemy_AI, int nInput) { 
    if (nPlayer_X == *nEnemy_X && *nEnemy_Y == 5 && nInput == 3) { //Conditions in order: If the player is in the same column as the enemy; If the enemy is in the last row; If the Player fires laser
        respawnEnemy(nEnemy_X, nEnemy_Y, nEnemy_AI);
    }
}

/* <This function checks to see whether the player is still alive by making sure the enemies' Y-coordinates have not exceeded 5>
Precondition: <nEnemy1_Y, nEnemy2_Y, and nEnemy3_Y are non-negative values>
@param <nEnemy1_Y> holds enemy 1's Y-coordinate in the game
@param <nEnemy2_Y> holds enemy 2's Y-coordinate in the game
@param <nEnemy3_Y> holds enemy 3's Y-coordinate in the game
@return <TRUE - if the player is still alive; FALSE if the player is dead>
*/
int checkPlayerLife(int nEnemy1_Y, int nEnemy2_Y, int nEnemy3_Y) {
	int nRet;
	if ((nEnemy1_Y == 6) || (nEnemy2_Y == 6) || (nEnemy3_Y == 6)) {
		nRet = FALSE; //ends the player's life :,(
	} else {
		nRet = TRUE; //player is still alive :D
    }
    return nRet;
}

/* <This is the main function of the program>
Precondition: <none>
@param <none>
@return <none>
*/
int main() {    
    int nEnemy1_X = 1, nEnemy1_Y = 1, nEnemy1_AI = 1; //initilizes Enemy 1 to the top-left
    int nEnemy2_X = 2, nEnemy2_Y = 1, nEnemy2_AI = 1; //initilizes Enemy 2 to be in-between Enemy 1 and Enemy 3
    int nEnemy3_X = 3, nEnemy3_Y = 1, nEnemy3_AI = 1; //initilizes Enemy 3 to the right of Enemy 2

    int nPlayer_X = 1; //initializes the player to be at the leftmost position
    int nScore = 0; //score starts at 0
    int nAlive = TRUE; //player starts as alive

    int nOnePunchRequirement = SCORE_FOR_PLAYER_WIN / 2; //defines the score required to use "Power Up: ONE PUNCH!"
    int nOnePunchUsed = FALSE; //initializes the value of nOnePunchUsed to false since the player has not used it yet

    int nFireActualLaserRequirement = SCORE_FOR_ENEMY_DOWN * 3; //defines the score required to use "Power Up: Fire Actual Laser"
    int nFireActualLaserUsed = FALSE; //initializes the value of nFireActualLaserUsed to false since the player has not used it yet

    int nInput = 0; //stores the user's input

    int nLoopContinues = TRUE;
    SetConsoleOutputCP(CP_UTF8); //this is so we can use unicode for the game border and dividers (Definition of CP_UTF8: https://www.freepascal.org/docs-html/rtl/system/cp_utf8.html)

    printMenu(); //prints the game menu

    printGame(nEnemy1_X, nEnemy1_Y, nEnemy2_X, nEnemy2_Y, nEnemy3_X, nEnemy3_Y, nPlayer_X, nScore); //prints the game at the beginning

    while (nLoopContinues) {
        if ((nScore < SCORE_FOR_PLAYER_WIN) && (nAlive == TRUE)) {
            printPlayerConsole(&nEnemy1_X, &nEnemy1_Y, &nEnemy2_X, &nEnemy2_Y, &nEnemy3_X, &nEnemy3_Y, &nPlayer_X, &nScore, &nEnemy1_AI, &nEnemy2_AI, &nEnemy3_AI, nOnePunchRequirement, &nOnePunchUsed, nFireActualLaserRequirement, &nFireActualLaserUsed, nInput);
            cycleEnemyMovement(&nEnemy1_X, &nEnemy1_Y, &nEnemy1_AI);
		    cycleEnemyMovement(&nEnemy2_X, &nEnemy2_Y, &nEnemy2_AI);
		    cycleEnemyMovement(&nEnemy3_X, &nEnemy3_Y, &nEnemy3_AI);
            printGame(nEnemy1_X, nEnemy1_Y, nEnemy2_X, nEnemy2_Y, nEnemy3_X, nEnemy3_Y, nPlayer_X, nScore);
            givePlayerChance(nPlayer_X, &nEnemy1_X, &nEnemy1_Y, &nEnemy1_AI, nInput);
            givePlayerChance(nPlayer_X, &nEnemy2_X, &nEnemy2_Y, &nEnemy2_AI, nInput);
            givePlayerChance(nPlayer_X, &nEnemy3_X, &nEnemy3_Y, &nEnemy3_AI, nInput);
            nAlive = checkPlayerLife(nEnemy1_Y, nEnemy2_Y, nEnemy3_Y);
        } else {
            if (nScore >= SCORE_FOR_PLAYER_WIN) {
                printf("\nCongratulations! You bought the entirety of DLSU (fictional)\n\n");
            } else if (nAlive == FALSE) {
                printf("\nYou lose!\n\n");
            }
            //The following section is for the reset feature
            int nInputReset;
            printf("\nPlay again?\n");
            printf("1 - Yes\n");
            printf("2 - No\n\n");
            printf("Input: ");
            scanf("%d", &nInputReset);

            if (nInputReset == 1) { //player enters yes
                // Resets the values of all variables

                nEnemy1_X = 1, nEnemy1_Y = 1, nEnemy1_AI = 1; //initilizes Enemy 1 to the top-left
                nEnemy2_X = 2, nEnemy2_Y = 1, nEnemy2_AI = 1; //initilizes Enemy 2 to be in-between Enemy 1 and Enemy 3
                nEnemy3_X = 3, nEnemy3_Y = 1, nEnemy3_AI = 1; //initilizes Enemy 3 to the right of Enemy 2

                nPlayer_X = 1; //initializes the player to be at the leftmost position
                nScore = 0; //score starts at 0
                nAlive = TRUE; //player starts as alive

                nOnePunchRequirement = SCORE_FOR_PLAYER_WIN / 2; //defines the score required to use "Power Up: ONE PUNCH!"
                nOnePunchUsed = FALSE; //initializes the value of nOnePunchUsed to false since the player has not used it yet

                nFireActualLaserRequirement = SCORE_FOR_ENEMY_DOWN * 3; //defines the score required to use "Power Up: Fire Actual Laser"
                nFireActualLaserUsed = FALSE; //initializes the value of nFireActualLaserUsed to false since the player has not used it yet

                nInput = 0; //stores the user's input

                printDivider();
                printf("Loading...\n"); //displays a cosmetic loading message
                printMenu(); //prints the game menu

                printGame(nEnemy1_X, nEnemy1_Y, nEnemy2_X, nEnemy2_Y, nEnemy3_X, nEnemy3_Y, nPlayer_X, nScore); //prints the game at the beginning

                nLoopContinues = TRUE; //continues the loop and resets the game
            } else if (nInputReset == 2) { //player enters no
                printDivider();
                printf("\nGoodbye!\n\n");
                printDivider();
                nLoopContinues = FALSE; //ends the game
            } else { //player enters an invalid input
                printDivider();
                printf("\nReally? ._.\n\n");
            }
        }
    }

    return 0;
}

