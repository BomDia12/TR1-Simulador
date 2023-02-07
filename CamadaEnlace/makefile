all: transmissor.o funcoesAuxiliares.o

funcoesAuxiliares.o: funcoesAuxiliares.hpp funcoesAuxiliares.cpp
	g++ -std=c++17 -Wall -c funcoesAuxiliares.cpp

transmissor.o: transmissor.hpp transmissor.cpp
	g++ -std=c++17 -Wall -c transmissor.cpp