/*
 **************************************************************** 
 * Grupo 34
 * 
 * António Tavares, nº78122
 * Luís Borges, nº78349
 * Paulo Ritto, nº78929
 * 
 **************************************************************** */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <sys/time.h>
#include <fcntl.h> 
#include <time.h>
#include <signal.h>


#define NFILES 5
#define NSTRINGS 10
#define NLINES 1024
#define NTIMES 512
#define NCHARS 11
#define NBYTES 10
#define NTIMESCHILD 10
