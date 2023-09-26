CPP = g++ -Wall -std=c++11
CPPFLAGS = -O2
CPPFLAGS += $(shell root-config --cflags)
LDFLAGS = $(shell root-config --cflags --libs)

all:
	@echo "Please give an option."
eff:
	@g++ -Wall -std=c++11 -o eff_main eff_main.cpp Mean.cpp StDetectorEfficiency.cpp `root-config --libs --cflags`

clean:
	@rm eff_main

