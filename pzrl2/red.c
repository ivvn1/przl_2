#include "red.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int process_file(const char *file_path, const char *operation) {
	FILE *file = fopen(file_path, "r+");
		if (!file) {
			perror("Failed to open file");
				        return -1;
}

regex_t regex;
	char buffer[MAX_LINE_LEN];
		char new_content[MAX_LINE_LEN * 100] = {0};
			char *pattern, *replacement;

if (strncmp(operation, "s/", 2) == 0) {
	        char *start = strchr(operation + 2, '/');
		        char *end = start ? strchr(start + 1, '/') : NULL;

if (!start || !end || end == start + 1) {
	fprintf(stderr, "Invalid substitution syntax.\n");
		fclose(file);
			return -1;
}

*start = '\0';
*end = '\0';

pattern = (char *)(operation + 2);
	replacement = start + 1;

if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
	fprintf(stderr, "Invalid regex pattern.\n");
		fclose(file);
			return -1;
}

while (fgets(buffer, sizeof(buffer), file)) {
	char result[MAX_LINE_LEN] = {0};
		char *start = buffer;
			regmatch_t pmatch;

while (regexec(&regex, start, 1, &pmatch, 0) == 0) {
	strncat(result, start, pmatch.rm_so);
		strcat(result, replacement);
			start += pmatch.rm_eo;
}
strcat(result, start);
	strcat(new_content, result);
}
regfree(&regex);

} else if (strncmp(operation, "/", 1) == 0 && strstr(operation, "/d")) {
pattern = strtok((char *)operation + 1, "/");
	if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
		fprintf(stderr, "Invalid deletion syntax.\n");
			fclose(file);
				return -1;
}

while (fgets(buffer, sizeof(buffer), file)) {
	if (regexec(&regex, buffer, 0, NULL, 0) != 0) {
		strcat(new_content, buffer);
}
	}
regfree(&regex);

} else if (strncmp(operation, "s/^", 3) == 0) {
	replacement = strtok((char *)operation + 3, "/");
		while (fgets(buffer, sizeof(buffer), file)) {
			strcat(new_content, replacement);
				strcat(new_content, buffer);
}

} else if (strncmp(operation, "s/$", 3) == 0) {
	replacement = strtok((char *)operation + 3, "/");
		while (fgets(buffer, sizeof(buffer), file)) {
			buffer[strcspn(buffer, "\n")] = 0;
				strcat(new_content, buffer);
					strcat(new_content, replacement);	
						strcat(new_content, "\n");	
}


} else {
	fprintf(stderr, "Invalid operation.\n");
		fclose(file);
			return -1;
}

freopen(file_path, "w", file);
	fputs(new_content, file);
	    fclose(file);
	        return 0;
}
