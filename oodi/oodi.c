#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oodi.h"

// Mikael Nenonen k90390
// 2017-07-10

int init_record(struct oodi *or, const char *p_student, const char *p_course,
        unsigned char p_grade, struct date p_compdate) {
  // Check if the student number has an end sign, and abort if needed
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
  
  // Copy the course name
  strcpy(or->student, p_student);
  int course_array_length = 1;  // There's the end sign
  const char* p_course_copy = p_course;
  while(*p_course_copy) {
    course_array_length++;
    p_course_copy++;
  }
  or->course = (char *) malloc(course_array_length);
  if(!or->course)
    return 0;
  // and the rest of the fields
  strcpy(or->course, p_course);
  or->grade = p_grade;
  or->compdate = p_compdate;
  return 1;
}

void print_oodi(struct oodi printed) {
  if(&printed == 0) {
    printf("The oodi given was NULL!\n");
  } else {
    printf("Student: %s\n", printed.student);
  }
}

struct oodi *add_record(struct oodi *array, unsigned int size, struct oodi newrec) {
/*  struct oodi* new_array;
  if(array == 0) {
    new_array = malloc(sizeof(struct oodi));
  } else {
    new_array = realloc((void*)array, sizeof(struct oodi)*size+1)
  }
  array[size] = newrec;
  */
  int i;
  for(i=0; i<size; i++) {
    print_oodi(array[i]);
  }
  return array;
}

int change_grade(struct oodi *array, unsigned int size, const char *p_student,
        const char *p_course, unsigned char newgrade, struct date newdate) {
  return 0;
}

int main(void) {
  return 0;
}