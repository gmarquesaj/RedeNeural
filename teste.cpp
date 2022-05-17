#include "neuronio.hpp"
#include "rede.hpp"
#include <cstdlib>
#include <iostream>
double Neuronio::eta = 0.15;
double Neuronio::alpha = 0.5;

int main() {
  srand(time(NULL)); // RANDOMIZANDO SEED A CADA RODADA
  // TESTANDO A REDE
  vector<unsigned int> topologia = {2,3,1};

  Rede Arede(topologia);
  // cout << "----------------\n";
  vector<vector<double>> entradas = {
      {1, 1}, {0, 1}, {1, 0}, {0, 0}};                     // valores para or
  vector<vector<double>> esperados = {{1}, {1}, {1}, {0}}; // valores para or
  cout << "\n\n\nTESTANDO OR \n";
  Arede.teste( entradas, esperados,true,true);
  entradas = {{1, 1}, {0, 1}, {1, 0}, {0, 0}}; // valores para AND
  esperados = {{1}, {0}, {0}, {0}};            // valores para AND
  cout << "\n\n\nTESTANDO AND \n";
  Arede.teste( entradas, esperados,true,true);
  entradas = {{1, 1}, {0, 1}, {1, 0}, {0, 0}}; // valores para XOR
  esperados = {{0}, {1}, {1}, {0}};            // valores para XOR
  cout << "\n\n\nTESTANDO XOR \n";
  Arede.teste( entradas, esperados,true,true,5000);

  return 0;
}