#include "neuronio.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

Ligacao::Ligacao() {
  peso = double(rand() % 100) / 100.0;

  deltaPeso = 0;
  cout << "Ligação criada com peso aleatorio = " << peso << " \n";
};
Ligacao::Ligacao(double peso, double delta)
    : peso(peso),
      deltaPeso(delta){
          // cout << "Ligação criada com peso definido = " << peso << " \n";
      };

Neuronio::Neuronio(int numSaidas, int index) : index(index) {
  for (int c = 0; c < numSaidas; c++) {
    PesosSaida.push_back(Ligacao());
  }
};
double Neuronio::Ativacao(double v) { return tanh(v); };
double Neuronio::AtivacaoDerivativa(double v) { return 1.0 - v * v; };
double Neuronio::SomaDOW(const vector<Neuronio> &Proxima) {
  double soma = 0.0;
  // somar contribuiçao desde neuronio para o erro dos neurorios q recebem
  // deste
  for (int n = 0; n < Proxima.size() - 1; n++) {
    soma += PesosSaida[n].peso * Proxima[n].gradiente;
  }
  return soma;
}
void Neuronio::feedFoward(const vector<Neuronio> &Anterior) {
  double soma = 0.0;
  for (int i = 0; i < Anterior.size(); i++) {
    soma += Anterior[i].Saida * Anterior[i].PesosSaida[index].peso;
  }

  Saida = Ativacao(soma);
};
void Neuronio::calcGradiente(double esperado) {
  double erro = esperado - Saida;
  gradiente = erro * AtivacaoDerivativa(Saida);
}
void Neuronio::calcGradienteOculto(vector<Neuronio> &Proxima) {
  double dow = SomaDOW(Proxima);
  gradiente = dow * AtivacaoDerivativa(Saida);
}
void Neuronio::AtualizarPesoEntradas(vector<Neuronio> &Anterior) {
  for (int n = 0; n < Anterior.size();
       n++) // PARA TODOS OS NEURONIOS DA CAMADA ANTERIOR
  {
    Neuronio &N = Anterior[n];
    double deltaPesoAntigo = N.PesosSaida[index].deltaPeso;

    double NovoDeltaPeso = eta * N.Saida * gradiente + alpha * deltaPesoAntigo;

    N.PesosSaida[index].deltaPeso = NovoDeltaPeso;
    N.PesosSaida[index].peso += NovoDeltaPeso;
  }
}