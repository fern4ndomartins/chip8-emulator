#include "chip8.h"
#include "graphics.h"
#include <raylib.h>

int main(int argc, char * argv[]) {
	const char * filename = argv[1];
	CHIP8 chip8;
	initialize_chip8(&chip8);
	int size = load_rom(&chip8, filename);
	InitWindow(640, 320, "Chip-8 Emulator");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		create_window();	
	}
	CloseWindow();
	printf("\e[1;1H\e[2J");
	for (int i=0; i<size; i++) {
		execute_instruction(&chip8);
	}
	return 0;
}

