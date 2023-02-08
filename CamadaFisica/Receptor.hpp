#ifndef RECEPTORFISICO
#define RECEPTORFISICO
#include <vector>
#include <string>
#include <iostream>
#include <bitset>
#include "./../CamadaEnlace/receptor.hpp"
using namespace std;

void camadaFisicaReceptora(vector<int> fluxoBrutoDeBits);

vector<int> camadaFisicaReceptoraDecodificadoraBinaria(vector<int> quadro);

vector<int> camadaFisicaReceptoraDecodificadoraManchester(vector<int> quadro);

vector<int> camadaFisicaReceptoraDecodificadoraBipolar(vector<int> quadro);

#endif
