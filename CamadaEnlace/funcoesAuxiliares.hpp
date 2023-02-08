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

template <size_t N1, size_t N2 >
bitset <N1 + N2> concat( const bitset <N1> & b1, const bitset <N2> & b2 );

#endif
