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
  ~Rede() { cout << "-------\n"; }
  // CRIAR A REDE NEURAL
  Rede(const vector<unsigned int> &topologia) {
    int QntCamadas = topologia.size(); // QUANTAS CAMADAS TEM A REDE NEURAL

    for (int i = 0; i < QntCamadas; i++) {

      Camadas.push_back(Camada()); // ADICIONA UMA CAMADA NA REDE
      int numSaidas = i == QntCamadas - 1 ? 0 : topologia[i + 1];
      // ADICIONAR NEURORIOS NA CAMADA RECEM CRIADA
      for (int ii = 0; ii <= topologia[i]; ii++) {
        Camadas.back().push_back(Neuronio(numSaidas, ii));
        // cout << "Neuronio " << ii << " criado\n";
      }
      Camadas.back().back().Saida = 1.0;
    }
  };
  void feedFoward(const vector<double> &entradas) {
    assert(entradas.size() ==
           Camadas[0].size() - 1); // GARANTE QUE OS DADOS DE ENTRADA TEM O
                                   // MESMO TAMANHO Q A CAMADA QUE VAI RECEBER
    // copiando entrada para neuronios de entrada
    for (int i = 0; i < entradas.size(); i++) {
      Camadas[0][i].Saida = entradas[i];
    }
    // propagando dados
    for (int i = 1; i < Camadas.size();
         i++) // para cada camada(ignorando a camada 0 que é a entrada)
    {
      Camada &Anterior = Camadas[i - 1];
      for (int ii = 0; ii < Camadas[i].size() - 1;
           ii++) // para cada neuronio na camada(ignorando o ultimo q é o peso)
      {
        Camadas[i][ii].feedFoward(Anterior);
      }
    }
  };
  void backProp(const vector<double> &esperados, bool printar = false) {
    // CALCULAR ERRO
    Camada &Saida = Camadas.back();
    erro = 0.0;
    for (int i = 0; i < Saida.size() - 1;
         i++) // para cada neuronio na camada de saida exceto o peso
    {
      // calcula o erro e adiciona ao erro total da REDE
      double erroNeuronio = esperados[i] - Saida[i].Saida;
      erro += erroNeuronio * erroNeuronio;
      if (printar) {
        cout << "\tChute " << Saida[i].Saida << " Esperado " << esperados[i]
             << " erro  = " << erroNeuronio << "\n";
      }
    }
    erro = sqrt(erro / (Saida.size() - 1)); // media RMS
    // medir media recente de precisao
    erroMedioRecente = (erroMedioRecente * fatorDeErroRecente + erro) /
                       (fatorDeErroRecente + 1.0);
    if (printar) {
      cout << "\tRMS = " << erro << " ErroMedioRecente = " << erroMedioRecente
           << "\n";
    }
    // calcular grandiente da camada de saida
    for (int i = 0; i < Saida.size() - 1; i++) {
      Saida[i].calcGradiente(esperados[i]);
    }
    // calcular gradiente das camadas ocultas
    // cout << "calculando grandiente oculto \n";
    for (int i = Camadas.size() - 2; i > 0;
         i--) // para todas as camadas da penultima para primeira
    {
      Camada &oculta = Camadas[i];
      Camada &proxima = Camadas[i + 1];
      for (int n = 0; n < oculta.size();
           n++) // para todos os neuronios da camada oculta
      {
        oculta[n].calcGradienteOculto(proxima);
      }
    }
    // Atualizar peso  das ligações para todas as camadas, da saida para entrada
    // cout << "atualizando pesos \n";
    for (int i = Camadas.size() - 1; i > 0; i--) // para todas as camadas
    {
      Camada &atual = Camadas[i];
      Camada &anterior = Camadas[i - 1];
      for (int n = 0; n < atual.size() - 1;
           n++) // para todos os neuronios da camada atual
      {
        atual[n].AtualizarPesoEntradas(anterior);
      }
    }
  };
  void PegarResultados(vector<double> &resultados) {
    resultados.clear();
    for (int n = 0; n < Camadas.back().size() - 1; n++) {
      resultados.push_back(Camadas.back()[n].Saida);
    }
  };
  void SalvarParaArquivo() {
    ofstream arq("vareaveis.txt");
    int ncamadas = Camadas.size();
    arq << ncamadas << " ";

    for (int i = 0; i < ncamadas; i++) {
      arq << Camadas[i].size() - 1 << " ";
    }
    arq << erro << " " << erroMedioRecente << " " << fatorDeErroRecente;
    arq << "\n";
    // arq << " # TOPOLOGIA\n";
    for (int c = 0; c < ncamadas; c++) {
      int qntNeu = Camadas[c].size();
      for (int n = 0; n < qntNeu; n++) {
        //  arq << c + 1 << " " << n + 1 << "\n";
        Neuronio &atual = Camadas[c][n];
        arq << "\t" << atual.Saida << " " << atual.PesosSaida.size() << " \n";
        for (int l = 0; l < atual.PesosSaida.size(); l++) {

          arq << "\t" << atual.PesosSaida[l].peso << " "
              << atual.PesosSaida[l].deltaPeso << " \n";
        }
        arq << "\t" << atual.gradiente << " \n";
      }
    }
  }
};
