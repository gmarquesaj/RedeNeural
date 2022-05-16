#include "neuronio.hpp"
#include "rede.hpp"
#include <cstdlib>
double Neuronio::eta = 0.15;
double Neuronio::alpha = 0.5;
void LerDoArquivo(Rede &Arede) {
  ifstream arq("vareaveis.txt");
  int numCamadas;
  arq >> numCamadas;
  Topologia topologia;
  topologia.clear();

  for (int c = 0; c < numCamadas; c++) {
    unsigned int v;
    arq >> v;
    topologia.push_back(v);
  }
  Arede = Rede(topologia);
  arq >> Arede.erro;
  arq >> Arede.erroMedioRecente;
  arq >> Arede.fatorDeErroRecente;
  for (int i = 0; i < numCamadas; i++) {

    int numSaidas = i == numCamadas - 1 ? 0 : topologia[i + 1];
    for (int ii = 0; ii <= topologia[i]; ii++) {
      Neuronio &atual = Arede.Camadas[i][ii];
      arq >> atual.Saida;
      int qntliga;
      arq >> qntliga;
      for (int l = 0; l < qntliga; l++) {
        arq >> atual.PesosSaida[l].peso;
        arq >> atual.PesosSaida[l].deltaPeso;
      }
      arq >> atual.gradiente;
    }
  }
}
int main() {
  srand(time(NULL)); // RANDOMIZANDO SEED A CADA RODADA
  // TESTANDO A REDE
  vector<unsigned int> topologia = {2, 4, 1};

  Rede Arede(topologia);
 
  vector<vector<double>> entradas = {
      {1, 1}, {0, 1}, {1, 0}, {0, 0}};                     // valores para XOR
  vector<vector<double>> esperados = {{0}, {1}, {1}, {0}}; // valores para XOR

  LerDoArquivo(Arede);
  cout << "\n\n\nTESTANDO XOR \n";
  Arede.teste(entradas,esperados,false,1);

 //  Arede.SalvarParaArquivo();
  return 0;
}
