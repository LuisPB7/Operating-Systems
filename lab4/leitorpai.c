#include "LAB4.h"

int main(){
	
	int i, status, ex, valorExit;
	char* fileNumber;
	char* fileNumbers[NFILES] = {"0","1","2","3","4"};
	pid_t pid;
	srand(time(NULL));
	for(i=0; i<NCHILDREN; i++){
		fileNumber = fileNumbers[rand()%NFILES];
		pid = fork();
		if(pid == -1){
			perror("Fork has failed");
			exit(-1);
		}
		if(pid==0){
			ex = execl("./leitor", "leitor", fileNumber, NULL);
			if(ex==-1){
				perror("Execl has failed");
				exit(-1);
			}
			exit(status);
		}
	}
	
	for(i=0; i<NCHILDREN; i++){
		pid = wait(&status);
		if (pid == -1) {
		  perror("Error on wait.");
		  exit(-1);
		}
		if (WIFEXITED(status)) {
		  valorExit = (char) WEXITSTATUS(status);
		  printf("Child with pid=%ld completed with status %d\n", (long)pid, valorExit);
		}
		else /* caso em que filho terminou sem exit ou return */
		printf("Child with pid=%ld completed without exit/return\n", (long)pid);
	}
	
	return 0;
	
}
