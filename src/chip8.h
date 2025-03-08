#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>

#define MEMORY_SIZE 4096
#define REGISTER_COUNT 16
#define STACK_SIZE 16
#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32
#define KEYPAD_SIZE 16

typedef struct {
	uint8_t memory[MEMORY_SIZE];
	uint8_t V[REGISTER_COUNT];
	uint16_t I;
	uint16_t PC;
	uint8_t delay_timer;
	uint8_t sound_timer;
	uint16_t stack[STACK_SIZE];
	uint8_t SP;
	uint8_t display[VIDEO_WIDTH * VIDEO_HEIGHT];
	uint8_t keypad[KEYPAD_SIZE];
} CHIP8;

void initialize_chip8(CHIP8* chip8);
int load_rom(CHIP8* chip8, const char* filename);
void execute_instruction(CHIP8* chip8);
void draw_screen(CHIP8* chip8);





