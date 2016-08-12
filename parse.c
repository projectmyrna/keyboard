#include <stdio.h>
#include <stdint.h>
#include "parseKey.h"

uint16_t digittoascii(uint16_t digit) {
	if (digit >=0 && digit <= 9) {
		return	digit+48;
	}
	else return digit+55;
}
uint16_t convert(uint16_t RAW_VALUE) {
	return digittoascii(RAW_VALUE/16) + 256*digittoascii(RAW_VALUE%16);
}

int main(int argc, char** argv) {
	FILE *fp;
	if (argc < 2) {
		fprintf(stderr, "Enter a input filename. Exiting...\n");
		return(-1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open file. Exiting...\n");
		return(-1);
	}

	char line[128];
	KeyInfo rawkey;
	uint16_t modifiers[4], keys[4];
	for (int i=0; i<4; i++) {
		fgets(line, 128, fp);
		rawkey = ParseKeyInfo(line);
		modifiers[i] = convert(rawkey.Modifier);
		keys[i] = convert(rawkey.Key);
	}
	fclose(fp);

	// Reset file pointer
	fp = NULL;

	// Open hex file for in-place editing
	fp = fopen("keyboard.cpp.hex", "r+b");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open hex file. Exiting...\n");
		return(-1);
	}

	fseek(fp, 9042, SEEK_SET);
	// uint16_t modifiers[4] = {convert(0), convert(0), convert(0), convert(0)};
	// uint16_t keys[4] = {convert(KEY_UP_ARROW), convert(KEY_UP_ARROW), convert(KEY_DOWN_ARROW), convert(KEY_LEFT_ARROW)};
	fwrite (modifiers, sizeof(uint16_t), 4, fp);
	fwrite (keys, sizeof(uint16_t), 4, fp);
	printf("Modifiers\n");
	for (int i = 0; i < 4; i++) {
		printf("\t%d %d\n", (modifiers[i]/256), (modifiers[i]%256) );
	}
	printf("Keys\n");
	for (int i = 0; i < 4; i++) {
		printf("\t%x %x\n", (keys[i]/256), (keys[i]%256) );
	}
	fclose(fp);
	return 0;
}