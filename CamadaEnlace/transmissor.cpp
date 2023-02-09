#include "./transmissor.hpp"
#include "../aplicacao.hpp"

using namespace std;

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
  // enquadra os dados
  vector<int> quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

  // aplica os códigos para controlar os erros
  vector<int> quadroComControleDeErro = CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);

  // chama a próxima camada
  camadaFisicaTransmissora(quadroComControleDeErro);
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro) {
  int tipoDeEnquadramento = 0; // determina o tipo de enquadramento a ser usado
  vector<int> quadroEnquadrado;

  switch (tipoDeEnquadramento) {
    case 0: // enquadramento por contagem de caracteres
      return CamadaEnlaceDadosTransmissoraContagemDeCaracteres(quadro);
    case 1: // enquadramenro por inserção de bytes
      return CamadaEnlaceDadosTransmissoraInsercaoDeBytes(quadro);
  }
}

vector<int> CamadaEnlaceDadosTransmissoraContagemDeCaracteres(vector<int> quadro) {
  vector<int> quadroEnquadrado; // resultado enquadrado
  int numOfBytes = quadro.size() / 8 + 1; // conta quantos bytes tem no quadro
  bitset<8> sizeByte = numOfBytes; // transforma a quantidade de bytes em notação binária
  
  // adiciona o byte de tamanho ao quadro
  for (int j = 0; j < 8; j++) {
    quadroEnquadrado.push_back(sizeByte[j]);
  }

  // adiciona o resto do quadro ao resultado
  for (int i = 0; i < quadro.size(); i++) {
    quadroEnquadrado.push_back(quadro[i]);
  }

  return quadroEnquadrado;
}

vector<int> CamadaEnlaceDadosTransmissoraInsercaoDeBytes(vector<int> quadro) {
  vector<int> quadroEnquadrado; // resultado
  int byteDeQuebra[8] = {0, 1, 1, 1, 1, 1, 1, 0}; // byte que simboliza o início e fim do quadro
  int byteDeFlag[8] = {1, 1, 1, 1, 1, 1, 1, 0}; // byte que simboliza um caracter especial

  int byteEstudado[8]; // byte que está sendo estudado

  // adiciona o byte de quebra ao início do quadro
  inserirByteEmVetor(&quadro, byteDeQuebra);

  // passa pelo quadro um byte por vez
  for (int i = 0; i < quadro.size(); i += 8) {
    selecionarByte(quadro, i, &byteEstudado); // seleciona o byte que será estudado

    // caso o byte seja igual ao flag, ou o de quebra, adiciona um byte de flag antes
    if (bytesIguais(byteDeQuebra, byteEstudado) || bytesIguais(byteDeFlag, byteEstudado))
      inserirByteEmVetor(&quadro, byteDeFlag);

    // adiciona o byte estudado ao quadro 
    inserirByteEmVetor(&quadro, byteEstudado);
  }

  // insere o byte de quebra que simboliza o fim do quadro
  inserirByteEmVetor(&quadro, byteDeQuebra);

  return quadroEnquadrado;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro) {
  int tipoDeControleDeErro = 1; // seleciona o tipo de controle de erro que será usado
  
  switch(tipoDeControleDeErro) {
    case 0: // controle de erro por bit de paridade par 
      return CamadaEnlaceDadosTransmissoraBitDeParidade(quadro);
    case 1: // controle de erro por código de redundância cíclica
      return CamadaEnlaceDadosTransmissoraCRC(quadro);
    case 2: // controle e correção dos erros por código de hamming
      return CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
  }
}

vector<int> CamadaEnlaceDadosTransmissoraBitDeParidade(vector<int> quadro) {
  int bits1 = 0; // a quantidade de bits 1 no quadro

  // conta a quantidade bits 1 no quadro
  for (int i = 0; i < quadro.size(); i++) {
    if (quadro[i] == 1) {
      bits1++;
    }
  }

  // caso o número de 1s for impar, coloca 1 no final do quadro
  if (bits1 % 2 != 0) {
    quadro.push_back(1);
  } else { // caso contrário coloca 0
    quadro.push_back(0);
  }

  return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraCRC(vector<int> quadro) {
  bitset<4> gerador (6); // gerador usado para criar o CRC '0110'
  bitset<4> geradorQuandoZero (0); // gerador quando o bit mais significativo é 0
  bitset<4> grupoDeBits; // grupo de bits que será dividido
  bitset<3> res; // resultado da divisão
  bitset<1> next_bit; // próximo bit do quadro a ser dividido

  // reverte o quadro para a divisão
  reverse(quadro.begin(), quadro.end());

  // seleciona o primeiro grupo de bits a ser divido
  selecionaBitGroup(quadro, &grupoDeBits, 0);

  // passa por cada bit para dividi-lo
  for (int i = 0; i < quadro.size(); i ++) {
    if (grupoDeBits[0] == 0) { // caso número mais significativo for 0 usa o gerador 0
      grupoDeBits = geradorQuandoZero ^ grupoDeBits; // divide usando o xor
    } else {
      grupoDeBits = gerador ^ grupoDeBits;
    }

    // seleciona os 3 últimos bits como resultado da divisão
    for (int j = 0; j < 3; j++) {
      res[j] = grupoDeBits[j];
    }

    next_bit = quadro[i+3]; // seleciona o próximo bit a ser dividido
    grupoDeBits = concat(res, next_bit); // cria o próximo grupo de bits
  }

  // reverte o quadro a sua configuração normal
  reverse(quadro.begin(), quadro.end());

  // usa o resto como CRC e adiciona ao quadro
  for (int i = 0; i < 4; i++) {
    quadro.push_back((int) res[i]);
  }

  return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro) {
  vector<int> resultado;

  // |1|2|3|4|5|6|7|
  //1:x _ x _ x _ x
  //2:_ x x _ _ x x
  //4:_ _ _ x x x x
  // |3|5|6|7|1|2|4|
  //1:x x _ x =
  //2:x _ x x   =
  //4:_ x x x     =

  for(int i = 0; i < quadro.size(); i += 4) {
    // coloca os 4 bits de dados
    resultado.push_back(quadro[i]);
    resultado.push_back(quadro[i + 1]);
    resultado.push_back(quadro[i + 2]);
    resultado.push_back(quadro[i + 3]);

    // calcula os bits de paridade
    resultado.push_back(quadro[i] ^ quadro[i + 1] ^ quadro[i + 3]);
    resultado.push_back(quadro[i] ^ quadro[i + 2] ^ quadro[i + 3]);
    resultado.push_back(quadro[i + 1] ^ quadro[i + 2] ^ quadro[i + 3]);
  }

  return resultado;
}
