#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>

const int PADDLE_SIZE = 5;

bool game_on = true;

char player_1_score = '0';
char player_2_score = '0';

//board
struct board {
	/*
                                         |20                 |40                 |60                 |80                 |100                
	*/
	char line1[119]  = {   "##################################################    0   -   0    ##################################################" };
	char line2[119]  = { "\n#                                                         |                                                         #" };
	char line3[119]  = { "\n#                                                         |                                                         #" };
	char line4[119]  = { "\n#                                                         |                                                         #" };
	char line5[119]  = { "\n#                                                         |                                                         #" };
	char line6[119]  = { "\n#                                                         |                                                         #" };
	char line7[119]  = { "\n#                                                         |                                                         #" };
	char line8[119]  = { "\n#                                                         |                                                         #" };
	char line9[119]  = { "\n#                                                         |                                                         #" };
	char line10[119] = { "\n#                                                         |                                                         #" };
	char line11[119] = { "\n#                                                         |                                                         #" };
	char line12[119] = { "\n#                                                         /\\                                                        #" };
	char line13[119] = { "\n#                                                       /    \\                                                      #" };
	char line14[119] = { "\n#                                                     /        \\                                                    #" };
	char line15[119] = { "\n#                                                    |    |     |                                                   #" };
	char line16[119] = { "\n#                                                     \\        /                                                    #" };
	char line17[119] = { "\n#                                                       \\    /                                                      #" };
	char line18[119] = { "\n#                                                         \\/                                                        #" };
	char line19[119] = { "\n#                                                         |                                                         #" };
	char line20[119] = { "\n#                                                         |                                                         #" };
	char line21[119] = { "\n#                                                         |                                                         #" };
	char line22[119] = { "\n#                                                         |                                                         #" };
	char line23[119] = { "\n#                                                         |                                                         #" };
	char line24[119] = { "\n#                                                         |                                                         #" };
	char line25[119] = { "\n#                                                         |                                                         #" };
	char line26[119] = { "\n#                                                         |                                                         #" };
	char line27[119] = { "\n#                                                         |                                                         #" };
	char line28[119] = { "\n#                                                         |                                                         #" };
	char line29[119] = { "\n#                                                         |                                                         #" };
	char line30[119] = { "\n#####################################################################################################################" };

	char* rows[30] = { line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,
		line11,line12,line13,line14,line15,line16,line17,line18,line19,line20,
		line21,line22,line23,line24,line25,line26,line27,line28,line29,line30 };
};

struct paddle {
	int top = 13;
	int bottom = top + PADDLE_SIZE;
	int dir = 0;
};

struct ball {
	double x = 60;
	double y = 14;
	double x_speed = -1;
	double y_speed = -0.5;
};

void draw(board*, paddle* , paddle*, ball*);
void move_ball(ball*, paddle*, paddle*);

void main() {
	paddle *left = new paddle;
	paddle *right = new paddle;



	while (player_1_score != 5 || player_2_score != 5) {

		ball *new_ball = new ball;
		while (game_on) {
			board *play_area = new board;

			if (GetAsyncKeyState(0x41)) {
				if (left->top != 1) {
					left->top--;
					left->bottom--;
				}
			}
			if (GetAsyncKeyState(0x5A)) {
				if (left->bottom != 29) {
					left->top++;
					left->bottom++;
				}
			}
			if (GetAsyncKeyState(0x4B)) {
				if (right->top != 1) {
					right->top--;
					right->bottom--;
				}
			}
			if (GetAsyncKeyState(0x4D)) {
				if (right->bottom != 29) {
					right->top++;
					right->bottom++;
				}
			}


			move_ball(new_ball, left, right);
			draw(play_area, left, right, new_ball);
			Sleep(10);
		}

		std::cout << '3';
		Sleep(1000); 
		std::cout << '2';
		Sleep(1000); 
		std::cout << '1';
		Sleep(1000);
		game_on = true;
		
	}
}

void draw(board *board, paddle *left, paddle *right, ball *ball) {
	system("cls");

	board->rows[0][54] = player_1_score; 
	board->rows[0][62] = player_2_score;

	for (int i = 0; i < PADDLE_SIZE; i++) {
		(board->rows[i + left->top])[4] = '|';
		(board->rows[i + right->top])[114] = '|';
	}

	board->rows[(int)ball->y][(int)ball->x] = 'O';

	std::cout << board->line1 << board->line2 << board->line3 << board->line4 << board->line5 << board->line6 << board->line7 << board->line8
		<< board->line9 << board->line10 << board->line11 << board->line12 << board->line13 << board->line14 << board->line15 << board->line16
		<< board->line17 << board->line18 << board->line19 << board->line20 << board->line21 << board->line22 << board->line23 << board->line24
		<< board->line25 << board->line26 << board->line27 << board->line28 << board->line29 << board->line30;
}


void move_ball(ball* ball, paddle* left, paddle* right) {
	
	
	ball->x = ball->x + ball->x_speed;
	ball->y = ball->y + ball->y_speed;
	
	if ((int)ball->y == 1 || (int)ball->y == 28) {
		ball->y_speed= ball->y_speed * (-1);
	}
	
	if ((int)ball->x == 5 && (int)ball->y > left->top && (int)ball->y < left->bottom) {

		ball->x_speed = ball->x_speed * (-1);
		if (ball->y == left->top) {
			ball->y_speed = ball->y_speed - 5;
		}
		else if (ball->y == left->top + 1) {
			ball->y_speed = ball->y_speed - 2.5;
		}
		else if (ball->y == left->bottom-1) {
			ball->y_speed = ball->y_speed + 2.5;
		}
		else if (ball->y == left->bottom) {
			ball->y_speed = ball->y_speed + 5;
		}
	}
	else if ((int)ball->x == 113 && (int)ball->y > right->top && (int)ball->y < right->bottom) {
		ball->x_speed = ball->x_speed * (-1);
		if (ball->y == right->top) {
			ball->y_speed = ball->y_speed - 5;
		}
		else if (ball->y == right->top + 1) {
			ball->y_speed = ball->y_speed - 2.5;
		}
		else if (ball->y == right->bottom - 1) {
			ball->y_speed = ball->y_speed + 2.5;
		}
		else if (ball->y == right->bottom) {
			ball->y_speed = ball->y_speed + 5;
		}
	}
	if ((int)ball->x == 1) {
		player_2_score++;
		game_on = false;
		return;
	}else if ((int)ball->x == 117) {
		player_1_score++;
		game_on = false;
		return;
	}

}