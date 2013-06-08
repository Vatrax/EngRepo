__start__: obj ./rownania clean
	./rownania < dane-$(TYP)
        

./rownania: test_wywolania test_stalej obj obj/program.o obj/macierz.o obj/wektory.o obj/uklad.o obj/symbol.o obj/lzespolone.o
	g++ -Iinc -g -o ./rownania obj/program.o obj/macierz.o obj/wektory.o obj/uklad.o obj/symbol.o obj/lzespolone.o

obj/program.o: src/program.cpp inc/macierz.hh inc/wektory.hh inc/uklad.hh obj/symbol.o obj/lzespolone.o
	g++ -Iinc -g -Wall -D$(TYP) -c -o obj/program.o src/program.cpp

obj/macierz.o: src/macierz.cpp inc/macierz.hh obj/symbol.o obj/lzespolone.o
	g++ -Iinc -g -Wall -D$(TYP) -c -o obj/macierz.o src/macierz.cpp

obj/uklad.o: src/uklad.cpp inc/uklad.hh obj/symbol.o obj/lzespolone.o
	g++ -Iinc -g -Wall -D$(TYP) -c -o obj/uklad.o src/uklad.cpp

obj/wektory.o: src/wektory.cpp inc/wektory.hh obj/symbol.o obj/lzespolone.o
	g++ -Iinc -g -Wall -D$(TYP) -c -o obj/wektory.o src/wektory.cpp

obj/symbol.o: src/symbol.cpp inc/symbol.hh
	g++ -Iinc -g -Wall -c -o obj/symbol.o src/symbol.cpp

obj/lzespolone.o: src/lzespolone.cpp inc/lzespolone.hh
	g++ -Iinc -g -Wall -c -o obj/lzespolone.o src/lzespolone.cpp

obj:
	mkdir obj

test_wywolania:
	@bash -c                                  \
          "if [ x$(TYP) = x ]             ||      \
              [ ! x$(TYP) = xDOUBLE ]     &&      \
              [ ! x$(TYP) = xLZESPOLONA ] &&      \
              [ ! x$(TYP) = xSYMBOL ]; then       \
            echo;                                 \
            echo ' Zle wywolane polecenie make';  \
            echo ' Akceptowalna postac to:';      \
            echo;                                 \
            echo '   make TYP=DOUBLE';            \
            echo '   make TYP=LZESPOLONA';        \
            echo '   make TYP=SYMBOL';            \
            echo '   make clear';                 \
            echo;                                 \
            exit  1;                              \
           fi"

test_stalej: obj/stala_$(TYP)

obj/stala_$(TYP):
	rm -f obj/*
	touch obj/stala_$(TYP)

clean:
	rm -f obj/*
