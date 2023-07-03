CXX=g++
CXXFLAGS=-c -Wall -pedantic

SRC=./src
INC=./inc
BLD=./build

TARGET=hash


all: main.o flags.o rom.o

main.o: $(SRC)/main.cpp $(INC)/flags.hpp
	$(CXX) $(CXXFLAGS) $< -o $(BLD)/$@.o -I$(INC)

flags.o: $(SRC)/flags.cpp $(INC)/flags.hpp
	$(CXX) $(CXXFLAGS) $< -o $(BLD)/$@.o -I$(INC)

rom.o: $(SRC)/rom.cpp $(INC)/rom.hpp
	$(CXX) $(CXXFLAGS) $< -o $(BLD)/$@.o -I$(INC)
