#pragma once
#include "neuronio.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using std::cout;
using std::ifstream;
using std::ofstream;
using std::vector;

typedef vector<Neuronio> Camada;
typedef vector<unsigned int> Topologia;
class Rede {
public:
  double erro = 0.0;
  double erroMedioRecente;
  double fatorDeErroRecente = 50.0;
  vector<Camada> Camadas;
  ~Rede();
  Rede(const vector<unsigned int> &topologia);
  void feedFoward(const vector<double> &entradas);
  void backProp(const vector<double> &esperados, bool printar = false);
  void PegarResultados(vector<double> &resultados);
  void SalvarParaArquivo();
  void Rodar(vector<vector<double>> &entradas,
             vector<vector<double>> &esperados, bool treinar = true,
             bool printar = true, int loops = 100);
};
