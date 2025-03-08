#include "chip8.h"

void initialize_chip8(CHIP8 *chip8) {
	memset(chip8, 0, sizeof(CHIP8));
	chip8->PC = 0x200;
	chip8->SP = 0;
	srand(time(NULL));
}

int load_rom(CHIP8 *chip8, const char *filename) {
	FILE *inst = fopen(filename, "rb");
	if (!inst) {
		perror("failed to read file\n");
		return -1;
	}
	size_t bytesRead = fread(&(chip8->memory[chip8->PC]), 1, 4096 - chip8->PC, inst);
	if (bytesRead == 0) {
		perror("Failed to read file");
	}
	fclose(inst);
	return ((int)bytesRead) / 2;
}

void execute_instruction(CHIP8 *chip8) {
	uint16_t opcode = chip8->memory[chip8->PC] << 8 | chip8->memory[chip8->PC + 1];
	chip8->PC += 2;
	if (opcode == 0x00E0) 1; //clear_screen()
	if (opcode == 0x00EE) chip8->PC = chip8->stack[chip8->SP];
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t nnn = opcode & 0x0FFF;
	uint8_t nn = opcode & 0x00FF;
	uint8_t n = opcode & 0x000F;
	switch (opcode & 0xF000) {
		case 0x1000:
			chip8->PC = nnn;
			break;
		case 0x2000:	
			chip8->stack[chip8->SP] = chip8->PC;
			chip8->PC = nnn;
			break;
		case 0x3000:
			if (chip8->V[Vx] == nn) {
				chip8->PC += 2;
			}
			break;
		case 0x4000:
			if (chip8->V[Vx] != nn) {
				chip8->PC += 2;
			}
			break;
		case 0x5000:
			if (chip8->V[Vx] == chip8->V[Vy]) {
				chip8->PC += 2;
			}
			break;
		case 0x6000:
			chip8->V[Vx] = nn;
			printf("value at v%d: %d\n", Vx, chip8->V[Vx]);
			break;
		case 0x7000:
			chip8->V[Vx] += nn;
			break;
		case 0x8000:
			switch (n) {
				case 0:
					chip8->V[Vx] = chip8->V[Vy];
					break;
				case 1:
					chip8->V[Vx] = chip8->V[Vx] | chip8->V[Vy]; 
					break;
				case 2:
					chip8->V[Vx] = chip8->V[Vx] & chip8->V[Vy]; 
					break;
				case 3:
					chip8->V[Vx] = chip8->V[Vx] ^ chip8->V[Vy]; 
					break;
				case 4:
					if (chip8->V[Vx] + chip8->V[Vy] > 256) chip8->V[15] = 1;
					chip8->V[Vx] += chip8->V[Vy];
					break;
				case 5:
					chip8->V[15] = 0;
					chip8->V[Vx] -= chip8->V[Vy];
					break;
				case 6:
					break;
				case 7:
					break;
				case 14:
					break;
				default:	
					printf("unknown opcode at 0x8000 :((\n");
			}
		case 0x9000:
			if (chip8->V[Vx] != chip8->V[Vy]) {
				chip8->PC += 2;
			}
			break;
		case 0xA000:
			chip8->I = nnn;
			break;
		case 0xB000:
			chip8->PC = nnn + chip8->V[0];
			break;
		case 0xC000: {
			uint8_t r = rand();
			printf("%d\n", r);
			chip8->V[Vx] = r & nn; 
			break;
		}
		case 0xD000: 
    		break;
		default:
			printf("unknown opcode :((\n");
	}

}
