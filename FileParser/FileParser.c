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

// Function to parse the file and extract the information into the Person structure, returning the number of people parsed
int parse_file(const char* filename, Person people[], int max_people)
{
	// Load the file into memory
	FILE* file = fopen(filename, "r");
	// Check if the file was opened successfully. Exit with error if it was not.
	if (!file) {
		printf("Error opening file\n");
		return 0;
	}

	char line[256];
	Person current = {0};
	int count = 0;

	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = 0; // Remove the newline character from the end of the line

		// Check for an empty line, which indicates the end of a person's information
		if (strlen(line) == 0)
		{
			if (count < max_people) // Check if we have space in the array before adding the person
			{
				people[count++] = current; // Save person
			}
			memset(&current, 0, sizeof(Person)); // Use memset to clear the current structure for the next person's information
			continue;
		}

		// Parse the line to extract the key and value, assuming the format is "key:value"
		char* key = strtok(line, ":");
		char* value = strtok(NULL, ":");

		if (!key || !value) continue; // Skip lines that don't have both key and value

		while (*value == ' ') value++; // Trim leading spaces from the value

		if (strcmp(key, "name") == 0)
		{
			snprintf(current.name, sizeof(current.name), "%s", value); // Safely copy the name to the structure
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
	if (current.name[0] != '\0' && count < max_people)
	{
		people[count++] = current;
	}

	fclose(file);
	return count;
}

// Function to loop through the people array and print the information of each person to the console
void print_people(Person people[], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("Person %d: %s (%d) - %s\n", i + 1, people[i].name, people[i].age, people[i].city);
	}
}

int main(int argc, char* argv[])
{
	// Check if the filename is provided as a command-line argument. If not, print usage information and exit with error.
	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	Person people[100];

	// Parse the file and extract the information into the people array, returning the number of people parsed
	int count = parse_file(argv[1], people, MAX_PEOPLE);

	// Loop through the people array and print the information of each person to the console
	print_people(people, count);

	return 0;
}
