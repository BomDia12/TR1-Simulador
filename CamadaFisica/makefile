all: Receptor.o Transmissor.o MeioDeTransicao.o

run: Simulador.exe
	./Simulador.exe

Transmissor.o: Transmissor.cpp Transmissor.hpp
	g++ -std=c++17 -Wall -c Transmissor.cpp

MeioDeTransicao.o: MeioDeTransicao.cpp MeioDeTransicao.hpp
	g++ -std=c++17 -Wall -c MeioDeTransicao.cpp

Receptor.o: Receptor.cpp Receptor.hpp
	g++ -std=c++17 -Wall -c Receptor.cpp

Simulador.exe: Simulador.cpp Transmissor.o Receptor.o MeioDeTransicao.o
	g++ -std=c++17 -Wall Simulador.cpp -o Simulador.exe ./*.o

clean:
	rm -rf *.o *.exe
