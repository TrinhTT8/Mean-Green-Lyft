CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

OBJS = main.o utils.o passenger.o passengers.o driver.o tiereddriver.o basic.o economy.o group.o luxury.o drivers.o ride.o rides.o

lyft: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o lyft

# Each object file is rebuilt only when its own .cpp or a header it includes changes
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

main.o: main.cpp passengers.h passenger.h drivers.h driver.h rides.h ride.h utils.h
utils.o: utils.cpp utils.h
passenger.o: passenger.cpp passenger.h utils.h
passengers.o: passengers.cpp passengers.h passenger.h utils.h
driver.o: driver.cpp driver.h utils.h
tiereddriver.o: tiereddriver.cpp tiereddriver.h driver.h utils.h
basic.o: basic.cpp basic.h tiereddriver.h driver.h
economy.o: economy.cpp economy.h tiereddriver.h driver.h
group.o: group.cpp group.h tiereddriver.h driver.h
luxury.o: luxury.cpp luxury.h tiereddriver.h driver.h utils.h
drivers.o: drivers.cpp drivers.h driver.h basic.h economy.h group.h luxury.h tiereddriver.h utils.h
ride.o: ride.cpp ride.h utils.h
rides.o: rides.cpp rides.h ride.h passenger.h driver.h utils.h

clean:
	rm -f *.o lyft
