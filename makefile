lyft: main.o passenger.o driver.o ride.o passengers.o drivers.o rides.o basic.o economy.o group.o luxury.o
	g++ main.o passenger.o driver.o ride.o passengers.o drivers.o rides.o basic.o economy.o group.o luxury.o -o lyft

main.o: main.cpp
	g++ -c main.cpp

passenger.o: passenger.cpp passenger.h
	g++ -c passenger.cpp

driver.o: driver.cpp driver.h
	g++ -c driver.cpp

ride.o: ride.cpp ride.h
	g++ -c ride.cpp

passengers.o: passengers.cpp passengers.h passenger.cpp passenger.h
	g++ -c passengers.cpp passenger.cpp

drivers.o: drivers.cpp drivers.h driver.cpp driver.h basic.cpp basic.h economy.cpp economy.h group.cpp group.h luxury.cpp luxury.h
	g++ -c drivers.cpp driver.cpp basic.cpp economy.cpp group.cpp luxury.cpp

rides.o: rides.cpp rides.h ride.cpp ride.h
	g++ -c rides.cpp ride.cpp

basic.o: basic.cpp basic.h driver.cpp driver.h drivers.cpp drivers.h
	g++ -c basic.cpp driver.cpp drivers.cpp

economy.o: economy.cpp economy.h driver.cpp driver.h
	g++ -c economy.cpp driver.cpp

group.o: group.cpp group.h driver.cpp driver.h
	g++ -c group.cpp driver.cpp

luxury.o: luxury.cpp luxury.h driver.cpp driver.h
	g++ -c luxury.cpp driver.cpp

clean:
	rm *.o
