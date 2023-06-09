
output: out/main.o out/image.o out/filter.o
	g++ out/main.o out/image.o out/filter.o -o out/output

out/main.o: main.cpp
	g++ -c main.cpp -o out/main.o

out/image.o: image.cpp image.h
	g++ -c image.cpp -o out/image.o

out/filter.o: filter.cpp filter.h
	g++ -c filter.cpp -o out/filter.o

clean:
	rm out/*.o