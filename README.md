# loan-management-and-budget-planner
This is my first Repository.
<br>
Author-Wabin sayed
<br>
Introduction:
The Loan Management & Budget Planner System is designed to help users efficiently manage their financial activities using a simple console-based application written entirely in C language. The main objectives of the system are:
Objective:
To maintain and track loan records for individuals.
To automatically calculate monthly loan payments based on principal, interest rate, and duration.
To manage and record income and expenses for effective personal budgeting.
To generate clear financial summaries and reports to help users make informed financial decisions.
To provide a user-friendly console interface with straightforward functionality suitable for all users.

Description:

2.1 Functional Requirements

The system provides the following core functionalities:
Loan Management:
 Add, update, and delete loan records.
 Calculate monthly installments automatically using standard formulas.
 Generate loan summaries and display detailed loan information.

Budget Management:
 Record and categorize income and expenses.
 Maintain accurate monthly and annual budget information.

Summary & Reporting:
 Provide total income, total expenses, and total loan balance.
 Generate concise financial summaries for selected periods.

Data Persistence:
 Save all loan and budget information to a text file.
 Load data from the file when the system restarts, ensuring continuity between sessions.


2.2 Non-Functional Requirements
  Usability: Simple and intuitive console interface for easy operation.
  Reliability: Accurate calculations and consistent reporting.
  Performance: Efficient handling of up to 50 loan records.
  Security: Basic data integrity maintained via structured storage.
  Portability: Runs on standard Windows systems without additional requirements.

System Design:

 The system is structured into three main modules:
 Loan Management Module:
 Stores loan data using C structures.
 Calculates monthly payment (EMI) using the formula:
𝑀
=
𝑃
𝑟
(
1
+
𝑟
)
𝑛
(
1
+
𝑟
)
𝑛
−
1
M=P
(1+r)
n
−1
r(1+r)
n
	​


Where:
M = Monthly Payment
P = Principal Amount
r = Monthly Interest Rate
n = Total Number of Months

Allows editing and deleting of loan records.

Budget Management Module:
 Records income and expenses in structured format.
 Categorizes transactions for easy tracking and summary.
 Summary & Reporting Module:
 Combines data from both loan and budget modules.
 Generates financial summaries for all or individual accounts.

Data Persistence Module:
 Saves all records to a text file (data.txt) for long-term storage.
 When loading data, the system recalculates loan duration approximately if it is not stored explicitly.
 The entire system is implemented in C language, using structures, functions, arrays, and modular programming to ensure clarity, maintainability, and efficient memory usage.

Design Model:

The project is developed following the Incremental Model of software development:
The system was built module by module, allowing each feature to be implemented, tested, and verified independently.
Benefits of this approach:
 Early delivery of functional modules.
 Easier testing and debugging.
 Flexibility to incorporate changes during development.

Phases Implemented:

Planning and requirement analysis.
System design (module-wise).
Incremental implementation of modules in C language.
Testing and verification of each module individually.
Final integration and complete system testing.
 
Language: C

Concepts:

Structures
Functions
Arrays
File Handling
Mathematical Calculations
Input Validation
Compiler: GCC

 
 

 
