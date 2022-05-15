app =  app
comp = clang++
all:
	clear
	$(comp) main.cpp -o $(app) -O3
	./$(app) > log.txt