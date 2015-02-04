#=========================== CVS =======================================
# $Author: Wojciech Krzaczek$
#=======================================================================


__start__: obj ./main
	rm -f core.* core; ./main

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir -p obj
./main: obj/main.o obj/modul.o
	g++ -o ./main obj/main.o obj/modul.o

obj/main.o: src/main.cpp inc/modul.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/modul.o: src/modul.cpp inc/modul.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/modul.o src/modul.cpp

clean:
	rm -f obj/* ./main core.* core

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo

