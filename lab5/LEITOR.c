#include "LAB5.h"

pthread_mutex_t lock;
sem_t full, empty, input;

char* files[BUFFSIZE];
int top = 0;
int bot = 0;

void putInBuffer(char* file){
	sem_wait(&empty);
	pthread_mutex_lock(&lock);
	files[top] = file;
	top = (top +1)%BUFFSIZE;									
	pthread_mutex_unlock(&lock);
	sem_post(&full);
}

char* removeFromBuffer(){
	char* file;
	sem_wait(&full);
	pthread_mutex_lock(&lock);
	file = files[bot];
	bot = (bot +1)%BUFFSIZE;
	pthread_mutex_unlock(&lock);
	sem_post(&empty);
	return file;
}

void* leitor(){
	int op,i,r,cl,fl;
	char* file = removeFromBuffer();
	char* buff = malloc(NCHARS * sizeof(char));
	char* teste = malloc(NCHARS * sizeof(char));
	while(1){
		sem_wait(&input);
		op = open(file, O_RDONLY);
		if(op == -1) {
			perror("Open unsuccessful");
			pthread_exit((void*)-1);
		}
		fl = flock(op, LOCK_SH);
		if (fl ==-1){
			printf("flock unsuccessful\n");
		}
		r = read(op, teste, NBYTES);
		if(r == -1){
			perror("Read unsuccessful");
			pthread_exit((void*)-1);
		}
		for(i=0; i<NLINES-1; i++){
		 r = read(op, buff, NBYTES);
		 if(r == -1){
			perror("Read unsuccessful");
			pthread_exit((void*)-1);
		 }
		 if(strcmp(buff,teste) != 0){
		  printf("Incorrect file\n");
		  pthread_exit((void*)-1);
		 }
		}
		fl = flock(op, LOCK_UN);
		if (fl ==-1){
			printf("flock unsuccessful\n");
		}
		cl = close (op);
		if(cl == -1){
			perror("Close unsuccessful");
			pthread_exit((void*)-1);
		}
		printf("Correct file: %s\n", file);
    }
	pthread_exit((void*)0);
	return NULL;
}

int main(){
	pthread_t threads[NTHREADS];
	int i, *status;
	char number;
	char file[LENFILENAME];
	sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFSIZE);
    sem_init(&input, 0, 0);
	if (pthread_mutex_init(&lock, NULL))
    {
        perror("\n mutex init failed\n");
        exit(-1);
    }
	for(i=0;i<NTHREADS;i++){
		if(pthread_create(&(threads[i]),NULL, leitor,NULL)){
			perror("Failed to create thread");
			exit(-1);
		}
	}
	while(1){
		read(STDIN_FILENO, file, LENFILENAME);
		if((strcmp(file,"SO2014-0.txt\n") != 0) && (strcmp(file,"SO2014-1.txt\n") != 0) && (strcmp(file,"SO2014-2.txt\n") != 0) && (strcmp(file,"SO2014-3.txt\n") != 0) && (strcmp(file,"SO2014-4.txt\n") != 0)){
			printf("Incorrect file\n");
		}
		else{
			number = file[NUMBER_INDEX];
			sprintf(file, "SO2014-%c.txt", number);
			putInBuffer(file);
			sem_post(&input);
		}
	}
	for (i=0;i<NTHREADS;i++){
        if(pthread_join(threads[i],(void**)&status)){
			perror("Failed to join thread");
			exit(-1);
		}
		printf("Thread returned %d\n", status);
    }
    pthread_mutex_destroy(&lock);
    free(file);
	return 0;
}
