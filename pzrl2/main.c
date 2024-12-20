#include "red.h"
#include <stdio.h>
#include <stdlib.h>

void print_usage(const char *program_name) {
	fprintf(stderr, "Usage: %s <file> '<operation>'\n", program_name);
	fprintf(stderr, "Examples:\n");
	fprintf(stderr, "  %s input.txt 's/old/new/'\n", program_name);
	fprintf(stderr, "  %s input.txt '/regex/d'\n", program_name);
	fprintf(stderr, "  %s input.txt 's/^/prefix/'\n", program_name);
	fprintf(stderr, "  %s input.txt 's/$/suffix/'\n", program_name);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		print_usage(argv[0]);
			return 1;
}

const char *file_path = argv[1];
	const char *operation = argv[2];

if (process_file(file_path, operation) != 0) {
	fprintf(stderr, "Error: Unable to process file.\n");
		return 1;
}

return 0;
}
