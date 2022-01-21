// planner_database.h
// Stores a collection of month nodes and allows users to create, read, and
// delete reminders
//

#ifndef planner_database_h
#define planner_database_h

#include <memory>
#include <string>
#include "reminder_storage.h"

using namespace std;

class PlannerDatabase
{
public:
    // Adds a month node by importing a file with saved reminders
    void open_planner(const string& month_name, const string& filename);

    // Save the specified monthly planner to its file
    void update_planner(const string& office, const string& filename) const;

    // Checks if the specified month can be found
    bool month_is_valid(const string& month) const;

    // Display all reminders for the specified user for the given month
    void show_reminders(const string& month, const string& recipient);

    // Creates a reminder for the receiver in the month's file
    void create_reminder(const string& month, const string& writer,
        const string& receiver, const string& schedule, const string& notice);

    // Delete a reminder for the specified user in the given month
    void delete_reminder(const string& month, const string& recipient, int msg_id);

private:
    // Stores an instance of a monthly planner
    class MonthlyPlanner {
    public:
        shared_ptr<ReminderStorage> database;   // the reminders for this monthly planner
        string name;                      // the name of the month
        shared_ptr<MonthlyPlanner> next_ptr;  // points to the next node
        MonthlyPlanner(const string& a_name); // constructor for a new month node
    };

    shared_ptr<MonthlyPlanner> root_ptr;    // points to the first node
};

# endif // planner_database_h
