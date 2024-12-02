#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Event
{
private:
    string name;
    string date;
    string time;
    string location;
    string description;
    int fees;

public:
    Event(string name, string date, string time, string location, string description, int fees)
        : name(name), date(date), time(time), location(location), description(description), fees(fees) {}

    string getName() const { return name; }
};

class Person
{
protected:
    string name;
    int ID;
    string contact_info;

public:
    Person(string name, int ID, string contact_info)
        : name(name), ID(ID), contact_info(contact_info) {}

    string getName() const { return name; }

    int getID() const { return ID; }

    string getContactInfo() const { return contact_info; }
};

class Participant : public Person
{
private:
    vector<Event *> events_participated;

public:
    Participant(string name, int ID, string contact_info)
        : Person(name, ID, contact_info) {}

    void registerForEvent(Event *event)
    {
        events_participated.push_back(event);
        cout << getName() << " registered for event: " << event->getName() << endl;
    }

    void viewRegisteredEvents() const
    {
        cout << "Registered Events for " << getName() << ":\n";
        for (const auto &event : events_participated)
        {
            cout << "- " << event->getName() << endl;
        }
    }
    virtual void printParticipantDetails() const
    {
        cout << "Participant Details for " << getName() << ":\n"
             << "College Participant"
             << "\n"
             << "ID: " << getID() << "\n"
             << "Contact Info: " << getContactInfo() << "\n";
    }
};

class NonCollegeParticipant : public Participant
{
private:
    string hostel_alloted;
    string college_name;
    int alloted_room_number;
    string food_preference;

public:
    NonCollegeParticipant(string name, int ID, string contact_info, string collegeName, string hostel_alloted, int alloted_room_number, string food_preference)
        : Participant(name, ID, contact_info), hostel_alloted(hostel_alloted), alloted_room_number(alloted_room_number), food_preference(food_preference), college_name(college_name) {}

    string getCollegeName() const
    {
        return college_name;
    }
    string getHostelName() const
    {
        return hostel_alloted;
    }
    int getAllotedRoomNo() const
    {
        return alloted_room_number;
    }
    string getFoodPreference() const
    {
        return food_preference;
    }
    void printParticipantDetails() const override
    {
        cout << "Participant Details for " << getName() << ":\n"
             << "Non- College Participant"
             << "\n"
             << "ID: " << getID() << "\n"
             << "Contact Info: " << getContactInfo() << "\n"
             << "College Name " << getCollegeName() << "\n"
             << "Hostel Alloted: " << getHostelName() << "\n"
             << "Room Number: " << getAllotedRoomNo() << "\n"
             << "Food preference: " << getFoodPreference() << endl;
    }
};

class Coordinator; // Forward declaration for Coordinator

class Workforce : public Person
{
private:
    Coordinator *coordinator;
    Event *event;

public:
    Workforce(string name, int ID, string contact_info, Coordinator *coordinator)
        : Person(name, ID, contact_info), coordinator(coordinator) {}

    void assignEvent(Event *event)
    {
        if (this->event != nullptr)
        {
            cout << getName() << " cannot be assigned another event. They are already managing an event: " << this->event->getName() << endl;
            return;
        }
        this->event = event;
        cout << getName() << " assigned event: " << event->getName() << endl;
    }

    void performTask()
    {
        cout << getName() << " performed a task." << endl;
    }

    void updateTaskStatus()
    {
        cout << getName() << "'s task status updated." << endl;
    }
};

class CoreMember : public Person
{
private:
    string specialization;
    vector<Coordinator *> coordinators;

public:
    CoreMember(string name, int ID, string contact_info, string specialization)
        : Person(name, ID, contact_info), specialization(specialization) {}

    void addCoordinator(Coordinator *coordinator);

    void removeCoordinator(Coordinator *coordinator);
};

class Coordinator : public Person
{
private:
    vector<Event *> events_managed;
    CoreMember *core_member;
    vector<Workforce *> workforce;

public:
    Coordinator(string name, int ID, string contact_info, CoreMember *core_member)
        : Person(name, ID, contact_info), core_member(core_member) {}

    void assignWorkforce(Workforce *worker)
    {
        workforce.push_back(worker);
        cout << getName() << " assigned workforce: " << worker->getName() << endl;
    }

    void manageEventDetails(Event *event)
    {
        events_managed.push_back(event);
        cout << getName() << " managed event: " << event->getName() << endl;
    }

    void updateEventStatus(Event *event)
    {
        cout << getName() << " updated status of event: " << event->getName() << endl;
    }
};

void CoreMember::addCoordinator(Coordinator *coordinator)
{
    coordinators.push_back(coordinator);
    cout << getName() << " added coordinator: " << coordinator->getName() << endl;
}

void CoreMember::removeCoordinator(Coordinator *coordinator)
{
    for (auto it = coordinators.begin(); it != coordinators.end(); ++it)
    {
        if (*it == coordinator)
        {
            coordinators.erase(it);
            cout << getName() << " removed coordinator: " << coordinator->getName() << endl;
            break;
        }
    }
}

void participant_creation()
{
    string pn, pe;
    int id;
    cout << "Name of participant: ";
    getline(cin, pn);
    cout << "ID: ";
    cin >> id;
    cin.clear();
    // cin.ignore();
    cout << "Contact info: ";
    while (pe.empty())
    {
        getline(cin, pe);
    }
    // cout << "participat Name: " << pn << "\nID: " << id << "\nContact Info: " << pe << endl;
    Participant *participant1 = new Participant(pn, id, pe);
    cout << "Participant created! Press <ENTER> to continue.\n";
}

void participant_registration(Event *event1)
{
    string pn, pe;
    int id;
    cout << "Name of participant: ";
    getline(cin, pn);
    cout << "ID: ";
    cin >> id;
    cout << "Contact info: ";
    while (pe.empty())
    {
        getline(cin, pe);
    }
    Participant *participant1 = new Participant(pn, id, pe);
    participant1->registerForEvent(event1);
    participant1->viewRegisteredEvents();
    cout << "Press <ENTER> to continue.\n";
}

void coremember_creation()
{
    string pn, pe, ps;
    int id;
    cout << "Name of Core Member: ";
    getline(cin, pn);
    cout << "ID: ";
    cin >> id;
    cout << "Contact info: ";
    while (pe.empty())
    {
        getline(cin, pe);
    }
    cout << "Specialisation: ";
    while (ps.empty())
    {
        getline(cin, ps);
    }
    CoreMember *coreMember1 = new CoreMember(pn, id, pe, ps);
    cout << "Core Member created! \n";
    cout << "Press <ENTER> to continue.\n";
}

Coordinator *coord_creation()
{
    string pn, pe, ps;
    int id;
    cout << "Name of Core Member that will assign the coordinator: ";
    getline(cin, pn);
    cout << "ID: ";
    cin >> id;
    cout << "Contact info: ";
    while (pe.empty())
    {
        getline(cin, pe);
    }
    cout << "Specialisation: ";
    getline(cin, ps);
    CoreMember *coreMember1 = new CoreMember(pn, id, pe, ps);
    string n, e;
    int ids;
    cout << "Name of Coordinator: ";
    getline(cin, n);
    cout << "ID: ";
    cin >> ids;
    cout << "Contact info: ";
    while (e.empty())
    {
        getline(cin, e);
    }
    Coordinator *coordinator1 = new Coordinator(n, ids, e, coreMember1);
    cout << "Coordinator created! \n";
    // cout << "Press <ENTER> to continue.\n";
    return coordinator1;
}

void coord_manage_event(Event *event1)
{
    Coordinator *coord = coord_creation();
    coord->manageEventDetails(event1);
    cout << "Press <ENTER> to continue.\n";
}

Workforce *create_coord_assign_worker()
{
    Coordinator *coord = coord_creation();
    cout << "Now creating a workforce for the coordinator: \n";
    string n, e;
    int id;
    cout << "Name of Worker: ";
    getline(cin, n);
    cout << "ID: ";
    cin >> id;
    cout << "Contact info: ";
    while (e.empty())
    {
        getline(cin, e);
    }
    Workforce *worker1 = new Workforce(n, id, e, coord);
    coord->assignWorkforce(worker1);
    cout << "Worker created! \n";
    cout << "Press <ENTER> to continue.\n";
    return worker1;
}

void add_coord_to_core()
{
    Coordinator *coord = coord_creation();

    string pn, pe, ps;
    int id;
    cout << "Name of Core Member that will add coordinator to core member's list: ";
    getline(cin, pn);
    cout << "ID: ";
    cin >> id;
    cout << "Contact info: ";
    while (pe.empty())
    {
        getline(cin, pe);
    }
    cout << "Specialisation: ";
    while (ps.empty())
    {
        getline(cin, ps);
    }
    CoreMember *coreMember1 = new CoreMember(pn, id, pe, ps);
    coreMember1->addCoordinator(coord);
    cout << "Press <ENTER> to continue.\n";
}

void manage_event_coord(Event *event1)
{
    Coordinator *coord = coord_creation();
    coord->manageEventDetails(event1);
    coord->updateEventStatus(event1);
    cout << "Press <ENTER> to continue.\n";
}

void task_workforce(Event *event1)
{
    Workforce *worker1 = create_coord_assign_worker();
    worker1->assignEvent(event1);
    worker1->performTask();
    worker1->updateTaskStatus();
    cout << "Press <ENTER> to continue.\n";
}

void noncollege_participant()
{
    string pn, pe, cn, hn, fp;
    int id, rn;
    cout << "Name of participant: ";
    while (pn.empty())
    {
        getline(cin, pn);
    }
    cout << "ID: ";
    cin >> id;
    cout << "Contact info: ";
    while (pe.empty())
    {
        getline(cin, pe);
    }
    cout << "College name: ";
    while (cn.empty())
    {
        getline(cin, cn);
    }
    cout << "Hostel alloted: ";
    while (hn.empty())
    {
        getline(cin, hn);
    }
    cout << "Room No: ";
    cin >> rn;
    cout << "Food preference: ";
    while (fp.empty())
    {
        getline(cin, fp);
    }
    NonCollegeParticipant *participant1 = new NonCollegeParticipant(pn, id, pe, cn, hn, rn, fp);
    cout << "Non- college Participant created\n";
    cout << "Press <ENTER> to continue.\n";
}

int main()
{
    // Creating an event
    int n;
    cout << "Enter Event Name: ";
    // cin.ignore();
    string name;
    getline(cin, name);
    cout << "Enter Event Date: ";
    string Date;
    getline(cin, Date);
    cout << "Enter Event Time: ";
    string Time;
    getline(cin, Time);
    cout << "Enter Event Location: ";
    string Location;
    getline(cin, Location);
    cout << "Enter Event Description: ";
    string Description;
    getline(cin, Description);
    int Fees;
    cout << "Enter Event Fees: ";
    cin >> Fees;
    // cin.ignore();
    Event *event1 = new Event(name, Date, Time, Location, Description, Fees);

    int count = 0;

    while (true)
    {
        cout << "What would you prefer to do(Enter number): \n";
        cout << "1) Create a college participant \n";
        cout << "2) Create and Registering a participant for the event \n";
        cout << "3) Create a Core Member \n";
        cout << "4) Creating a Coordinator and managing the event \n";
        cout << "5) Create a Coordinator \n";
        cout << "6) Creating a Coordinator and assigning a workforce \n";
        cout << "7) Adding Coordinator to Core Member's list \n";
        cout << "8) Managing event details and updating status by Coordinator \n";
        cout << "9) Assigning and Performing tasks by Workforce and updating task status \n";
        cout << "10) Create a non-college participant \n";
        cout << "11) Exit \n";
        cout << "Enter the no. of the task you wish to perform: ";

        if (count == 0)
        {
            cin.clear();
            cin.ignore();
            count++;
        }

        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(); // clear the error flags
            // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
            cout << "Invalid input! Please enter a number.\n";
            continue; // skip the rest of the loop
        }
        cin.clear();
        cin.ignore();

        cout << "You have chosen to perform task " << n << "\n";
        if (n == 11)
        {
            cout << "Thank you for using our system!\n";
            break;
        }

        switch (n)
        {
        case 1:
            participant_creation();
            break;
        case 2:
            participant_registration(event1);
            break;
        case 3:
            coremember_creation();
            break;
        case 4:
            coord_manage_event(event1);
            break;
        case 5:
            coord_creation();
            // cout << "Coordinator created!";
            cout << "Press <ENTER> to continue.\n";
            break;
        case 6:
            create_coord_assign_worker();
            break;
        case 7:
            add_coord_to_core();
            break;
        case 8:
            manage_event_coord(event1);
            break;
        case 9:
            task_workforce(event1);
            break;
        case 10:
            noncollege_participant();
            break;
        default:
            cout << "Invalid input! Please enter a number between 1 and 11.\n";
            cout << "Press <ENTER> to end this invalid task.\n";
            break;
        }
        // // flush the cin buffer
        cin.ignore();

        cout << "Task ended successfully!\n\n\n";
    }
    return 0;
}
