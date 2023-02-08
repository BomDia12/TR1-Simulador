all: aplicacao.o
	+$(MAKE) -C CamadaEnlace
	+$(MAKE) -C CamadaFisica

clean:
	rm -rf ./*.o ./*/*.o ./*.exe

aplicacao.o: aplicacao.hpp aplicacao.cpp
	g++ -std=c++17 -Wall -c aplicacao.cpp

Simulador.exe: Simulador.cpp all
	g++ -std=c++17 -Wall Simulador.cpp -o Simulador.exe ./*.o ./*/*.o

run: Simulador.exe
	./Simulador.exe
