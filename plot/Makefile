CPP = g++ -Wall -std=c++11
CPPFLAGS = -O2
CPPFLAGS += $(shell root-config --cflags)
LDFLAGS = $(shell root-config --cflags --libs)

all:
	@echo "Please give an option."
first:
	@mkdir -p output/files/third/ output/pics/
	@g++ -Wall -std=c++11 -o first first_systematic.cpp `root-config --libs --cflags`
clean:
	@rm -rf first output/files/ output/pics/

