g++ -c main.cpp -I/home/phil/Documents/Programming/SFML-2.5.1/include 
g++ -c ./src/*.cpp
g++ -o sfml-app  *.o -L/home/phil/Documents/Programming/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
