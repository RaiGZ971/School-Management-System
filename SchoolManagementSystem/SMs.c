#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSTUDENT 100

//STRUCTURES
struct Program
{
    char course[50];
    int section;
    int pYear;
};

struct Name
{
    char first[50];
    char middle[50];
    char last[50];
};

struct Birth
{
    char month[50];
    int day;
    int bYear;
};

struct Student
{
    char ID[50];
    char gender;
    struct Name name;
    struct Birth birth;
    struct Program program;
};

//FUNCTION DECLARATION (Insert Data, Find Student Data, Count Student, Delete a Student, Update Student Data)

void readData(struct Student *p);           //DONE

void insertData(struct Student *p);         //DONE

void findStudent(struct Student *p);        //DONE

int getLastIndex();                         //DONE

void countStudent(struct Student *p);       //DONE

void deleteStudent(struct Student *p);      //DONE

void updateStudent(struct Student *p);      //DONE

//MAIN FUNCTION

int main(int argc, char const *argv[])
{
    bool isExit = false;
    struct Student student[MAXSTUDENT];
    readData(student);

    do{
        int function;
        printf("\n\t=====Student System Management=====\n");
        printf("\n\t1) Insert Student Data\n\t2) Find Student Data\n\t3) Display Numbers of Enrolees\n\t4) Delete Student Data\n\t5) Update Student Data\n\t6) Exit\n");
        printf("\n\tEnter: ");
        scanf("%d", &function);
        printf("\n\t-----------------------------------\n");

        switch(function){
        case 1:
            printf("\n\t========Insert Student Data========\n");
            insertData(student);
            break;
        case 2:
            printf("\n\t========Find Student Data========\n");
            findStudent(student);
            break;
        case 3:
            printf("\n\t========Count Student Data========\n");
            countStudent(student);
            break;
        case 4:
            printf("\n\t========Delete Student Data========\n");
            deleteStudent(student);
            break;
        case 5:
            printf("\n\t========Update Student Data========\n");
            updateStudent(student);
            break;
        case 6:
            printf("\n\t[Exiting System...]\n");
            sleep(3);
            isExit = true;
            break;
        default:
            sleep(1);
            system("cls");
            break;    
        }

    }while(isExit == false);
    
    return 0;
}

//FUNCTION ALGORITHM

void readData(struct Student *p){
    FILE *file = fopen("Student Details.csv", "r");
    FILE *fileP = fopen("Student Program.csv", "r");

    if(file != NULL || fileP != NULL){
        char buffer[100];
        char bufferP[100];
        int size = 0;

        while(fgets(buffer, sizeof(buffer), file) && fgets(bufferP, sizeof(bufferP), fileP)){

            sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%c,%d,%[^,],%d", 
                &(p + size)->ID,
                &(p + size)->name.last, 
                &(p + size)->name.first, 
                &(p + size)->name.middle, 
                &(p + size)->gender, 
                &(p + size)->birth.bYear, 
                &(p + size)->birth.month, 
                &(p + size)->birth.day
            );
            sscanf(bufferP, "%[^,],%[^,],%d,%d", 
                &(p + size)->ID, 
                &(p + size)->program.course, 
                &(p + size)->program.pYear, 
                &(p + size)->program.section
            );

            size++;
        }

        fclose(file);
        fclose(fileP);

    }else{
        printf("\t[Creating New File.]\n");
        FILE *file = fopen("Student Details.csv", "w");
        FILE *fileP = fopen("Student Program.csv", "w");
        fclose(file);
        fclose(fileP);
    }
        
}


void insertData(struct Student *p){

    bool isExit = false;
    do{
        int last = getLastIndex();
            
        printf("\n\t         ID :   ");
        scanf(" %[^\n]", &(p + last)->ID);
        printf("\tGender(M/F) :   ");
        scanf(" %c", &(p + last)->gender);
        printf("\n\t--Name details--\n");
        printf("\t First Name :   ");
        scanf(" %[^\n]", &(p + last)->name.first);
        printf("\tMiddle Name :   ");
        scanf(" %[^\n]", &(p + last)->name.middle);
        printf("\t  Last Name :   ");
        scanf(" %[^\n]", &(p + last)->name.last);
        printf("\n\t--Birthdate details--\n");
        printf("\t      Month :   ");
        scanf(" %[^\n]", &(p + last)->birth.month);
        printf("\t        Day :   ");
        scanf("%d", &(p + last)->birth.day);
        printf("\t       Year :   ");
        scanf("%d", &(p + last)->birth.bYear);
        printf("\n\t--Program details--\n");
        printf("\t     Course :   ");
        scanf(" %[^\n]", &(p + last)->program.course);
        printf("\t    Section :   ");
        scanf("%d", &(p + last)->program.section);
        printf("\t       Year :   ");
        scanf("%d", &(p + last)->program.pYear);

        //check for duplication
        bool isDuplicate = false;

        printf("\n\t[Checking for duplication...]\n");
        sleep(3);
        for(int i = 0; i < last; i++){
            if(strcmp((p + i)->ID, (p + last)->ID) == 0){
                printf("\n\t[Data Duplication Detected. Please try again]\n");
                isDuplicate = true;
                break;
            }
            if((p + i)->gender == (p + last)->gender && strcmp((p + i)->name.last, (p + last)->name.last) == 0 && strcmp((p + i)->name.first, (p + last)->name.first) == 0 && strcmp((p + i)->name.middle, (p + last)->name.middle) == 0){
                if(strcmp((p + i)->birth.month, (p + last)->birth.month) == 0 && (p + last)->birth.bYear == (p + last)->birth.bYear && (p + last)->birth.day == (p + last)->birth.day){
                    printf("\n\t[Data Duplication Detected. Please try again]\n");
                    isDuplicate = true;
                    break;
                }
            }
        }

        //save data from database

        if(isDuplicate == false){
            printf("\t[Processing Saving Details...]\n");
            FILE *file = fopen("Student Details.csv", "a");
            FILE *fileP = fopen("Student Program.csv", "a");

            if(file != NULL || fileP != NULL){
                //student details
                fprintf(file, "%s,%s,%s,%s,%c,%d,%s,%d\n", (p + last)->ID, (p + last)->name.last, (p + last)->name.first, (p + last)->name.middle, (p + last)->gender, (p + last)->birth.bYear, (p + last)->birth.month, (p + last)->birth.day);

                //student program
                fprintf(fileP, "%s,%s,%d,%d\n", (p + last)->ID, (p + last)->program.course, (p + last)->program.pYear, (p + last)->program.section);

                printf("\n\t[Inserting Student Completed.]\n");
            }else{
                printf("\t[Saving Details Failed.]\n");
            }

            fclose(file);
            fclose(fileP);
        }

        char temp;
        printf("\n\tDo you want to input another? (y/n): ");
        scanf(" %c", &temp);

        printf("\n\t-----------------------------------\n");

        if(temp != 'y'){
            printf("\n\t[Exiting Find Student Data...]\n");
            sleep(3);
            isExit = true;
            system("cls");
        }

    }while(isExit == false);

}

void findStudent(struct Student *p){
    bool isExit = false;
    do{
        int option;
        int keyIndex = -1;
        char keyID[50];
        int size = getLastIndex();
        char keyLast[50];
        char keyFirst[50];
        printf("\n\tChoose an option to identify the person\n");
        printf("\t1) By ID\n\t2) By Last and First name\n");
        printf("\n\tEnter: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("\n\t[Searching Person through ID.]\n");
            printf("\tID : ");
            scanf(" %[^\n]", &keyID);

            for(int i = 0; i < size; i++){
                if(strcmp((p + i)->ID, keyID) == 0){
                    keyIndex = i;
                    break;
                }
            }
            break;
        case 2:
            printf("\n\t[Searching Person through Name.]\n");
            printf("\tFirst Name : ");
            scanf(" %[^\n]", &keyFirst);
            printf("\tLast Name : ");
            scanf(" %[^\n]", &keyLast);

            for(int i = 0; i < size; i++){
                if(strcmp((p + i)->name.first, keyFirst) == 0 && strcmp((p + i)->name.last, keyLast) == 0){
                    keyIndex = i;
                    break;
                }
            }
            break;
        }

        if(keyIndex != -1){
            sleep(3);
            printf("\n\t[Search Completed.]\n");
            printf("\n\t     Student ID : %s\n", (p + keyIndex)->ID);
            printf("\n\t   Student Name : %s, %s %s\n", (p + keyIndex)->name.last, (p + keyIndex)->name.first, (p + keyIndex)->name.middle);
            printf("\t       Birthday : %s %d, %d\n", (p + keyIndex)->birth.month, (p + keyIndex)->birth.day, (p + keyIndex)->birth.bYear);
            printf("\n\tStudent Program : %s\n", (p + keyIndex)->program.course);
            printf("\t   Student Year : %d\n", (p + keyIndex)->program.pYear);
            printf("\tStudent Section : %d\n", (p + keyIndex)->program.section);
        }else{
            sleep(3);
            printf("\n\t[Student Data Doesn't Exist.]\n");
        }

        char temp;
        printf("\n\tDo you want to search another? (y/n): ");
        scanf(" %c", &temp);

        printf("\n\t-----------------------------------\n");

        if(temp != 'y'){
            printf("\n\t[Exiting Search Student System...]\n");
            sleep(3);
            isExit = true;
            system("cls");
        }

    }while(isExit == false);
    
}

int getLastIndex(){
    FILE *file = fopen("Student Details.csv", "r");

    int size = 0;
    char buffer[100];

    while(fgets(buffer, sizeof(buffer), file)){
        size++;
    }
    fclose(file);

    return size;
}

void countStudent(struct Student *p){

    bool isExit = false;
    do{
        int size = getLastIndex();
        int count = 0;
        char courses[size][50];
        bool duplicated = false;

        int male = 0, female = 0;

        //count gender and store courses in array
        for(int i = 0; i < size; i++){          
            for(int j = 0; j < size; j++){
                if(strcmp((p + i)->program.course, courses[j]) == 0){
                    duplicated = true;
                }
            }
            if(duplicated == false){
                strcpy(courses[count++], (p + i)->program.course);
            }

            duplicated = false;
            
            (p + i)->gender == 'M' ? male++:female++;
        }

        int sizes[count];

        memset(sizes, 0, count*sizeof(sizes[0])); // to set the value of array to zero.

        //count each courses
        for(int i = 0; i < size; i++){              
            for(int j = 0; j < count; j++){
                if(strcmp((p + i)->program.course, courses[j]) == 0){
                    sizes[j]++;
                }
            }
        }

        printf("\n\t[Counting Data...]\n");
        sleep(3);

        printf("\n\tNumber of Student : %d\n", size);
        printf("\n\t     Male Student : %d\n", male);
        printf("\t   Female Student : %d\n", female);

        printf("\n\t-----------------------------------\n");
        printf("\tNumber of Student in each courses");
        printf("\n\t-----------------------------------\n\n");


        for(int i = 0; i < count; i++){
            printf("\t%s : %d\n", courses[i], sizes[i]);
        }

        char temp;
        printf("\n\tDo you want to restart the count system? (y/n): ");
        scanf(" %c", &temp);

        printf("\n\t-----------------------------------\n");

        if(temp != 'y'){
            printf("\n\t[Exiting Count Student Data...]\n");
            sleep(3);
            isExit = true;
            system("cls");
        }

    }while(isExit == false);
    
}

void deleteStudent(struct Student *p){
    bool isExit = false;

    do{
        bool confirmation = false;
        char lName[50];
        char fName[50];
        char key[50];
        int size = getLastIndex();
        int sTarget;

        printf("\n\t Last name : ");
        scanf(" %[^\n]", &lName);
        printf("\tfirst name : ");
        scanf(" %[^\n]", &fName);
        printf("\n\tEnter the ID to confirm the deletion : ");
        scanf(" %[^\n]", &key);

        for(int i = 0; i < size; i++){
            if(strcmp((p + i)->ID, key) == 0 && strcmp((p + i)->name.last, lName) == 0 && strcmp((p + i)->name.first, fName) == 0){
                printf("\n\t[Student Confirmed]\n");
                confirmation = true;
                sTarget = i;
                break;
            }
        }

        if(confirmation == true){

            remove("Student Details.csv");
            remove("Student Program.csv");

            FILE *fDetails = fopen("Student Details.csv", "w");
            FILE *fProgram = fopen("Student Program.csv", "w");

            if(fDetails != NULL || fProgram != NULL){     
                printf("\t[Proccessing Deletion...]\n");
                sleep(3);

                for(int i = 0; i < size; i++){
                    if(i != sTarget){
                        //student details
                        fprintf(fDetails, "%s,%s,%s,%s,%c,%d,%s,%d\n", (p + i)->ID, (p + i)->name.last, (p + i)->name.first, (p + i)->name.middle, (p + i)->gender, (p + i)->birth.bYear, (p + i)->birth.month, (p + i)->birth.day);

                        //student program
                        fprintf(fProgram, "%s,%s,%d,%d\n", (p + i)->ID, (p + i)->program.course, (p + i)->program.pYear, (p + i)->program.section);
                    }
                }
                printf("\n\t[Student been Deleted.]\n");
            }else{
                printf("\n\t[Deletion Failed.]\n");
            }

            fclose(fDetails);
            fclose(fProgram);

            readData(p);

        }else{
            printf("\n\t[No Student Record to the Database. Please try again.]\n");
        }

        char temp;
        printf("\n\tDo you want to delete another data? (y/n): ");
        scanf(" %c", &temp);

        printf("\n\t-----------------------------------\n");

        if(temp != 'y'){
            printf("\n\t[Exiting Count Student Data...]\n");
            sleep(3);
            isExit = true;
            system("cls");
        }

    }while(isExit == false);  

}

void updateStudent(struct Student *p){
    bool isExit = false;

    do{
        char key[50];
        bool isExist = false;
        bool toSave = false;
        int size = getLastIndex();
        int toEdit;

        printf("\n\tEnter the ID of student to update : ");
        scanf(" %[^\n]", &key);

        for(int i = 0; i < size; i++){
            if(strcmp((p + i)->ID, key) == 0){
                isExist = true;

                printf("\n\t-----------------------------------\n");
                printf("\n\tStudent Current Data:\n");
                printf("\t    Name : %s, %s %s\n", (p+i)->name.last, (p+i)->name.first, (p+i)->name.middle);
                printf("\tBirthday : %s %d, %d\n", (p+i)->birth.month, (p+i)->birth.day, (p+i)->birth.bYear);
                printf("\n\tProgram:\n");
                printf("\t Course : %s\n", (p+i)->program.course);
                printf("\t   Year : %d\n", (p+i)->program.pYear);
                printf("\tSection : %d\n", (p+i)->program.section);
                printf("\n\t-----------------------------------\n");

                printf("\n\tList of Data to Update:\n");
                printf("\t1) Student ID\n\t2) Student Name\n\t3) Student Birthday\n\t4) Student Program\n");
                printf("\n\tEnter : ");
                scanf("%d", &toEdit);

                char cInput1[50], cInput2[50];
                int iInput1, iInput2;
                switch (toEdit){
                case 1:
                    printf("\n\t-----------------------------------\n");
                    printf("\n\t    Current ID : %s\n", key);
                    printf("\t        New ID : ");
                    scanf(" %[^\n]", &cInput1);
                    printf("\tConfirm New ID : ");
                    scanf(" %[^\n]", &cInput2);

                    if(strcmp(cInput1, cInput2) == 0){
                        strcpy((p+i)->ID, cInput2);
                        toSave = true;
                    }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                    }
                break;
                case 2:
                    printf("\n\t-----------------------------------\n");
                    int isName;
                    printf("\t1) First Name\n\t2) Last Name\n\t3) Middle Name\n");
                    printf("\n\tEnter : ");
                    scanf("%d", &isName);

                    switch(isName){
                    case 1:
                        printf("\n\t    Current First Name : %s\n", (p+i)->name.first);
                        printf("\t        New First Name : ");
                        scanf(" %[^\n]", &cInput1);
                        printf("\tConfirm New First Name : ");
                        scanf(" %[^\n]", &cInput2);

                        if(strcmp(cInput1, cInput2) == 0){
                        strcpy((p+i)->name.first, cInput2);
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    case 2:
                        printf("\n\t    Current Last Name : %s\n", (p+i)->name.last);
                        printf("\t        New Last Name : ");
                        scanf(" %[^\n]", &cInput1);
                        printf("\tConfirm New Last Name : ");
                        scanf(" %[^\n]", &cInput2);

                        if(strcmp(cInput1, cInput2) == 0){
                        strcpy((p+i)->name.last, cInput2);
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    case 3:
                        printf("\n\t    Current Middle Name : %s\n", (p+i)->name.middle);
                        printf("\t        New Middle Name : ");
                        scanf(" %[^\n]", &cInput1);
                        printf("\tConfirm New Middle Name : ");
                        scanf(" %[^\n]", &cInput2);

                        if(strcmp(cInput1, cInput2) == 0){
                        strcpy((p+i)->name.middle, cInput2);
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    default:
                        printf("\n\t[No option found. Please try again.]\n");
                    break;
                    }   
                break;     
                case 3:
                    printf("\n\t-----------------------------------\n");
                    int isBirth;
                    printf("\t1) Month\n\t2) Day\n\t3) Year\n");
                    printf("\n\tEnter : ");
                    scanf("%d", &isBirth);

                    switch(isBirth){
                    case 1:
                        printf("\n\t    Current Birth Month : %s\n", (p+i)->birth.month);
                        printf("\t        New Birth Month : ");
                        scanf(" %[^\n]", &cInput1);
                        printf("\tConfirm New Birth Month : ");
                        scanf(" %[^\n]", &cInput2);

                        if(strcmp(cInput1, cInput2) == 0){
                        strcpy((p+i)->birth.month, cInput2);
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    case 2:
                        printf("\n\t    Current Birth Day : %d\n", (p+i)->birth.day);
                        printf("\t        New Birth Day : ");
                        scanf("%d", &iInput1);
                        printf("\tConfirm New Birth Day : ");
                        scanf("%d", &iInput2);

                        if(iInput1 == iInput2){
                        (p+i)->birth.day = iInput2;
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    case 3:
                        printf("\n\t    Current Birth Year : %d\n", (p+i)->birth.bYear);
                        printf("\t        New Birth Year : ");
                        scanf("%d", &iInput1);
                        printf("\tConfirm New Birth Year : ");
                        scanf("%d", &iInput2);

                        if(iInput1 == iInput2){
                        (p+i)->birth.bYear = iInput2;
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    default:
                        printf("\n\t[No option found. Please try again.]\n");
                    break;
                    }   

                break;
                case 4:
                    printf("\n\t-----------------------------------\n");
                    int isProgram;
                    printf("\t1) Course\n\t2) Year\n\t3) Section\n");
                    printf("\n\tEnter : ");
                    scanf("%d", &isProgram);

                    switch(isProgram){
                    case 1:
                        printf("\n\t    Current Program Course : %s\n", (p+i)->program.course);
                        printf("\t        New Program Course : ");
                        scanf(" %[^\n]", &cInput1);
                        printf("\tConfirm New Program Course : ");
                        scanf(" %[^\n]", &cInput2);

                        if(strcmp(cInput1, cInput2) == 0){
                        strcpy((p+i)->program.course, cInput2);
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    case 2:
                        printf("\n\t    Current Program Year : %d\n", (p+i)->program.pYear);
                        printf("\t        New Program Year : ");
                        scanf("%d", &iInput1);
                        printf("\tConfirm New Program Year : ");
                        scanf("%d", &iInput2);

                        if(iInput1 == iInput2){
                        (p+i)->program.pYear = iInput2;
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    case 3:
                        printf("\n\t    Current Program Section : %d\n", (p+i)->program.section);
                        printf("\t        New Program Section : ");
                        scanf("%d", &iInput1);
                        printf("\tConfirm New Program Section : ");
                        scanf("%d", &iInput2);

                        if(iInput1 == iInput2){
                        (p+i)->program.section = iInput2;
                        toSave = true;
                        }else{
                        printf("\n\t[Your Input Doesn't Match. Please try again.]\n");
                        sleep(1);
                        i--;
                        }
                    break;
                    default:
                        printf("\n\t[No option found. Please try again.]\n");
                    break;
                    }   
                break;
                default:
                    printf("\n\t[No option found. Please try again.]\n");
                break;
                }
            }
            if(toSave == true){
                printf("\n\t[Saving Updated Data...]\n");
                sleep(1);
                remove("Student Details.csv");
                remove("Student Program.csv");

                FILE *fDetails = fopen("Student Details.csv", "w");
                FILE *fProgram = fopen("Student Program.csv", "w");

                if(fDetails != NULL || fProgram != NULL){    
                    for(int j = 0; j < size; j++){
                        //student details
                        fprintf(fDetails, "%s,%s,%s,%s,%c,%d,%s,%d\n", (p + j)->ID, (p + j)->name.last, (p + j)->name.first, (p + j)->name.middle, (p + j)->gender, (p + j)->birth.bYear, (p + j)->birth.month, (p + j)->birth.day);
                        //student program
                        fprintf(fProgram, "%s,%s,%d,%d\n", (p + j)->ID, (p + j)->program.course, (p + j)->program.pYear, (p + j)->program.section);
                    }
                    printf("\n\t[Updating Data Complete.]\n");
                }else{
                    printf("\n\t[Updating Data Failed.]\n");
                }

                fclose(fDetails);
                fclose(fProgram);

                break;
            }     
        }
        if(isExist == false){
            sleep(2);
            printf("\n\t[There is no matching Student ID. Please try again.]\n");
        }

        char temp;
        printf("\n\tDo you want to update another data? (y/n): ");
        scanf(" %c", &temp);

        printf("\n\t-----------------------------------\n");

        if(temp != 'y'){
            printf("\n\t[Exiting Update Data...]\n");
            sleep(3);
            isExit = true;
            system("cls");
        }

    }while(isExit == false);  
}
