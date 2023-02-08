#include "aplicacao.hpp"

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
  CamadaEnlaceDadosTransmissora(quadro);
}

// Transforma a mensagem de bites em uma string de caracteres e chama a aplicação
void camadaAplicacaoReceptora(vector<int> quadro) {
  // transforma o vetor de bits em uma string de caracteres usando ASCII
  string mensagem = bitsToMensagem(quadro);

  // chama a aplicação receptora
  aplicacaoReceptora(mensagem);
} // fim da camada aplicação receptora

// A aplicação receptora apenas imprime a mensagem recebida
void aplicacaoReceptora(string mensagem) {
  cout << "A mensagem recebida foi: " << mensagem << endl;
}

// Transforma um vetor de bits em uma string de caracteres
string bitsToMensagem(vector<int> quadro) {
  bitset<8> byte; // Um byte que representa um único caracter
  string mensagem;

  int aux = 0; // contador para o byte

  for (int i = 0; i < quadro.size(); i ++) {
    // Se um byte for completar esse ciclo
    if (aux >= 7) {
      byte[aux] = quadro[i]; // adiciona o último bit ao byte
      aux = 0; // reinicia o contador
      // adiciona o caracter correspondete ao byte a string sendo construida
      mensagem.push_back(static_cast<unsigned char>(byte.to_ulong())); 
    } else { // caso o byte não for completar
      byte[aux] = quadro[i]; // adicionar mais um bit ao byte
      aux++; // aumenta o contador
    }
  } // fim do for

  return mensagem;
} // fim do método bitsToMensagemas
