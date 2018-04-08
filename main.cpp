/*
 * main.cpp
 *
 */

#include "Table.h"

#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
	std::string filename;
	
	Table hash_table;

	if (argc == 2) { // if there is a filename on the command line
		hash_table.read_lyrics(argv[1],true);
	}
	else { // use a pre-defined filename
		filename = "lyrics_fulldb.txt";
		//filename = "lyrics_fulldb.txt";
		
		// read lyrics into song vector
	    hash_table.read_lyrics(filename.c_str(),true);
	}
	
	// fill hash table with data from song vector
    hash_table.fillTable();
        
	// take user input
	string input;
        cin >> input;
	
	// wait for user input, end program if BREAK
	while (input != "BREAK") {
	    hash_table.printWord(alpha_only(input));
	    cin >> input;
	}
	    
	return 0;
}