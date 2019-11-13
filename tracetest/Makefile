INC_CXXFLAGS ?= -I$(CURDIR)/../include

objects = main.o

libs = $(CURDIR)/../trace/libtrace.a \
       $(CURDIR)/../timer/libtimer.a \
       $(CURDIR)/../ppm/libppm.a
	
.PHONY: all
all: tracetest

tracetest: $(objects) $(libs)
	$(CXX) $^ -o $@

main.o: main.cc

%.o: %.cc
	$(CXX) $(INC_CXXFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(objects) tracetest

.PHONY: test
test:

.PHONY: install
install:
