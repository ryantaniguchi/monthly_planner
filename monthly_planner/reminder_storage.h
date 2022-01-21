// reminder_storage.h
// Stores reminders and lets users create, read, and delete them.
//

#ifndef reminder_storage_h
#define reminder_storage_h

#include <fstream>
#include <list>
#include <map>
#include <string>
#include "reminder.h"

using namespace std;

class ReminderStorage
{
public:
    // Default constructor to create an empty reminder database
    ReminderStorage() = default;

    // Constructor that reads a file to populate reminders
    ReminderStorage(const string& filename);

    // Displays all the reminders for a given user
    void display_reminders_for_user(const string& user) const;

    // Deletes a single reminder
    void delete_reminder(const string& user, int msg_id);

    // Creates a reminder for the specified user
    void create_reminder(const string& author, const string& receiver,
        const string& schedule, const string& notice);

    // Save all reminders to a file
    void update_reminder_database(const string& filename);

private:
    // Stores usernames that are mapped to a list of reminders
    map<string, list<Reminder>> reminders;

    // Reads the reminders from the appropriate file.
    void read_reminders_from_file(const string& filename);
};

#endif // reminder_storage_h
