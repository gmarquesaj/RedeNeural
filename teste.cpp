#include "neuronio.hpp"
#include "rede.hpp"
#include <cstdlib>
#include <iostream>
double Neuronio::eta = 0.15;
double Neuronio::alpha = 0.5;
void teste(Rede &Arede, vector<vector<double>> &entradas,
           vector<vector<double>> &esperados,int loops=100) {
  for (int i = 0; i < 4 * loops; i++) {
    //int ii = rand() % 4;
    // cout <<"\n"<< ii<<"\n";
     int ii = i % 4;
    Arede.feedFoward(entradas[ii]);
    vector<double> resultados;
    Arede.PegarResultados(resultados);
    cout << "\tX = " << entradas[ii][0] << " X2 = " << entradas[ii][1]
         << " Esperado " << esperados[ii][0] << " Chute = " << resultados[0]
         << " Erro = " << esperados[ii][0] - resultados[0] << "\n";
   // cout << "\tAPRENDENDO..\n";
    Arede.backProp(esperados[ii]);
  }
}
int main() {
  srand(time(NULL)); // RANDOMIZANDO SEED A CADA RODADA
  // TESTANDO A REDE
  vector<unsigned int> topologia = {2, 4, 1};

  Rede Arede(topologia);
  // cout << "----------------\n";
  vector<vector<double>> entradas = {
      {1, 1}, {0, 1}, {1, 0}, {0, 0}};                     // valores para or
  vector<vector<double>> esperados = {{1}, {1}, {1}, {0}}; // valores para or
  cout << "\n\n\nTESTANDO OR \n";
  teste(Arede, entradas, esperados);
  entradas = {{1, 1}, {0, 1}, {1, 0}, {0, 0}}; // valores para AND
  esperados = {{1}, {0}, {0}, {0}};            // valores para AND
  cout << "\n\n\nTESTANDO AND \n";
  teste(Arede, entradas, esperados);
  entradas = {{1, 1}, {0, 1}, {1, 0}, {0, 0}}; // valores para XOR
  esperados = {{0}, {1}, {1}, {0}};            // valores para XOR
  cout << "\n\n\nTESTANDO XOR \n";
  teste(Arede, entradas, esperados,500);

  return 0;
}