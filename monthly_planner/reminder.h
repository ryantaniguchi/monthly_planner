// reminder.h
// Header file for Reminder, which represents a single reminder reminder.
//

#ifndef reminder_h
#define reminder_h

#include <string>

using namespace std;

class Reminder {

public:
    // The constructor for a reminder
    Reminder(const string& author, const string& receiver, const string& day,
        const string& notice);

    // Gets the ID for a reminder
    int get_id() const;

    // Display the properties of the specified reminders.
    void display_properties() const;

    // Get individual reminder properties
    string get_author() const { return writer; }
    string get_receiver() const { return recipient; }
    string get_schedule() const { return schedule; }
    string get_notices() const { return notice; }

private:
    int id;
    static int id_next;
    string writer;
    string recipient;
    string schedule;
    string notice;
};

#endif // reminder_h
