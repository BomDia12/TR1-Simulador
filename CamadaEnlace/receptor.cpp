#include "./receptor.hpp"
using namespace std;

void CamadaEnlaceDadosReceptora(vector<int> quadro) {
  vector<int> quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErro(quadro);

  vector<int> quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadroControleDeErro);

  camadaAplicacaoReceptora(quadroDesenquadrado);
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro) {
  int tipoDeEnquadramento = 0;
  vector<int> quadroDesenquadrado;

  switch (tipoDeEnquadramento) {
    case 0:
      quadroDesenquadrado = CamadaEnlaceDadosReceptoraContagemDeCaracteres(quadro);
      break;
    case 1:
      quadroDesenquadrado = CamadaEnlaceDadosReceptoraInsercaoDeBytes(quadro);
      break;
  }

  return quadroDesenquadrado;
}

// desenquadra o quadro a partir da quantidade de bytes
vector<int> CamadaEnlaceDadosReceptoraContagemDeCaracteres(vector<int> quadro) {
  vector<int> quadroDesenquadrado;
  int numOfBytes = 0;
  bitset<8> sizeByte;

  // copia o byte contendo a quantidade de bytes
  for (int j = 0; j < 8; j++) {
    sizeByte[j] = quadro[j];
  }

  // converte o bitset em um int
  numOfBytes = (int) sizeByte.to_ulong();

  // obtém numOfBytes bytes do quadro
  for (int i = 8; i < numOfBytes * 8; i++) {
    quadroDesenquadrado.push_back(quadro[i]);
  }

  return quadroDesenquadrado;
}

vector<int> CamadaEnlaceDadosReceptoraInsercaoDeBytes(vector<int> quadro) {
  vector<int> quadroDesenquadrado;
  int byteDeQuebra[8] = {0, 1, 1, 1, 1, 1, 1, 0};
  int byteDeFlag[8] = {1, 1, 1, 1, 1, 1, 1, 0};

  int byteEstudado[8];
  for (int i = 0; i < quadro.size(); i += 8) {
    selecionarByte(quadro, i, &byteEstudado);

    if (bytesIguais(byteDeFlag, byteEstudado)) {
      i += 8;
      selecionarByte(quadro, i, &byteEstudado);
    }

    if (bytesIguais(byteDeQuebra, byteEstudado)) {
      i += 8;
      selecionarByte(quadro, i, &byteEstudado);
    }

    inserirByteEmVetor(&quadroDesenquadrado, byteEstudado);
  }

  return quadroDesenquadrado;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro) {
  vector<int> quadroControleDeErro;
  int tipoDeControleDeErro = 0;

  switch(tipoDeControleDeErro) {
    case 0:
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
      break;
    case 1:
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
      break;
  }

  return quadroControleDeErro;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(vector<int> quadro) {
  vector<int> resultado;
  int contadorDeBits = 0;

  for (int i = 0; i < quadro.size() - 1; i++) {
    if (quadro[i] == 1) {
      contadorDeBits++;
    }
  }
  
  // checa se o bit de paridade é par
  if (contadorDeBits % 2 == 0) {
    cout << "Bit de paridade par, mensagem correta" << endl;
  } else {
    cout << "Bit de paridade impar, mensagem incorreta" << endl;
  }

  // remove o bit de paridade
  for (int i = 0; i < quadro.size() - 1; i++) {
    resultado.push_back(quadro[i]);
  }

  return resultado;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro) {
  bitset<4> gerador (6);
  bitset<4> geradorQuandoZero (0);
  bitset<4> grupoDeBits;
  bitset<3> res;
  bitset<1> next_bit;
  bitset<3> resultadoEsperado (0);

  reverse(quadro.begin(), quadro.end());

  selecionaBitGroup(quadro, &grupoDeBits, 0);


  for (int i = 0; i + 4 < quadro.size(); i ++) {
    if (grupoDeBits[3] == 0) {
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

  if (res == resultadoEsperado) {
    cout << "nenhum erro foi detectado!" << endl;
  } else {
    cout << "Tivemos um erro na transmição :(" << endl;
  }

  reverse(quadro.begin(), quadro.end());

  for (int i = 0; i < 4; i++) {
    quadro.push_back((int) res[i]);
  }

  return quadro; 

}