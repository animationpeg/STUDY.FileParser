#include <stdio.h>

int main()
{
	// Load the file into memory
	FILE *file = fopen("data.txt", "r");

	// Check if the file was opened successfully. Exit with error if it was not.
	if (file == NULL)
	{
		printf("Error opening file\n");
		return 1;
	}

	// Read the file line by line and print it to the console
	char line[256];
	while (fgets(line, sizeof(line), file))
	{
		printf("%s", line);
	}

	// Close the file before ending the program
	fclose(file);
	return 0;
}
