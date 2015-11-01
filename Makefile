all: converter

converter: Main.o converter.o
	g++ -o converter Main.o converter.o

Main.o: Main.cpp
	g++ -c Main.cpp

converter.o: converter.cpp
	g++ -c converter.cpp

clean:
	rm -f *.o converter