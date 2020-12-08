scheduler: input.o functions_elaborations.o round_robin.o
	g++ -c input.o functions_elaborations.o round_robin.o -o scheduler

input.o: input.cpp
	g++ -c input.cpp

functions_elaborations.o: functions_elaborations.cpp
	g++ -c functions_elaborations.cpp

round_robin.o: round_robin.cpp
	g++ -c round_robin.cpp

clean:
	rm *.o scheduler