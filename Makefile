GCC = gcc
FLAGS =
MODULO =

PROGRAMAS = lab00 lab01 lab02 lab03 lab04 lab05 lab06 lab07

all: $(PROGRAMAS)

lab00:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab01:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab02:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab03:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab04:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab05:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab06:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

lab07:
	$(GCC) $(FLAGS) $@.c $(MODULO) -o $@

clean:
	rm -f $(PROGRAMAS)

