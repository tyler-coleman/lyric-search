#include <vector>
#include "Song.h"

#include <string>
#include <iostream>

using namespace std;

// constructor
Song::Song() {
    title = "";
    artist = "";
}

// destructor
Song::~Song() {
    lyrics.~vector();
}

// adds lyric
void Song::addLyric(string s) {
    lyrics.push_back(s);
}

// returns length of lyrics
int Song::length() {
    return lyrics.size();
}

// sets song artist
void Song::setArtist(string s) {
    artist = s;
}

// sets song title
void Song::setTitle(string s) {
    title = s;
}

// returns song artist
string Song::getArtist() {
    return artist;
}

// returns song title
string Song::getTitle() {
    return title;
}