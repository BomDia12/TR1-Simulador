#include "funcoesAuxiliares.hpp"

void selecionarByte(vector<int> quadro, int start, int * byte[8]) {
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
