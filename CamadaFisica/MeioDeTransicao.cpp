#include "./MeioDeTransicao.hpp"

// Método que simula o meio de comunicação, passando bit a bit a informação
// para a camada física da aplicação receptora
void meioDeComunicacao(vector<int> fluxoBrutoDeBits) {
  vector<int> fluxoBrutoDeBitsA, fluxoBrutoDeBitsB;
  int porcentagemDeErros = 0;

  // Inicia A com os simbolos elétricos a serem passados
  fluxoBrutoDeBitsA = fluxoBrutoDeBits;

  // Passa os bits de A para B um a um
  for (int i = 0; i < fluxoBrutoDeBitsA.size(); i++) {
    if (rand() % 100 >= porcentagemDeErros) {
      fluxoBrutoDeBitsB.push_back(fluxoBrutoDeBitsA[i]);
    } else {
      fluxoBrutoDeBitsB.push_back(1 - fluxoBrutoDeBitsA[i]);
    }
  }

  // Chama a próxima camada
  camadaFisicaReceptora(fluxoBrutoDeBitsB);
}
