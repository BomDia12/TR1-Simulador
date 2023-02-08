#ifndef APLICACAO
#define APLICACAO
#include <vector>
#include <string>
#include "./CamadaEnlace/transmissor.hpp"

void aplicacaoTransmissora();

void camadaAplicacaoTransmissora(string mensagem);

vector<int> stringToBits(string mensagem);

void camadaAplicacaoReceptora(vector<int> quadro);

string bitsToMensagem(vector<int> quadro);

void aplicacaoReceptora(string mensagem);

#endif
