#pragma once
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
using std::cout;
using std::vector;
class Ligacao {
public:
  double peso;
  double deltaPeso;
  Ligacao();
  Ligacao(double peso, double delta);
};

class Neuronio {
public:
  int index;
  double Saida;
  double gradiente;
  static double eta;   // TAXA DE APRENDIZADO GERAL
  static double alpha; // MOMENTUM

  vector<Ligacao> PesosSaida;

  Neuronio(int numSaidas, int index);
  double Ativacao(double v);
  double AtivacaoDerivativa(double v);
  double SomaDOW(const vector<Neuronio> &Proxima) ;
  void feedFoward(const vector<Neuronio> &Anterior);
  void calcGradiente(double esperado);
  void calcGradienteOculto(vector<Neuronio> &Proxima);
  void AtualizarPesoEntradas(vector<Neuronio> &Anterior);
};