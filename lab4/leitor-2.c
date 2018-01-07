#include "LAB4.h"

void* leitor (void* f) {
  char* file = (char*)f;
  int fd,i,fl;
  fd  = open(file, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    pthread_exit((void*)-1);
  }
  fl = flock(fd, LOCK_SH);
  if (fl ==-1){
	perror("flock unsuccessful");
	pthread_exit((void*)-1);
  }
  else {
    char buff[NBYTES+1];
    char teste[NBYTES+1];
    if (read (fd, teste, NBYTES) == -1) {
      perror("Error reading file");
      pthread_exit((void*)-1);
    }
    for (i=0; i<NLINES-1; i++) {
      if (read (fd, buff, NBYTES) == -1) {
		perror("Error reading file");
		pthread_exit((void*)-1);
      }
      if (strncmp(buff, teste, NBYTES)) {
		fprintf (stderr, "Incorrect file: %s\n", file);
		pthread_exit((void*)-1);
      }
    }
    fl = flock(fd, LOCK_UN);
	if (fl ==-1){
		perror("flock unsuccessful");
		pthread_exit((void*)-1);
	}
    if (close (fd) == -1)  {
      perror("Error closing file");
      pthread_exit((void*)-1);
    }
  }
  printf("Correct file: %s\n", file);
  pthread_exit((void*)0);
  return NULL;
}

int main(){
	
	char* fileNames[NFILES] = {"SO2014-0.txt","SO2014-1.txt","SO2014-2.txt","SO2014-3.txt","SO2014-4.txt"};
	pthread_t threads[NTHREADS];
	int i, *status;
	srand(time(NULL));
	for(i=0;i<NTHREADS;i++){
		if(pthread_create(&(threads[i]),NULL, leitor, fileNames[rand()%NFILES])){
			perror("Failed to create thread");
			exit(-1);
		}
	}
	for (i=0;i<NTHREADS;i++){
        if(pthread_join(threads[i],(void**)&status)){
			printf("Failed to join thread\n");
			exit(-1);
		}
		printf("Thread returned %d\n", status);
    }
	return 0;
}
