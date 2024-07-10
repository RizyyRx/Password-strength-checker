#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_LENGTH_DISPLAY 1

//Function prototypes
int pass_check(char *password);
int pass_len(char *password);
int one_upper(char *password);
int three_lower(char *password);
int one_symbol(char *password);
int three_num(char *password);
int num_notseq(char *password);

//returns score based on scores returned by various functions
int pass_check(char *password){
    int score=0;
    score=pass_len(password);
    if(score==0){ //If password length less than 8, return score as 0
        return score;
    }

    //Add scores returned by all remaining functions
    score=score+one_upper(password)+three_lower(password)+one_symbol(password)+three_num(password)+num_notseq(password);
    return score;
}

/*
    Returns a score 1 if length of password is greater that or equal to 8
*/
int pass_len(char *password){
    if(strlen(password)<8){
        return 0;
    }
    else{
        return 1;
    }
}
/*
    *Checks if the password has atleast one uppercase character
    *returns 1 if condition satisfies
*/
int one_upper(char *password){
    for(int i=0;i<strlen(password);i++){
        if(isupper(password[i])){
            return 1;         
        }
    }
    return 0;
}

/*
    *Checks if the password has atleast 3 lowercase characters
    *returns 1 if condition satisfies
*/
int three_lower(char *password){
    int count=0;
    for(int i=0;i<strlen(password);i++){
        if(islower(password[i])){
            count++;         
        }
        if(count>=3){
            return 1;
        }
    }
    return 0;
}

/*
    *Checks if the password has atleast one symbol character
    *returns 1 if condition satisfies
*/
int one_symbol(char *password){
    for(int i=0;i<strlen(password);i++){
        if(ispunct(password[i])){
            return 1;         
        }
    }
    return 0;
}

/*
    *Checks if the password has atleast three numeric characters.
    *returns 1 if condition satisfies.
*/
int three_num(char *password){
    int count=0;
    for(int i=0;i<strlen(password);i++){
        if(isdigit(password[i])){
            count++;
        }
    }
    if(count>=3){
        return 1;
    }
    else{
        return 0;
    }
}
/*
    *Checks if the numbers are sequential or not.
    *If sequential, returns score 2
    *If not sequential, returns score 4
*/

int num_notseq(char *password){
    int count=0;
    for(int i=0;i<strlen(password);i++){
        if(isdigit(password[i])){
            count++;
        }
    }
    if(count>=3){
        /*i<strlen(password)-2 because lets say we enter a 10 digit 
         password,the loop will iterate one by one. Now when it reaches
         the 10th char, the condition we used i.e password[i+1] or
         password [i+2] will access 11th and 12th unwanted data.
         To prevent this, we negate -2 so that the data access will
         be in the limit of the password string only.
        */
        for(int i=0;i<strlen(password)-2;i++){  
            if(isdigit(password[i]) && isdigit(password[i+1]) && isdigit(password[i+2])){
                int n1=password[i];
                int n2=password[i+1];
                int n3=password[i+2];
                if(abs(n2-n1)==1 && abs(n3-n2)==1){
                    return 0;
                }
                else{
                    return 4;
                }
            }   
        }
    }
    return 0;
}         


int main(){
    char *pass;
    char *pass_display;

    printf("-------PASSWORD STRENGTH CHECKER-------\n\n1.Password must be minimum of 8 characters\n2.Password must have one Uppercase Character\n3.Password must have three Lowercase Characters\n4.Password must have one symbol\n5.Password must have three Numeric Characters that are not sequential\n\n");

    //User input for pasword
    pass=getpass("Enter password:");
    
    //prompt user to whether display their password or not
    printf("Do you want your password to be displayed?(y/n): ");
    scanf("%s",pass_display);

    if(strcmp(pass_display,"y")==0){
        printf("Your password:%s\n",pass);
    }

    //pass the password to pass_check function
    int score = pass_check(pass);
    if(score==0){
        printf("Your password must have 8 characters or more\n");
    }
    else if(score ==1){
        printf("Your password is very weak\n");
    }
    else if(score ==2){
        printf("Your password is weak\n");
    }
    else if(score ==3){
        printf("Your password is average\n");
    }
    else if(score ==4){
        printf("Your password is good\n");
    }
    else if(score ==5){
        printf("Your password is strong\n");
    }
    else if(score ==9){
        printf("Your password is very strong\n");
    }
}