CXX=g++
CXXFLAGS=-c -Wall -pedantic

SRC=./src
INC=./inc
BLD=./build

TARGET=hash


all: $(TARGET)

$(TARGET): $(BLD)/main.o $(BLD)/files.o $(BLD)/flags.o $(BLD)/hash.o $(BLD)/interface.o $(BLD)/rom.o $(BLD)/xml.o
	g++ $^ -o $(BLD)/$(TARGET)

$(BLD)/main.o: $(SRC)/main.cpp $(INC)/files.hpp $(INC)/flags.hpp $(INC)/interface.hpp $(INC)/rom.hpp $(INC)/xml.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/files.o: $(SRC)/files.cpp $(INC)/files.hpp $(INC)/interface.hpp $(INC)/rom.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/flags.o: $(SRC)/flags.cpp $(INC)/flags.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/hash.o: $(SRC)/hash.cpp $(INC)/hash.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/interface.o: $(SRC)/interface.cpp $(INC)/interface.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/rom.o: $(SRC)/rom.cpp $(INC)/rom.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(BLD)/xml.o: $(SRC)/xml.cpp $(INC)/rom.hpp $(INC)/xml.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

clean:
	rm -rf ./build/*

run:
	$(BLD)/$(TARGET)
