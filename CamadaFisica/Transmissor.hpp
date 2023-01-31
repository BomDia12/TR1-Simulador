#include <string>
#include <vector>
#include "./MeioDeTransicao.hpp"
using namespace std;

void aplicacaoTransmissora();

void camadaAplicacaoTransmissora(string mensagem);

vector<int> stringToBits(string mensagem);

void camadaFisicaTransmissora(vector<int> quadro);
vector<int> camadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);
vector<int> camadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);
vector<int> camadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);
