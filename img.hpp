#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::ofstream;
using std::vector;
class IMAGEM {
public:
  int w, h;
  vector<vector<double>> pixels;
  void abrir(std::string caminho) {
    ifstream imgori(caminho.c_str());
    {
      imgori >> w;
      imgori >> h;
      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          double r, g, b;
          imgori >> r;
          imgori >> g;
          imgori >> b;
          r = r < 0 ? 0 : r > 1.0 ? 1.0 : r;
          g = g < 0 ? 0 : g > 1.0 ? 1.0 : g;
          b = b < 0 ? 0 : b > 1.0 ? 1.0 : b;
          // cout << r<<" "<<g<<" "<<b <<"\n";
          pixels.push_back({r, g, b});
        }
      }
    }
  }
};