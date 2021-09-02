main: main.o Simulation.o
	g++ main.o Simulation.o -o main -Llib -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	g++ -Iinclude -c main.cpp

Simulation.o: Simulation.h
	g++ -Iinclude -c Simulation.cpp

clean:
	del main.exe 
	del main.o 
	del Simulation.o