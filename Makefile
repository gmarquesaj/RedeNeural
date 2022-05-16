app =  app
comp = clang++
all:
	clear
	$(comp) main.cpp -o $(app) -O3
	./$(app) > log.txt
teste:
	clear
	$(comp) teste.cpp -o $(app)_teste -O3
	./$(app)_teste > log.txt