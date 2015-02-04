__start__: obj ./rownania
	./rownania

./rownania: obj/program.o obj/macierz.o obj/wektory.o obj/uklad.o
	g++ -Iinc -g -o ./rownania obj/program.o obj/macierz.o obj/wektory.o obj/uklad.o

obj/program.o: src/program.cpp inc/macierz.hh inc/wektory.hh inc/uklad.hh
	g++ -Iinc -g -Wall -c -o obj/program.o src/program.cpp

obj/macierz.o: src/macierz.cpp inc/macierz.hh
	g++ -Iinc -g -Wall -c -o obj/macierz.o src/macierz.cpp

obj/uklad.o: src/uklad.cpp inc/uklad.hh
	g++ -Iinc -g -Wall -c -o obj/uklad.o src/uklad.cpp

obj/wektory.o: src/wektory.cpp inc/wektory.hh
	g++ -Iinc -g -Wall -c -o obj/wektory.o src/wektory.cpp
