#include "LAB5.h"

char tmp[LENFILENAME];

int main(){
	pid_t leitor, escritor;
	int leitorStatus, escritorStatus;
	int mypipe[2];
	char* input;

	if ((pipe (mypipe)) < 0){
		exit(-1);
    }

	escritor = fork(); 
	if (escritor == -1){
		perror("Fork failed");
		exit(-1);
	}
	else if ( escritor == 0){
		execl("./ESCRITOR", "ESCRITOR",NULL);
		exit(escritorStatus);
	}

	leitor = fork(); 
	if (leitor == -1){
		perror("Fork failed");
		exit(-1);
	}
	else if (leitor == 0){
		close(mypipe[1]);
      	read(mypipe[0], tmp, LENFILENAME);
		execl("./LEITOR", "LEITOR",NULL);
		exit(leitorStatus);
	}
	else if ( leitor!=0 && escritor !=0){	
		read(STDIN_FILENO, input, 100);								
	    while(strncmp(input, "sair",4*sizeof(char) ) != 0){
	    	if(strncmp(input, "il",2*sizeof(char)) == 0){
	    			kill(escritor, SIGUSR1);
	    	}
	    	else if(strncmp(input, "ie", 2*sizeof(char)) == 0){
	    			kill(escritor, SIGUSR2);
	    	}
	    	else{
				write(mypipe[1], input, LENFILENAME); 
		   		
		   	}
		   	close(mypipe[1]);
		   	kill(escritor, SIGTSTP);
		   	wait(&escritorStatus);
		   	wait(&leitorStatus);
		}

	}
	exit(0);
}
