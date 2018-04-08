#include <vector>
#include "Table.h"
#include "hashfunc.h"

#include <string>
#include <iostream>

using namespace std;

// constructor
Table::Table() {
    // create hash table of set length (minimizes time spent expanding)
    table = new hash_node[1200000];
    length = 1200000;
}

// destructor
Table::~Table() {
    delete [] table;
}

// generates hash value for a given string and length of table
uint32_t Table::hash(string s, int length) {
    uint32_t h = hash_string(s);
    h = h % length;
    return h;
}

// orders the structs present at a given index of the table
// selection sort
void Table::orderIndex(int index) {
    for (int unsorted = 0; unsorted < 11; unsorted++) {
		word_occurrence low_freq = table[index].array[unsorted];
		int low_ind = unsorted;
		for (int j = unsorted; j < 11; j++) {
		    // compare frequency of each struct to unsorted
		    if (table[index].array[j].frequency > 
		        table[index].array[unsorted].frequency) {
				low_freq = table[index].array[j];
				low_ind = j;
		    }
		}
		// swap unsorted struct with struct with highest frequency
		table[index].array[low_ind] = table[index].array[unsorted];
		table[index].array[unsorted] = low_freq;
    }
}
      
// expands table when load factor increases above .75
void Table::expand() {
    
    // generate new table
    hash_node *new_table = new hash_node[length * 2];
    length = length * 2;
    
    delete [] table;
    table = new_table;
    
    // fill new table using same algorithm
    fillTable();
}

// calculates table's load factor
float Table::loadFactor() {
    // convert values to floats
    return (float)entries / (float)length;
}

// inserts a single instance of a given word
void Table::insertWord(string word, string title, string artist) {
    // check if need for expansion
    if (loadFactor() > .75)
		expand();
    int h;
    
    // check if word is already present
    if (checkForWord(word)) {
		h = findWord(word);
    }
    else h = hash(word, length);
    
    // probe for word or empty index
    while (table[h].word != "") {
		if (table[h].word == word) break;
		h = (h+1) % length;
    }
    
    // check if word from specific song instance is already present at index
    for (int i = 0; i < 11; i++) {
		if (table[h].array[i].song == title &&
		    table[h].array[i].artist == artist) {
		    // increment
		    table[h].array[i].frequency++;
		    return;
		}
    }
    
    // insert at end of array at index temporarily
    table[h].array[10].song = title;
    table[h].array[10].artist = artist;
    table[h].array[10].frequency = 1;
    table[h].word = word;
}

// checks for the presence of a word in table
bool Table::checkForWord(string s) {
    // find hash value
    int h = hash(s, length);
    
    // probe for word or first empty index
    while (table[h].word != s) {
		if (table[h].word == "")
		    return false;
		h++;
	}
    return true;
}

// finds index of a given word in table
int Table::findWord(string s) {
    int h = hash(s, length);
    // probe for given word near hash value
    while (table[h].word != s)
      h++;
    return h;
}

// prints searched word's most frequent instances in top 10 songs
void Table::printWord(string s) {
      
    // check that word exists in table
    if (!checkForWord(s)) {
		cout << "<END OF REPORT>" << endl;
		return;
    }
  
    // find word in table
    int index = findWord(s);
    
    // print top 10 songs
    for (int i = 0; i < 10; i++) {
      
		// start at beginning of songs' lyrics
		int start = 0;
		// repeat context printing for each occurrence of word in song
		for (int j = 0; j < table[index].array[i].frequency; j++) {
		    cout << "Title: " << table[index].array[i].song << endl;
		    cout << "Artist: " << table[index].array[i].artist << endl;
		    cout << "Context: ";
		    
		    // start search for word in lyrics after last found instance
		    start = printContext(s, table[index].array[i].song, 
				table[index].array[i].artist, start);
		}
    }
    cout << "<END OF REPORT>" << endl;
}

// prints context of a word in a given song
int Table::printContext(string word, string song, string artist, int start) {
    int next;

    for (int i = 0; i < songs.size(); i++) {
		// search songs for given song by given artist
		if (songs[i]->getTitle() == song && songs[i]->getArtist() == artist) {
		    // search lyrics for given word
		    for (int j = start; j < songs[i]->length(); j++) {
				if (songs[i]->lyrics[j] == word) {
				    for (int k = -5; k < 6; k++) {
					// print previous 5, the word, and following 5
					if (j+k >=0 && j+k < songs[i]->lyrics.size())
					    cout << songs[i]->lyrics[j+k] << ' ';
				    }
				    // return index of next word in lyrics
				    // (to avoid repeat printing)
				    next = j + 1;
				    cout << endl << endl;
				    return next;
				}
		    }
		}
    }
}

// reads data in from database file to song class instances
void Table::read_lyrics(const char * filename, bool show_progress) {
    ifstream in(filename);			// creates an input stream
    int song_count = 0;			// for progress indicator
	string artist, title, word;

	// -- While more data to read...
	while (!in.eof()) {
		// allocate space for new song instance
		Song *new_song = new Song;
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;
		new_song->setArtist(artist);
		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;
		new_song->setTitle(title);

		if (show_progress) {
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "At "       << song_count << 
					" Artist: " << artist     << 
					" Title:"   << title << endl;
			}
		}
		// -- Then read all words until we hit the 
		// -- special <BREAK> token
		while (in >> word && word != "<BREAK>") {
			word = alpha_only(word);
			new_song->lyrics.push_back(word);
		}
		// add new song to vector of song instances
		songs.push_back(new_song);
		// -- Important: skip the newline left behind
		in.ignore();
	}
}

// fills hash table with song vector data
void Table::fillTable() {
      for (int i = 0; i < songs.size(); i++)
	  	// insert songs one at a time
	  	insertSongLyrics(songs[i]);
}

// inserts information from a specific song instance
void Table::insertSongLyrics(Song *s) {
    string title = s->getTitle();
    string artist = s->getArtist();
    // iterate through lyrics and add them to hash table
    for (int i = 0; i < s->lyrics.size(); i++) {
		if (alpha_only(s->lyrics[i]) != "") {
		    insertWord(s->lyrics[i], title, artist);
		    orderIndex(hash(s->lyrics[i], length));
		}
    }
}