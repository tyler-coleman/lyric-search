## Song Search 

1.  The purpose of this program is to allow the searching of a large database
    of songs and their lyrics via user input. When the user types a word, the
    program prints the top 10 songs with the greatest occurrences of that
    particular lyric, and the context of the songs in which the word appears.

2.  main.cpp		- Chooses database to draw lyrics from and facilitates
			  user input and searching of the database.
    Table.h		- Header file for hash table class. Outlines all
			  member functions and data.
    Table.cpp		- Implementation of hash table functions. Contains the
			  vast majority of code for this assignment. Handles
			  the reading in of songs, sorting of words in the hash
			  table, and searching/printing of words and contexts.
    Song.h		- Header file for song class. Contains vector of lyrics
			  unique to each individual instance.
    Song.cpp		- Implementation of song functions. Handles reading in
			  of lyrics and contains basic song information.
    util.h	     - Contains given alpha_only function.
    util.cpp	- Implementation of alpha_only function.
    hashfunc.h		- Interface for given hash function.
    hashfunc.cpp	- Implementation of hash function.

3.  Use included makefile by typing command "make" at command line.
    To run this program with the included sample .txt file, type 
    "./songsearch rick_db.txt" at the command line.

    The program will then read in and organize the lyrics contained in the
    file, but will not provide any prompting to the user when ready.
    Simply type the desired word to search for and hit enter.

    The program will then print out the top 10 songs in which the specified
    word occurs most frequently, along with the context of those songs in
    which the word appears.

    Type "BREAK" and hit enter to exit the program.

4.  First, the vector of song class instances was built one at a time. Data
    was read in from the database file and appropriately filed into the
    relevant variables in a given song class instance. Instances were pushed
    onto the back of the vector to be later manipulated.

    Then, each songs' lyrics were one by one hashed and appropriately entered
    into the hash table. The hash table itself was comprised of arrays of
    structs of 11 length each. This allowed for the maintanence of a top 10,
    while the 11th spot served as a temporary holder for a given song's word
    frequency while it was being inserted. If inserting a word that already
    existed in the table for a given song, the song's frequency for that word
    is incremented. Once each word is inserted, the index of that word is
    reordered in order of decreasing frequency for each song within.

    When a user inputs a word, the word is hashed and found in the table. The
    title and artist of each element in the struct array at that index is
    printed, and then the context. The context was printed by searching the
    vector of song class instances for the specific song, finding the given
    word in the song's vector of lyrics, and printing the previous 5 and next
    5 words.