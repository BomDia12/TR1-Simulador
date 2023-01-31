#include "./transmissor.hpp"
#include <vector>
using namespace std;

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
  CamadaEnalceDadosTransmissoraEnquadramento(quadro);
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
}


