#include "./Transmissor.hpp"
#include <bitset>
#include <iostream>
using namespace std;

// Seleciona o método de codificação a ser usado para a transmissão,
// codifica o quadro e manda o fluxo de bits para o meio de comunicação
void camadaFisicaTransmissora(vector<int> quadro) {
  int tipoDeCodificacao = 0;
  vector<int> fluxoBrutoDeBits; // Os valores desse vetor são as voltagens do sinal

  switch (tipoDeCodificacao) {
    case 0:
      fluxoBrutoDeBits = camadaFisicaTransmissoraCodificacaoBinaria(quadro);
      break;
    case 1:
      fluxoBrutoDeBits = camadaFisicaTransmissoraCodificacaoManchester(quadro);
      break;
    case 2:
      fluxoBrutoDeBits = camadaFisicaTransmissoraCodificacaoBipolar(quadro);
      break;
  } // fim do switch/case

  // Passa o fluxo de bits para o meio físico de comunicação
  meioDeComunicacao(fluxoBrutoDeBits);
} // fim do método camada física transmissora

// Aplica a codificação binária para um quadro, usando 5v para representar 1 e 0v para representar 0
vector<int> camadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro) {
  vector<int> quadroCodificado;

  for (int i = 0; i < quadro.size(); i ++) {
    if (quadro[i] == 1) {
      quadroCodificado.push_back(5); // usa 5v como sinal alto para representar 1
    } else {
      quadroCodificado.push_back(0); // usa 0v como sinal para representar 0
    } // fim do if/else para conferir se o bit é 1 ou 0
  } // fim do loop pelo quadro

  return quadroCodificado;
} // fim da função de codificação binária

// Aplica a codificação bipolar ao quadro, na qual 0v representa 0;
// e 1 é representado por 5v e -5v, alternando
vector<int> camadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
  vector<int> quadroCodificado;
  bool alternado = true; // Variável que diz se o 1 é negativo

  for (int i = 0; i < quadro.size(); i ++) {
    if (quadro[i] == 1) {
      if (alternado) {
        quadroCodificado.push_back(-5); // usa 5v como sinal alto para representar 1
        alternado = false; // grava para o próximo 1 alternar a polaridade
      } else {
        quadroCodificado.push_back(5); // usa 5v como sinal baixo para representar 1
        alternado = true; // grava para o próximo 1 alternar a polaridade
      }
    } else {
      quadroCodificado.push_back(0); // usa 0v como sinal para representar 0
    } // fim do if/else para conferir se o bit é 1 ou 0
  } // fim do loop pelo quadro

  return quadroCodificado;
} // fim da função de codificação Bipolar

// Aplica a codificação bipolar ao quadro, na qual cada bit é representado por
// dois sinais elétricos, 5v e -5v. Nesse caso, 1 é representado pelo par (-5v, 5v)
// e 0 é representado pelo par (5v, -5v).
vector<int> camadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
  vector<int> quadroCodificado;

  for (int i = 0; i < quadro.size(); i ++) {
    if (quadro[i] == 1) {
      // alterna o sinal de baixo pra alto, para simbolizar o 1
      quadroCodificado.push_back(-5);
      quadroCodificado.push_back(5);
    } else {
      // alterna o sinal de baixo pra alto, para simbolizar o 0
      quadroCodificado.push_back(5);
      quadroCodificado.push_back(-5);
    } // fim do if/else para conferir se o bit é 1 ou 0
  } // fim do loop pelo quadro

  return quadroCodificado;
} // fim do metodo de codificação Manchester
