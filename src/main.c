#include "JogoDaVelha.h"
#include <raylib.h>

int main(int argc, char const *argv[]){
	jogoInit(1000, 700);
	while(!WindowShouldClose()){
		jogoInput();

		BeginDrawing();
			ClearBackground(BLACK);
			jogoRender();
		EndDrawing();
	}

	jogoEnd();

	return 0;
}