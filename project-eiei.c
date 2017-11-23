#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct card{
    int index;
    char id[8];
    char firstname[30];
    char lastname[30];
    char phone[11];
    char email[100];
    char password[20];
};

struct card info[100];
struct card login_session;

////////////////////////////////////////////////
////            UTILITIES FUNCTION          ////
////////////////////////////////////////////////

//// CALL MAIN MENU
void mainmenu() {
    char choice;
    printf("=======================\n");
    printf(" ICT MANAGEMENT SYSTEM\n");
    printf("=======================\n");
    printf("[1] Register\n");
    printf("[2] Login\n");
    printf("[3] Forget Password\n");
    printf("[0] Logout\n");
    printf("Select your choices : ");
    scanf(" %c",&choice);
    if(choice == '1')
    {
        system("cls");
        registration();
    }
    else if(choice == '2')
    {
        system("cls");
        login();
    }
    else if(choice == '3')
    {
        system("cls");
        forget_pass();
    }else if(choice == '0')
    {
        system("cls");
        exitout();
    }

    else
    {
        system("cls");
        mainmenu();
    }
}

//// Check num or char
int isallnum(char id[]) {
    int size = strlen(id);
    int i=0;
    char tmp[size];
    while(id[i] != '\0') {
        tmp[i] = id[i];
        i++;
    }

    for(i=0;i<size;i++) {
    //printf("%c:%d\n",tmp[i],isdigit(tmp[i]));
    if(isdigit(tmp[i]) == 0) {
        return 0;
        break;
    }
    }
    return 1;
}
//// Check e-mail
int is_email(char email[]) {
    int size = strlen(email);
    int i=0,ismail=0;
    char tmp[size];
    while(email[i] != '\0') {
        tmp[i] = email[i];
        i++;
    }

    for(i=0;i<size;i++) {
    //printf("%c\n",tmp[i]);
    if(tmp[i] == '@') {
        ismail = 1;
        break;
    }
    }

    if(ismail == 1) {
    return 1;
    } else {
        return 0;
    }
}

//// Count how many data in file data.txt
int count_data() {
    FILE *fp;
    char buffer[255];
    int num=0;
    fp = fopen("data.txt", "r");
    while (fgets(buffer, 255, fp) != NULL) {
        num++;
    }
    fclose(fp);
    //printf("Current data: %d\n",num);
    return num;
}

//// LOAD DATA FROM FILE AND KEEP IN Array "info" with structures card
int load_data() {
    int i=0;
    FILE *fp;
    int data = count_data();

    fp = fopen("data.txt", "r");
    char buffer[255];

    while (fgets(buffer, 255, fp) != NULL) {
    //printf("%s", buffer);
    sscanf(buffer,"%d,%[^,],%[^,],%[^,],%10[^,],%[^,],%[^,],",&info[i].index,info[i].id,info[i].firstname,info[i].lastname,info[i].phone,info[i].email,info[i].password);
    i++;
    }

    fclose(fp);
    return 0;
}

//// Check role of the user that Admin or Student
int check_role(char id[]) {
    int size = strlen(id);
    int i=0;
    char tmp[size];
    while(id[i] != '\0') {
        tmp[i] = id[i];
        i++;
    }
    if(tmp[0] == '0' && tmp[1] == '0') {
        return 1;
    } else {
        return 0;
    }
}

//// Function that call when user exit the program
void exitout()
{
    printf("**************        *****           *****       *****************\n");
    printf("***************        *****         *****        *****************\n");
    printf("****        ****        *****       *****         *****************\n");
    printf("****        ****         *****     *****          ******\n");
    printf("****        ****          *****   *****           ******\n");
    printf("****        ****           ***** *****            ******\n");
    printf("***************             *********             *****************\n");
    printf("***************             *********             *****************\n");
    printf("****        ****            *********             ******\n");
    printf("****        ****            *********             ******\n");
    printf("****        ****            *********             ******\n");
    printf("****        ****            *********             *****************\n");
    printf("***************             *********             *****************\n");
    printf("**************              *********             *****************\n");
}

//// CLEAR THE VALUE THAT KEPT WHEN USER LOGGED IN
void syslogout() {
    login_session.index = 999;
    strcpy(login_session.id,"\0");
    strcpy(login_session.firstname,"\0");
    strcpy(login_session.lastname,"\0");
    strcpy(login_session.phone,"\0");
    strcpy(login_session.email,"\0");
    strcpy(login_session.password,"\0");
    /*printf("%d\n",login_session.index);
    printf("%s\n",login_session.id);
    printf("%s\n",login_session.firstname);
    printf("%s\n",login_session.lastname);
    printf("%s\n",login_session.phone);
    printf("%s\n",login_session.email);
    printf("%s\n",login_session.password);*/
    printf("Logged out!\n\n");
    mainmenu();
}

//// Check that does user exist in the system or not
int check_user_exists(char id[8]) {
    load_data();
    int total_data = count_data();
    int i;
    for(i=0;i<total_data;i++) {
        int cmp = strcmp(id,info[i].id);
        if(cmp == 0) {
            return 1;
        }
    }
    return 0;
}

//// Return index of user from an ID
int get_index_from_id(char id[8]) {
    load_data();
    int total_data = count_data();
    int i;
    for(i=0;i<total_data;i++) {
        int cmp = strcmp(info[i].id,id);
        if(cmp == 0) {
            return info[i].index;
        }
    }
    return -1;
}

////////////////////////////////////////////////
////       END OF UTILITIES FUNCTION        ////
////////////////////////////////////////////////

////////////////////////////////////////////////
////          REGISTRATION FUNCTION         ////
////////////////////////////////////////////////
////   WRITE Data to file
int regis_to_file(char id[8],char firstname[30],char lastname[30],char phone[11],char email[100],char password[20]) {
    FILE *fp;
    fp = fopen("data.txt", "a+");
    int index = count_data();

    fprintf(fp, "%d,", index);
    fprintf(fp, "%s,", id);
    fprintf(fp, "%s,", firstname);
    fprintf(fp, "%s,", lastname);
    fprintf(fp, "%s,", phone);
    fprintf(fp, "%s,", email);
    fprintf(fp, "%s,\n", password);

    int status = fclose(fp);
    if (status == 0) {
        return 0;
    } else {
        return 1;
    }
}

void registration()
{
    struct card contact;
    char confirm_pass[20];
    printf("Please enter the following information\n");
    printf("ID: ");
    scanf("%s", contact.id);

    while(strlen(contact.id) != 7 || isallnum(contact.id) == 0) {
        printf("[ERROR] You can use only 7 digits for ID\n");
        printf("[Re-type] ID: ");
        scanf("%s",contact.id);
    }
    while(check_user_exists(contact.id) == 1)
    {
        printf("This user is already exist!\n");
        printf("[Re-type] ID: ");
        scanf("%s",contact.id);
    }
    printf("First Name: ");
    scanf("%s", contact.firstname);
    printf("Last Name: ");
    scanf("%s", contact.lastname);
    printf("Phone Number: ");
    scanf("%s", contact.phone);
    while(strlen(contact.phone) != 10 || isallnum(contact.phone) == 0) {
        printf("[ERROR] You must use only 10 digit numbers for phone number\n");
        printf("[Re-type] Phone Number: ");
        scanf("%s",contact.phone);
    }

    printf("Email: ");
    scanf("%s", contact.email);
    while(is_email(contact.email) == 0) {
        printf("[ERROR] You must contain character @\n");
        printf("[Re-type] Email: ");
        scanf("%s",contact.email);
    }
    printf("Password: ");
    scanf("%s", contact.password);
    while(strlen(contact.password) < 8) {
        printf("[ERROR] You must use at least 8 characters for password\n");
        printf("[Re-type] Password: ");
        scanf("%s",contact.password);
    }
    printf("Confirmed Password: ");
    scanf("%s", confirm_pass);
    while(strcmp(contact.password,confirm_pass) != 0)
    {
        printf("[ERROR] These passwords don't match\n");
        printf("[Re-type] Confirmed Password:");
        scanf("%s", confirm_pass);
    }

    printf("\n-- End of the Registration Process --\n");
    printf("Congratulation!! %s,\n", contact.firstname);
    printf("Now you can login to the ICT Contact Management System and Start to\n search for ICT faculty staff's and friend's information.\n");
    regis_to_file(contact.id,contact.firstname,contact.lastname,contact.phone,contact.email,contact.password);
    printf("[INFO] : Press ENTER to go to main menu.");
    getchar();
    getchar();
    system("cls");
    mainmenu();
}

////////////////////////////////////////////////
////    END OF REGISTRATION FUNCTION        ////
////////////////////////////////////////////////

////////////////////////////////////////////////////////
//                     LOGIN                          //
////////////////////////////////////////////////////////

void set_session(int index,char id[8],char firstname[30],char lastname[30],char phone[11],char email[100],char password[20]) {
    login_session.index = index;
    strcpy(login_session.id,id);
    strcpy(login_session.firstname,firstname);
    strcpy(login_session.lastname,lastname);
    strcpy(login_session.phone,phone);
    strcpy(login_session.email,email);
    strcpy(login_session.password,password);
}

int check_pass(char id[8],char pass[20]) {
    load_data();
    int i;
    int data = count_data();
    int cmp,pass_cmp;
    for(i=0;i<data;i++) {
        cmp = strcmp(id,info[i].id);
        if(cmp == 0) {
            pass_cmp = strcmp(pass,info[i].password);
            if(pass_cmp == 0) {
            set_session(info[i].index,info[i].id,info[i].firstname,info[i].lastname,info[i].phone,info[i].email,info[i].password);
            return 0;
            break;
            }
            return 2;
        }
    }
    return 1;
}

void login()
{
    char id[8],password[20];
    printf("Enter ID:");
    scanf("%s",id);
    printf("Password:");
    scanf("%s",password);
    int status_check = check_pass(id,password);
    if (status_check == 0) {
        //printf("Logged in!!\n");
        if(check_role(id) == 1) {
            system("cls");
            printf("[INFO] Now you are logged in as a admin in the system.\n");
            printf("[INFO] You can start using the following functions.\n\n");
            admin_menu();
        } else {
            system("cls");
            printf("[INFO] Now you are logged in as a student in the system.\n");
            printf("[INFO] You can start using the following functions.\n\n");
            student_menu();
        }
    } else if (status_check == 2) {
        system("cls");
        printf("[ERROR] Invalid password!\n");
        login();
    } else {
        system("cls");
        printf("[ERROR] User not found!\n");
        login();
    }
}

////////////////////////////////////////////////////////
//                END OF LOGIN                        //
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//              ADMIN SECTION                       ////
////////////////////////////////////////////////////////
void admin_menu()
{
    char choice;
    printf("[1] Edit User's Contact\n");
    printf("[2] Show all Contacts\n");
    printf("[3] Search for a Contact\n");
    printf("[4] Delete User's Contact\n");
    printf("[0] Log out\n");
    printf("Please enter the choice : ");
    scanf(" %c",&choice);
    if(choice == '1'){
        system("cls");
        edit_userinfo();
    } else if (choice == '2') {
        system("cls");
        showall_contact(1);
    } else if (choice == '3') {
        system("cls");
        search_contact(1);
    } else if (choice == '4') {
        system("cls");
        delete_menu();
    } else if (choice == '0') {
        system("cls");
        syslogout();
    } else {
        system("cls");
        student_menu();
    }
}

void edit_userinfo() {
    char edit_id[8];
    char choice;
    char tmp[100];
    int edit_stat;
    printf("[Edit User's Contact]\n\n");
    printf("[ADMIN] ID: %s\n\n",login_session.id);
    printf("Please enter the id for editing: ");
    scanf("%s", edit_id);
    int check_id = check_user_exists(edit_id);
    while(check_id == 0) {
        printf("[ERROR] There is no matched id in the system.\n");
        printf("[Re-Type] Please enter the id for editing:");
        scanf("%s",edit_id);
        check_id = check_user_exists(edit_id);
    }
    int edit_index = get_index_from_id(edit_id);
    char pass_censored[20]="\0";
    int i;
    printf("[STUDENT] ID : %s\n\n",info[edit_index].id);
    printf("[Existing Information]\n");
    printf("First name: %s\n",info[edit_index].firstname);
    printf("Last name: %s\n",info[edit_index].lastname);
    printf("Phone number: %s\n",info[edit_index].phone);
    printf("Email: %s\n",info[edit_index].email);
    strncpy(pass_censored, info[edit_index].password, 5);
    printf("Password: %s",pass_censored);
    for(i=5;i<strlen(info[edit_index].password);i++) {
        printf("*");
    }
    printf("\n\n");

    printf("[1] First Name\n");
    printf("[2] Last Name\n");
    printf("[3] Phone Number\n");
    printf("[4] Email\n");
    printf("[5] Password\n");
    printf("[0] Cancel\n");
    printf("Please enter the choice to edit:");
    scanf(" %c",&choice);
    if(choice == '1') {
        printf("[Re-input] Firstname : ");
        scanf("%s",tmp);
        edit_stat = edit_data(edit_index,"firstname",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        admin_menu();
    } else if(choice == '2') {
        printf("[Re-input] Lastname : ");
        scanf("%s",tmp);
        edit_stat = edit_data(edit_index,"lastname",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        admin_menu();
    } else if (choice == '3') {
        printf("[Re-input] Phone number : ");
        scanf("%s",tmp);
        while(strlen(tmp) != 10 || isallnum(tmp) == 0) {
        printf("[ERROR] You must use only 10 digit numbers for phone number\n");
        printf("[Re-input] Phone number : ");
        scanf("%s",tmp);
        }
        edit_stat = edit_data(edit_index,"phone",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        admin_menu();
    } else if (choice == '4') {
        printf("[Re-input] Email : ");
        scanf("%s",tmp);
        while(is_email(tmp) == 0) {
        printf("[ERROR] You must contain character @\n");
        printf("[Re-type] Email: ");
        scanf("%s",tmp);
        }
        edit_stat = edit_data(edit_index,"email",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        admin_menu();
    } else if (choice == '5') {
        printf("[Re-input] Password : ");
        scanf("%s",tmp);
        while(strlen(tmp) < 8) {
        printf("[ERROR] You must use at least 8 characters for password\n");
        printf("[Re-type] Password: ");
        scanf("%s",tmp);
        }
        edit_stat = edit_data(edit_index,"password",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        admin_menu();
    } else if (choice == '0') {
        admin_menu();
    } else {
        admin_menu();
    }
}

void delete_menu() {
    char usrdel[8];
    char choice;
    printf("[Delete User's Contact]\n");
    printf("[ADMIN] ID: %s\n\n",login_session.id);
    printf("Please enter the id for deleting: ");
    scanf("%s",usrdel);
    while(check_user_exists(usrdel) == 0) {
        printf("User nor found!\n");
        printf("Please enter the id for deleting: ");
        scanf("%s",usrdel);
    }
    while(strcmp(usrdel,login_session.id) == 0)
    {
        printf("You can't delete yourself!\n");
        printf("Please enter the id for deleting: ");
        scanf("%s",usrdel);
    }
    int delindex = get_index_from_id(usrdel);
    printf("[STUDENT]\nID : %s\n\n",info[delindex].id);
    printf("First name: %s\n",info[delindex].firstname);
    printf("Last name: %s\n",info[delindex].lastname);
    printf("Phone number: %s\n",info[delindex].phone);
    printf("Email: %s\n",info[delindex].email);

    printf("\nDo you want to delete this contact information? [y/n]:");
    scanf(" %c",&choice);
    while(choice != 'y' || choice != 'Y' || choice != 'n' || choice != 'N') {
        if(choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
            break;
        } else {
        printf("\nDo you want to delete this contact information? [y/n]:");
        scanf(" %c",&choice);
        }
    }
    if(choice == 'y' || choice == 'Y') {
        if(delete_user(usrdel) == 0) {
            printf("\nDelete this user succesfully!");
            load_data();
            printf("\nPress ENTER to back to menu");
            char c;
            getchar();
            c = getchar();
            if(c != NULL) {
                system("cls");
                admin_menu();
            }
        }
    } else if (choice == 'n' || choice == 'N') {
        system("cls");
        delete_menu();
    } else {
        system("cls");
        delete_menu();
    }

}

////////////////////////////////////////////////////////
//              END OF ADMIN SECTION                ////
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//                STUDENT SECTION                   ////
////////////////////////////////////////////////////////
void student_menu()
{
    char choice;
    printf("[1] Edit My Contact Information\n");
    printf("[2] Show all Contacts\n");
    printf("[3] Search for a Contact\n");
    printf("[0] Log out\n");
    printf("Please enter the choice : ");
    scanf(" %c",&choice);
    if(choice == '1'){
        system("cls");
        edit_myinfo();
    } else if (choice == '2') {
        system("cls");
        showall_contact(0);
    } else if (choice == '3') {
        system("cls");
        search_contact(0);
    } else if (choice == '0') {
        system("cls");
        syslogout();
    } else {
        system("cls");
        student_menu();
    }
}

void edit_myinfo() {
    char choice;
    int edit_stat;
    char tmp[100];
    char pass_censored[20]="\0";
    char confirm_pass[20];
    int i;
    printf("[Edit My Contact Information]\n\n");
    printf("[STUDENT] ID : %s\n\n",login_session.id);
    printf("[Existing Information]\n");
    printf("First name: %s\n",login_session.firstname);
    printf("Last name: %s\n",login_session.lastname);
    printf("Phone number: %s\n",login_session.phone);
    printf("Email: %s\n",login_session.email);
    strncpy(pass_censored, login_session.password, 5);
    printf("Password: %s",pass_censored);
    for(i=5;i<strlen(login_session.password);i++) {
        printf("*");
    }
    printf("\n\n");
    printf("[1] First Name\n");
    printf("[2] Last Name\n");
    printf("[3] Phone Number\n");
    printf("[4] Email\n");
    printf("[5] Password\n");
    printf("[0] Cancel\n");
    printf("Please enter the choice to edit:");
    scanf(" %c",&choice);
    if(choice == '1') {
        printf("[Re-input] Firstname : ");
        scanf("%s",tmp);
        edit_stat = edit_data(login_session.index,"firstname",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        strcpy(login_session.firstname,tmp);
        system("cls");
        student_menu();
    } else if(choice == '2') {
        printf("[Re-input] Lastname : ");
        scanf("%s",tmp);
        edit_stat = edit_data(login_session.index,"lastname",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        strcpy(login_session.lastname,tmp);
        system("cls");
        student_menu();
    } else if (choice == '3') {
        printf("[Re-input] Phone number : ");
        scanf("%s",tmp);
        while(strlen(tmp) != 10 || isallnum(tmp) == 0) {
        printf("[ERROR] You must use only 10 digit numbers for phone number\n");
        printf("[Re-input] Phone number : ");
        scanf("%s",tmp);
        }
        edit_stat = edit_data(login_session.index,"phone",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        strcpy(login_session.phone,tmp);
        system("cls");
        student_menu();
    } else if (choice == '4') {
        printf("[Re-input] Email : ");
        scanf("%s",tmp);
        while(is_email(tmp) == 0) {
        printf("[ERROR] You must contain character @\n");
        printf("[Re-type] Email: ");
        scanf("%s",tmp);
        }
        edit_stat = edit_data(login_session.index,"email",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        strcpy(login_session.email,tmp);
        system("cls");
        student_menu();
    } else if (choice == '5') {
        printf("[Re-input] Password : ");
        scanf("%s",tmp);
        while(strlen(tmp) < 8) {
        printf("[ERROR] You must use at least 8 characters for password\n");
        printf("[Re-type] Password: ");
        scanf("%s",tmp);
        }
        printf("Confirmed Password : ");
        scanf("%s",confirm_pass);
        while(strcmp(tmp,confirm_pass) != 0)
        {
        printf("[ERROR] These passwords don't match\n");
        printf("[Re-type] Confirmed Password:");
        scanf("%s",confirm_pass);
        }
        edit_stat = edit_data(login_session.index,"password",tmp);
        if(edit_stat != 0) {
            printf("\nError! Can't edit data\n");
        }
        strcpy(login_session.password,tmp);
        system("cls");
        student_menu();
    } else if (choice == '0') {
        system("cls");
        student_menu();
    } else {
        system("cls");
        student_menu();
    }
}

////////////////////////////////////////////////////////
//                END OF STUDENT SECTION            ////
////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
////                   DATA MANAGEMENT                     ////
///////////////////////////////////////////////////////////////

//to write data after edited to new file and remove old file
int write_new_data() {
    int i;
    int data = count_data();
    FILE *fp;
    fp = fopen("data_new.txt", "w");

    for(i=0;i<data;i++) {
    fprintf(fp, "%d,", info[i].index);
    fprintf(fp, "%s,", info[i].id);
    fprintf(fp, "%s,", info[i].firstname);
    fprintf(fp, "%s,", info[i].lastname);
    fprintf(fp, "%s,", info[i].phone);
    fprintf(fp, "%s,", info[i].email);
    fprintf(fp, "%s,\n", info[i].password);
    }

    fclose(fp);
    int rem = remove("data.txt");
    int ren = rename("data_new.txt","data.txt");
    if(rem == 0 && ren == 0) {
        return 0;
    } else {
        return 1;
    }
}

//to edit data in structure that we keep in info
int edit_data(int index,char column[],char newdata[]) {
    if(column == "firstname") {
        strcpy(info[index].firstname,newdata);
    } else if(column == "lastname") {
        strcpy(info[index].lastname,newdata);
    } else if(column == "phone") {
        strcpy(info[index].phone,newdata);
    } else if(column == "email") {
        strcpy(info[index].email,newdata);
    } else if(column == "password") {
        strcpy(info[index].password,newdata);
    }
    int stat = write_new_data();
    if (stat == 0) {
        return 0;
    } else {
        return 1;
    }
}

void showall_contact(int role) {
    int i=0;
    load_data();
    char showrole[9];
    int checkrole;

    printf("================================\n");
    printf("||        [USER LISTS]        ||\n");
    printf("================================\n");
    printf("============================================================================================\n");
    printf("%-2s %-8s %-20s %-20s %-8s %-13s %-30s\n","NO","ID","NAME","SURNAME","ROLE","PHONE","EMAIL");
    printf("============================================================================================\n");
    for(i=0;i<count_data();i++) {
        checkrole = check_role(info[i].id);
        if(checkrole == 1) {
            strcpy(showrole,"ADMIN");
        } else {
            strcpy(showrole,"STUDENTS");
        }
        if(role == 0 && checkrole == 1) { continue; }
        printf("%-2d %-8s %-20s %-20s %-8s %-13s %-30s\n",info[i].index,info[i].id,info[i].firstname,info[i].lastname,showrole,info[i].phone,info[i].email);

    }
    printf("\n");
    printf("Press ENTER to back to menu");
    char c;
    getchar();
    c = getchar();
    if(role == 0 && c != NULL) {
    system("cls");
    student_menu();
    } else if (role == 1 && c != NULL) {
    system("cls");
    admin_menu();
    }
}

void search_contact(int role)
{
    int i,check=0;
    char find[20];
    char showrole[9];
    int checkrole;
    printf("Search For Contact\n\n");
    printf("=========================\n");
    printf("Contact information\n");
    printf("=========================\n\n");
    printf("Please input First Name for searching : ");
    scanf("%s", find);
    while(check_contact(find,role) != 1)
    {
        printf("[ERROR] There is no person Name '%s' in the system.\n",find);
        printf("[Retype] First name for searching : ");
        scanf("%s", find);
    }
    if(check_contact(find,role) == 1)
    {
        printf("%-2s %-8s %-20s %-20s %-8s %-13s %-30s\n","NO","ID","NAME","SURNAME","ROLE","PHONE","EMAIL");
        printf("===========================================================================================\n");
        for (i=0;i<count_data();i++) {
        if(strstr(info[i].firstname,find) != NULL)
        {
            check=1;
            checkrole = check_role(info[i].id);
            if(checkrole == 1) {
            strcpy(showrole,"ADMIN");
            } else {
            strcpy(showrole,"STUDENTS");
            }
            if(role == 0 && checkrole == 1) { continue; }
            printf("%-2d %-8s %-20s %-20s %-8s %-13s %-30s\n",info[i].index,info[i].id,info[i].firstname,info[i].lastname,showrole,info[i].phone,info[i].email);
        }
        }
        printf("===========================================================================================\n");
        printf("\n");
        printf("Press ENTER to back to menu");
        char c;
        getchar();
        c = getchar();
        if(role == 0 && c != NULL) {
        system("cls");
        student_menu();
        } else if (role == 1 && c != NULL) {
        system("cls");
        admin_menu();
        }

    }
}

int check_contact(char find[],int role)
{
    int i, check = 0;
    for (i=0; i<count_data(); i++) {
        if(role == 0 && check_role(info[i].id) == 1) {
            continue;
        }
        if(strstr(info[i].firstname,find) != NULL)
        {
                check=1;
                break;
                //printf("[%d] %-8s%-20s%-20s%-13s%-30s\n",info[i].index,info[i].id,info[i].firstname,info[i].lastname,info[i].phone,info[i].email);
        }
    }
    if(check == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void delete_user(char id[]) {
    int i;
    int data = count_data();
    int isdelete=0;
    FILE *fp;
    fp = fopen("data_new.txt", "w");

    for(i=0;i<data;i++) {
    if(strcmp(id,info[i].id) == 0) {
        isdelete = 1;
        continue;
    }
    if(isdelete == 1) {
    fprintf(fp, "%d,", info[i].index-1);
    fprintf(fp, "%s,", info[i].id);
    fprintf(fp, "%s,", info[i].firstname);
    fprintf(fp, "%s,", info[i].lastname);
    fprintf(fp, "%s,", info[i].phone);
    fprintf(fp, "%s,", info[i].email);
    fprintf(fp, "%s,\n", info[i].password);
    } else {
    fprintf(fp, "%d,", info[i].index);
    fprintf(fp, "%s,", info[i].id);
    fprintf(fp, "%s,", info[i].firstname);
    fprintf(fp, "%s,", info[i].lastname);
    fprintf(fp, "%s,", info[i].phone);
    fprintf(fp, "%s,", info[i].email);
    fprintf(fp, "%s,\n", info[i].password);
    }
    }
    fclose(fp);
    int rem = remove("data.txt");
    int ren = rename("data_new.txt","data.txt");
    if(rem == 0 && ren == 0) {
        return 0;
    } else {
        return 1;
    }
}

///////////////////////////////////////////////////////////////
////               END OF DATA MANAGEMENT                  ////
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
////            EXTRA FEATUEES - FORGOT PASSWORD           ////
///////////////////////////////////////////////////////////////
void forget_pass()
{
    struct card forgotpass;
    int reset=0;
    int index=0;
    char newpass[20];
    char cnewpass[20];
    printf("=======================================\n");
    printf("||          FORGOT PASSWORD          ||\n");
    printf("=======================================\n\n");
    printf("In order to reset password.\nUser must enter all of information correctly\nwith the old information in the system.\n");
    printf("ID:");
    scanf("%s",forgotpass.id);
    printf("Firstname:");
    scanf("%s",forgotpass.firstname);
    printf("Lastname:");
    scanf("%s",forgotpass.lastname);
    printf("Phone Number:");
    scanf("%s",forgotpass.phone);
    printf("Email:");
    scanf("%s",forgotpass.email);
    if(check_user_exists(forgotpass.id) == 1) {
        load_data();
        index = get_index_from_id(forgotpass.id);
        if(strcmp(info[index].firstname,forgotpass.firstname) == 0) {
            if(strcmp(info[index].lastname,forgotpass.lastname) == 0) {
                if(strcmp(info[index].phone,forgotpass.phone) == 0) {
                    if(strcmp(info[index].email,forgotpass.email) == 0) {
                        reset = 1;
                    }
                }
            }
        }
    }
    if(reset == 1) {
        printf("\nData validated! You can reset password now!\n");
        printf("New password :");
        scanf("%s",newpass);
        while(strlen(newpass) < 8) {
        printf("[ERROR] You must use at least 8 characters for password\n");
        printf("[Re-type] New password: ");
        scanf("%s",newpass);
        }
        printf("Confirmed Password: ");
        scanf("%s", cnewpass);
        while(strcmp(newpass,cnewpass) != 0)
        {
            printf("[ERROR] These passwords don't match\n");
            printf("[Re-type] Confirmed Password:");
            scanf("%s", cnewpass);
        }
        int sta = edit_data(index,"password",cnewpass);
        if(sta == 0) {
            printf("Password Reset succesfully!");
            printf("\nPress ENTER to back to main menu");
            char c;
            getchar();
            c = getchar();
            if(c != NULL) {
                system("cls");
                mainmenu();
            }
        }
    } else {
        printf("Data that you type doesn't match our record in system!");
        printf("\nPress ENTER to back to main menu");
        char c;
        getchar();
        c = getchar();
        if(c != NULL) {
            system("cls");
            mainmenu();
        }
    }
}

///////////////////////////////////////////////////////////////
////       END OF EXTRA FEATUEES - FORGOT PASSWORD         ////
///////////////////////////////////////////////////////////////

int main() {
    mainmenu();
}
