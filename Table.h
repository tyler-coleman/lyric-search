#include <vector>
#include "Song.h"

#include <string>
#include <iostream>
#include "util.h"

using namespace std;

// struct that contains frequency for a given word in a specified song
struct word_occurrence {
    string song;
    string artist;
    int frequency;
};

// comprises each index of hash table
struct hash_node {
    string word;
    word_occurrence array[11];
};

class Table {
  public:
      //constructor
      Table();
      //destructor
      ~Table();
      
      // hash value generator
      unsigned int hash(string s, int length);

      // orders structs at table index by frequency
      void orderIndex(int index);

      // expands hash table when load factor reaches .75
      void expand();

      // fills table with all lyrics from all songs
      void fillTable();

      // inserts all lyrics from one song
      void insertSongLyrics(Song *s);

      // inserts a single word
      void insertWord(string word, string title, string artist);

      // checks for existence of a word in hash table
      bool checkForWord(string s);

      // calculates table's load factor
      float loadFactor();

      // finds index of a given word in table
      int findWord(string s);

      // prints all necessary info for a given word
      void printWord(string s);

      // prints context of a word in a given song instance
      int printContext(string word, string song, string artist, int start);
      
      // reads in info from database file
      void read_lyrics(const char * filename, bool show_progress);
      
  private:
      // the hash table
      hash_node *table;
      // song vector
      vector<Song *> songs;
      int length;
      int entries;
};