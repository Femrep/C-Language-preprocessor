#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ArrayTable {
    char name[10];
    char size[5];
    char type[10];
};
struct ArrayTable AT[20];

void remove_spaces(char*) ;


void inc();



void dec(char* );

void read(char*);


void same_line(char*);

void print(char*);

void copy(char*);

int countletter(char*);

int isInMat(char*);




void initialize(char*);



void arithmetic(char*);


void declare(char*,char*);


//struct ArrayTable AT[20];

int main()
{
    FILE* ptr;
    char beforeremoval[100];
    char line[250];
    inc();

    ptr = fopen("test.txt", "r");

    while (!feof(ptr)) {

        fgets(line, 250, ptr);
		line;
        strcpy(beforeremoval, line);
        remove_spaces(line);

        if(strncmp(line, "$", strlen("$")) == 0 ){
        if(strncmp(line, "$dec", strlen("$dec")) == 0 ){ // if command is $dec
                declare(line,"$dec");
                continue;
            }

        if(strncmp(line, "$read", strlen("$read")) == 0 ){ // if command is $read
                declare(line,"$read");
                continue;
            }
        if(strncmp(line, "$print", strlen("$print")) == 0 ){ // if command is $print
                declare(line,"$print");
                continue;
            }
        if(strchr(line,'=')!=NULL ){
            int count_dol=countletter(line);
            int inIT=isInMat(line);
            if(count_dol==2&& inIT==0){
                copy(line);
                continue;
            }
            if(count_dol==1&& inIT==0){
                initialize(line);
                continue;
            }
            if(count_dol>=2&& inIT!=0){

                arithmetic(line);
                continue;
            }
   
        }}
       else{
            same_line(beforeremoval);
            continue;
        }


    }

    fclose(ptr);
    system("cd /home/emre/Masaüstü/232");
    system("g++ extended.c -o test2");
    
    system("./test2");
    return 0;
    
}
void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ' || *d == '\t') {
            ++d;
        }
    } while (*s++ = *d++);
}
void dec(char *line ){
    char *t = strtok (line, "$(,)");
    t = strtok(NULL, "$(,);");
    char *arrname = t;
    FILE *file;
    file = fopen("extended.c", "a+");



    t = strtok(NULL, "$(,)");
    char *array_size=t;


    t = strtok(NULL, "$(,)");
    char *array_type=t;
	int i=0;
    for( i;i<20;i++){
        if(strcmp(AT[i].type,"")==0){

        strcpy(AT[i].name,arrname);
        strcpy(AT[i].size,array_size);
        strcpy(AT[i].type,array_type);
        break;
        }
    }

    fprintf(file, "%s %s[%s];\n", array_type, arrname, array_size);
    fclose(file);

}
void read(char *line){
    char *p = strtok (line, "$(,)");
    p = strtok(NULL, "$(,)");
    char *filename = p;
    FILE *file;
    file = fopen("extended.c", "a+");
    fprintf(file, "FILE *ff=fopen(\"%s.txt\", \"r\");\n", filename);

    p = strtok(NULL, "$(,)");
	int i = 0;
    for(i; i < 20; i++){
        if(strcmp(AT[i].name, p) == 0){
            if(strcmp(AT[i].type, "int") == 0){
                fprintf(file, "for(int i = 0; i<%d; i++) fscanf(ff, \"%%d\", &%s[i]);\nfclose(ff);\n", atoi(AT[i].size), p);
                break;
            }
            else if(strcmp(AT[i].type, "char") == 0){
                fprintf(file, "for(int i = 0; i<%d; i++) fscanf(ff, \"%%c\", &%s[i]);\nfclose(ff);\n", atoi(AT[i].size), p);
                break;
            }
            else if(strcmp(AT[i].type, "float") == 0){
                fprintf(file, "for(int i = 0; i<%d; i++) fscanf(ff, \"%%f\", &%s[i]);\nfclose(ff);\n", atoi(AT[i].size), p);
                break;
            }
            else if(strcmp(AT[i].type, "double") == 0){
                fprintf(file, "for(int i = 0; i<%d; i++) fscanf(ff, \"%%lf\", &%s[i]);\nfclose(ff);\n", atoi(AT[i].size), p);
                break;
            }
        }
    }
    fclose(file);

}
void same_line(char *line){
    FILE *file;
    file = fopen("extended.c", "a+");
    fprintf(file, "%s",line );
    fclose(file);
}

void print(char *line){
    char *p = strtok (line, "$(,)");
    p = strtok(NULL, "$(,)");
    char *ARR = p;
    FILE *file;
    file = fopen("extended.c", "a+");
	int i = 0;
    for(i; i < 20; i++){
        if(strcmp(AT[i].name, ARR) == 0){
            if(strcmp(AT[i].type, "int") == 0){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\tprintf( \"%%d\", %s[i]);\nprintf(\"\\n\");\n", atoi(AT[i].size),ARR );
                break;
            }
            else if(strcmp(AT[i].type, "char") == 0){
               fprintf(file, "for(int i = 0; i<%d; i++) \n\tprintf( \"%%c\", %s[i]);\nprintf(\"\\n\");\n", atoi(AT[i].size),ARR );
                break;
            }
            else if(strcmp(AT[i].type, "float") == 0){
               fprintf(file, "for(int i = 0; i<%d; i++) \n\tprintf( \"%%f\", %s[i]);\nprintf(\"\\n\");\n", atoi(AT[i].size),ARR );
                break;
            }
            else if(strcmp(AT[i].type, "double") == 0){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\tprintf( \"%%lf\", %s[i]);\nprintf(\"\\n\");\n", atoi(AT[i].size),ARR );
                break;
            }
        }
    }
    fclose(file);
}
void copy(char *line){
     char *p = strtok (line, "$(,)=;");
     char *first_arr = p;
    p = strtok(NULL, "$(,)=;");

    FILE *file;
    file = fopen("extended.c", "a+");

    char *Second_arr = p;
    int i = 0;
     for(i; i < 20; i++){

        if(strcmp(AT[i].name, first_arr) == 0){
            fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]=%s[i];\n", atoi(AT[i].size),first_arr,Second_arr );
            break;

        }
    }

    fclose(file);
}
int countletter(char *array){
  int i = 0;
  int count = 0;
  for (i = 0; array[i] != '\0'; i++)
     if(array[i] == '$')
       count++;
 // printf("Number of %c's: %d\n", '$', count);
  return count;
}

int isInMat(char *array){
  int i = 0;
  int count = 0;
  for (i = 0; array[i] != '\0'; i++)
     if(array[i] == '+')
        count=1;
     if(array[i] == '-')
        count=2;
     if(array[i] == '*')
        count=3;
     if(array[i] == '/')
        count=4;

  return count;
}

void initialize(char *line){
     char *p = strtok (line, "$(,)=;");
     char *first_arr = p;
    p = strtok(NULL, "$(,)=;");

    FILE *file;
    file = fopen("extended.c", "a+");

    char *Second_arr = p;
    int i = 0;
     for(i; i < 20; i++){

        if(strcmp(AT[i].name, first_arr) == 0){
            fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]=%s;\n", atoi(AT[i].size),first_arr,Second_arr );
            break;

        }
    }

    fclose(file);
}
void arithmetic(char *line){
    FILE *file;
    file = fopen("extended.c", "a+");
    int a=0;
    if( strchr(line,'+')!=0)
        a=1;
    if(strchr(line,'-')!=0)
        a=2;
    if(strchr(line,'*')!=0)
        a=3;
    if(strchr(line,'/')!=0)
        a=4;

    char *p = strtok (line, "$=");
    char *first=p;
    //printf("\n%s\n",first);

    int truth=0;
    int i = 0;
    for(i; i < 20; i++){

        if(strcmp(AT[i].name, first) == 0){
            // find location

        }
    }
    p=strtok(NULL,"+*-/=");
    char *second=p;
   // printf("%s\n",p);

    if(countletter(second)==1){
        p=strtok(NULL,";");
        char *thirt=p;
           if(countletter(thirt)==1){
            char* secarr= strtok(second,"$");
            char* thiarr=strtok(thirt,"$");
            if(a==1){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]+%s[i];\n", atoi(AT[2].size),first,secarr,thiarr );
            }
            if(a==2){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]-%s[i];\n", atoi(AT[2].size),first,secarr,thiarr );
            }
            if(a==3){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]*%s[i];\n", atoi(AT[2].size),first,secarr,thiarr );
            }
            if(a==4){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]/%s[i];\n", atoi(AT[2].size),first,secarr,thiarr );
            }
           }
           if(countletter(thirt)==0){
            char* secarr= strtok(second,"$");

            if(a==1){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]+%s;\n", atoi(AT[2].size),first,secarr,thirt );
            }
            if(a==2){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]-%s;\n", atoi(AT[2].size),first,secarr,thirt );
            }
            if(a==3){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]*%s;\n", atoi(AT[2].size),first,secarr,thirt );
            }
            if(a==4){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s[i]/%s;\n", atoi(AT[2].size),first,secarr,thirt );
            }
           }

    }
    if(countletter(second)==0){
        p=strtok(NULL,";");
        char *thirt=p;
           if(countletter(thirt)==1){

            char* thiarr=strtok(thirt,"$");
            if(a==1){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s+%s[i];\n", atoi(AT[2].size),first,second,thiarr );
            }
            if(a==2){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s-%s[i];\n", atoi(AT[2].size),first,second,thiarr );

            }
            if(a==3){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s*s[i];\n", atoi(AT[2].size),first,second,thiarr );

            }
            if(a==4){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s/%s[i];\n", atoi(AT[2].size),first,second,thiarr );

            }
           }
           if(countletter(thirt)==0){


            if(a==1){
                fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s+%s;\n", atoi(AT[2].size),first,second,thirt );
            }
            if(a==2){
                 fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s-%s;\n", atoi(AT[2].size),first,second,thirt );
            }
            if(a==3){
                 fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s*%s;\n", atoi(AT[2].size),first,second,thirt );
            }
            if(a==4){
                 fprintf(file, "for(int i = 0; i<%d; i++) \n\t %s[i]= %s/%s;\n", atoi(AT[2].size),first,second,thirt );
            }
           }

    }



    fclose(file);
}

void declare(char *line,char *str){
    if(str=="$dec"){
        dec(line);
    }
    if (str=="$read"){
        read(line);
    }
    if(str=="$print"){
        print(line);
    }
}
void inc(){
    FILE *file;
    file = fopen("extended.c", "a+");
    fprintf(file, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n");
    fclose(file);
}
