#include "rede.hpp"
int main() {
  srand(time(NULL));
  // TESTANDO A REDE
  vector<unsigned int> topologia;
  topologia.push_back(2); // 2 NEURONIOS PARA CAMADA DE ENTRADA
  topologia.push_back(4); // 4 NEURONIOS NA CAMADA OCULTA
  topologia.push_back(1); // 1 NEURORIO NA CAMADA DE SAIDA
  Rede Arede(topologia);
  /*  vector<vector<double>> entradas = {{1, 1}, {0, 1}, {1, 0}, {0,
   0}};//valores para or vector<vector<double>> esperados = {{1}, {1}, {1},
   {0}};//valores para or
  */
  /*   vector<vector<double>> entradas =  {{1, 1}, {0, 1}, {1, 0}, {0,
    0}};//valores para XOR vector<vector<double>> esperados = {{0},    {1}, {1},
    {0}};//valores para XOR
   */
  vector<vector<double>> entradas = {
      {1, 1}, {0, 1}, {1, 0}, {0, 0}};                     // valores para AND
  vector<vector<double>> esperados = {{1}, {0}, {0}, {0}}; // valores para AND

  for (int i = 0; i < 40000; i++) {
    int ii = i % 3;
    Arede.feedFoward(entradas[ii]);
    Arede.backProp(esperados[ii]);
  }

  vector<double> resultados;
  Arede.PegarResultados(resultados);
  cout << resultados[0];

  return 0;
}
