#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct // Data structure to hold the information of a person, taken from the sample file
{
	char name[50];
	int age;
	char city[50];
} Person;

// Function to parse the file and extract the information into the Person structure, returning the number of people parsed
int parse_file(const char* filename, Person** people_out)
{
    if (!people_out)
	{
        fprintf(stderr, "parse_file: people_out is NULL\n");
        return -1;
    }
	// Load the file into memory
	FILE* file = fopen(filename, "r");
	// Check if the file was opened successfully. Exit with error if it was not.
	if (!file) {
		printf("Error opening file\n");
		return -1;
	}

	Person* people = NULL; // Declare a pointer to an array of Person structures
	int count = 0;
	int capacity = 0;
	char line[256];
	Person current = {0};

	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = 0; // Remove the newline character from the end of the line

		// Check for an empty line, which indicates the end of a person's information
		if (strlen(line) == 0)
		{
			if (current.name[0] != '\0') // Check if we have a valid person to add (name is not empty)
			{
				if (count >= capacity) // Check if we need to increase the capacity of the people array
				{
					capacity = (capacity == 0) ? 4 : capacity * 2; // Double the capacity if needed, starting with an initial capacity of 4

					Person* temp = realloc(people, capacity * sizeof(Person)); // Reallocate memory for the people array
					
					if (!temp) // Check if realloc succeeded
					{
						printf("Memory allocation failed\n");
						free(people); // Free previously allocated memory before exiting
						fclose(file);
						return -1;
					}
					people = temp; // Update the people pointer to the newly allocated memory
				}

				people[count++] = current; // Save person
				memset(&current, 0, sizeof(Person)); // Use memset to clear the current structure for the next person's information
			}
			continue;
		}

		// Parse the line to extract the key and value, assuming the format is "key:value"
		char* key = strtok(line, ":");
		char* value = strtok(NULL, ":");

		// Skip lines that don't have both key and value
		if (!key || !value) 
		{
			fprintf(stderr, "Invalid line format: %s\n", line);
			continue; 
		}

		while (*value == ' ') value++; // Trim leading spaces from the value

		// Trim trailing whitespace (spaces, tabs, CR, LF) from value
		size_t vlen = strlen(value);
		while (vlen > 0 && (value[vlen - 1] == ' ' || value[vlen - 1] == '\t' || value[vlen - 1] == '\r' || value[vlen - 1] == '\n'))
		{
			value[--vlen] = '\0';
		}

		if (strcmp(key, "name") == 0)
		{
			snprintf(current.name, sizeof(current.name), "%s", value); // Safely copy the name to the structure
		}
		else if (strcmp(key, "age") == 0)
		{
			char* endptr; // Declare a pointer for error checking in strtol
			long age = strtol(value, &endptr, 10); // Convert age from string to long integer with error checking

			if (*endptr != '\0' || age < 0 || age > 150) // Check if the conversion was successful and if the age is within a reasonable range
			{
				fprintf(stderr, "Invalid age value: %s\n", value);
				continue; // Skip this line if the age value is invalid
			}
			current.age = (int)age; // Convert age from string to integer
		}
		else if (strcmp(key, "city") == 0)
		{
			snprintf(current.city, sizeof(current.city), "%s", value); // Safely copy the city to the structure
		}
	}

	// If the file does not end with an empty line, the last person's information will not be added to the array, so we need to check for that and add it if necessary.
	if (current.name[0] != '\0')
	{
		if (count >= capacity) // Check if we need to increase the capacity of the people array
		{
			capacity = (capacity == 0) ? 4 : capacity * 2; // Double the capacity if needed, starting with an initial capacity of 4

			Person* temp = realloc(people, capacity * sizeof(Person)); // Reallocate memory for the people array

			if (!temp) // Check if realloc succeeded
			{
				printf("Memory allocation failed\n");
				free(people); // Free previously allocated memory before exiting
				fclose(file);
				return -1;
			}
			people = temp; // Update the people pointer to the newly allocated memory
		}
		people[count++] = current; // Save person
	}

	fclose(file);
	*people_out = people;
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

	Person *people = NULL;

	// Parse the file and extract the information into the people array, returning the number of people parsed
	int count = parse_file(argv[1], &people);

	// Check if the file was parsed successfully. If not, exit with error.
	if (count < 0)
	{
		return 1;
	}
	// Loop through the people array and print the information of each person to the console
	print_people(people, count);

	free(people); // Free the allocated memory for the people array

	return 0;
}
