out/proj5.x: proj5.cpp out/passserver.o
	g++ -std=c++11 -lcrypt proj5.cpp out/passserver.o -o out/proj5.x

out/passserver.o: passserver.h passserver.cpp hashtable.hpp hashtable.h
	g++ -c -std=c++11 passserver.cpp -o out/passserver.o

out/ht_test.x:
	g++ -std=c++11 ht_test.cpp -o out/ht_test.x

out/scrypt.x:
	g++ -std=c++11 scrypt.cpp -o out/script.x

clean:
	rm -r *.o out/*
