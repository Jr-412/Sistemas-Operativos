###################################################################################
#		Pontificia Universidad Javeriana
#	Autor: Juan José Ballesteros
#	       Juan Diego Rojas
#	Materia: Sistemas Operativos
#	Fichero: Automatizacion de compilación para taller 
###############################################################################

GCC = gcc
CFLAGS = -Wall
LDFLAGS = -pthread -lrt

all: concurrenciaPosix posixSincro producer consumer

# Programa concurrenciaPosix
concurrenciaPosix: concurrenciaPosix.c maximo.c
	$(GCC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Programa posixSincro
posixSincro: posixSincro.c buffer.c
	$(GCC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Productor con memoria compartida y semáforos POSIX
producer: producer.c
	$(GCC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Consumidor con memoria compartida y semáforos POSIX
consumer: consumer.c
	$(GCC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f concurrenciaPosix posixSincro producer consumer