#include <vector>
#include <bitset>
#include "funcoesAuxiliares.hpp"
#include "../CamadaFisica/Transmissor.hpp"
using namespace std;

vector<int> CamadaEnlaceDadosReceptora (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraContagemDeCaracteres (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraInsercaoDeBytes (vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);