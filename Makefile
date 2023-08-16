CXX=g++
CXXFLAGS=-c -Wall -pedantic

SRC=./src
INC=./inc
BLD=./build

TARGET=hash


all: $(TARGET)

$(TARGET): $(BLD)/main.o $(BLD)/directory.o $(BLD)/file.o $(BLD)/flags.o $(BLD)/hash.o $(BLD)/interface.o $(BLD)/xml.o
	g++ $^ -o $(BLD)/$(TARGET)

$(BLD)/main.o: $(SRC)/main.cpp $(INC)/directory.hpp $(INC)/file.hpp $(INC)/flags.hpp $(INC)/interface.hpp $(INC)/xml.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/directory.o: $(SRC)/directory.cpp $(INC)/directory.hpp $(INC)/file.hpp $(INC)/interface.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/file.o: $(SRC)/file.cpp $(INC)/file.hpp $(INC)/hash.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/flags.o: $(SRC)/flags.cpp $(INC)/flags.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/hash.o: $(SRC)/hash.cpp $(INC)/hash.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/interface.o: $(SRC)/interface.cpp $(INC)/interface.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/xml.o: $(SRC)/xml.cpp $(INC)/file.hpp $(INC)/xml.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

clean:
	rm -rf ./build/*

run:
	$(BLD)/$(TARGET)

test:
	$(BLD)/$(TARGET) hashes/GameBoyAdvance.dat
	$(BLD)/$(TARGET) hashes/PlayStation.dat
