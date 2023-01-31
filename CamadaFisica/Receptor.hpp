#include <vector>
#include <string>
#include <iostream>
#include <bitset>
using namespace std;

void camadaFisicaReceptora(vector<int> fluxoBrutoDeBits);

vector<int> camadaFisicaReceptoraDecodificadoraBinaria(vector<int> quadro);

vector<int> camadaFisicaReceptoraDecodificadoraManchester(vector<int> quadro);

vector<int> camadaFisicaReceptoraDecodificadoraBipolar(vector<int> quadro);

void camadaAplicacaoReceptora(vector<int> quadro);

string bitsToMensagem(vector<int> quadro);

void aplicacaoReceptora(string mensagem);
