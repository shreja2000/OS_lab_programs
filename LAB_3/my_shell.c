#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

struct list{
	int count;
	struct node *head;
};

struct node{
	char *command;
	struct node *next;
};

struct list history;

void insert (char *);
void show (int);
void get_cmd(char *[]);

int main (){

	char hostname[HOST_NAME_MAX], username[LOGIN_NAME_MAX], work_dir[PATH_MAX];
	gethostname(hostname, 20);
	getlogin_r(username, 20);

	history.count = 0;
	history.head = NULL;

	printf("\n\n\n\033[1;36m  ************* W E L C O M E ***************\033[0m\n\n\n");
	char *argv[100];
	
	while(1){

		getcwd(work_dir, sizeof(work_dir));
		printf("\033[1;31m%s@\033[1;34m%s:\033[1;37m%s\033[1;39m@ \033[0m", username, hostname, work_dir);
		// printf("\033[1;36msubash:\033[0m ");
		char *argv[100];
		get_cmd(argv);

		if(strcmp(argv[0],"exit")==0){
			exit(0);
		}
		else if(argv[0][0] == '!'){
			if(argv[1] != NULL){
				show(atoi(argv[1]));
			}
			else{
				show(10);
			}
		}
		else if(strcmp(argv[0],"cd")==0){
			chdir(argv[1]);
		}
		else{
			pid_t pid = vfork();
			if(pid == 0){
				execvp(argv[0], argv);
			}
			else{
				wait(NULL);
			}
		}
	}
	return 0;
}

void get_cmd(char *argv[100]){

	char *user_input = (char *)malloc(100);
	scanf(" %[^\n]", user_input);
	
	char *cmd = (char *)malloc(100);
	strcpy(cmd, user_input);
	insert(cmd);

	argv[0] = strtok(user_input, " ");
	int i=0;

	while (argv[i] != NULL) {
		i++;
		argv[i] = strtok(NULL, " ");
	}
}

void insert (char *cmd){
	
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->command = cmd;
	
	if(history.head == NULL){
		temp->next = NULL;
		history.head = temp;
		history.count = 1;
		return;
	}

	temp->next = history.head;
	history.head = temp;

	if(history.count == 10){
		struct node* temp = history.head, temp1;
		
		for(int i=0; i<9; i++){
			temp = temp->next;
		}
		temp->next = NULL;
	}
	else{
		history.count += 1;
	}
	
}

void show (int n){

	struct node* temp = history.head;
	int counter = 0;
	while(temp != NULL && counter < n){
		printf("%s\n", temp->command);
		temp = temp->next;
		counter += 1;
	}
}