#include <vector>
#include <bitset>
#include "funcoesAuxiliares.hpp"
#include "../CamadaFisica/Transmissor.hpp"
using namespace std;

void CamadaEnlaceDadosReceptora (vector<int> quadro);

void CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);

void CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraContagemDeCaracteres (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraInsercaoDeBytes (vector<int> quadro);