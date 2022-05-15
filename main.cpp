#include "neuronio.hpp"
#include "rede.hpp"


int main() {
  srand(time(NULL)); // RANDOMIZANDO SEED A CADA RODADA
  // TESTANDO A REDE
  vector<unsigned int> topologia = {2, 4, 1};

  Rede Arede(topologia);

  /*  vector<vector<double>> entradas = {{1, 1}, {0, 1}, {1, 0}, {0,
   0}};//valores para or vector<vector<double>> esperados = {{1}, {1}, {1},
   {0}};//valores para or
  */

  /*   vector<vector<double>> entradas = {
        {1, 1}, {0, 1}, {1, 0}, {0, 0}};                     // valores para AND
    vector<vector<double>> esperados = {{1}, {0}, {0}, {0}}; // valores para AND
   */
  vector<vector<double>> entradas = {
      {1, 1}, {0, 1}, {1, 0}, {0, 0}};                     // valores para XOR
  vector<vector<double>> esperados = {{0}, {1}, {1}, {0}}; // valores para XOR

  for (int i = 0; i < 4 * 10; i++) {
    int ii = i % 4;
    // cout <<"\n"<< ii<<"\n";
    Arede.feedFoward(entradas[ii]);
    Arede.backProp(esperados[ii]);
  }

  vector<double> resultados;
  Arede.PegarResultados(resultados);
  Arede.SalvarParaArquivo();
  // cout << resultados[0];
  Arede.LerDoArquivo();
  return 0;
}
