#include "hw3_p1.h"

int intComparator(void* p, void* q) {
    return ((int)p - (int)q);
}

int strComparator(void* str1, void* str2) {
    char* s1 = (char*)str1, *s2 = (char*)str2;
    for (; *s1 && *s2 && *s1 == *s2; ++s1, ++s2){}
    if (*s1 < *s2){
        return -1;
    }
    else if (*s1 > *s2){
        return 1;
    }
    return 0;
}

int idComparator(void *student1, void *student2){
    //return -1 if id of student1 is less than id of student2
    //return 1 if id of student1 is greater than id of student2
    //return 0 if id of student1 = studnet2

    int *stud_ID_1 = &((Student *)student1)-> id;
    int *stud_ID_2 = &((Student *)student2)-> id;
    int value = *stud_ID_1 - *stud_ID_2;
    if(value == 0)
        return 0;
    else if(value < 0)
        return -1;
    return 1;
}

int nameComparator(void *student1, void *student2){
    //sort by the name field (L_N, F_N, M_N)
    //ties are broken using the id(unique)
    //empty strings come lexicographoiically before any string

    //return -1 if stud1<stud2
    //return 1 if stud1>stud2

    //    Student *s1 = student1;
    //    Student *s2 = student2;

    char *Stud_1_LN =  ((Student*)student1)->name.lastName;
    char *Stud_2_LN =  ((Student*)student2)->name.lastName;

    int L_N_condition = strComparator(Stud_1_LN, Stud_2_LN);
    if(L_N_condition == -1)
        return -1;
    else if(L_N_condition == 1)
        return 1;

    char *Stud_1_FN =  ((Student*)student1)->name.firstName;
    char *Stud_2_FN =  ((Student*)student2)->name.firstName;

    int F_N_condition = strComparator(Stud_1_FN, Stud_2_FN);
    if(F_N_condition == -1)
        return -1;
    else if(F_N_condition == 1)
        return 1;
    char *Stud_1_MN =  ((Student*)student1)->name.middleName;
    char *Stud_2_MN =  ((Student*)student2)->name.middleName;

    int M_N_condition = strComparator(Stud_1_MN, Stud_2_MN);
    if(M_N_condition == -1)
        return -1;
    else if(M_N_condition == 1)
        return 1;

    return idComparator(student1,student2);
}

int totalHWComparator(void *student1, void *student2){
    //add hw1 + hw2 + he3
    //tie use student id


    //return -1 if s1<s2
    //return 1 if s1>s2
    //return student id if tie


    int stud1_hw_score = 0;
    int stud2_hw_score = 0;
    int i = 0;
    for(i = 0; i < 3; i++){
        stud1_hw_score += *((((Student*)student1)->hw_score)+i);
        stud2_hw_score += *((((Student*)student2)->hw_score)+i);
    }
    if(stud1_hw_score<stud2_hw_score)
        return -1;
    else if(stud1_hw_score>stud2_hw_score)
        return 1;
    return idComparator(student1,student2);
}

int totalMidtermComparator(void *student1, void *student2){
    //return -1 if st1<st2
    //return 1 if st1>st2

    int Midterm_St1 = (((Student*)student1)->m_scores)->m1_score +
                      (((Student*)student1)->m_scores)->m2_score;
    int Midterm_St2 = (((Student*)student2)->m_scores)->m1_score +
                      (((Student*)student2)->m_scores)->m2_score;

    if(Midterm_St1 < Midterm_St2)
        return -1;
    else if(Midterm_St1 > Midterm_St2)
        return 1;
    return idComparator(student1,student2);
}

int totalPtsComparator(void *student1, void *student2){
    //all hws _ allmidterm + final
    int Midterm_St1 = (((Student*)student1)->m_scores)->m1_score +
                      (((Student*)student1)->m_scores)->m2_score;
    int Midterm_St2 = (((Student*)student2)->m_scores)->m1_score +
                      (((Student*)student2)->m_scores)->m2_score;
    int stud1_hw_score = 0;
    int stud2_hw_score = 0;

    int i = 0;
    for(i = 0; i < 3; i++){
        stud1_hw_score += *((((Student*)student1)->hw_score)+i);
        stud2_hw_score += *((((Student*)student2)->hw_score)+i);
    }
    int score_student1 = stud1_hw_score + Midterm_St1;
    int score_studnet2 = stud2_hw_score + Midterm_St2;
    if(score_student1<score_studnet2)
        return -1;
    else if(score_student1>score_studnet2)
        return 1;
    return idComparator(student1,student2);
}

void printCSVStudentList(List_t *list){
    //idNum, FN, LN, MN, hw1, hw2, hw3, mt1, mt2, final

    node_t *currentStudent;
    while(list->head != '\0'){
        currentStudent = ((Student*)list->head);
        Student *s = currentStudent->value;
        printf("%d,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                s->id,s->name.firstName, s->name.lastName, s->name.middleName, s->hw_score[0],
                s->hw_score[1], s->hw_score[2], s->m_scores->m1_score, s->m_scores->m2_score,
                s-> final);
        list->head = list->head->next;
    }
}