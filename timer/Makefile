objects = function.o main.o

.PHONY: all
all: libtimer.a

libtimer.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

function.o: function.cc timer.h

main.o: main.cc timer.h

.PHONY: clean
clean:
	$(RM) libtimer.a $(objects)

.PHONY: install
install:

.PHONY: test
test:
