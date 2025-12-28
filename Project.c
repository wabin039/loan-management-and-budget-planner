 //.........Loan Management & Budget Planner Application........//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_LOANS 50                                // Maximum number of loan accounts
#define FILE_NAME "data.txt"                        // Data file name

// Structure Loan Account & Budget // 
struct Loan {
    int id;                                         // Loan ID
    char name[50];                                  // Borrower Name
    char type[30];                                  // Loan Type
    float amount;                                   // Loan Amount
    float rate;                                     // Interest Rate (% per year)
    int years;                                      // Loan Duration
    float monthly;                                  // Monthly EMI
    float income;                                   // Account Income
    float expense;                                  // Account Expense
};

struct Loan loans[MAX_LOANS];                       // Array to store loan accounts
int loanCount = 0;                                  // Current number of loan accounts

//  Function Declaration // 
float calculateMonthly(float a, float r, int y);    // Calculate Monthly EMI
void addLoan();                                     // Add Loan Account
void addBudget();                                   // Add Budget 
void overallReport();                               // Overall Report
void individualReport();                            // Individual Account Report (by Loan ID any user) 
void editLoan();                                    // Edit Loan Account
void editBudget();                                  // Edit Budget
void deleteLoan();                                  // Delete Loan Account
void saveAllData();                                 // Save All Data to File
void loadData();                                    // Load Data from File
int generateLoanID();                               // Generate Unique Loan ID

// main function //
int main() {
    int choice;
    loadData();

    do {
        printf("\n====== Loan Management & Budget Planner ======\n");
        printf("1. Add Loan Account\n");
        printf("2. Add Budget (Income / Expense)\n");
        printf("3. Overall Report (All Accounts)\n");
        printf("4. Individual Account Report\n");
        printf("5. Edit Loan Account\n");
        printf("6. Edit Budget\n");
        printf("7. Delete Loan Account\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        int c;
        while((c=getchar())!='\n' && c!=EOF);          // flush leftover newline

        switch(choice) {                             // Handle user choices
            case 1: addLoan(); break;                 
            case 2: addBudget(); break;
            case 3: overallReport(); break;
            case 4: individualReport(); break;
            case 5: editLoan(); break;
            case 6: editBudget(); break;
            case 7: deleteLoan(); break;
            case 0: saveAllData(); printf("Data saved successfully.\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);                                // Loop until user chooses to exit

    printf("\nPress Enter to exit...");
    int ch;
    while((ch=getchar())!='\n' && ch!=EOF);              // flush leftover
    getchar();                                           // wait for enter
    return 0;
}

//Monthly EMI Calculation Function //                 
float calculateMonthly(float a, float r, int y) {                       // a=loan amount, r=annual interest rate %, y=loan duration in years
    if(r == 0) return a / (y * 12);                                     // If interest rate is 0%  
    float m = r / 1200;                                                 // Monthly interest rate
    int n = y * 12;                                                     // Total number of monthly payments
    return (a * m) / (1 - pow(1 + m, -n));                              // EMI formula, EMI= p*r*(1+r)^n/((1+r)^n-1)
}

// Generate Unique Loan ID //
int generateLoanID() {
    int lastID = 1000;
    for(int i=0;i<loanCount;i++)
        if(loans[i].id > lastID) lastID = loans[i].id;
    return lastID + 1;
}

// Add Loan Account //
void addLoan() {
    if(loanCount >= MAX_LOANS) {
        printf("Loan account limit reached!\n");
        return;
    }

    struct Loan l;
    l.id = generateLoanID();                                      // Generate unique Loan ID

    printf("\nBorrower Name: ");                                  
    fgets(l.name, 50, stdin);                                     // Read borrower name
    l.name[strcspn(l.name, "\n")] = '\0';                         // Remove newline character

    printf("Loan Type (Home/Personal/Education/Business/Auto): ");
    scanf("%s", l.type);

    printf("Loan Amount: ");
    scanf("%f", &l.amount);

    printf("Interest Rate (%% per year): ");
    scanf("%f", &l.rate);

    printf("Loan Duration (Years): ");
    scanf("%d", &l.years);
    int c;
    while((c=getchar())!='\n' && c!=EOF);                        // flush leftover newline

    l.monthly = calculateMonthly(l.amount, l.rate, l.years);     // Calculate Monthly EMI
    l.income = 0;
    l.expense = 0;                                               // Initialize income and expense

    loans[loanCount++] = l;                                       // Add loan to array
    saveAllData();

    printf("\nLoan ID for this account: %d\n", l.id);               // Display generated Loan ID
    printf("Monthly Payment (EMI)  : %.2f\n", l.monthly);
    printf("Loan Added Successfully!\n");                          // Finiahed add loan
}

// Add Budget //
void addBudget() {
    int id;           
    float in, ex;                                                // income and expense amounts

    printf("Enter Loan ID to add Budget: ");                    // first loan id identifier then add income and expense
    scanf("%d",&id);
    int c;
    while((c=getchar())!='\n' && c!=EOF);

    for(int i=0;i<loanCount;i++) {                            // search loan id
        if(loans[i].id == id) {
            printf("Income Amount: ");
            scanf("%f",&in);
            printf("Expense Amount: ");
            scanf("%f",&ex);
            while((c=getchar())!='\n' && c!=EOF);

            if(in>0) loans[i].income += in;                        // update income and expense
            if(ex>0) loans[i].expense += ex;

            saveAllData();                                          // save balance 
            printf("Updated Balance for %s: %.2f\n", loans[i].name, loans[i].income - loans[i].expense);
            return;
        }
    }
    printf("Loan ID not found!\n");
}

// Overall Report //
void overallReport() {
    if(loanCount == 0) { printf("No loan records found!\n"); return; }       // check any loan record

    printf("\n================ OVERALL LOAN & BUDGET REPORT ================\n");          // print header
    printf("%-6s | %-20s | %-10s | %-12s | %-12s | %-6s | %-12s | %-12s | %-12s\n",
           "LoanID","Borrower Name","Loan Type","Amount","EMI","Rate","Income","Expense","Balance");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    float totalLoan=0, totalIncome=0, totalExpense=0;                   // total information for all loan accounts 

    for(int i=0;i<loanCount;i++) {                               
        char loanType[20];
        strcpy(loanType, loans[i].type);
        loanType[0] = toupper(loanType[0]);                             // Capitalize first letter of loan type

        printf("%-6d | %-20s | %-10s | %12.2f | %12.2f | %6.2f | %12.2f | %12.2f | %12.2f\n",
               loans[i].id,
               loans[i].name,
               loanType,
               loans[i].amount,
               loans[i].monthly,
               loans[i].rate,
               loans[i].income,
               loans[i].expense,
               loans[i].income - loans[i].expense);

        totalLoan += loans[i].amount;
        totalIncome += loans[i].income;                
        totalExpense += loans[i].expense;
    }

    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("%-6s | %-20s | %-10s | %12.2f | %12s | %6s | %12.2f | %12.2f | %12.2f\n",
           "", "TOTAL", "", totalLoan, "", "", totalIncome, totalExpense, totalIncome - totalExpense);
    printf("=================================================================\n");
}

// Individual Account Report (by Loan ID) //
void individualReport() {
    int id;
    printf("Enter Loan ID to view report: ");
    scanf("%d",&id);
    int c;
    while((c=getchar())!='\n' && c!=EOF);

    for(int i=0;i<loanCount;i++) {
        if(loans[i].id == id) {
            struct Loan l = loans[i];
            printf("\n===== LOAN INFORMATION =====\n");
            printf("Loan ID           : %d\n", l.id);
            printf("Borrower Name     : %s\n", l.name);
            printf("Loan Type         : %s\n", l.type);
            printf("Loan Amount       : %.2f\n", l.amount);
            printf("Interest Rate     : %.2f %% per year\n", l.rate);
            printf("Loan Duration     : %d Years\n", l.years);
            printf("Monthly EMI       : %.2f\n", l.monthly);

            printf("\n===== BUDGET SUMMARY =====\n");
            printf("Total Income      : %.2f\n", l.income);
            printf("Total Expense     : %.2f\n", l.expense);
            printf("Account Balance   : %.2f\n", l.income - l.expense);
            printf("===========================================\n");
            return;
        }
    }
    printf("Loan ID not found!\n");
}

// Edit Loan Account //
void editLoan() {
    int id;
    printf("Enter Loan ID to edit: ");
    scanf("%d",&id);
    int c;
    while((c=getchar())!='\n' && c!=EOF);
                                                         
    for(int i=0;i<loanCount;i++) {
        if(loans[i].id == id) {
            struct Loan *l = &loans[i];
            char input[50];
            float finput;
            int iinput;                                // Editing loan account details

            printf("Editing Loan ID %d\n", l->id);

            // Name
            printf("Current Borrower Name: %s\n", l->name);
            printf("Enter new name (or press Enter to keep): ");
            fgets(input,50,stdin);
            if(input[0]!='\n') { input[strcspn(input,"\n")]=0; strcpy(l->name,input); }

            // Loan Type
            printf("Current Loan Type: %s\n", l->type);
            printf("Enter new type (or press Enter to keep): ");
            fgets(input,50,stdin);
            if(input[0]!='\n') { input[strcspn(input,"\n")]=0; strcpy(l->type,input); }   

            // Amount
            printf("Current Amount: %.2f\n", l->amount);
            printf("Enter new amount (0 to keep): ");
            scanf("%f",&finput);
            if(finput>0) l->amount = finput;

            // Interest Rate
            printf("Current Rate: %.2f\n", l->rate);
            printf("Enter new rate (0 to keep): ");
            scanf("%f",&finput);
            if(finput>0) l->rate = finput;

            // Duration
            printf("Current Years: %d\n", l->years);
            printf("Enter new years (0 to keep): ");
            scanf("%d",&iinput);
            if(iinput>0) l->years = iinput;

            l->monthly = calculateMonthly(l->amount,l->rate,l->years);
            saveAllData();
            printf("Loan updated successfully!\n");
            return;
        }
    }
    printf("Loan ID not found!\n");
}

// Edit Budget Account //
void editBudget() {
    int id;
    printf("Enter Loan ID to edit Budget: ");
    scanf("%d",&id);
    int c;
    while((c=getchar())!='\n' && c!=EOF);

    for(int i=0;i<loanCount;i++) {
        if(loans[i].id == id) {
            struct Loan *l = &loans[i];
            float finput;

            printf("Current Income: %.2f\n", l->income);
            printf("Enter new Income (0 to keep unchanged): ");
            scanf("%f",&finput);
            if(finput>0) l->income = finput;

            printf("Current Expense: %.2f\n", l->expense);
            printf("Enter new Expense (0 to keep unchanged): ");
            scanf("%f",&finput);
            if(finput>0) l->expense = finput;

            printf("Budget updated successfully!\n");
            printf("New Balance: %.2f\n", l->income - l->expense);
            saveAllData();
            return;
        }
    }
    printf("Loan ID not found!\n");
}

// Delete Loan Account //
void deleteLoan() {
    int id, found = 0;                                  // Deleting loan account by Loan ID then shift array .
    printf("Enter Loan ID to delete: ");
    scanf("%d", &id);
    int c;
    while((c=getchar())!='\n' && c!=EOF);

    for(int i=0;i<loanCount;i++) {
        if(loans[i].id == id) {
            found = 1;
            for(int j=i; j<loanCount-1; j++) loans[j] = loans[j+1];
            loanCount--;
            saveAllData();
            printf("Loan ID %d deleted successfully!\n", id);
            break;
        }
    }

    if(!found) printf("Loan ID not found!\n");
}

// Save All Data to File //
void saveAllData() {
    FILE *fp = fopen(FILE_NAME, "w");                          // open file for writing
    if(fp==NULL) { printf("Error saving file!\n"); return; }

    fprintf(fp,"%-6s | %-20s | %-10s | %-12s | %-12s | %-6s | %-12s | %-12s | %-12s\n",
            "LoanID","Borrower Name","Loan Type","Amount","EMI","Rate","Income","Expense","Balance");
    fprintf(fp,"-----------------------------------------------------------------------------------------------------------\n");

    for(int i=0;i<loanCount;i++) {
        fprintf(fp,"%-6d | %-20s | %-10s | %12.2f | %12.2f | %6.2f | %12.2f | %12.2f | %12.2f\n",
               loans[i].id,
               loans[i].name,
               loans[i].type,
               loans[i].amount,
               loans[i].monthly,
               loans[i].rate,
               loans[i].income,
               loans[i].expense,
               loans[i].income - loans[i].expense);
    }

    fclose(fp);
}

// Load Data from File //
void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");                    // open file for reading
    if(fp==NULL) return;

    char line[256];
    int row = 0;

    while(fgets(line,sizeof(line),fp)) {
        if(row<2) { row++; continue; }                    // skip header lines 
        if(loanCount>=MAX_LOANS) break;

        struct Loan l;
        // sscanf fixed - no NULL, all required fields
        sscanf(line,"%d | %20[^|] | %10[^|] | %f | %f | %f | %f | %f | %f",
               &l.id,l.name,l.type,&l.amount,&l.monthly,&l.rate,&l.income,&l.expense,&l.amount);
        l.years = (int)(l.amount/l.monthly/12);           // approximate if not saved 
        loans[loanCount++] = l;
    }
    fclose(fp);
}
