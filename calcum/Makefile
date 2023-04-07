CPP = g++ -Wall -std=c++11
CPPFLAGS = -O2
CPPFLAGS += $(shell root-config --cflags)
LDFLAGS = $(shell root-config --cflags --libs)

all:
	@echo "Please give an option."
cum:
	@g++ -Wall -std=c++11 -o eff_cbwc_main eff_cbwc_main.cpp Cum.cpp CalCum.cpp `root-config --libs --cflags`

clean:
	@rm eff_cbwc_main

