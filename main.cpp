#include "neuronio.hpp"
#include "rede.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
double Neuronio::eta = 0.1;
double Neuronio::alpha = 0.1;
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
int main(int argc, char *argv[]) {

  srand(time(NULL)); // RANDOMIZANDO SEED A CADA RODADA
  // TESTANDO A REDE
  vector<unsigned int> topologia = {3, 15, 3};

  Rede Arede(topologia);

  vector<vector<double>> entradas = {};
  vector<vector<double>> esperados = {};
  vector<vector<double>> IMGFINAL = {};

  int wOri, hOri;
  int wFx, hFx;
  int wFinal, hFinal;
  ifstream imgori("./img em texto/ori.txt");
  {
    imgori >> wOri;
    imgori >> hOri;
    for (int y = 0; y < hOri; y++) {
      for (int x = 0; x < wOri; x++) {
        double r, g, b;
        imgori >> r;
        imgori >> g;
        imgori >> b;
        r = r < 0 ? 0 : r > 1.0 ? 1.0 : r;
        g = g < 0 ? 0 : g > 1.0 ? 1.0 : g;
        b = b < 0 ? 0 : b > 1.0 ? 1.0 : b;
        // cout << r<<" "<<g<<" "<<b <<"\n";
        entradas.push_back({r, g, b});
      }
    }
  }
  ifstream imgfx("./img em texto/bordas.txt");
  {
    imgfx >> wFx;
    imgfx >> hFx;
    for (int y = 0; y < hFx; y++) {
      for (int x = 0; x < wFx; x++) {
        double r, g, b;
        imgfx >> r;
        imgfx >> g;
        imgfx >> b;
        r = r < 0 ? 0 : r > 1.0 ? 1.0 : r;
        g = g < 0 ? 0 : g > 1.0 ? 1.0 : g;
        b = b < 0 ? 0 : b > 1.0 ? 1.0 : b;
        esperados.push_back({r, g, b});
      }
    }
  }
  ifstream imgFinal("./img em texto/ori2.txt");
  {
    imgFinal >> wFinal;
    imgFinal >> hFinal;
    for (int y = 0; y < hFinal; y++) {
      for (int x = 0; x < wFinal; x++) {
        double r, g, b;
        imgFinal >> r;
        imgFinal >> g;
        imgFinal >> b;
        r = r < 0 ? 0 : r > 1.0 ? 1.0 : r;
        g = g < 0 ? 0 : g > 1.0 ? 1.0 : g;
        b = b < 0 ? 0 : b > 1.0 ? 1.0 : b;
        IMGFINAL.push_back({r, g, b});
      }
    }
  }
  cout << "\n\n\nTESTANDO IMAGENS \n";
  cout << entradas.size();
  Arede.teste(entradas, esperados, true, false, 1000);
  cout << "\nerro " << Arede.erro << " erro medio " << Arede.erroMedioRecente
       << "\n";

  std::ofstream ArqImgTreino("./treino.ppm");
  ArqImgTreino << "P3\n" << wFx << " " << hFx << "\n256\n";
  const int m = (entradas.size());
  for (int i = 0; i < m; i++) {
    Arede.feedFoward(entradas[i]);
    vector<double> resultados;
    Arede.PegarResultados(resultados);
    int r, g, b;
    r = int(resultados[0] * 254);
    g = int(resultados[1] * 254);
    b = int(resultados[2] * 254);

    /*
      r = int(entradas[i][0] * 250);
      g = int(entradas[i][1] * 250);
      b = int(entradas[i][2] * 250);
   */
    r = r < 0 ? 0 : r > 255 ? 255 : r;
    g = g < 0 ? 0 : g > 255 ? 255 : g;
    b = b < 0 ? 0 : b > 255 ? 255 : b;
    ArqImgTreino << r << " " << g << " " << b << "\n";
    Arede.backProp(esperados[i]);
  }

std::ofstream ArqImgFinal("./final.ppm");
  ArqImgFinal << "P3\n" << wFinal << " " << hFinal << "\n256\n";
  const int m2 = (IMGFINAL.size());
  for (int i = 0; i < m2; i++) {
    Arede.feedFoward(IMGFINAL[i]);
    vector<double> resultados;
    Arede.PegarResultados(resultados);
    int r, g, b;
    r = int(resultados[0] * 254);
    g = int(resultados[1] * 254);
    b = int(resultados[2] * 254);

    /*
      r = int(entradas[i][0] * 250);
      g = int(entradas[i][1] * 250);
      b = int(entradas[i][2] * 250);
   */
    r = r < 0 ? 0 : r > 255 ? 255 : r;
    g = g < 0 ? 0 : g > 255 ? 255 : g;
    b = b < 0 ? 0 : b > 255 ? 255 : b;
    ArqImgFinal << r << " " << g << " " << b << "\n";
   // Arede.backProp(esperados[i]);
  }

  return 0;
}
