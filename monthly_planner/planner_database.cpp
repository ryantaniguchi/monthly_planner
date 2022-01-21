// planner_database.cpp
//

#include <iostream>
#include "planner_database.h"

PlannerDatabase::MonthlyPlanner::MonthlyPlanner(const string& a_name) : name{ a_name }
{
    database = make_shared<ReminderStorage>(); // creates a new reminder database
}

// Opens the specified monthly planner.
void PlannerDatabase::open_planner(const string& month_name, const string& filename)
{
    shared_ptr<MonthlyPlanner> node_to_add_ptr = make_shared<MonthlyPlanner>(month_name);

    // create ReminderStorage by opening filename
    node_to_add_ptr->database = make_shared<ReminderStorage>(filename);

    if (root_ptr == nullptr) {
        root_ptr = node_to_add_ptr;
        return;
    }
    shared_ptr<MonthlyPlanner> curr_ptr = root_ptr;
    while (curr_ptr->next_ptr != nullptr) {
        curr_ptr = curr_ptr->next_ptr;
    }
    curr_ptr->next_ptr = node_to_add_ptr;
}

// Creates a reminder in the specified monthly planner.
void PlannerDatabase::create_reminder(const string& month, const string& writer,
    const string& receiver, const string& schedule, const string& notice)
{
    shared_ptr<MonthlyPlanner> curr = root_ptr;

    // walk list searching for correct month
    while (curr != nullptr) {
        if (curr->name == month) {
            curr->database->create_reminder(writer, receiver, schedule, notice);
            cout << "sent reminder from " << writer << " to " << receiver << " at " << month << endl;
            return;
        }
        curr = curr->next_ptr;
    }
    cout << "Month " << month << " does not exist. Please check your spelling\n";
}

// Deletes the specified reminder from the appropriate monthly planner.
void PlannerDatabase::delete_reminder(const string& month, const string& recipient, int msg_id)
{
    shared_ptr<MonthlyPlanner> curr = root_ptr;
    while (curr != nullptr) {
        if (curr->name == month) { // found correct office 
            curr->database->delete_reminder(recipient, msg_id);
            return;
        }
        curr = curr->next_ptr;
    }
    cout << "No reminders with ID [" << msg_id << "] for " << recipient << " found\n";
}

// Shows reminders for the user in the specified monthly planner.
void PlannerDatabase::show_reminders(const string& month, const string& recipient)
{
    shared_ptr<MonthlyPlanner> curr = root_ptr;
    while (curr != nullptr) {
        // If the correct node is found, display the appropriate reminders
        if (curr->name == month) {
            curr->database->display_reminders_for_user(recipient);
            return;
        }
        curr = curr->next_ptr;
    }

    cout << "No reminders for " << recipient << " found.\n";
}

// Saves the month's PlannerDatabase to a file
void PlannerDatabase::update_planner(const string& office, const string& filename) const
{
    shared_ptr<MonthlyPlanner> curr = root_ptr;
    while (curr != nullptr) {
        if (curr->name == office) {
            curr->database->update_reminder_database(filename);
            return;
        }
        curr = curr->next_ptr;
    }
    cout << "There is no " << office << " month. Please check the spelling\n";
}

// Verifies that the user-provided month is a valid one.
bool PlannerDatabase::month_is_valid(const string& month) const
{
    shared_ptr<MonthlyPlanner> curr = root_ptr;
    while (curr != nullptr) {
        if (curr->name == month) {
            return true;
        }
        curr = curr->next_ptr;
    }
    return false;
}
