// reminder.cpp
//

#include "reminder.h"
#include <iostream>

Reminder::Reminder(const string& author, const string& receiver,
    const string& schedule, const string& notice) :
    id{ ++id_next }, writer{ author }, recipient{ receiver },
    schedule{ schedule }, notice{ notice } {}

// Formats the displayed notification.
void Reminder::display_properties() const
{
    cout << "[" << id << "]From:" << writer << ": " << schedule << " - " << notice << endl;
}

// Gets the specified reminder ID.
int Reminder::get_id() const
{
    return id;
}

// Incremented ID so that each response has a unique ID.
int Reminder::id_next = 0;
