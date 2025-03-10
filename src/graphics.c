#include "graphics.h"
#include <stdint.h>

void set_pixel(unsigned char x, unsigned char y, unsigned char value, CHIP8 *chip8) {
	if (x < VIDEO_WIDTH && y < VIDEO_HEIGHT) {
		unsigned char byteIndex = x / 8;
		unsigned char bitIndex = x % 8;
		if (value) {
			chip8->display[y][byteIndex] |= (1 << (7 - bitIndex));
		} else {
			chip8->display[y][byteIndex] &= ~(1 << (7 - bitIndex));
		}
	}
}

void draw_display(CHIP8 *chip8) {
	const unsigned char pixelSize = 10;
	for (int y=0; y<VIDEO_HEIGHT; y++) {
		for (int x=0; x<VIDEO_WIDTH; x++) {
			unsigned char byteIndex = x/8;
			unsigned char bitIndex = x%8;
			unsigned char pixelValue = (chip8->display[y][byteIndex] >> (7 - bitIndex)) & 1;
			if (pixelValue) {
                		DrawRectangle(x * pixelSize, y * pixelSize, pixelSize, pixelSize, BLACK);
            		} else {
                		DrawRectangle(x * pixelSize, y * pixelSize, pixelSize, pixelSize, WHITE);
            		}
		}
	}
}
int posx =  31;
void create_window(CHIP8 *chip8) {
	if (IsKeyDown(KEY_ONE)) {
         	printf("1 is pressed\n");
        }
	if (IsKeyDown(KEY_TWO)) {
         	printf("2 is pressed\n");
        }
	if (IsKeyDown(KEY_THREE)) {
            	printf("3 is pressed\n");
        }
	if (IsKeyDown(KEY_FOUR)) {
            	printf("4 is pressed\n");
        }
	if (IsKeyDown(KEY_Q)) {
            	printf("Q is pressed\n");
        }
	if (IsKeyDown(KEY_W)) {
            	printf("W is pressed\n");
        }
	if (IsKeyDown(KEY_E)) {
            	printf("E is pressed\n");
        }
	if (IsKeyDown(KEY_R)) {
           	printf("R is pressed\n");
        }
	if (IsKeyDown(KEY_A)) {
            	printf("A is pressed\n");
		posx--;
        }
	if (IsKeyDown(KEY_S)) {
            	printf("S is pressed\n");
        }
	if (IsKeyDown(KEY_D)) {
            	printf("D is pressed\n");
		posx++;
        }
	if (IsKeyDown(KEY_F)) {
            	printf("F is pressed\n");
        }
	if (IsKeyDown(KEY_Z)) {
            	printf("Z is pressed\n");
        }
	if (IsKeyDown(KEY_X)) {
            	printf("X is pressed\n");
        }
	if (IsKeyDown(KEY_C)) {
            	printf("C is pressed\n");
        }
	if (IsKeyDown(KEY_V)) {
            	printf("V is pressed\n");
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
	for (int y=0; y<VIDEO_HEIGHT; y++) {
		for (int x=0; x<VIDEO_WIDTH; x++) {
			set_pixel(x, y, 0, chip8);
		}
	}
	set_pixel(posx, 15, 1, chip8);
	draw_display(chip8);
        EndDrawing();
}

