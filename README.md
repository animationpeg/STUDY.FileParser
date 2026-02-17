# STUDY.FileParser
•	A small C command-line utility that reads a simple key/value text file and prints parsed person records.
•	Input format: blocks of lines with key:value pairs (name, age, city) separated by a blank line. Example: name: Alice age: 30 city: London
name: Bob age: 25 city: Manchester
•	Behavior: parse_file loads and parses the file into a dynamically allocated array of Person structures; print_people prints each record. The program returns non-zero on error.
•	Build / run:
•	Build with your C toolchain (Visual Studio project included) or gcc FileParser.c -o FileParser.
•	Run: FileParser <input-file> (Windows: FileParser.exe <input-file>).
•	Notes: input values are trimmed; invalid lines or ages are logged to stderr. Memory allocated by parse_file is freed on exit.
