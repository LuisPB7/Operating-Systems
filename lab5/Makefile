all: ESCRITOR LEITOR MONITOR ESCRITOR-SIMPLES
	
ESCRITOR-SIMPLES:
	gcc -ansi -Wall -pedantic -o ESCRITOR-SIMPLES ESCRITOR-SIMPLES.c

ESCRITOR:
	gcc -ansi -Wall -pedantic -w -o ESCRITOR ESCRITOR.c -lpthread 
	
LEITOR:
	gcc -ansi -Wall -pedantic -w -o LEITOR LEITOR.c -lpthread 
	
MONITOR:
	gcc -ansi -Wall -pedantic -w -o MONITOR MONITOR.c -lpthread 
