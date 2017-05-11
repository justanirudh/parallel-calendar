#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include"data_def.h"
#include <stdbool.h>

int main (){
	
	setbuf(stdout, NULL);
	DaysInfo graph = initializeDaysInfo();	
	for(;;){		
		char *buffer;
		size_t bufsize = 50;
		size_t size_chars;

		buffer = (char *)malloc(bufsize * sizeof(char));
		if( buffer == NULL){
			perror("Unable to allocate buffer");
			exit(1);
		}

		size_chars = getline(&buffer,&bufsize,stdin);
		if(size_chars == EOF){ //this is where program will normally stop
			return 0;
		}
		buffer = strtok(buffer, "\n");
 
		char** tokens = str_split(buffer, ',');

		char* action = *tokens;
		char* name = *(tokens + 1);
		char* date = *(tokens + 2);
		char* time = *(tokens + 3);
		char* location = *(tokens + 4);
		
		if(graph->size == 0){ //graph is empty, first entry
			if(strcmp(action, "D") == 0 || strcmp(action, "X") == 0 ){
				printf("Cannot delete or change an event in an empty calendar\n");
				continue;
			}
			DayNode dn = initializeDayNode(date);
			EventNode en = initializeEventNode(name, time, location);
			graph->head = dn;
			(graph->size)++;
			dn->head = en;
			printf("%s:%s\n", date, location);
		}
		else{ //graph is non-empty
			//check if the date exists or not
			DayNode pred;
			DayNode curr = graph->head;
			while(curr != NULL && strcmp(curr->date, date) != 0){
				pred = curr;
				curr = curr->next;
			}
			if(curr == NULL ) //date doesnt exist in graph
				addDayNodeAndFirstEventNode(graph, pred, date,action, name, time, location); //also prints 
			else{ //date exists in graph
				if(curr->head == NULL){ //head of the date node points to null
					if(strcmp(action, "D") == 0 || strcmp(action, "X") == 0 ){
						printf("Cannot delete or change an event in an empty calendar for the date %s\n", date);
						continue;
					}
					EventNode en = initializeEventNode(name, time, location);
					curr->head = en;
					printf("%s:%s\n", date, location);
				}
				else{ //head of date node does not point to null. Then iterate over eventNodes
					//location of old first event node
					EventNode en = curr->head; //curr is current DayNode and is not null
					char* oldLocation = en->location;
					//now do any one of the stated actions
					if( strcmp(action, "C") == 0 ){
						createEvent(curr, name, time, location );
					}
					else if (strcmp(action, "D") == 0 ){
						deleteEvent(curr, name, time, true);
					}
					else if (strcmp(action, "X") == 0 ){
						modifyEvent(curr, name, time, location);
					}
					else {
						printf("Unknown event type: %s\n", action);
						continue;
					}
					//if there is any change to the location of the earliest meeting on a date, 
					//then it will output the date along with the new location of the earliest meeting on that date.
					en = curr->head; //potentially new head
					if(en == NULL) //was not null before
						printf("%s:None\n", date);
					else{
						char* newLocation = en->location;
						if(strcmp(oldLocation, newLocation) != 0) //if location changed, print
							printf("%s:%s\n", date, newLocation);
					}
				}
			}
		}		
	}
	return 0; //flow will almost NEVER come here
}

