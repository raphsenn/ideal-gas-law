
compile:
	g++ -c -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include simulation.cpp
	g++ -c -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include slider.cpp
	g++ -c -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include button.cpp
	g++ -c -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include particle.cpp
	g++ -c -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include random.cpp
	g++ -c -std=c++17 -I/opt/homebrew/Cellar/sfml/2.6.1/include main.cpp
	g++ -c -std=c++17 vector2.cpp
	g++ -o main -std=c++17 main.o simulation.o slider.o button.o particle.o vector2.o random.o -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o
	rm -f main


