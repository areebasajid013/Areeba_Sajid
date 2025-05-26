#include <iostream>
using namespace std;

struct Expense {
    string expensename;
    int amount;
    Expense* next;
    Expense(string e, int a) {
        expensename = e;
        amount = a;
        next = NULL;
    }
};

struct Month {
    string monthname;
    Month* next;
    Expense* expensehead;
    Month(string m) {
        monthname = m;
        next = NULL;
        expensehead = NULL;
    }
};

void addmonth(Month*& head, string monthname) {
    Month* newmonth = new Month(monthname);
    newmonth->next = head;
    head = newmonth;
}

void addexpense(Month* head, string monthname, string expensename, int amount) {
    Month* temp = head;
    while (temp && temp->monthname != monthname) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Month " << monthname << " not found.\n";
        return;
    }
    Expense* newexpense = new Expense(expensename, amount);
    newexpense->next = temp->expensehead;
    temp->expensehead = newexpense;
}

void displayAllExpenses(Month* head) {
    Month* currentmonth = head;
    while (currentmonth) {
        cout << "\nMonth: " << currentmonth->monthname << endl;
        Expense* currentexpense = currentmonth->expensehead;
        while (currentexpense) {
            cout << " - " << currentexpense->expensename << ": Rs " << currentexpense->amount << endl;
            currentexpense = currentexpense->next;
        }
        currentmonth = currentmonth->next;
    }
}

void MaxExpense(Month* head, string monthname) {
    Month* temp = head;
    while (temp && temp->monthname != monthname) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Month " << monthname << " not found.\n";
        return;
    }
    Expense* maxexpense = NULL;
    Expense* currentexpense = temp->expensehead;
    while (currentexpense) {
        if (!maxexpense || currentexpense->amount > maxexpense->amount) {
            maxexpense = currentexpense;
        }
        currentexpense = currentexpense->next;
    }
    if (maxexpense) {
        cout << "Most expensive item in " << temp->monthname << ": " << maxexpense->expensename << " (Rs " << maxexpense->amount << ")\n";
    } else {
        cout << "No expenses recorded for " << temp->monthname << endl;
    }
}

void updateExpense(Month* head, string monthname, string expensename, int newamount) {
    Month* temp = head;
    while (temp && temp->monthname != monthname) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Month " << monthname << " not found.\n";
        return;
    }

    Expense* currentexpense = temp->expensehead;
    while (currentexpense && currentexpense->expensename != expensename) {
        currentexpense = currentexpense->next;
    }
    if (!currentexpense) {
        cout << "Expense " << expensename << " not found in " << monthname << ".\n";
        return;
    }

    currentexpense->amount = newamount;
    cout << "Updated " << expensename << " to Rs " << newamount << " in " << monthname << ".\n";
}

void deleteExpense(Month* head, string monthname, string expensename) {
    Month* temp = head;
    while (temp && temp->monthname != monthname) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Month " << monthname << " not found.\n";
        return;
    }

    Expense* current = temp->expensehead;
    Expense* prev = NULL;
    while (current && current->expensename != expensename) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        cout << "Expense " << expensename << " not found in " << monthname << ".\n";
        return;
    }

    if (prev) {
        prev->next = current->next;
    } else {
        temp->expensehead = current->next;
    }

    delete current;
    cout << "Deleted expense " << expensename << " from " << monthname << ".\n";
}

int main() {
    Month* head = NULL;
    int choice;
    string monthname, expensename;
    int amount;

    do {
        cout << "\n--- Expense Manager Menu ---\n";
        cout << "1. Add Month\n";
        cout << "2. Add Expense\n";
        cout << "3. Display All Expenses\n";
        cout << "4. Show Most Expensive Item in a Month\n";
        cout << "5. Update an Expense\n";
        cout << "6. Delete an Expense\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter month name: ";
                cin >> monthname;
                addmonth(head, monthname);
                break;
            case 2:
                cout << "Enter month name: ";
                cin >> monthname;
                cout << "Enter expense name: ";
                cin >> expensename;
                cout << "Enter amount: ";
                cin >> amount;
                addexpense(head, monthname, expensename, amount);
                break;
            case 3:
                displayAllExpenses(head);
                break;
            case 4:
                cout << "Enter month name: ";
                cin >> monthname;
                MaxExpense(head, monthname);
                break;
            case 5:
                cout << "Enter month name: ";
                cin >> monthname;
                cout << "Enter expense name to update: ";
                cin >> expensename;
                cout << "Enter new amount: ";
                cin >> amount;
                updateExpense(head, monthname, expensename, amount);
                break;
            case 6:
                cout << "Enter month name: ";
                cin >> monthname;
                cout << "Enter expense name to delete: ";
                cin >> expensename;
                deleteExpense(head, monthname, expensename);
                break;
            case 7:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}



