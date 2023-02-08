#include "./transmissor.hpp"
using namespace std;

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
  vector<int> quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
  
  vector<int> quadroComControleDeErro = CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);

  camadaFisicaTransmissora(quadro);
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro) {
  int tipoDeEnquadramento = 0;
  vector<int> quadroEnquadrado;

  switch (tipoDeEnquadramento) {
    case 0:
      return CamadaEnlaceDadosTransmissoraContagemDeCaracteres(quadro);
    case 1:
      return CamadaEnlaceDadosTransmissoraInsercaoDeBytes(quadro);
  }
}

vector<int> CamadaEnlaceDadosTransmissoraContagemDeCaracteres(vector<int> quadro) {
  vector<int> quadroEnquadrado;
  int numOfBytes = quadro.size() / 8 + 1;
  bitset<8> sizeByte = numOfBytes;
  
  for (int j = 0; j < 8; j++) {
    quadroEnquadrado.push_back(sizeByte[j]);
  }

  for (int i = 0; i < quadro.size(); i++) {
    quadroEnquadrado.push_back(quadro[i]);
  }

  return quadroEnquadrado;
}

vector<int> CamadaEnlaceDadosTransmissoraInsercaoDeBytes(vector<int> quadro) {
  vector<int> quadroEnquadrado;
  int byteDeQuebra[8] = {0, 1, 1, 1, 1, 1, 1, 0};
  int byteDeFlag[8] = {1, 1, 1, 1, 1, 1, 1, 0};

  int byteEstudado[8];

  inserirByteEmVetor(&quadro, byteDeQuebra);

  for (int i = 0; i < quadro.size(); i += 8) {
    selecionarByte(quadro, i, &byteEstudado);

    if (bytesIguais(byteDeQuebra, byteEstudado) || bytesIguais(byteDeFlag, byteEstudado))
      inserirByteEmVetor(&quadro, byteDeFlag);

    inserirByteEmVetor(&quadro, byteEstudado);
  }

  inserirByteEmVetor(&quadro, byteDeFlag);

  return quadroEnquadrado;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro) {
  int tipoDeControleDeErro = 0;
  
  switch(tipoDeControleDeErro) {
    case 0:
      return CamadaEnlaceDadosTransmissoraBitDeParidade(quadro);
    case 1:
      return CamadaEnlaceDadosTransmissoraCRC(quadro);
  }
}

vector<int> CamadaEnlaceDadosTransmissoraBitDeParidade(vector<int> quadro) {
  int bits1 = 0;

  for (int i = 0; i < quadro.size(); i++) {
    if (quadro[i] == 1) {
      bits1++;
    }
  }

  if (bits1 % 2 != 0) {
    quadro.push_back(1);
  } else {
    quadro.push_back(0);
  }

  return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraCRC(vector<int> quadro) {
  bitset<4> gerador (6);
  bitset<4> geradorQuandoZero (0);
  bitset<4> grupoDeBits;
  bitset<3> res;
  bitset<1> next_bit;

  reverse(quadro.begin(), quadro.end());

  selecionaBitGroup(quadro, &grupoDeBits, 0);

  for (int i = 0; i + 4 < quadro.size(); i ++) {
    if (grupoDeBits[0] == 0) {
      grupoDeBits = geradorQuandoZero ^ grupoDeBits;
    } else {
      grupoDeBits = gerador ^ grupoDeBits;
    }
    for (int j = 0; j < 3; j++) {
      res[j] = grupoDeBits[j];
    }
    next_bit = quadro[i+4];
    grupoDeBits = concat(res, next_bit);
  }

  reverse(quadro.begin(), quadro.end());

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

  for(int i = 0; i < quadro.size() / 4; i += 4) {
    // coloca os 4 bits de dados
    resultado.push_back(quadro[i]);
    resultado.push_back(quadro[i + 1]);
    resultado.push_back(quadro[i + 2]);
    resultado.push_back(quadro[i + 3]);

    // calcula os bits de paridade
    resultado.push_back(quadro[i] ^ quadro[i + 1] ^ quadro[i + 3]);
    resultado.push_back(quadro[i] ^ quadro[i + 2] ^ quadro[i + 3]);
    resultdao.push_back(quadro[i + 1] ^ quadro[i + 2] ^ quadro[i + 3]);
  }

  return resultado;
}