all: flocking_simulation

flocking_simulation: main.o Vector2D.o Boid.o Flock.o
	g++ -o flocking_simulation main.o Vector2D.o Boid.o Flock.o Constants.h -lGL -lGLU -lglut -O3

Vector2D.o: Vector2D.cpp
	g++ -o Vector2D.o -c Vector2D.cpp -std=c++11 -O3

Boid.o: Boid.cpp
	g++ -o Boid.o -c Boid.cpp -std=c++11 -O3

Flock.o: Flock.cpp
	g++ -o Flock.o -c Flock.cpp -std=c++11 -O3

main.o: main.cpp
	g++ -o main.o -c main.cpp -std=c++11 -O3

clean:
	rm -f *o core
