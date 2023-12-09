#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
# make                   makes FindPath
# make GraphTest        makes GraphTest
# make clean             removes all binaries
# make checkTest       checks GraphTest for memory errors
# make checkPath          checks FindPath for memory errors
#------------------------------------------------------------------------------

FindComponents : Graph.o FindComponents.o List.o
	gcc -std=c17 -Wall -g -o FindComponents Graph.o FindComponents.o List.o

FindComponents.o : FindComponents.c List.h Graph.h
	gcc -std=c17 -Wall -g -c FindComponents.c

GraphTest: GraphTest.o List.o Graph.o
	gcc -std=c17 -Wall -g -o GraphTest GraphTest.o List.o Graph.o

GraphTest.o : GraphTest.c List.h Graph.h
	gcc -std=c17 -Wall -g -c GraphTest.c

List.o : List.c List.h
	gcc -std=c17 -Wall -g -c List.c

Graph.o : Graph.c Graph.h List.h
	gcc -std=c17 -Wall -g -c Graph.c

clean :
	rm -f FindComponents GraphTest FindComponents.o GraphTest.o List.o Graph.o

checkTest : GraphTest
	valgrind --leak-check=full ./GraphTest

checkPath :
	valgrind --leak-check=full FindPath in3 blah3
