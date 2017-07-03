#include <stdio.h>
/*
 * This is a mini program that opens a file for
 * "writing".
 *
 * This effectively clears an entire file.
 */

int main(int argc, char** argv){
	FILE* f;
	f = fopen(argv[1],"w");
	fclose(f);
	return 0;
}
