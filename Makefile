app =  app
comp = clang++
all:
	clear
	$(comp) main.cpp -o $(app) -O3
	./$(app) > log.txt
	convert final.ppm final.png;convert treino.ppm treino.png
teste:
	clear
	$(comp) teste.cpp -o $(app)_teste -O3
	./$(app)_teste > log.txt