#include "funcoesAuxiliares.hpp"

void selecionarByte(vector<int> quadro, int start, int (*byte) [8]) {
  for (int i = 0; i < 8; i++) {
    *byte[i] = quadro[start + i];
  }
}

void inserirByteEmVetor(vector<int> * quadro, int byte[8]) {
  for (int i = 0; i < 8; i++) {
    quadro->push_back(byte[i]);
  }
}

bool bytesIguais(int byte1[8], int byte2[8]) {
  for (int i = 0; i < 8; i++) {
    if (byte1[i] != byte2[i]) return false;
  }

  return true;
}

void selecionaBitGroup(vector<int> quadro, bitset<4> * grupo, int start) {
  for (int i = 0; i < 4; i++) {
    grupo[i] = quadro[i + start];
  }
}

template <size_t N1, size_t N2 >
bitset <N1 + N2> concat( const bitset <N1> & b1, const bitset <N2> & b2 ) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    return bitset <N1 + N2>( s1 + s2 );
}
