#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int idNo;
    double avgGrade;
    int age;
    char *name;
} Student;


void* encodeArray(void* *array, int size, void*(*encodeVar)(void*));
void* encodeStudentAge(void *s);
void printStudents(Student **array, int size);
void printStudent(Student *s);

int main(){
    Student a = {1,80,19,"a"};
    Student b = {1,80,19,"b"};
    Student c = {1,80,19,"c"};
    Student d = {1,80,19,"d"};
    Student e = {1,80,19,"e"};
    Student f = {1,80,19,"f"};
    Student *studentArray[] = {
            &a,
            &b,
            &c,
            &d,
            &e,
            &f,
    };
    printf("before:\n");
    printStudents(studentArray, 6);

    encodeArray((void **) studentArray, 6, encodeStudentAge);

    printf("after:\n");
    printStudents(studentArray, 6);
    return 0;
}

void printStudents(Student **array, int size) {
    int i;

    for (i=0; i<size; i++){
        printStudent(array[i]);
    }
}

void printStudent(Student *s) {
    printf("------------------------------\n");
    printf("name: %s\n", s->name);
    printf("id #: %d\n", s->idNo);
    printf("age: %d\n", s->age);
    printf("average grade: %.2lf\n", s->avgGrade);
    printf("------------------------------\n");
}

/*  input: student
 *  output: student, with encrypted age
 * */
void* encodeStudentAge(void *s){
    Student *student = (Student*)s;
    int newAge = 0;
    int i;

    for (i=0; i<sizeof(int)*8;i++){
        newAge |= student->age&0x1;
        newAge <<= 1;
        student->age >>= 1;
    }

    student->age = newAge;
    return (void*)student;
}

/*  intput: array & it's size. encoding function
 *  output: new array filled with elements that encodeVar was called upon
 *          each index in original array
 *  calls encodeVar function on each element in array
 * */
void* encodeArray(void* *array, int size, void*(*encodeVar)(void*)){
    void* *newArray;
    int i;

    newArray = malloc(size* sizeof(void*));

    for (i=0; i<size; i++){
        newArray[i] = encodeVar(array[i]);
    }

    return newArray;
}