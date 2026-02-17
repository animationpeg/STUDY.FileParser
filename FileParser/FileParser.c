#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PEOPLE 100

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

	Person people[MAX_PEOPLE];
	int person_count = 0;

	// Parse the file and extract the information into the Person structure
	Person p;
	char line[256];
	Person current = {0};
	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = 0; // Remove the newline character from the end of the line

		// Check for an empty line, which indicates the end of a person's information
		if (strlen(line) == 0)
		{
			// Save person
			people[person_count++] = current;
			// Reset for the next person
			memset(&current, 0, sizeof(Person));
		}

		// Parse the line to extract the key and value, assuming the format is "key:value"
		char* key = strtok(line, ":");
		char* value = strtok(NULL, ":");

		if (!key || !value) continue; // Skip lines that don't have both key and value

		while (*value == ' ') value++; // Trim leading spaces from the value)

		// Store the extracted information in the Person structure based on the key
		if (strcmp(key, "name") == 0)
		{
			snprintf(current.name, sizeof(current.name), "%s", value); // Safely copy the name to the 
		}
		else if (strcmp(key, "age") == 0)
		{
			current.age = atoi(value); // Convert age from string to integer
		}
		else if (strcmp(key, "city") == 0)
		{
			snprintf(current.city, sizeof(current.city), "%s", value); // Safely copy the city to the structure
		}
	}

	// If the file does not end with an empty line, the last person's information will not be added to the array, so we need to check for that and add it if necessary.
	if (current.name[0] != "\0")
	{
		people[person_count++] = current;
	}

	// Close the file before ending the program
	fclose(file);

	// Loop through the people array and print the information of each person to the console
	for (int i = 0; i < person_count; i++)
	{
		printf("Name: %s, Age: %d, City: %s\n", people[i].name, people[i].age, people[i].city);
	}

	return 0;
}
