#include "./Transmissor.hpp"
#include <bitset>
#include <iostream>
using namespace std;

// Função que pega uma string de characteres e transforma eles em um vetor de bits
vector<int> stringToBits(string mensagem) {
  vector<int> bits;
  bitset<8> byte;

  for(int i = 0; i < (int) mensagem.length(); i++) {
    // Operação que transforma um char em um byte
    byte = bitset<8>(mensagem[i]);

    // Coloca cada bit do byte dentro do vetor para tratamento individual
    for (int j = 0; j < 8; j++) {
      bits.push_back(byte[j]);
    }
  } // fim do loop pela string mensagem

  return bits;
} // fim da função stringToBits

// Aplicação simples que pega uma mensagem do usuário
void aplicacaoTransmissora() {
  string mensagem;
  cout << "Digite uma mensagem" << endl;
  cin >> mensagem;

  camadaAplicacaoTransmissora(mensagem); // Chamando a próxima camada
} // fim do método aplicação transmissora

// Camada que passa a mensagem da aplicação transmissora para a camada física
void camadaAplicacaoTransmissora(string mensagem) {
  // converte a string de caracteres em um vetor de bits (ints 0 ou 1)
  vector<int> quadro = stringToBits(mensagem);

  // Chama a próxima camada
  camadaFisicaTransmissora(quadro);
}

// Seleciona o método de codificação a ser usado para a transmissão,
// codifica o quadro e manda o fluxo de bits para o meio de comunicação
void camadaFisicaTransmissora(vector<int> quadro) {
  int tipoDeCodificacao = 2;
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
