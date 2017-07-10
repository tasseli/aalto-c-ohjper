#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-07-10

int init_record(struct oodi *or, const char *p_student, const char *p_course,
        unsigned char p_grade, struct date p_compdate) {
  int i;
  int ended=0;
  for(i=0; i<7; i++) {
    if(*(p_student+i))
      continue;
    ended = 1;
    break;
  }
  if(!ended)
    return 0;
  
  strcpy(or->student, p_student);
  or->course = p_course;
  or->grade = p_grade;
  or->compdate = p_compdate;
  return 1;
}
