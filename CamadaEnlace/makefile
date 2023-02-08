all: transmissor.o funcoesAuxiliares.o receptor.o

funcoesAuxiliares.o: funcoesAuxiliares.hpp funcoesAuxiliares.cpp
	g++ -g -std=c++17 -Wall -c funcoesAuxiliares.cpp

transmissor.o: transmissor.hpp transmissor.cpp
	g++  -g -std=c++17 -Wall -c transmissor.cpp

receptor.o: receptor.cpp receptor.hpp
	g++ -g -std=c++17 -Wall -c receptor.cpp