#include "./receptor.hpp"
using namespace std;

void CamadaEnlaceDadosReceptora(vector<int> quadro) {
  // confere ou corrige os erros que aparecerem no quadro
  vector<int> quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErro(quadro);

  // desenquadra a informação
  vector<int> quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadroControleDeErro);

  // chama a próxima camada
  camadaAplicacaoReceptora(quadroDesenquadrado);
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro) {
  int tipoDeEnquadramento = 0; // seleciona o tipo de enquadramento que foi usado
  vector<int> quadroDesenquadrado;

  switch (tipoDeEnquadramento) {
    case 0: // enquadramento por contagem de caracteres
      quadroDesenquadrado = CamadaEnlaceDadosReceptoraContagemDeCaracteres(quadro);
      break;
    case 1: // enquadramento por inserção de bytes
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
  // byte que representa o início ou fim de um quadro
  int byteDeQuebra[8] = {0, 1, 1, 1, 1, 1, 1, 0};
  // byte de flag para sinalisar simbolos especiais na mensagem
  int byteDeFlag[8] = {1, 1, 1, 1, 1, 1, 1, 0};

  int byteEstudado[8];
  for (int i = 0; i < quadro.size(); i += 8) {
    // seleciona o próximo byte do quadro
    selecionarByte(quadro, i, &byteEstudado);

    // caso o byte estudado for o de quebra, retorna o quadroDesenquadrado
    if (bytesIguais(byteDeQuebra, byteEstudado)) {
      i += 8;
      return quadroDesenquadrado;
    }

    // caso o byte estudado for a flag, pula a flag
    if (bytesIguais(byteDeFlag, byteEstudado)) {
      i += 8;
      selecionarByte(quadro, i, &byteEstudado);
    }

    // insere o próximo byte no quadro desenquadrado
    inserirByteEmVetor(&quadroDesenquadrado, byteEstudado);
  }

  return quadroDesenquadrado;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro) {
  vector<int> quadroControleDeErro;
  int tipoDeControleDeErro = 1; // seleciona o tipo de controle de erro que será usado;

  switch(tipoDeControleDeErro) {
    case 0: // controle por bit de paridade par
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
      break;
    case 1: // controle por código de redundância cíclica
      quadroControleDeErro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
      break;
    case 2: // controle e correção dos erros por código de hamming
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
  if (contadorDeBits % 2 == quadro[quadro.size() - 1]) {
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
  bitset<4> gerador (6); // Grupo de bits gerador do CRC (0110)
  bitset<4> geradorQuandoZero (0); // Quando o número mais a esquerda for 0, o gerador vira 0000
  bitset<4> grupoDeBits; // grupo de bits sendo dividido
  bitset<3> res; // resultado de cada operação
  bitset<1> next_bit; // próximo bit a ser dividido
  bitset<3> resultadoEsperado (0); // se o resultado for 000, o código está correto

  // revertendo o quadro para começar do lado certo dele
  reverse(quadro.begin(), quadro.end());

  // seleciona o primeiro grupo de bits a ser divido
  selecionaBitGroup(quadro, &grupoDeBits, 0);


  // faz um loop pelo quadro, dividindo os grupos de bits pelo caminho
  for (int i = 0; i < quadro.size(); i ++) {
    if (grupoDeBits[3] == 0) { // caso o primeiro valor for 0, usa o gerador 0
      grupoDeBits = geradorQuandoZero ^ grupoDeBits; // divide os bits usando uma operação bitwise xor
    } else { // caso o primeiro valor for 1 usa o gerador normal
      grupoDeBits = gerador ^ grupoDeBits;
    }
    // seleciona os últimos 3 bits como resposta
    for (int j = 0; j < 3; j++) {
      res[j] = grupoDeBits[j];
    }
    next_bit = quadro[i+3]; // seleciona o próximo bit a ser divido
    grupoDeBits = concat(res, next_bit); // atualiza o grupo de bits com o próximo bit
  }

  if (res == resultadoEsperado) {
    cout << "nenhum erro foi detectado!" << endl; // caso o resultado seja 0, não há erro
  } else {
    cout << "Tivemos um erro na transmição :(" << endl; // caso o contrário, algum erro foi detectado
  }

  // reverte o quadro de volta para o formato original 
  reverse(quadro.begin(), quadro.end());
  vector<int> resultado;

  // retira o CRC do quadro
  for (int i = 0; i < quadro.size() - 3; i++) {
    resultado.push_back(quadro[i]);
  }

  return quadro; 

}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro) {
  vector<int> resultado;

  // esquema de como funciona o código de hamming
  // |1|2|3|4|5|6|7|
  //1:x _ x _ x _ x
  //2:_ x x _ _ x x
  //4:_ _ _ x x x x
  // |3|5|6|7|1|2|4|
  //1:x x _ x =
  //2:x _ x x   =
  //4:_ x x x     =

  // faz um loop por cada byte do quadro
  for (int i = 0; i < quadro.size(); i += 7) {
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

    continue;
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

  }

  return resultado;
}
