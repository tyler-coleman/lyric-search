#include <vector>

#include <string>
#include <iostream>

using namespace std;

class Song {
public:
      // constructor
      Song();
      // destructor
      ~Song();
      
      // adds a lyric to the string vector
      void addLyric(string s);

      // returns the length of the song's string vector
      int length();

      // returns the artist of a song
      string getArtist();

      // returns the title of a song
      string getTitle();

      // sets the artist of a song
      void setArtist(string s);

      // sets the title of a song
      void setTitle(string s);
      
      // string vector of lyrics
      vector<string> lyrics;      
      
private:
      string title;
      string artist;
};