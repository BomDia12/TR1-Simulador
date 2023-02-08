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
  int tipoDeControleDeErro = 2;

  switch(tipoDeControleDeErro) {
    case 0:
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
      break;
    case 1:
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
      break;
    case 2:
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
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

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro) {
  vector<int> resultado;

  // |1|2|3|4|5|6|7|
  //1:x _ x _ x _ x
  //2:_ x x _ _ x x
  //4:_ _ _ x x x x
  // |3|5|6|7|1|2|4|
  //1:x x _ x =
  //2:x _ x x   =
  //4:_ x x x     =

  for (int i = 0; i < quadro.size() / 7; i += 7) {
    // copia os bits de dados
    resultado.push_back(quadro[i]);
    resultado.push_back(quadro[i + 1]);
    resultado.push_back(quadro[i + 2]);
    resultado.push_back(quadro[i + 3]);

    int bit1 = quadro[i + 4];
    int bit2 = quadro[i + 5];
    int bit4 = quadro[i + 6];

    int paridade1 = quadro[i] ^ quadro[i + 1] ^ quadro[i + 3];
    int paridade2 = quadro[i] ^ quadro[i + 2] ^ quadro[i + 3];
    int paridade4 = quadro[i + 1] ^ quadro[i + 2] ^ quadro[i + 3];

    // constroi um indice (posicao) para o erro
    int posicao = ((int) bit1 != paridade1) | ((int) bit2 != paridade2) << 1 | ((int) bit4 != paridade4) << 2;

    switch(posicao) {
      case 0:
        // nenhum bit de paridade esta errado, nao fazemos nada
        break;
      case 1:
        // o erro esta no bit de paridade 1, nao fazemos nada
        break;
      case 2:
        // o erro esta no bit de paridade 2, nao fazemos nada
        break;
      case 3:
        // o erro esta no bit 3 = resultado[i]
        resultado[i] = 1 - resultado[i];
        break;
      case 4:
        // o erro esta no bit de paridade 4, nao fazemos nada
        break;
      case 5:
        // o erro esta no bit 5 = resultado[i+1]
        resultado[i+1] = 1 - resultado[i+1];;
        break;
      case 6:
        // o erro esta no bit 6 = resulta[i+2]
        resultado[i+2] = 1 - resultado[i+2];
        break;
      case 7:
        // o erro esta no bit 7 = resulta[i+3]
        resultado[i+3] = 1 - resultado[i+3];
        break;
    }

    return resultado;
  }
}