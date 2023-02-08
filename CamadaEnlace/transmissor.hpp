#ifndef TRANSMISSORENLACE
#define TRANSMISSORENLACE
#include <vector>
#include <bitset>
#include "funcoesAuxiliares.hpp"
#include "../CamadaFisica/Transmissor.hpp"
using namespace std;

void CamadaEnlaceDadosTransmissora (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraContagemDeCaracteres (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraInsercaoDeBytes (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraBitDeParidade (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraCRC (vector<int> quadro);

#endif
