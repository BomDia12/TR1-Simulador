#include <vector>
#include <bitset>
#include "funcoesAuxiliares.hpp"
#include "../CamadaFisica/Transmissor.hpp"
using namespace std;

void CamadaEnlaceDadosTransmissora (vector<int> quadro);

void CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);

void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraContagemDeCaracteres (vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraInsercaoDeBytes (vector<int> quadro);
