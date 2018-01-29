#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
struct Pizza{
	char name[64];
	float pizzaPerDollar;
	struct Pizza* next;
};
void addPizza(struct Pizza** head, struct Pizza* ptr){
	struct Pizza* current = *head;
	if(ptr->pizzaPerDollar > (*head)->pizzaPerDollar || (ptr->pizzaPerDollar == (*head)->pizzaPerDollar && strcmp(ptr->name,(*head)->name) < 0)){
		ptr->next = *head;
		*head = ptr;
	}else{
		while((current->next != NULL && current->next->pizzaPerDollar > ptr->pizzaPerDollar)
			||(current->next != NULL && current->next->pizzaPerDollar == ptr->pizzaPerDollar && strcmp(current->next->name,ptr->name) < 0)){
			current = current->next;
		}
		ptr->next = current->next;
		current->next = ptr;
	}
}
int main(int argc, char* argv[]){
	//get stuff ready for reading file and using fgets
	char* fileName = argv[1];
	char line[64];
	FILE *fr = fopen(fileName,"rt");
	float diameter;
	float cost;
	//initialize just the head of the linked list
	struct Pizza* head = (struct Pizza*)malloc(sizeof(struct Pizza));
	if(fgets(line,64,fr) == NULL){
		printf("PIZZA FILE IS EMPTY");
		free(head);
		return EXIT_SUCCESS;
	}
	strcpy(head->name, strtok(line, "\n"));
	fgets(line,64,fr);
	diameter = atof(line);
	fgets(line,64,fr);
	cost = atof(line);
	if(cost == 0 || diameter == 0){
		head->pizzaPerDollar = 0;
	}else{
		head->pizzaPerDollar = (PI/4)*pow(diameter,2)/cost;
	}
	head->next = NULL;
	//now add the rest of the pizzas in the list to the head of the linked list using addPizza()
	struct Pizza* ptr;
	fgets(line,64,fr);
	while(strcmp(line,"DONE\n") != 0){
		ptr = (struct Pizza*)malloc(sizeof(struct Pizza));
		strcpy(ptr->name, strtok(line, "\n"));
		fgets(line,64,fr);
		diameter = atof(line);
		fgets(line,64,fr);
		cost = atof(line);
		if(cost == 0 || diameter == 0){
			ptr->pizzaPerDollar = 0;
		}else{
			ptr->pizzaPerDollar = (PI/4)*pow(diameter,2)/cost;
		}
		ptr->next = NULL;
		addPizza(&head,ptr);
		fgets(line,64,fr);
	}
	//print out all values of sorted linked list
	while(head != NULL){
		printf("%s ",head->name);
		printf("%f\n",head->pizzaPerDollar);
		struct Pizza* temp = head;
		head = head->next;
		if(temp!= NULL){
			free(temp);
		}
	}
	fclose(fr);
	return EXIT_SUCCESS;
}
