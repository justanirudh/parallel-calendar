#include <stdbool.h>
struct eventNode
{
  char* time;
  char* name;
	char* location;
  struct eventNode  *next;
};

typedef struct eventNode* EventNode;

struct dayNode
{
  char* date;
  EventNode head;
  struct dayNode  *next;
};

typedef struct dayNode* DayNode;

struct daysInfo{
  int size;
  DayNode head;
};

typedef struct daysInfo* DaysInfo;

DaysInfo initializeDaysInfo();
char** str_split(char*, const char);
DayNode initializeDayNode(char*);
EventNode initializeEventNode(char*, char*, char*);
void addDayNodeAndFirstEventNode(DaysInfo cal, DayNode pred, char*, char*, char* name,char*  time, char* location); 
void createEvent(DayNode curr, char* name, char*  time, char*  location );
void deleteEvent(DayNode curr, char* name, char* time, bool consider_time);
void modifyEvent(DayNode curr, char* name, char* time, char* location);

