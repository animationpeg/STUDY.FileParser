#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct // Data structure to hold the information of a person, taken from the sample file
{
	char name[50];
	int age;
	char city[50];
} Person;

int main()
{
	// Load the file into memory
	FILE* file = fopen("data.txt", "r");

	// Check if the file was opened successfully. Exit with error if it was not.
	if (file == NULL)
	{
		printf("Error opening file\n");
		return 1;
	}

	// Read the file line by line and print its contents to the console
	Person p;
	char line[256];

	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = 0; // Remove the newline character from the end of the line

		// Parse the line to extract the key and value, assuming the format is "key:value"
		char* key = strtok(line, ":");
		char* value = strtok(NULL, ":");

		if (!key || !value) continue; // Skip lines that don't have both key and value

		while (*value == ' ') value++; // Trim leading spaces from the value)

		// Store the extracted information in the Person structure based on the key
		if (strcmp(key, "name") == 0)
		{
			snprintf(p.name, sizeof(p.name), "%s", value); // Safely copy the name to the 
		}
		else if (strcmp(key, "age") == 0)
		{
			p.age = atoi(value); // Convert age from string to integer
		}
		else if (strcmp(key, "city") == 0)
		{
			snprintf(p.city, sizeof(p.city), "%s", value); // Safely copy the city to the structure
		}
	}

	// Close the file before ending the program
	fclose(file);
	
	printf("person: %s (%d) from %s\n", p.name, p.age, p.city);

	return 0;
}
