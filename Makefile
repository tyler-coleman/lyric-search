#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -g3

songsearch: Table.h Table.cpp Song.h Song.cpp main.cpp util.cpp hashfunc.h hashfunc.cpp
	${CXX} ${FLAGS} -o songsearch Song.cpp main.cpp Table.cpp util.cpp hashfunc.cpp
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw6_design songsearch_design.txt

provide:
	provide comp15 hw6 <all your files go here>

