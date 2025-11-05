
#/*Archivo Makefile para compilar el codigo completo para la realizacion de este taller*/

GCC = gcc
MODULO = funciones
PROGRAMAS = tallerFork

tallerFork: $(MODULO).o
	$(GCC) $@.c $(MODULO).o -o $@

$(MODULO).o: $(MODULO).c
	$(GCC) $(MODULO).c -c

clear:
	$(RM) $(PROGRAMAS) $(MODULO).o
