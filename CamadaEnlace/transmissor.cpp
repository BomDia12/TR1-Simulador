#include "./transmissor.hpp"
using namespace std;

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
  CamadaEnalceDadosTransmissoraEnquadramento(quadro);
  
  CamadaEnalceDadosTransmissoraControleDeErro(quadro);
}

void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro) {
  int tipoDeEnquadramento = 0;
  vector<int> quadroEnquadrado;

  switch (tipoDeEnquadramento) {
    case 0:
      quadroEnquadrado = CamadaEnalceDadosTransmissoraContagemDeCaracteres(quadro);
      break;
    case 1:
      quadroEnquadrado = CamadaEnalceDadosTransmissoraInsercaoDeBytes(quadro);
      break;
  }

  camadaFisicaTransmissora(quadroEnquadrado);
}

vector<int> CamadaEnalceDadosTransmissoraContagemDeCaracteres(vector<int> quadro) {
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

vector<int> CamadaEnalceDadosTransmissoraInsercaoDeBytes(vector<int> quadro) {
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
