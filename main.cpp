#include <iostream>
#include <vector>
using std::cout;
using std::vector;

class Neuronio {};
typedef vector<Neuronio> Camada;
class Rede {
public:
  vector<Camada> Camadas;

  // CRIAR A REDE NEURAL
  Rede(const vector<unsigned int> &topologia) {
    int QntCamadas = topologia.size(); // QUANTAS CAMADAS TEM A REDE NEURAL
    for (int i = 0; i < QntCamadas; i++) {

      Camadas.push_back(Camada()); // ADICIONA UMA CAMADA NA REDE
      // ADICIONAR NEURORIOS NA CAMADA RECEM CRIADA
      for (int ii = 0; ii <= topologia[i]; ii++) {
        Camadas.back().push_back(Neuronio());
        cout << "um neuronio criado\n";
      }
    }
  };
  void feedFoward(const vector<double> &entradas){};
  void backProp(const vector<double> &esperados){};
  void getResults(vector<double> &resultados){};
};
int main() {
  vector<unsigned int> topologia;
  topologia.push_back(3); // 3 NEURONIOS PARA CAMADA DE ENTRADA
  topologia.push_back(2); // 2 NEURONIOS NA CAMADA OCULTA
  topologia.push_back(1); // 1 NEURORIO NA CAMADA DE SAIDA
  Rede Arede(topologia);

  vector<double> entradas;
  Arede.feedFoward(entradas);

  vector<double> esperados;
  Arede.backProp(esperados);

  vector<double> resultados;
  Arede.getResults(resultados);

  return 0;
}
