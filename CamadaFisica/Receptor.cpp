#include "Receptor.hpp"
using namespace std;

// Seleciona a decodificação a ser usada e chama a próxima camada
void camadaFisicaReceptora(vector<int> fluxoBrutoDeBits) {
  int tipoDeDecodificacao = 2; // Variável que determina qual será o método de codificação utilizado
  vector<int> quadro;

  switch (tipoDeDecodificacao) {
    case 0:
      quadro = camadaFisicaReceptoraDecodificadoraBinaria(fluxoBrutoDeBits);
      break;
    case 1:
      quadro = camadaFisicaReceptoraDecodificadoraManchester(fluxoBrutoDeBits);
      break;
    case 2:
      quadro = camadaFisicaReceptoraDecodificadoraBipolar(fluxoBrutoDeBits);
      break;
  } // fim do switch case

  // Chama a próxima camada
  CamadaEnlace(quadro);
} // fim do método camada física receptora

// Decodifica o fluxo de símbolos elétricos em bits, tornando 5v em 1 e 0v em 0
vector<int> camadaFisicaReceptoraDecodificadoraBinaria(vector<int> fluxoBrutoDeBits) {
  vector<int> quadro;

  for (int i = 0; i < fluxoBrutoDeBits.size(); i ++) {
    if (fluxoBrutoDeBits[i] == 5) {
      quadro.push_back(1); // transforma 5v no bit 1
    } else {
      quadro.push_back(0); // transforma 0v no bit 0
    } // fim do if/else para conferir se o bit é 1 ou 0
  } // fim do loop pelo fluxo de bits

  return quadro;
} // fim do mérodo decodificador binário

// Decodifica o fluxo de símbolos elétricos em bits, tornando 5v ou -5v em 1 e 0v em 0
vector<int> camadaFisicaReceptoraDecodificadoraBipolar(vector<int> fluxoBrutoDeBits) {
  vector<int> quadro;

  for (int i = 0; i < fluxoBrutoDeBits.size(); i ++) {
    if (fluxoBrutoDeBits[i] == 5 || fluxoBrutoDeBits[i] == -5) {
      quadro.push_back(1); // transforma 5v ou -5v no bit 1
    } else {
      quadro.push_back(0); // transforma 0v no bit 0
    } // fim do if/else para conferir se o bit é 1 ou 0
  } // fim do loop pelo fluxo de bits

  return quadro;
} // fim do mérodo decodificador bipolar

// Decodifica o fluxo de símbolos elétricos em bits, tornando uma subida de sinal em 1 e uma queda em 0
vector<int> camadaFisicaReceptoraDecodificadoraManchester(vector<int> fluxoBrutoDeBits) {
  vector<int> quadro;

  for (int i = 0; i + 1 < fluxoBrutoDeBits.size(); i += 2) {
    if (fluxoBrutoDeBits[i] == -5 & fluxoBrutoDeBits[i + 1] == 5) {
      quadro.push_back(1); // Transforma uma subida do sinal em 1
    } else {
      quadro.push_back(0); // Transforma uma queda de sinal em 0
    } // fim do if/else para conferir se o bit é 1 ou 0
  } // fim do loop pelo fluxo de bits

  return quadro;
} // fim do mérodo decodificador Manchester
