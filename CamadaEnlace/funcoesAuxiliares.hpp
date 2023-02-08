#ifndef AUX
#define AUX
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

void selecionarByte(vector<int> quadro, int start, int (*byte) [8]);

void inserirByteEmVetor(vector<int> * quadro, int byte[8]);

bool bytesIguais(int byte1[8], int byte2[8]);

void selecionaBitGroup(vector<int> quadro, bitset<4> * grupo, int start);

bitset <4> concat( const bitset <3> & b1, const bitset <1> & b2 );

#endif
