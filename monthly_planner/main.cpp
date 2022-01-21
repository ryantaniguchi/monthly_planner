// main.cpp
// The main file for the monthlyplanner program.
//

#include <iostream>
#include <limits>
#include <string>
#include <ctime>
#include "planner_database.h"

using namespace std;

void show_options();
void l(const string& username, const string& month, PlannerDatabase& r);
void login(PlannerDatabase& r);
int request_id();

// Function to provide the number of days in the current month
int  count_days(int month, int current_year)
{
    // If it is a leap year, February has 29 days. Otherwise, it has 28. 
    if (month == 2)
    {
        if ((current_year % 400 == 0) || (current_year % 4 == 0 && current_year % 100 != 0))
            return 29;
        else
            return 28;
    }
    // Tracking which months have 31 days
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    // All other months have 30 days.
    else
        return 30;
}

// Determine what day of the week a given date would land on.
int day_number(int day, int month, int current_year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    current_year -= month < 3;
    return (current_year + current_year / 4 - current_year / 100 + current_year / 400 + t[month - 1] + day) % 7;
}

// Print a calendar based on the month the user is viewing.
void calendar(int current_year, string month)
{
    int days;
    int int_month = 0;
    // Create an integer value based on the name of the month the user entered.
    if (month == "January")
        int_month = 1;
    else if (month == "February")
        int_month = 2;
    else if (month == "March")
        int_month = 3;
    else if (month == "April")
        int_month = 4;
    else if (month == "May")
        int_month = 5;
    else if (month == "June")
        int_month = 6;
    else if (month == "July")
        int_month = 7;
    else if (month == "August")
        int_month = 8;
    else if (month == "September")
        int_month = 9;
    else if (month == "October")
        int_month = 10;
    else if (month == "November")
        int_month = 11;
    else if (month == "December")
        int_month = 12;
    int current = day_number(1, int_month, current_year);
    days = count_days(int_month, current_year);
    // Print out the calendar header
    cout << "\n\n\n  ----X----" << month << ", " << current_year << "----X---- \t\t\n";
    cout << " Sun   Mon  Tue  Wed  Thu  Fri  Sat \n";
    // Print out the individual days in the month
    int k;
    for (k = 0; k < current; k++)
        cout << "     ";
    for (int j = 1; j <= days; j++) {
        printf("%5d", j);
        // Print out the days in a week
        if (++k > 6) {
            k = 0;
            cout << endl;
        }
    }
    if (k)
        cout << endl;
    current = k;
    return;
}

// Main function of the program.
int main()
{
    // Create a new reminder router
    PlannerDatabase r;

    // Open monthly planners
    r.open_planner("January", "January.txt");
    r.open_planner("February", "February.txt");
    r.open_planner("March", "March.txt");
    r.open_planner("April", "April.txt");
    r.open_planner("May", "May.txt");
    r.open_planner("June", "June.txt");
    r.open_planner("July", "July.txt");
    r.open_planner("August", "August.txt");
    r.open_planner("September", "September.txt");
    r.open_planner("October", "October.txt");
    r.open_planner("November", "November.txt");
    r.open_planner("December", "December.txt");

    // Main loop
    login(r);

}

// Prints the different options that are available to the user in the main loop.
void show_options()
{

    cout << "\nChoose an option: \n\n";
    cout << "\ts - Show reminders\n";
    cout << "\ta - Add a reminder\n";
    cout << "\td - Delete a reminder\n";
    cout << "\tc - Change the current month\n";
    cout << "\tq - Quit\n\n";

}

// Interaction with a given user
void user_loop(const string& username, const string& month, PlannerDatabase& r)
{
    char response;           // user reponse
    int id;                  // store a reminder id
    string receiver;         // reminder recipient
    string schedule;          // when notice is scheduled for
    string reminder_body;  // reminder notice
    string new_month; // change month

    // Collects the current date and time to be used in the program.
    time_t current_time;
    struct tm  local_time;
    time(&current_time);
    localtime_s(&local_time, &current_time);

    // Formats the current date so it can be displayed to the user.
    int current_year = local_time.tm_year + 1900;
    int current_month = local_time.tm_mon + 1;
    int current_day = local_time.tm_mday;

    // Prints greeting to the user with the time and date.
    cout << "\nWelcome, " << username << ". It is " << (local_time.tm_hour) << ":" << (local_time.tm_min) << " on " << current_month << "/" << current_day << "/" << current_year << ".";

    // Prints calendar for the month the user is viewing.
    calendar(current_year, month);

    while (true) {

        show_options();
        cout << "\n" << username << " (" << current_month << "/" << current_day << "/" << current_year << ")> ";
        // Reads the first character the user enters, ignoring subsequent characters.
        cin >> response;
        cin.ignore();  // '\n'

        cout << endl;
        switch (response) {
            // Displays every reminder for the user in the given month.
        case 's':
            r.show_reminders(month, username);
            break;
        case 'a':
            // Allows the user to add a new reminder
            cout << "Who is this reminder intended for? ";
            getline(cin, receiver);
            cout << "Which month does this event take place? ";
            getline(cin, new_month);
            cout << "When does this event take place? ";
            getline(cin, schedule);
            cout << "What is the reminder? ";
            getline(cin, reminder_body);
            r.create_reminder(new_month, username, receiver, schedule, reminder_body);
            break;
            // Deletes a selected reminder based on user-provided ID
        case 'd':
            id = request_id();
            // Otherwise, delete the specified reminder
            r.delete_reminder(month, username, id);
            break;
            // Change month to the selected one
        case 'c':
            cout << "\nPlease enter the month that you would like to check: ";
            getline(cin, new_month);
            if (!r.month_is_valid(new_month)) {
                cout << "No such month\n";
            }
            else {
                cout << "Retrieving " << new_month << "...\n";
                user_loop(username, new_month, r);
            }
            // Exit the current user
        case 'q':
            // Save the events for each month before exiting
            r.update_planner("January", "January.txt");
            r.update_planner("February", "February.txt");
            r.update_planner("March", "March.txt");
            r.update_planner("April", "April.txt");
            r.update_planner("May", "May.txt");
            r.update_planner("June", "June.txt");
            r.update_planner("July", "July.txt");
            r.update_planner("August", "August.txt");
            r.update_planner("September", "September.txt");
            r.update_planner("October", "October.txt");
            r.update_planner("November", "November.txt");
            r.update_planner("December", "December.txt");
            // Prints reminder for every planner that they checked.
            cout << "Exiting " << month << "...\n\n";
            return;
            // Any other response gives an error.
        default:
            cout << "Invalid option: " << response << endl;
            break;
        }
        cout << endl;
    }
}

// Allows user to login to system
void login(PlannerDatabase& r)
{

    while (true) {
        string username;
        string month;

        cout << "\nPlease enter your name ('quit' to exit): ";
        getline(cin, username);

        if (username == "quit") {
            cout << "Goodbye.\n\n";
            return;
        }

        cout << "\nPlease enter the month that you would like to check: ";
        getline(cin, month);

        if (!r.month_is_valid(month)) {
            cout << "No such month.\n";
        }
        else {
            cout << "Retrieving " << month << "...\n";
            user_loop(username, month, r);
        }
    }
}

// Requests ID from user and disregards invalid characters
int request_id()
{
    int id;
    cout << "Enter reminder ID number: ";
    cin >> id;
    // Invalid IDs will return error reminder and return to menu
    if (!cin || id < 1) {
        cout << "You have entered an invalid ID.\n";
        cin.clear();
        return -1;
    }
    return id;
}
