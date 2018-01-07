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
#include <sys/file.h>
#include <fcntl.h> 
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <bits/sigaction.h>

int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);

#define NFILES 5
#define BUFFSIZE 50
#define NSTRINGS 10
#define NLINES 1024
#define NTIMES 512
#define NCHARS 11
#define NBYTES 10
#define NTIMESCHILD 10
#define NTHREADS 3
#define LENFILENAME 13
#define L 1024
#define K 10
#define NCHILDREN 3
#define NUMBER_INDEX 7
