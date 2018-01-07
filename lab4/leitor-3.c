#include "LAB4.h"

typedef struct ThreadInformation{
	int firstLine;
	int nLines;
	char firstString[NBYTES];
	char fileName[LENFILENAME];
}*ThreadInfo;

void* leitor (void* ti) {
  ThreadInfo threadinfo = (ThreadInfo)ti;
  int fd,i,fl;
  fd  = open(threadinfo->fileName, O_RDONLY);
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
	 char buff[NBYTES];
	 lseek(fd, (threadinfo->firstLine)*NBYTES*sizeof(char), SEEK_SET);
    if (read (fd, threadinfo->firstString, NBYTES) == -1) {
      perror("Error reading file");
      free(threadinfo);
      pthread_exit((void*)-1);
    }
    for (i=0; i<(threadinfo->nLines)-1; i++) {
      if (read (fd, buff, NBYTES) == -1) {
		perror("Error reading file");
		free(threadinfo);
		pthread_exit((void*)-1);
      }
      if (strncmp(buff, threadinfo->firstString,NBYTES)) {
		fprintf(stderr, "Incorrect file: %s\n", threadinfo->fileName);
		free(threadinfo);
		pthread_exit((void*)-1);
      }
    }
    fl = flock(fd, LOCK_UN);
	if (fl ==-1){
		perror("flock unsuccessful");
		free(threadinfo);
		pthread_exit((void*)-1);
	}
    if (close (fd) == -1)  {
      perror("Error closing file");
      free(threadinfo);
      pthread_exit((void*)-1);
    }
  }
  free(threadinfo);
  pthread_exit((void*)0);
  return NULL;
}

int main(){
	
	char* fileNames[NFILES] = {"SO2014-0.txt","SO2014-1.txt","SO2014-2.txt","SO2014-3.txt","SO2014-4.txt"};
	char* file; 
	pthread_t threads[K];
	int size,remainder,i,start,*status, random, sumReturnValues=0;
	size = L/K;
	remainder = L%K;
	srand(time(NULL));
	random = rand()%NFILES;
	file = fileNames[random];
	for(i=0,start=0;i<K;i++,start+=size){
		ThreadInfo ti = (ThreadInfo)malloc(sizeof(struct ThreadInformation));
		if(i==K-1){
			ti->nLines = size+remainder;
		}
		else{
			ti->nLines = size;
		}
		ti->firstLine = start;
		strcpy(ti->fileName,  file);
		if(pthread_create(&(threads[i]),NULL, leitor, ti)){
			perror("Failed to create thread");
			free(ti);
			exit(-1);
		}
	}
	for (i=0;i<K;i++){
        if(pthread_join(threads[i],(void**)&status)){
			printf("Failed to join thread\n");
			exit(-1);
		}
		sumReturnValues += status;
    }
    if(sumReturnValues == 0){
		printf("Correct file: %s\n", file);
	}
	return 0;
}




