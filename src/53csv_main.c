#include "hw3_p1.h"
#include "linkedList.h"

// 53csv implemenation
void idInsertion(void *student1, void *student2);

int main(int argc, char* argv[]){

//    Student *s1 = malloc(sizeof(Student));
//    Student *s2 = malloc(sizeof(Student));
//
//
//    //s1
//    s1->id = 123;
//    s1->name.firstName = "abc";
//    s1->name.lastName = "sas";
//    s1->name.middleName = "wef";
//    s1->hw_score[0] = 1;
//    s1->hw_score[1] = 2;
//    s1->hw_score[2] = 3;
//    s1->m_scores->m1_score = 23;
//    s1->m_scores->m2_score = 45;
//    s1->final = 0;
//
//    //s2
//    s1->name.firstName = "vvads";
//    s1->name.lastName = "asdfas";
//    s1->name.middleName = "asdfaasd";
//    s1->hw_score[0] = 23;
//    s1->hw_score[1] = 26;
//    s1->hw_score[2] = 756;
//    s1->m_scores->m1_score = 764;
//    s1->m_scores->m2_score = 674;
//    s1->final = 34;

    int (*value)(void *, void *);
    int command = atoi(argv[1]);
    if(command== 1)
        value = &idComparator;
    else if(command == 2)
        value = &nameComparator;
    else if(command== 3)
        value = &totalHWComparator;
    else if(command == 4)
        value = &totalMidtermComparator;
    else if(command == 5)
        value = &totalPtsComparator;
    else
        return 0;
    List_t *list = malloc(sizeof(List_t));
    list->length = 0;
    list->comparator = value;
//
//    char *firstName = malloc(20*sizeof(char));
//    char *lastName = malloc(20*sizeof(char));
//    char *middleName = malloc(20*sizeof(char));
//
//    int m1 = 0;
//    int m2 = 0;
//
//    int id = 0;
//    int hw[3];
//    int final = 0;

    Student *student = malloc(sizeof(Student*));
    int index = 0;
    char *buffer = malloc(100);
    int size = 1;

    while(fscanf(stdin,"%s", buffer) == 1){
        student = malloc(sizeof(Student*));

        struct person *p = malloc(sizeof(struct person));
        p->firstName = malloc(20*sizeof(char));
        p->lastName = malloc(20*sizeof(char));
        p->middleName = malloc(20* sizeof(char));
        //        student->name.firstName = ;
//        student->name.lastName = malloc(20*sizeof(char));
//        student->name.middleName = malloc(20*sizeof(char));

//         student->m_scores = malloc(sizeof(Midterms));
        Midterms *m = malloc(sizeof(Midterms));

        char *temp = strtok (buffer, ",");
        student->id = atoi(temp);

        temp = strtok(NULL,",");
        strcpy(p->firstName, temp);
        temp = strtok(NULL,",");
        strcpy(p->lastName, temp);
        temp = strtok(NULL,",");
        if(isdigit(*temp))
            p->middleName = "";
        else {
            strcpy(p->middleName, temp);
            temp = strtok(NULL, ",");
        }

        student->name = *p;


        student->hw_score[0] = atoi(temp);
        temp = strtok(NULL, ",");
        student->hw_score[1] = atoi(temp);
        temp = strtok(NULL, ",");
        student->hw_score[2] = atoi(temp);

        temp = strtok(NULL, ",");
        m->m1_score = atoi(temp);
        temp = strtok(NULL, ",");
        m->m2_score = atoi(temp);

        student->m_scores = m;

        temp = strtok(NULL, ",");
        student->final = atoi(temp);

        insertInOrder(list, student);

        free(buffer);
        buffer = malloc(100);
        student++;
        size++;
    }

    printCSVStudentList(list);
    return 0;
}
