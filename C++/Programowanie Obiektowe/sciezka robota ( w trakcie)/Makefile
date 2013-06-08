start: main
	./main
main: main.o przeszkoda.o robot.o lacze.o cel.o start.o algorytm.o start
	g++ obj/main.o obj/przeszkoda.o obj/robot.o obj/lacze.o obj/cel.o obj/start.o obj/algorytm.o -o main
	rm -f obj/main.o obj/przeszkoda.o obj/robot.o obj/lacze.o
main.o: src/main.cpp inc/przeszkoda.hh inc/robot.hh inc/lacze_do_gnuplota.hh
	g++ -c -Wall -pedantic -Iinc/ src/main.cpp -o obj/main.o
przeszkoda.o: src/przeszkoda.cpp inc/przeszkoda.hh 
	g++ -c -Wall -pedantic -Iinc/ src/przeszkoda.cpp -o obj/przeszkoda.o
robot.o: src/robot.cpp inc/robot.hh
	g++ -c -Wall -pedantic -Iinc/ src/robot.cpp -o obj/robot.o
lacze.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ -c -Wall -pedantic -Iinc/ src/lacze_do_gnuplota.cpp -o obj/lacze.o
cel.o: src/cel.cpp inc/cel.hh
	g++ -c -Wall -pedantic -Iinc/ src/cel.cpp -o obj/cel.o
start.o: src/start.cpp inc/start.hh
	g++ -c -Wall -pedantic -Iinc/ src/start.cpp -o obj/start.o
algorytm.o: src/algorytm.cpp inc/algorytm.hh inc/robot.hh inc/start.hh inc/cel.hh inc/przeszkoda.hh 
	g++ -c -Wall -pedantic -Iinc/ src/algorytm.cpp -o obj/algorytm.o
