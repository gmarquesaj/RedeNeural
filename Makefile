app =  app
comp = clang++
all: main.o neuronio.o rede.o
	clear
	clang++ main.o neuronio.o rede.o -o  $(app)  -O3
	./$(app) > log.txt
	convert final.ppm final.png;convert treino.ppm treino.png
main.o: main.cpp
	$(comp) -c main.cpp -o main.o
neuronio.o: neuronio.cpp
	$(comp) -c neuronio.cpp -o neuronio.o
rede.o: rede.cpp
	$(comp) -c rede.cpp -o rede.o

teste: neuronio.o rede.o
	clear
	$(comp) teste.cpp neuronio.o rede.o -o $(app)_teste -O3
	./$(app)_teste > log.txt
clean:
	rm -f *.o