// reminder_storage.cpp
//

#include "reminder_storage.h"
#include <algorithm>
#include <iostream>

// Read reminders from the specified month's planner file.
ReminderStorage::ReminderStorage(const string& filename)
{
    read_reminders_from_file(filename);
}

// Displays reminders from the specified month's planner file.
void ReminderStorage::display_reminders_for_user(const string& user) const
{
    // Find the map item that is associated with the specified user.
    auto iterator = reminders.find(user);

    // If the user isn't found by the end, return
    if (iterator == reminders.end()) {
        return;
    }

    // This gives access to the list of reminders.
    auto& list = iterator->second;

    // Use a range-based for loop to iterate over each
    // item in the list
    for (const auto& reminder : list) {
        reminder.display_properties();
    }
}

// Deletes a reminder from the specified month's planner file.
void ReminderStorage::delete_reminder(const string& user, int msg_id)
{
    // Find the map entry for the given user
    auto iterator = reminders.find(user);

    if (iterator == reminders.end()) { // user not found in map
        return;
    }

    auto& list = iterator->second; // get the list of reminders

    // Remove the reminder with the matching ID.
    list.remove_if([msg_id](auto m) { return msg_id == m.get_id(); });
}

// Creates a reminder to add to the specified month's planner file.
void ReminderStorage::create_reminder(const string& author, const string& receiver,
    const string& schedule, const string& notice)
{
    // Create a new reminder.
    Reminder reminder(author, receiver, schedule, notice);

    // Finds the reminders for the specified user and adds the most recent reminder 
    // to the end of that list. If the user doesn't exist already, the user is given
    // a new entry in the map.
    reminders[receiver].push_back(reminder);

}

// Updates the specified month's planner file with changes.
void ReminderStorage::update_reminder_database(const string& filename)
{
    // open a file so that updates can be saved to it.
    ofstream fout(filename);
    if (fout.fail()) {
        cout << "Unable to save to " << filename << endl;
        return;
    }

    for (auto& each : reminders) {
        for (auto& reminder : each.second) {
            fout << reminder.get_author() << "|"
                << reminder.get_receiver() << "|"
                << reminder.get_schedule() << "|"
                << reminder.get_notices() << endl;
        }
    }
    fout.close();
}

// Retrieves information from the specified month's planner file.
void ReminderStorage::read_reminders_from_file(const string& filename)
{
    // Opens the specified file.
    ifstream fin(filename);

    // Prints an error message if the file can't be opened.
    if (fin.fail()) {
        cout << "Error, can't open " << filename << ".\n";
        return;
    }

    while (!fin.fail()) {
        string author;
        string receiver;
        string schedule;
        string notice;
        getline(fin, author, '|');
        getline(fin, receiver, '|');
        getline(fin, schedule, '|');
        getline(fin, notice, '\n');

        if (!fin.fail()) {
            Reminder reminder(author, receiver, schedule, notice);
            reminders[receiver].push_back(reminder);
        }
    }
    fin.close();
}
