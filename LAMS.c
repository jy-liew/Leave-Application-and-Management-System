// author: jy-liew

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define BACKSPACE 8  // define ASCII codes for characters
#define TAB 9
#define ENTER 13
char username[70], password[70]; // global variables

// function prototypes
void admin_menu(), add_staff_info(), update_leave_balance(), search_leave(), leave_report();
void staff_menu(), apply_leave(), cancel_leave(), check_leave_status(), leave_summary();
void superior_menu(), approve_leave(), search_date();
void pwmask(), check_superior(int);

// global structures
typedef struct Staff
{
    char name[100];
    char gender[10];
    int staffid;
    char role[20];
    char position[100];
    char department[20];
    int annual_leave;
    int compassionate_leave;
    int emergency_leave;
    int maternity_leave;
    int medical_leave;
    char username[70];
} Staff;

typedef struct Leave
{
    char name[100];
    int staffid;
    char department[20];
    char leave_type[20];
    int days;
    // date[0] = day, date[1] = month, date[2] = year
    int start_date[3];
    int end_date[3];
    char approve_status[20];
    char username[70];
} Leave;

// Function that displays all options for admin and lets admin choose which option he wants.
void admin_menu()
{
    char choice;
    while(1){
        // administrator menu
        printf("-------------------\n");
        printf("Administrator Menu\n");
        printf("-------------------\n");
        printf("1. Add new staff information\n");
        printf("2. Update staff leave balance\n");
        printf("3. Search staff leave information\n");
        printf("4. Generate leave statistics monthly report\n");
        printf("5. Exit\n");
        printf("------------------\n");

        // let admin select the option
        printf("Please select by entering 1, 2, 3, 4 or 5: ");
        scanf(" %d", &choice);
        getchar(); // for negative test case

        switch(choice){
            case 1:
            add_staff_info(); break;
            case 2: 
            update_leave_balance(); break;
            case 3:
            search_leave(); break;
            case 4:
            leave_report(); break;
            case 5:
            exit(0); break;
            default:
            printf("Error: Invalid input\n\n"); break;
        }
    }
}

// Function that allows admin to add new staff information to the system.
void add_staff_info()
{
    FILE *credentials;
    FILE *staff_information;
    Staff staff1, staff2;
    char create_username[70], create_password[70];
    char gender;
    int staffid = 1;
    int loop_choice = 0;
    int role, department;
    staff_information = fopen("staff_information.bin", "rb");
    if(staff_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n-----------------------\n");
    printf("Add Staff Information\n");
    printf("-----------------------\n");
    
    // Auto generate staff ID for staff
    while(fread(&staff2, sizeof(Staff), 1, staff_information) == 1){
        if(staff2.staffid != NULL)
        {
            staffid += 1;
        }
    }
    
    staff1.staffid = staffid;
    printf("\nStaff ID: %04d\n", staff1.staffid);

    printf("Name: ");
    scanf("%[^\n]s", &staff1.name);

    while(1){
        printf("Gender (M/F): ");
        scanf(" %c", &gender);
        if(gender == 'M' || gender == 'm')
        {
            strcpy(staff1.gender, "Male");
            break;
        }
        else if(gender == 'F' || gender == 'f')
        {
            strcpy(staff1.gender, "Female");
            break;
        }
        else
        {
            printf("Error: Invalid input\n\n");
        }
    }

    while(1){
        printf("Role (Enter 1 for Administrator, 2 for Staff, 3 for Superior): ");
        scanf("%d", &role);
        getchar(); // for negative test case
        if(role == 1)
        {
            strcpy(staff1.role, "Administrator");
            break;
        }
        if(role == 2)
        {
            strcpy(staff1.role, "Staff");
            break;
        }
        if(role == 3)
        {
            strcpy(staff1.role, "Superior");
            break;
        }
        else
        {
            printf("Error: Invalid input\n\n");
        }
    }
    printf("Position: ");
    scanf("%[^\n]s", &staff1.position);
    while(1){
        printf("Department (Enter 1 for Academic, 2 for Admistration, 3 for Management, 4 for Techincal): ");
        scanf("%d", &department);
        getchar();
        if(department == 1)
        {
            strcpy(staff1.department, "Academic");
            break;
        }
        if(department == 2)
        {
            strcpy(staff1.department, "Administration"); 
            break;
        }
        if(department == 3)
        {
            strcpy(staff1.department, "Management");
            break;
        }
        if(department == 4)
        {
            strcpy(staff1.department, "Technical"); 
            break;
        }
        else
        {
            printf("Error: Invalid input\n\n");
        }
    }

    while(1){
        printf("Annual leave amount: ");
        scanf("%d", &staff1.annual_leave);
        getchar();
        if(staff1.annual_leave < 0)
        {
            printf("Error: Invalid input\n\n");
        }
        else
        {
            break;
        }
    }
    while(1){
        printf("Compassionate leave amount: ");
        scanf("%d", &staff1.compassionate_leave);
        getchar();
        if(staff1.compassionate_leave < 0)
        {
            printf("Error: Invalid input\n\n");
        }
        else
        {
            break;
        }
    }
    while(1){
        printf("Emergency leave amount: ");
        scanf("%d", &staff1.emergency_leave);
        getchar();
        if(staff1.emergency_leave < 0)
        {
            printf("Error: Invalid input\n\n");
        }
        else
        {
            break;
        }
    }
    while(1){
        printf("Maternity leave amount: ");
        scanf("%d", &staff1.maternity_leave);
        getchar();
        if(staff1.maternity_leave < 0)
        {
            printf("Error: Invalid input\n\n");
        }
        else
        {
            break;
        }
    }
    while(1){
        printf("Medical leave amount: ");
        scanf("%d", &staff1.medical_leave);
        getchar();
        if(staff1.medical_leave < 0)
        {
            printf("Error: Invalid input\n\n");
        }
        else
        {
            break;
        }
    }

    // Check username that is entered by user to make sure there is no duplication of usernames.
    while(loop_choice == 0){
        fseek(staff_information, 0, SEEK_SET);
        printf("Username (cannot have space, cannot be same as other staff): ");
        scanf("%s", create_username);
        while(fread(&staff2, sizeof(Staff), 1, staff_information) == 1){
            if(strcmp(create_username, staff2.username) == 0)
            {
                printf("Error: Username has been used by another staff. Please enter a different username.\n\n");
                break;
            }
        }
        if(feof(staff_information))
        {
            strcpy(staff1.username, create_username);
            loop_choice = 1;
        }
    }
    fclose(staff_information);

    printf("Password: ");
    scanf("%s", create_password);

    staff_information = fopen("staff_information.bin", "ab");
    fwrite(&staff1, sizeof(Staff), 1, staff_information); // append new staff information into binary file
    fclose(staff_information);
    
    if(strcmp(staff1.role, "Administrator") == 0)
    {
        credentials = fopen("admin_credentials.txt", "a");
        if (credentials == NULL)
        {
            printf("Error opening file.\n");
            exit(1);
        }
        else
        {
            fprintf(credentials, "%s %s \n", create_username, create_password);
            printf("Administrator account successfully registered.\n\n");
            fclose(credentials);
        }
    }
    else if(strcmp(staff1.role, "Staff") == 0)
    {
        credentials = fopen("staff_credentials.txt", "a");
        if (credentials == NULL)
        {
            printf("Error opening file.\n");
            exit(1);
        }
        else
        {
            fprintf(credentials, "%s %s \n", create_username, create_password);
            printf("Staff account successfully registered.\n\n");
            fclose(credentials);
        }
    }
    else if(strcmp(staff1.role, "Superior") == 0)
    {
        credentials = fopen("superior_credentials.txt", "a");
        if (credentials == NULL)
        {
            printf("Error opening file.\n");
            exit(1);
        }
        else
        {
            fprintf(credentials, "%s %s \n", create_username, create_password);
            printf("Superior account successfully registered.\n\n");
            fclose(credentials);
        }
    }
}

// Function that allows admin to update the leave balance of staff.
void update_leave_balance()
{
    FILE *staff_information;
    Staff staff1;
    int loop_choice = 0, loop_choice2;
    int found = 0;
    int staffid, choice, choice2, update_status;
    staff_information = fopen("staff_information.bin", "rb+");

    if(staff_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n----------------------------\n");
    printf("Update Staff Leave Balance\n");
    printf("----------------------------\n");
    printf("Staff Information\n");
    printf("------------------\n");
    while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
        printf("Name: %s\tStaff ID: %04d\n", staff1.name, staff1.staffid);
    }

    while(found == 0){
        fseek(staff_information, 0, SEEK_SET);
        printf("\nPlease enter the staff ID to modify: ");
        scanf("%d", &staffid);
        getchar();

        while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
            if(staffid == staff1.staffid)
            {
                found = 1;
                break;
            }
        }
    
        if(found == 0)
        {
            printf("\nError: Staff is not found\n");
        }
    }

    while(loop_choice == 0){
        loop_choice2 = 0;
        fseek(staff_information, 0, SEEK_SET);
        while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
            if(staffid == staff1.staffid)
            {
                printf("\nStaff record with requested ID is found.\n");
                printf("1. Annual leave: %d days\n", staff1.annual_leave);
                printf("2. Compassionate leave: %d days\n", staff1.compassionate_leave);
                printf("3. Emergency leave: %d days\n", staff1.emergency_leave);
                printf("4. Maternity leave: %d days\n", staff1.maternity_leave);
                printf("5. Medical leave: %d days\n", staff1.medical_leave);

                while(loop_choice2 == 0){
                    printf("Please select the type of leave to update by entering 1, 2, 3, 4 or 5: ");
                    scanf("%d", &choice);
                    getchar();
                    if(choice == 1)
                    {
                        loop_choice2 = 1;
                        while(1){
                            printf("Enter new Annual leave amount: ");
                            scanf("%d", &staff1.annual_leave);
                            getchar();
                            if(staff1.annual_leave < 0)
                            {
                                printf("Error: Invalid input\n\n");
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else if(choice == 2)
                    {
                        loop_choice2 = 1;
                        while(1){
                            printf("Enter new Compassionate leave amount: ");
                            scanf("%d", &staff1.compassionate_leave);
                            getchar();
                            if(staff1.compassionate_leave < 0)
                            {
                                printf("Error: Invalid input\n\n");
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else if(choice == 3)
                    {
                        loop_choice2 = 1;
                        while(1){
                            printf("Enter new Emergency leave amount: ");
                            scanf("%d", &staff1.emergency_leave);
                            getchar();
                            if(staff1.emergency_leave < 0)
                            {
                                printf("Error: Invalid input\n\n");
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else if(choice == 4)
                    {
                        loop_choice2 = 1;
                        while(1){
                            printf("Enter new Maternity leave amount: ");
                            scanf("%d", &staff1.maternity_leave);
                            getchar();
                            if(staff1.maternity_leave < 0)
                            {
                                printf("Error: Invalid input\n\n");
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else if(choice == 5)
                    {
                        loop_choice2 = 1;
                        while(1){
                            printf("Enter new Medical leave amount: ");
                            scanf("%d", &staff1.medical_leave);
                            getchar();
                            if(staff1.medical_leave < 0)
                            {
                                printf("Error: Invalid input\n\n");
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("Error: Invalid input\n\n");
                        continue;
                    }
                    fseek(staff_information, ftell(staff_information) - sizeof(Staff), SEEK_SET);
                    update_status = fwrite(&staff1, sizeof(Staff), 1, staff_information);
                }
                break;
            }
        }
    
        if(update_status == 1)
        {
            printf("Leave balance is updated successfully\n\n");
            printf("Do you want to update another type of leave?\n");
            while(1){
                printf("Enter 1 for Yes, enter 2 for No: ");
                scanf("%d", &choice2);
                getchar();
                if(choice2 == 1)
                {
                    break;
                }
                else if(choice2 == 2)
                {
                    loop_choice = 1;
                    printf("\n");
                    break;
                }
                else
                {
                    printf("Error: Invalid input\n\n");
                }
            }
        }
        else
        {
            printf("Error: Leave balance is not updated\n");
        }
    }
    fclose(staff_information);
}

// Function that allows admin to search for a staff using staff ID, then display leave balance of staff.
void search_leave()
{
    FILE *staff_information;
    Staff staff1;
    int staffid, found = 0;

    staff_information = fopen("staff_information.bin", "rb");
    if(staff_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n--------------\n");
    printf("Search Leave\n");
    printf("--------------\n");
    printf("Please enter the staff ID to search: ");
    scanf("%d", &staffid);
    getchar();

    while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
        if(staff1.staffid == staffid)
        {
            found = 1;
            printf("\nName: %s\n", staff1.name);
            printf("Department: %s\n", staff1.department);
            printf("Annual leaves: %d\n", staff1.annual_leave);
            printf("Compassionate leaves: %d\n", staff1.compassionate_leave);
            printf("Emergency leaves: %d\n", staff1.emergency_leave);
            printf("Maternity leaves: %d\n", staff1.maternity_leave);
            printf("Medical leaves: %d\n", staff1.medical_leave);
            break;
        }
    }
    printf("\n");
    fclose(staff_information);
    if(found == 0)
    {
        printf("\nError: Staff is not found\n");
        search_leave(); // call the search_leave function again
    }
}

// Function that allows admin to generate monthly report that contains the quantity of approved leaves for every department.
void leave_report()
{
    struct DepartLeave
    {
        int annual_leave;
        int compassionate_leave;
        int emergency_leave;
        int maternity_leave;
        int medical_leave;
    };
    FILE *leave_information;
    FILE *leave_report;
    Leave leave1;
    /* Array of structures: 0 = Academic, 1 = Administration, 2 = Management, 3 = Technical
    Set all leave values to 0 */
    struct DepartLeave department[4] = {{0},{0},{0},{0}};
    char department_type[4][20] = {"Academic", "Administration", "Management", "Technical"};
    int month;
    char line[50];

    leave_information = fopen("leave_information.bin", "rb");
    if(leave_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    
    printf("\n-------------------------\n");
    printf("Leave Statistics Report\n");
    printf("-------------------------");

    while(1){
        printf("\nEnter the month (1-12) to generate report: ");
        scanf("%d", &month);
        getchar();

        if(month < 1 || month > 12)
        {
            printf("\nError: Invalid month was entered\n");
        }
        else
        {
            break;
        }
    }

    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        for(int i = 0; i < 4; i++){
            if(leave1.start_date[1] == month && strcmp(leave1.department, department_type[i]) == 0 &&
            strcmp(leave1.leave_type, "Annual") == 0 && strcmp(leave1.approve_status, "Approved") == 0)
            {
                department[i].annual_leave += leave1.days;
            }
            else if(leave1.start_date[1] == month && strcmp(leave1.department, department_type[i]) == 0 &&
            strcmp(leave1.leave_type, "Compassionate") == 0 && strcmp(leave1.approve_status, "Approved") == 0)
            {
                department[i].compassionate_leave += leave1.days;
            }
            else if(leave1.start_date[1] == month && strcmp(leave1.department, department_type[i]) == 0 &&
            strcmp(leave1.leave_type, "Emergency") == 0 && strcmp(leave1.approve_status, "Approved") == 0)
            {
                department[i].emergency_leave += leave1.days;
            }
            else if(leave1.start_date[1] == month && strcmp(leave1.department, department_type[i]) == 0 &&
            strcmp(leave1.leave_type, "Maternity") == 0 && strcmp(leave1.approve_status, "Approved") == 0)
            {
                department[i].maternity_leave += leave1.days;
            }
            else if(leave1.start_date[1] == month && strcmp(leave1.department, department_type[i]) == 0 &&
            strcmp(leave1.leave_type, "Medical") == 0 && strcmp(leave1.approve_status, "Approved") == 0)
            {
                department[i].medical_leave += leave1.days;
            }
        }
    }
    fclose(leave_information);

    leave_report = fopen("leave_report.txt", "w");
    if(leave_report == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    else
    {
        for(int i = 0; i < 4; i++){
        fprintf(leave_report, "Month: %d\n", month);
        fprintf(leave_report, "%s Department\n", department_type[i]);
        fprintf(leave_report, "---------------------------\n");
        fprintf(leave_report, "Annual leave: %d days\n", department[i].annual_leave);
        fprintf(leave_report, "Compassionate leave: %d days\n", department[i].compassionate_leave);
        fprintf(leave_report, "Emergency leave: %d days\n", department[i].emergency_leave);
        fprintf(leave_report, "Maternity leave: %d days\n", department[i].maternity_leave);
        fprintf(leave_report, "Medical leave: %d days\n", department[i].medical_leave);
        fprintf(leave_report, "Total: %d days\n\n\n", department[i].annual_leave + department[i].compassionate_leave + 
                department[i].emergency_leave + department[i].maternity_leave + department[i].medical_leave);
        }
        printf("\nReport generated successfully!\n\n");
        fclose(leave_report);
    }

    leave_report = fopen("leave_report.txt", "r");

    while(!feof(leave_report)){
        if(fgets(line, 50, leave_report) != NULL)
        {
            printf("%s", line);
        }
    }
    fclose(leave_report);
}

// Function that displays all options for staff and lets staff choose which option he wants.
void staff_menu()
{
    int choice;
    while(1)
    {
        printf("\n------------\n");
        printf("Staff Menu\n");
        printf("------------\n");
        printf("1. Apply leave\n");
        printf("2. Cancel leave\n");
        printf("3. Check leave status\n");
        printf("4. Summary of leave information\n");
        printf("5. Exit\n");
        printf("------------------\n");

        printf("Please select by entering 1, 2, 3, 4 or 5: ");
        scanf("%d", &choice);
        getchar(); // for negative test case
        switch (choice){
            case 1: apply_leave(); break;
            case 2: cancel_leave(); break;
            case 3: check_leave_status(); break;
            case 4: leave_summary(); break;
            case 5: exit(0); break;
            default: printf("Error: Invalid input\n"); break;
        }
    }
}

// Function that allows staff to apply for a leave.
void apply_leave()
{
    FILE *staff_information;
    FILE *leave_information;
    Staff staff1;
    Leave leave1;
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int choice, found = 0;
    leave1.start_date[2] = 2023;
    leave1.end_date[2] = 2023;

    staff_information = fopen("staff_information.bin", "rb");
    if(staff_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
        if(strcmp(staff1.username, username) == 0)
        {
            found = 1;
            strcpy(leave1.name, staff1.name);
            leave1.staffid = staff1.staffid;
            strcpy(leave1.department, staff1.department);
            break;
        }
    }
    if(found == 0)
    {
        printf("\nError: Staff cannot be found\n");
        exit(1);
    }
    
    printf("\n--------------\n");
    printf("Apply Leave\n");
    printf("--------------");
    while(1){
        printf("\nWhat type of leave do you want to apply?\n");
        printf("1. Annual leave\n");
        printf("2. Compassionate leave\n");
        printf("3. Emergency leave\n");
        printf("4. Maternity leave\n");
        printf("5. Medical leave\n");
        printf("Enter the number to choose: ");
        scanf("%d", &choice);
        getchar();

        if(choice == 1)
        {
            strcpy(leave1.leave_type, "Annual");
            break;
        }
        else if(choice == 2)
        {
            strcpy(leave1.leave_type, "Compassionate");
            break;
        }
        else if(choice == 3)
        {
            strcpy(leave1.leave_type, "Emergency");
            break;
        }
        else if(choice == 4)
        {
            strcpy(leave1.leave_type, "Maternity");
            break;
        }
        else if(choice == 5)
        {
            strcpy(leave1.leave_type, "Medical");
            break;
        }
        else
        {
            printf("Error: Invalid input\n");
        }
    }

    while(1){
        printf("Please enter the days of leave: ");
        scanf("%d", &leave1.days);
        getchar();
        if(leave1.days < 1)
        {
            printf("Error: Invalid input\n\n");
        }
        else
        {
            break;
        }
    }

    fseek(staff_information, 0, SEEK_SET);
    while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
        if(strcmp(staff1.username, username) == 0 && strcmp(leave1.leave_type, "Annual") == 0)
        {
            if(staff1.annual_leave < leave1.days)
            {
                printf("\nError: Insufficient annual leave is available.\n");
                staff_menu();
            }
            else
            {
                break;
            }
        }
        else if(strcmp(staff1.username, username) == 0 && strcmp(leave1.leave_type, "Compassionate") == 0)
        {
            if(staff1.compassionate_leave < leave1.days)
            {
                printf("\nError: Insufficient compassionate leave is available.\n");
                staff_menu();
            }
            else
            {
                break;
            }
        }
        else if(strcmp(staff1.username, username) == 0 && strcmp(leave1.leave_type, "Emergency") == 0)
        {
            if(staff1.emergency_leave < leave1.days)
            {
                printf("\nError: Insufficient emergency leave is available.\n");
                staff_menu();
            }
            else
            {
                break;
            }
        }
        else if(strcmp(staff1.username, username) == 0 && strcmp(leave1.leave_type, "Maternity") == 0)
        {
            if(staff1.maternity_leave < leave1.days)
            {
                printf("\nError: Insufficient maternity leave is available.\n");
                staff_menu();
            }
            else
            {
                break;
            }
        }
        else if(strcmp(staff1.username, username) == 0 && strcmp(leave1.leave_type, "Medical") == 0)
        {
            if(staff1.medical_leave < leave1.days)
            {
                printf("\nError: Insufficient medical leave is available.\n");
                staff_menu();
            }
            else
            {
                break;
            }
        }
    }
    fclose(staff_information);

    printf("Please enter starting date of leave\n");
    printf("Year: %d\n", leave1.start_date[2]);
    while(1){
        printf("Month (Enter Digit): ");
        scanf("%d", &leave1.start_date[1]);
        getchar();
        if(leave1.start_date[1] < 1 || leave1.start_date[1] > 12)
        {
            printf("Error: Invalid month was entered\n\n");
        }
        else
        {
            break;
        }
    }
    while(1){
        printf("Day (Enter Digit): ");
        scanf("%d", &leave1.start_date[0]);
        getchar();
        if(leave1.start_date[0] < 1 || leave1.start_date[0] > days_in_month[leave1.start_date[1] - 1])
        {
            printf("Error: Invalid day was entered\n\n");
        }
        else
        {
            break;
        }
    }

    printf("Please enter ending date of leave\n");
    printf("Year: %d\n", leave1.end_date[2]);
    while(1)
    {
        printf("Month (Enter Digit): ");
        scanf("%d", &leave1.end_date[1]);
        getchar();
        if(leave1.end_date[1] < 1 || leave1.end_date[1] > 12)
        {
            printf("Error: Invalid month was entered\n\n");
        }
        else
        {
            break;
        }
    }
    while(1){
        printf("Day (Enter Digit): ");
        scanf("%d", &leave1.end_date[0]);
        getchar();
        if(leave1.end_date[0] < 1 || leave1.end_date[0] > days_in_month[leave1.end_date[1] - 1])
        {
            printf("Error: Invalid day was entered\n\n");
        }
        else
        {
            break;
        }
    }

    strcpy(leave1.approve_status, "Pending");
    strcpy(leave1.username, username);

    // append leave information of staff into binary file
    leave_information = fopen("leave_information.bin", "ab");
    if(leave_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fwrite(&leave1, sizeof(Leave), 1, leave_information);

    printf("\nLeave has been applied successfully!\n");
    fclose(leave_information);
}

// Function that allows staff to cancel an applied leave.
void cancel_leave()
{
    FILE *leave_information;
    FILE *leave_information_temp;
    Leave leave1;
    int start_date[3];
    int found1 = 0, found2 = 0;
    start_date[2] = 2023;

    leave_information = fopen("leave_information.bin", "rb");
    leave_information_temp = fopen("temp2.bin", "wb");

    if(leave_information == NULL || leave_information_temp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n--------------\n");
    printf("Cancel Leave\n");
    printf("--------------");
    printf("\nYour Leave Information\n");
    printf("------------------------");
    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        if(strcmp(leave1.username, username) == 0)
        {
            found1 = 1;
            printf("\nLeave Type: %s\n", leave1.leave_type);
            printf("Days: %d\n", leave1.days);
            printf("Start Date: %d-%d-%d\n", leave1.start_date[0], leave1.start_date[1], leave1.start_date[2]);
            printf("End Date: %d-%d-%d\n", leave1.end_date[0], leave1.end_date[1], leave1.end_date[2]);
            printf("Approve Status: %s\n", leave1.approve_status);
        }
    }
    if(found1 == 0)
    {
        printf("\nError: You have not applied any leave\n");
        staff_menu(); // call the staff_menu function again
    }

    printf("\nPlease enter starting date of leave to cancel\n");
    printf("Year: %d\n", start_date[2]);
    printf("Month: ");
    scanf("%d", &start_date[1]);
    getchar();
    printf("Day: ");
    scanf("%d", &start_date[0]);
    getchar();

    fseek(leave_information, 0, SEEK_SET);
    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        if(strcmp(leave1.username, username) == 0 && leave1.start_date[1] == start_date[1] &&
        leave1.start_date[0] == start_date[0] && strcmp(leave1.approve_status, "Pending") == 0)
        {
            found2 = 1;
        }
        else
        {
            fwrite(&leave1, sizeof(Leave), 1, leave_information_temp);
        }
    }
    fclose(leave_information);
    fclose(leave_information_temp);

    // if specified leave is found, write the leave information from temp file into actual file
    if(found2 == 1)
    {
        leave_information_temp = fopen("temp2.bin", "rb");
        leave_information = fopen("leave_information.bin", "wb");

        while(fread(&leave1, sizeof(Leave), 1, leave_information_temp) == 1){
            fwrite(&leave1, sizeof(Leave), 1, leave_information);
        }

        printf("\nYour leave has been cancelled successfully!\n");
        fclose(leave_information);
        fclose(leave_information_temp);
    }
    else
    {
        printf("Error: Leave not found or leave has been approved/rejected\n");
    }
    remove("temp2.bin");
}

// Function that displays staff's leave details and approval status.
void check_leave_status()
{
    FILE *leave_information;
    Leave leave1;
    int found = 0;
    leave_information = fopen("leave_information.bin", "rb");

    if(leave_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n------------------------\n");
    printf("Your leave Information\n");
    printf("------------------------");
    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        if(strcmp(leave1.username, username) == 0)
        {
            found = 1;
            printf("\nLeave Type: %s\n", leave1.leave_type);
            printf("Days: %d\n", leave1.days);
            printf("Start Date: %d-%d-%d\n", leave1.start_date[0], leave1.start_date[1], leave1.start_date[2]);
            printf("End Date: %d-%d-%d\n", leave1.end_date[0], leave1.end_date[1], leave1.end_date[2]);
            printf("Approve Status: %s\n", leave1.approve_status);
        }
    }
    printf("\n");
    fclose(leave_information);
    if(found == 0)
    {
        printf("\nError: You have not applied any leave\n");
        staff_menu(); // call the staff_menu function again
    }
}

// Function that allows staff to check their leave balance.
void leave_summary()
{
    FILE *staff_information;
    Staff staff1;
    int found = 0;
    staff_information = fopen("staff_information.bin", "rb");

    if(staff_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n------------------------\n");
    printf("Your Summary of Leaves\n");
    printf("------------------------");

    while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
        if(strcmp(staff1.username, username) == 0)
        {
            found = 1;
            printf("\nAnnual leaves: %d\n", staff1.annual_leave);
            printf("Compassionate leaves: %d\n", staff1.compassionate_leave);
            printf("Emergency leaves: %d\n", staff1.emergency_leave);
            printf("Maternity leaves: %d\n", staff1.maternity_leave);
            printf("Medical leaves: %d\n", staff1.medical_leave);
            break;
        }
    }
    printf("\n");
    fclose(staff_information);
    if(found == 0)
    {
        printf("\nError: Staff is not found\n");
        staff_menu(); // call the staff_menu function again
    }
}

// Function that displays all options for superior and lets superior choose which option he wants.
void superior_menu()
{
    int choice;
    while(1)
    {
        printf("\n-------------------\n");
        printf("Superior Menu\n");
        printf("-------------------\n");
        printf("1. Approve/Reject leave\n");
        printf("2. View number of staff who applied leave by date\n");
        printf("3. Exit\n");
        printf("------------------\n");

        printf("Please select by entering 1, 2 or 3: ");
        scanf("%d", &choice);
        getchar(); // for negative test case
        switch (choice){
        case 1: approve_leave(); break;
        case 2: search_date(); break;
        case 3: exit(0); break;
        default: printf("Error: Invalid input\n"); break;
        }
    }
}

// Function that allows superior to approve or reject a leave that is applied by staff.
void approve_leave()
{
    FILE *leave_information;
    FILE *staff_information;
    Staff staff1;
    Leave leave1;
    int staffid, days, approve;
    int update_status1, update_status2;
    char leave_type[20];
    int start_date[3];
    int found1 = 0, found2 = 0;
    int edit_days = 0;
    start_date[2] = 2023;
    leave_information = fopen("leave_information.bin", "rb+");
    staff_information = fopen("staff_information.bin", "rb+");

    if(leave_information == NULL || staff_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n----------------------\n");
    printf("Approve/Reject Leave\n");
    printf("----------------------\n");
    printf("Pending Leaves\n");
    printf("-------------------");

    // display all pending leaves in the system
    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        if(strcmp(leave1.approve_status, "Pending") == 0)
        {
            found1 = 1;
            printf("\nStaff ID: %04d\n", leave1.staffid);
            printf("Name: %s\n", leave1.name);
            printf("Leave Type: %s\n", leave1.leave_type);
            printf("Days: %d\n", leave1.days);
            printf("Start Date: %d-%d-%d\n", leave1.start_date[0], leave1.start_date[1], leave1.start_date[2]);
            printf("End Date: %d-%d-%d\n", leave1.end_date[0], leave1.end_date[1], leave1.end_date[2]);
            printf("Approve Status: %s\n", leave1.approve_status);
        }
    }
    if(found1 == 0)
    {
        printf("\nError: No pending leaves to review\n");
        superior_menu(); // call the superior_menu function again
    }
    
    printf("\nTo approve or reject leave, please enter the staff ID of staff: ");
    scanf("%d", &staffid);
    getchar(); // for negative test case

    printf("Please enter the starting date of leave\n");
    printf("Year: %d\n", start_date[2]);
    printf("Month: ");
    scanf("%d", &start_date[1]);
    getchar();
    printf("Day: ");
    scanf("%d", &start_date[0]);
    getchar();

    while(1){
        printf("Please enter 1 to approve or 2 to reject the leave: ");
        scanf("%d", &approve);
        getchar();
        if(approve == 1 || approve == 2)
        {
            break;
        }
        else
        {
            printf("Error: Invalid input\n\n");
        }
    }

    // find the specified leave to approve/reject, then modify the leave information file
    fseek(leave_information, 0, SEEK_SET);
    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        if(leave1.staffid == staffid && leave1.start_date[1] == start_date[1] &&
        leave1.start_date[0] == start_date[0] && approve == 1)
        {
            found2 = 1;
            strcpy(leave1.approve_status, "Approved");
            days = leave1.days;
            strcpy(leave_type, leave1.leave_type);
        }
        else if(leave1.staffid == staffid && leave1.start_date[1] == start_date[1] &&
        leave1.start_date[0] == start_date[0] && approve == 2)
        {
            found2 = 1;
            strcpy(leave1.approve_status, "Rejected");
        }

        if(found2 == 1)
        {
            fseek(leave_information, ftell(leave_information) - sizeof(Leave), SEEK_SET);
            update_status1 = fwrite(&leave1, sizeof(Leave), 1, leave_information);
            break;
        }
    }
    if(found2 == 0)
    {
        printf("\nError: Leave is not found\n");
        approve_leave(); // call the approve_leave function again
    }
    fclose(leave_information);

    // if the specified leave is rejected, print success message
    if(found2 == 1 && approve == 2 && update_status1 == 1)
    {
        printf("\nLeave has been rejected successfully.\n");
    }

    // if the specified leave is approved, minus the staff's leave balance by number of days of leave applied
    // then modify the staff information file
    if(found2 == 1 && approve == 1)
    {
        while(fread(&staff1, sizeof(Staff), 1, staff_information) == 1){
            if(staff1.staffid == staffid && strcmp(leave_type, "Annual") == 0)
            {
                staff1.annual_leave -= days;
                edit_days = 1;
            }
            else if(staff1.staffid == staffid && strcmp(leave_type, "Compassionate") == 0)
            {
                staff1.compassionate_leave -= days;
                edit_days = 1;
            }
            else if(staff1.staffid == staffid && strcmp(leave_type, "Emergency") == 0)
            {
                staff1.emergency_leave -= days;
                edit_days = 1;
            }
            else if(staff1.staffid == staffid && strcmp(leave_type, "Maternity") == 0)
            {
                staff1.maternity_leave -= days;
                edit_days = 1;
            }
            else if(staff1.staffid == staffid && strcmp(leave_type, "Medical") == 0)
            {
                staff1.medical_leave -= days;
                edit_days = 1;
            }
            
            if(edit_days == 1)
            {
                fseek(staff_information, ftell(staff_information) - sizeof(Staff), SEEK_SET);
                update_status2 = fwrite(&staff1, sizeof(Staff), 1, staff_information);
                break;
            }
        }

        if(update_status1 == 1 && update_status2 == 1)
        {
            printf("\nLeave has been approved successfully.\n");
        }
    }
    fclose(staff_information);
}

// Function that allows superior to view number of staff that applied leave on a specific date.
void search_date()
{
    FILE *leave_information;
    Leave leave1;
    int date[3];
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int found = 0, amount = 0;
    date[2] = 2023;
    leave_information = fopen("leave_information.bin", "rb");

    if(leave_information == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\n----------------------------------------------\n");
    printf("Search Date to View Staff That Applied Leave\n");
    printf("----------------------------------------------\n");
    printf("Please enter the date to search\n");
    printf("Year: %d\n", date[2]);
    printf("Month: ");
    scanf("%d", &date[1]);
    getchar();
    printf("Day: ");
    scanf("%d", &date[0]);
    getchar();

    printf("\nStaff who Applied Leave\n");
    printf("-------------------------\n");

    while(fread(&leave1, sizeof(Leave), 1, leave_information) == 1){
        // condition 1: leave starts and ends in same month
        if(leave1.start_date[0] <= date[0] && date[0] <= leave1.end_date[0] &&
        leave1.start_date[1] == date[1])
        {
            found = 1;
            amount += 1;
            printf("Name: %s\t", leave1.name);
            printf("Staff ID: %04d\t", leave1.staffid);
            printf("Department: %s\t", leave1.department);
            printf("Status: %s\n", leave1.approve_status);
        }
        // condition 2: leave starts and ends in different month
        // date entered has same month as leave start date
        else if(leave1.start_date[1] != leave1.end_date[1] && date[1] == leave1.start_date[1] &&
        leave1.start_date[0] <= date[0] && date[0] <= days_in_month[date[1] - 1])
        {
            found = 1;
            amount += 1;
            printf("Name: %s\t", leave1.name);
            printf("Staff ID: %04d\t", leave1.staffid);
            printf("Department: %s\t", leave1.department);
            printf("Status: %s\n", leave1.approve_status);
        }
        // condition 3: leave starts and ends in different month
        // date entered has same month as leave end date
        else if(leave1.start_date[1] != leave1.end_date[1] && date[1] == leave1.end_date[1] &&
        1 <= date[0] && date[0] <= leave1.end_date[0])
        {
            found = 1;
            amount += 1;
            printf("Name: %s\t", leave1.name);
            printf("Staff ID: %04d\t", leave1.staffid);
            printf("Department: %s\t", leave1.department);
            printf("Status: %s\n", leave1.approve_status);
        }
    }
    if(found == 0)
    {
        printf("\nNo staff has applied leave on %d-%d-%d\n\n", date[0], date[1], date[2]);
    }
    else
    {
        printf("\nTotal number of staff that applied leave on %d-%d-%d = %d\n\n", date[0], date[1], date[2], amount);
    }
    fclose(leave_information);
}

// Main function that allows user to log in to the system.
int main()
{
    int choice, loop_choice = 0;
    int superior = 0;
    char username_f[20], password_f[20];
    FILE * fp;
    while(1)
    {
        printf("--------------------------------------------\n");
        printf("APU Leave Application and Management System\n");
        printf("--------------------------------------------\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("----------\n");
        printf("WELCOME user, please select by entering 1 or 2: ");
        scanf(" %d", &choice);
        getchar(); // for negative test case

        if(choice == 1)
        {
            while(loop_choice == 0){
                printf("\nPlease enter your login credentials\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                pwmask();
                
                fp = fopen("admin_credentials.txt", "r");
                if(fp == NULL)
                {
                    printf("Error opening file.\n");
                    exit(1);
                }

                while((fscanf(fp, "%s %s ", username_f, password_f)) != EOF){
                    if(strcmp(username, username_f) == 0 && strcmp(password, password_f) == 0)
                    {
                        printf("\nAdministrator login successful.\n\n");
                        fclose(fp);
                        admin_menu();
                    }
                }

                fp = fopen("staff_credentials.txt", "r");
                if(fp == NULL)
                {
                    printf("Error opening file.\n");
                    exit(1);
                }

                while((fscanf(fp, "%s %s ", username_f, password_f)) != EOF){
                    if(strcmp(username, username_f) == 0 && strcmp(password, password_f) == 0)
                    {
                        printf("\nStaff login successful.\n\n");
                        loop_choice = 1;
                        break;
                    }
                }
                fclose(fp);

                fp = fopen("superior_credentials.txt", "r");
                if(fp == NULL)
                {
                    printf("Error opening file.\n");
                    exit(1);
                }

                while((fscanf(fp, "%s %s ", username_f, password_f)) != EOF){
                    if(strcmp(username, username_f) == 0 && strcmp(password, password_f) == 0)
                    {
                        printf("\nStaff login successful.\n\n");
                        superior = 1;
                        loop_choice = 1;
                        break;
                    }
                }
                fclose(fp);
                
                if(loop_choice == 1)
                {
                    check_superior(superior);
                }
                else
                {
                    printf("\nError: Wrong username or password was entered. Please try again.\n");
                }
            }
        }
        else if(choice == 2)
        {
            exit(0);
        }
        else
        {
            printf("Error: Invalid input\n\n");
        }
    }

    return 0;
}

// Function that masks password during login.
void pwmask()
{
    char c;
    int i = 0;
    while(1){
        c = getch(); // asks user to enter character
        if(c == ENTER)
        {
            password[i] = NULL; // string is ended with NULL character
            break;
        }
        else if(c == TAB)
        {
            continue; // start next iteration
        }
        else if(c == BACKSPACE)
        {
            if(i > 0)
            {
                i--;
                printf("\b \b"); // move cursor back and print empty space
            }
        }
        else
        {
            password[i] = c;
            i++;
            printf("*"); // print asterisk instead of characters
        }
    }
}

// Function that checks whether staff is a superior or not.
void check_superior(int superior)
{
    int choice;
    while(1){
        printf("---------------------\n");
        printf("WELCOME staff\n");
        printf("1. Leave Application\n");
        printf("2. Leave Approval\n");
        printf("---------------------\n");
        printf("Please select by entering 1 or 2: ");
        scanf(" %d", &choice);
        getchar(); // for negative test case

        if(choice == 1)
        {
            staff_menu();
        }
        else if(choice == 2)
        {
            if(superior == 1)
            {
                superior_menu();
            }
            else
            {
                printf("\nError: You cannot approve leave(s) because you are not a superior\n\n");
            }
        }
        else
        {
            printf("Error: Invalid input\n\n");
        }
    }
}