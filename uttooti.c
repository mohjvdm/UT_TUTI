#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct postinfo post; //post struct contain post data
struct postinfo{
    int post_id;
    char *post_writer;
    int likes;
    char *post_content;
    post* next;
};


typedef struct userinfo user; // user struct contain user data
struct userinfo{
    char username[40];
    char password[40];
    user* next;
    post* postptr; //head of user post linklist
};

#include "signup.h" //sign up func header file



int main(){
    int finish = 0; //define finish for main loop and exit from program 
    int flag, statnam;
    int cnt; 
    char username_input[40];
    char password_input[40];
    int signany = 0;
    int id_input;
    char user_command[20];
    int login_status = 1;
    user* cur_user;// temp struct 
    post* cur_post;
    post* prev_post;
    user* head_user = NULL;
    head_user = signup_user("head", "head", head_user);// create head of user link list 
    user* loged_in_user = NULL; // if loged in user = null meaning that any user isnot login
    int i, j;
    printf("Welcome to Ut Tooti");

    while(finish <= 20){ //main loop
        printf("\n\nWhat do you want to do ?\n");
        scanf("%s",user_command); 
        if(!strcmp(user_command, "signup")){
            scanf("%s", username_input);
            scanf("%s", password_input);
            signup_user(username_input, password_input, head_user); //func
            signany = 1;
        }
        else if(!strcmp(user_command, "login")){
            if(loged_in_user != NULL){
                printf("\nIf you want to login in another account you must logout this account first!");
                fflush(stdin); 
                fflush(stdout);
            }
            else{
                scanf("%s", username_input);
                scanf("%s", password_input);
                cur_user = head_user;
                while(1){//in this loop we check all of users from user link list to compare and finding user
                    if(!strcmp(username_input, cur_user->username) && !strcmp(password_input, cur_user->password)){
                        loged_in_user = cur_user; // if input data matches user data
                        printf("\nLogin succesfully");
                        printf("\n%s",cur_user->username);
                        break;
                    }
                    if(cur_user->next == NULL){
                        break; //end of list
                    }
                    else if(cur_user->next != NULL){
                        cur_user = cur_user->next;
                    }
                }
                if(loged_in_user == NULL){
                    printf("\nLogin unsuccesfully\nUsername or password is wrong!");
                }    
            }
        }
        else if(!strcmp(user_command, "post")){
            if(loged_in_user == NULL){
                printf("\nFirst you must login in your account!");
                fflush(stdin);
                fflush(stdout);
            }
            else{
                post* new_post = (post *)malloc(sizeof(post));
                new_post->next = NULL; // cause adding to end of list
                new_post->post_content = (char *)malloc(300 * sizeof(char));
                fgets(new_post->post_content, 300, stdin);
                new_post->post_writer = (char *)malloc(40 * sizeof(char));
                for(i=0;i<40;i++){
                    new_post->post_writer[i] = loged_in_user->username[i] ;
                }
                new_post->likes = 0;

                cur_post = loged_in_user->postptr; //cheking list of post of loged in user
                while(cur_post->next != NULL){
                    printf("\n%d", cur_post->post_id);
                    cur_post = cur_post->next;
                }
                new_post->post_id = (cur_post->post_id) + 1;
                cur_post->next = new_post;

                printf("\nPost sent.");
                printf("\n%s",new_post->post_writer);
                printf("\ncontent :");
                for(i=0;i<300;i++){
                    if(new_post->post_content[i-1] == '\n'){
                        break;
                    }
                    printf("%c", new_post->post_content[i]);
                }
            }
        }
        else if(!strcmp(user_command, "like")){
            if(loged_in_user == NULL){
                printf("\nFirst you must login in your account!");
            }
            else{
                flag = 1;
                scanf("%s", username_input);
                scanf("%d", &id_input);
                cur_user = head_user;
                while(1){ // loop for find user and post
                    if(!strcmp(cur_user->username, username_input)){
                        flag = 0;
                        break;
                    }
                    if(cur_user->next == NULL){
                        break;
                    }
                    else{
                        cur_user = cur_user->next;
                    }
                }
                if(flag != 0){
                    printf("\nUser not found !");
                }
                else{
                    cur_post = cur_user->postptr;
                    while(1){
                        if(cur_post->post_id == id_input){
                            cur_post->likes++;// if post data and user data matches
                            flag = 2;
                            printf("\nPost liked.");
                            break;
                        }
                        if(cur_post->next == NULL){
                            break;
                        }
                        else{
                            cur_post = cur_post->next;
                        }
                    }
                    if(flag != 2){
                        printf("\nPost not found !");
                    }
                }
            }
        }
        else if(!strcmp(user_command, "logout")){
            if(loged_in_user == NULL){
                printf("\nAlready you are not login!");
            }
            else{
                loged_in_user = NULL;
                printf("Logout succesfully!");
            }    
        }
        else if(!strcmp(user_command, "delete")){
            if(loged_in_user == NULL){
                printf("\nFirst you must login in your account!");
            }
            else{
                flag = 1;
                scanf("%d", &id_input);
                cur_post = loged_in_user->postptr;
                while(1){ // loop for find desired post
                    if(cur_post->post_id == id_input){
                        prev_post->next = cur_post->next;
                        free(cur_post);
                        flag = 0;
                        printf("\nPost deleted .");
                        break;
                    }
                    if(cur_post->next == NULL){
                        break;
                    }
                    else{
                        prev_post = cur_post;
                        cur_post = cur_post->next;
                    }
                }
                if(flag != 0){
                    printf("\nPost not found .");
                }
            }
        }
        else if(!strcmp(user_command, "info")){
            if(loged_in_user == NULL){
                printf("\nFirst you must login in your account!");
                fflush(stdin);
                fflush(stdout);
            }
            else{
                cur_user = head_user->next;
                while(1){           // loop for find loged in user in users link list
                    statnam = strcmp(cur_user->username,loged_in_user->username);
                    if(statnam != 0 ){
                        cur_user = cur_user->next;
                    }
                    else{
                        break;
                    }
                }
                printf("\nUsername : ");
                printf("%s",cur_user->username);

                printf("\nPassword : ");
                printf("%s\n", cur_user->password);

                cur_post = cur_user->postptr->next;
                if(cur_post == NULL){
                    cur_post = NULL;
                    printf("\nUser has not any post.");
                    break;
                }
                while(1){
                    printf("\nPost id : %d", cur_post->post_id);
                    printf("\ncontent :");
                    for(i=0;i<300;i++){         //printing of post content
                        if(cur_post->post_content[i-1] == '\n'){
                            break;
                        }
                        printf("%c", cur_post->post_content[i]);
                    }
                    printf("Likes : %d\n", cur_post->likes);
                    if(cur_post->next == NULL){
                        break;
                    }
                    cur_post = cur_post->next;
                }
            }
        }
        else if(!strcmp(user_command, "find_user")){
            scanf("%s", username_input);
            cur_user = head_user;
            flag = 1;                                         //flag = 1 meaning user not found
            while(1){  //loop for finding user in users link list
                if(!strcmp(cur_user->username, username_input)){
                    printf("\nUsername : ");
                    printf("%s",cur_user->username);
                    cur_post = cur_user->postptr->next;
                    if(cur_post == NULL){
                        cur_post = NULL;
                        flag = 4;                        //flag = 4 meaning user found but hasnt any post
                        printf("\nUser has not any post.");
                        break;
                    }
                    while(1){ // loop for printing all of posts
                        printf("\nPost id : %d", cur_post->post_id);
                        printf("\ncontent :");
                        for(i=0;i<300;i++){
                            if(cur_post->post_content[i-1] == '\n'){
                                break;
                            }
                            printf("%c", cur_post->post_content[i]);
                        }
                        printf("Likes : %d\n", cur_post->likes);
                        if(cur_post->next == NULL){
                            break;
                        }
                        cur_post = cur_post->next;
                    }
                        flag = 0;                         //flag = 0 mening user found and has post
                        break;
                }
                if(cur_user->next == NULL){
                    break;
                }
                else{
                    cur_user = cur_user->next;
                }
            }
            if(flag == 1){
                printf("\nUser not found !");                     //flag = 1
            }
        }
        else if(!strcmp(user_command, "exit")){
                finish = 30;                     //finish and exit from main loop and program
        }
        else{
            printf("\nCommand is not clear!");
        }
        fflush(stdin);
        fflush(stdout);


        if(signany == 1){
            FILE* userfile = fopen("userfile.txt", "w");
            cur_user = head_user;                          //write user data from link list in userfile
            while(cur_user != NULL){
                fwrite(cur_user->username, sizeof(char), strlen(cur_user->username), userfile);
                fwrite(" ", 1, 1, userfile);
                fwrite(cur_user->password, sizeof(char), strlen(cur_user->password), userfile);
                fwrite(" ", 1, 1, userfile);

                cur_post = cur_user->postptr;     //counting number of users post
                cnt = 0;
                while(cur_post->next != NULL){

                    cnt++;
                    cur_post = cur_post->next;

                }
                fprintf(userfile, "%d" , cnt);   //print number of posts
                fwrite("\n", 1,1, userfile);
                cur_user = cur_user->next;
            }
            fclose(userfile);


            FILE* postfile = fopen("postfile.txt", "w");           //write all posts in postfile

            cur_user = head_user;
            while(cur_user != NULL){                //loop for user
                cur_post = cur_user->postptr;
                while(cur_post->next != NULL){     //loop for post

                    cur_post = cur_post->next;

                    fwrite(cur_post->post_content, sizeof(char), strlen(cur_post->post_content), postfile);
                    fwrite(" ", 1, 1, postfile);
                    fwrite(cur_post->post_writer, sizeof(char), strlen(cur_post->post_writer), postfile);
                    fwrite(" ", 1, 1, postfile);
                    fprintf(postfile,"%d", cur_post->likes);        //print number of likes
                    fwrite("\n", 1,1, postfile);          
                    fwrite("\n", 1,1, postfile);
                }
                cur_user = cur_user->next;
            }
            fclose(postfile);


        }    
    }
}
