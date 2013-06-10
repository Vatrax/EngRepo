main: obj main.o bloki.o lacze_do_gnuplota.o uklad.o main.o
	g++ obj/main.o obj/bloki.o obj/lacze_do_gnuplota.o  obj/uklad.o -o main
main.o: src/main.cpp inc/bloki.hh inc/uklad.hh
	g++ -c -Wall -pedantic -Iinc/ src/main.cpp -o obj/main.o
bloki.o: src/bloki.cpp inc/bloki.hh 
	g++ -c -Wall -pedantic -Iinc/ src/bloki.cpp -o obj/bloki.o
lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ -c -Wall -pedantic -Iinc/ src/lacze_do_gnuplota.cpp -o obj/lacze_do_gnuplota.o
uklad.o: src/uklad.cpp inc/uklad.hh
	g++ -c -Wall -pedantic -Iinc/ src/uklad.cpp -o obj/uklad.o
obj:
	mkdir -p obj

