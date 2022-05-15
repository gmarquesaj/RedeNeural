#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
using std::cout;
using std::vector;

class Ligacao {
public:
  double peso;
  double deltaPeso;
  Ligacao() {
    peso = double(rand() % 100) / 100.0;
    deltaPeso = 0;
  };
  Ligacao(double peso)
      : peso(peso){

        };
};

class Neuronio {
public:
  int index;
  double Saida;
  double gradiente;
  static double eta;   // TAXA DE APRENDIZADO GERAL
  static double alpha; // MOMENTUM
  vector<Ligacao> PesosSaida;
  Neuronio(int numSaidas, int index) : index(index) {
    for (int c = 0; c < numSaidas; c++) {
      PesosSaida.push_back(Ligacao());
    }
  };
  double Ativacao(double v) { return tanh(v); };
  double AtivacaoDerivativa(double v) { return 1.0 - v * v; };
  double SomaDOW(const vector<Neuronio> &Proxima) {
    double soma = 0.0;
    // somar contribuiçao desde neuronio para o erro dos neurorios q recebem
    // deste
    for (int n = 0; n < Proxima.size() - 1; n++) {
      soma += PesosSaida[n].peso * Proxima[n].gradiente;
    }
    return soma;
  }
  void feedFoward(const vector<Neuronio> &Anterior) {
    double soma = 0.0;
    for (int i = 0; i < Anterior.size(); i++) {
      soma += Anterior[i].Saida * Anterior[i].PesosSaida[index].peso;
    }

    Saida = Ativacao(soma);
  };
  void calcGradiente(double esperado) {
    double erro = esperado - Saida;
    gradiente = erro * AtivacaoDerivativa(Saida);
  }
  void calcGradienteOculto(vector<Neuronio> &Proxima) {
    double dow = SomaDOW(Proxima);
    gradiente = dow * AtivacaoDerivativa(Saida);
  }
  void AtualizarPesoEntradas(vector<Neuronio> &Anterior) {
    for (int n = 0; n < Anterior.size();
         n++) // PARA TODOS OS NEURONIOS DA CAMADA ANTERIOR
    {
      Neuronio &N = Anterior[n];
      double deltaPesoAntigo = N.PesosSaida[index].deltaPeso;

      double NovoDeltaPeso =
          eta * N.Saida * gradiente + alpha * deltaPesoAntigo;

      N.PesosSaida[index].deltaPeso = NovoDeltaPeso;
      N.PesosSaida[index].peso += NovoDeltaPeso;
    }
  }
};
typedef vector<Neuronio> Camada;

class Rede {
public:
  double erro = 0.0;
  double erroMedioRecente;
  double fatorDeErroRecente;
  vector<Camada> Camadas;

  // CRIAR A REDE NEURAL
  Rede(const vector<unsigned int> &topologia) {
    int QntCamadas = topologia.size(); // QUANTAS CAMADAS TEM A REDE NEURAL

    for (int i = 0; i < QntCamadas; i++) {

      Camadas.push_back(Camada()); // ADICIONA UMA CAMADA NA REDE
      int numSaidas = i == QntCamadas - 1 ? 0 : topologia[i + 1];
      // ADICIONAR NEURORIOS NA CAMADA RECEM CRIADA
      for (int ii = 0; ii <= topologia[i]; ii++) {
        Camadas.back().push_back(Neuronio(numSaidas, ii));
        cout << "Neuronio " << ii << " criado\n";
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
  void backProp(const vector<double> &esperados) {
    // CALCULAR ERRO
    Camada &Saida = Camadas.back();
    erro = 0.0;
    for (int i = 0; i < Saida.size() - 1;
         i++) // para cada neuronio na camada de saida exceto o peso
    {
      // calcula o erro e adiciona ao erro total da REDE
      double erroNeuronio = esperados[i] - Saida[i].Saida;
      erro += erroNeuronio * erroNeuronio;
    }
    erro = sqrt(Saida.size() - 1); // media RMS

    // medir media recente de precisao
    erroMedioRecente = (erroMedioRecente * fatorDeErroRecente + erro) /
                       (fatorDeErroRecente + 1.0);
    // calcular grandiente da camada de saida
    for (int i = 0; i < Saida.size() - 1; i++) {
      Saida[i].calcGradiente(esperados[i]);
    }
    // calcular gradiente das camadas ocultas
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
    for (int i = Camadas.size() - 1; i > 0; i--) // para todas as camadas
    {
      Camada &atual = Camadas[i];
      Camada &anterior = Camadas[i - 1];
      for (int n = 0; n < atual.size();
           n++) // para todos os neuronios da camada atual
      {
        atual[n].AtualizarPesoEntradas(anterior);
      }
    }
  };
  void getResults(vector<double> &resultados) {
    resultados.clear();
    for (int n = 0; n < Camadas.back().size() - 1; n++) {
      resultados.push_back(Camadas.back()[n].Saida);
    }
  };
};
double Neuronio::eta = 0.15;
double Neuronio::alpha = 0.5;
int main() {
  vector<unsigned int> topologia;
  topologia.push_back(3); // 3 NEURONIOS PARA CAMADA DE ENTRADA
  topologia.push_back(2); // 2 NEURONIOS NA CAMADA OCULTA
  topologia.push_back(1); // 1 NEURORIO NA CAMADA DE SAIDA
  Rede Arede(topologia);

  vector<double> entradas = {1, 1, 0};
  Arede.feedFoward(entradas);

  vector<double> esperados = {1};
  Arede.backProp(esperados);

  vector<double> resultados;
  Arede.getResults(resultados);

  return 0;
}
