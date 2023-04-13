#include "JogoDaVelha.h"
#include <raylib.h>

#define BASEOFFSET 25u
#define LETTEROFFSET 20u

int tabuleiro[3][3];
int width, height;
int lineSize, sideDiff, thirdDist;
int fontSize;
Rectangle posClick[3][3];
Rectangle restartClick;
char turn;
char end;

void jogoInit(int win_width, int win_height){
	width = win_width;
	height = win_height;

	restartClick.x = (width/2)-200;
	restartClick.y = (height/2)-50;
	restartClick.width = 400;
	restartClick.height = 100;

	if(width>height){
		lineSize = height-50;
		sideDiff = (width-height)/2;
		thirdDist = lineSize/3;
		fontSize = height/3;
	}
	else{
		lineSize = width-50;
		sideDiff = (height-width)/2;
		thirdDist = lineSize/3;
		fontSize = width/3;
	}
	
	for(int i=0; i<3; ++i)
	for(int j=0; j<3; ++j){
		tabuleiro[i][j] = 0;
		if(width>height){
			posClick[i][j].x = sideDiff+BASEOFFSET+LETTEROFFSET+(i*lineSize/3);
			posClick[i][j].y = BASEOFFSET+LETTEROFFSET+(j*lineSize/3);
			posClick[i][j].width = (lineSize/3)-(LETTEROFFSET*2);
			posClick[i][j].height = (lineSize/3)-(LETTEROFFSET*2);
		}
		else{
			posClick[i][j].x = BASEOFFSET+LETTEROFFSET+(i*lineSize/3);
			posClick[i][j].y = sideDiff+BASEOFFSET+LETTEROFFSET+(j*lineSize/3);
			posClick[i][j].width = (lineSize/3)-(LETTEROFFSET*2);
			posClick[i][j].height = (lineSize/3)-(LETTEROFFSET*2);
		}
	}

	InitWindow(win_width, win_height, "JOGO DA VELHA");
	SetTargetFPS(60);
	turn = 0;
	end = 0;
}

void jogoDrawSymbol(char type, int x, int y, int w, int h, Color color){
	switch(type){
	case '/':
		DrawLine(x, y, x+w, y+h, color);
		break;

	case 'x':
		DrawLine(x, y, x+w, y+h, color);
		DrawLine(x, y+h, x+w, y, color);
		break;

	case 'o':
		DrawCircleLines(x+(w/2), y+(h/2), w/2, color);
		break;
	
	default:
		return;
	}
}

void jogoRender(){

	if(width>height){
		DrawRectangleLines(sideDiff+10, 10, height-20, height-20, WHITE);
		
		DrawLine(sideDiff+BASEOFFSET, thirdDist+BASEOFFSET, lineSize+sideDiff+BASEOFFSET, thirdDist+BASEOFFSET, WHITE);
		DrawLine(sideDiff+BASEOFFSET, (thirdDist*2)+BASEOFFSET, lineSize+sideDiff+BASEOFFSET, (thirdDist*2)+BASEOFFSET, WHITE);
		DrawLine(sideDiff+thirdDist+BASEOFFSET, BASEOFFSET, sideDiff+thirdDist+BASEOFFSET, lineSize+BASEOFFSET, WHITE);
		DrawLine(sideDiff+(thirdDist*2)+BASEOFFSET, BASEOFFSET, sideDiff+(thirdDist*2)+BASEOFFSET, lineSize+BASEOFFSET, WHITE);
	
		for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j){
			switch (tabuleiro[i][j]){
			// case 0:
				// jogoDrawSymbol('/', posClick[i][j].x, posClick[i][j].y, posClick[i][j].width, posClick[i][j].height, WHITE);
				// break;

			case 1:
				jogoDrawSymbol('x', posClick[i][j].x, posClick[i][j].y, posClick[i][j].width, posClick[i][j].height, RED);
				break;

			case 2:
				jogoDrawSymbol('o', posClick[i][j].x, posClick[i][j].y, posClick[i][j].width, posClick[i][j].height, BLUE);
				break;

			default:
				break;
			}
		}
	}
	else{
		DrawRectangleLines(10, sideDiff+10, width-20, width-20, WHITE);

		DrawLine(thirdDist+BASEOFFSET, sideDiff+BASEOFFSET, thirdDist+BASEOFFSET, lineSize+sideDiff+BASEOFFSET, WHITE);
		DrawLine((thirdDist*2)+BASEOFFSET, sideDiff+BASEOFFSET, (thirdDist*2)+BASEOFFSET, lineSize+sideDiff+BASEOFFSET, WHITE);
		DrawLine(BASEOFFSET, sideDiff+thirdDist+BASEOFFSET, lineSize+BASEOFFSET, sideDiff+thirdDist+BASEOFFSET, WHITE);
		DrawLine(BASEOFFSET, sideDiff+(thirdDist*2)+BASEOFFSET, lineSize+BASEOFFSET, sideDiff+(thirdDist*2)+BASEOFFSET, WHITE);
	
		for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j){
			switch (tabuleiro[i][j]){
			// case 0:
				// jogoDrawSymbol('/', posClick[i][j].x, posClick[i][j].y, posClick[i][j].width, posClick[i][j].height, WHITE);
				// break;

			case 1:
				jogoDrawSymbol('x', posClick[i][j].x, posClick[i][j].y, posClick[i][j].width, posClick[i][j].height, RED);
				break;

			case 2:
				jogoDrawSymbol('o', posClick[i][j].x, posClick[i][j].y, posClick[i][j].width, posClick[i][j].height, BLUE);
				break;

			default:
				break;
			}
		}
	}

	if(end){
		DrawRectangleRec(restartClick, BLACK);
		DrawRectangleLinesEx(restartClick, 2.0f, WHITE);
		DrawText("Restart?", restartClick.x+10, restartClick.y+10, restartClick.height-20, WHITE);
	}
}

int jogoCheckWin(){
	int curr = 0;
	int win = 0;
	
	for(int i=0; i<3; ++i){
		curr = tabuleiro[i][0];
		if(curr==0)
			continue;
		
		for(int j=1; j<3; ++j){
			if(curr!=tabuleiro[i][j]){
				curr = -1;
				break;
			}
		}

		if(curr!=-1)
			win = 1;
	}

	if(win)
		return 1;

	for(int i=0; i<3; ++i){
		curr = tabuleiro[0][i];
		if(curr==0)
			continue;

		for(int j=1; j<3; ++j){
			if(curr!=tabuleiro[j][i]){
				curr = -1;
				break;
			}
		}

		if(curr!=-1)
			win = 1;
	}

	if(win)
		return 1;
	
	if(tabuleiro[0][0]!=0 && tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[0][0]==tabuleiro[2][2])
		return 1;
	if(tabuleiro[0][2]!=0 && tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[0][2]==tabuleiro[2][0])
		return 1;
	
	return 0;
}

void jogoReset(){
	for(int i=0; i<3; ++i)
	for(int j=0; j<3; ++j)
		tabuleiro[i][j] = 0;
		
	turn = 0;
	end = 0;
}

void jogoInput(){
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
		Vector2 pos = GetMousePosition();
		for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j){
			if(CheckCollisionPointRec(pos, posClick[i][j]) && tabuleiro[i][j]==0){
				if(!turn)
					tabuleiro[i][j] = 1;
				else
					tabuleiro[i][j] = 2;

				if(jogoCheckWin())
					end = 1;
				
				turn = !turn;
			}
		}

		if(CheckCollisionPointRec(pos, restartClick) && end)
			jogoReset();
	}
}

void jogoEnd(){
	CloseWindow();
}