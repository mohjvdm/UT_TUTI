user* signup_user(char* username_in, char* password_in, user* head_user){
    int i;
    user* new_user = NULL;
    new_user = (user*)malloc(sizeof(user));//alloc memory for new user
    for(i=0;i<40;i++){
        new_user->username[i] = username_in[i];    //creating new user
        new_user->password[i] = password_in[i];
    }                                                   // fill new user data
    new_user->next = NULL;                              //add to end of list
    new_user->postptr = NULL;                           // creat posts link list for new user and post ptr is the head of the list
    new_user->postptr = (post *)malloc(sizeof(post));  
    new_user->postptr->post_id = 0;
    new_user->postptr->next = NULL;

    if(head_user == NULL){
        return new_user;            // this for head of users link list
    }   
    user* temp = head_user;         //loop for find end of link list
    while(temp->next != NULL){
        temp = temp->next;
    }    
    temp->next = new_user;
    printf("\nSignup succesfully");
}
