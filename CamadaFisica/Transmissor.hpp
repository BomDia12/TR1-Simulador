#ifndef TRANSMISSORFISICO
#define TRANSMISSORFISICO
#include <string>
#include <vector>
#include "./MeioDeTransicao.hpp"
using namespace std;

void camadaFisicaTransmissora(vector<int> quadro);
vector<int> camadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);
vector<int> camadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);
vector<int> camadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);

#endif
