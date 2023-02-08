all: transmissor.o funcoesAuxiliares.o receptor.o

funcoesAuxiliares.o: funcoesAuxiliares.hpp funcoesAuxiliares.cpp
	g++ -std=c++17 -Wall -c funcoesAuxiliares.cpp

transmissor.o: transmissor.hpp transmissor.cpp
	g++ -std=c++17 -Wall -c transmissor.cpp

receptor.o: receptor.cpp receptor.hpp
	g++ -std=c++17 -Wall -c receptor.cpp