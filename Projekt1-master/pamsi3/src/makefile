all: wynik

wynik: main.o benchmark.o program.o mnozenie.o tablice.o
	g++ main.o benchmark.o mnozenie.o program.o tablice.o -o wynik

main.o: main.cpp
	g++ -c main.cpp

benchmark.o: benchmark.cpp
	g++ -c benchmark.cpp

mnozenie.o: mnozenie.cpp
	g++ -c mnozenie.cpp

program.o: program.cpp
	g++ -c program.cpp

tablice.o: tablice.cpp
	g++ -c tablice.cpp

clean:
	rm -rf *o wynik
