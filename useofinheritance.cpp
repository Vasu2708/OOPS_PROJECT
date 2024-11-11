#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;

class Movie
{
public:
    string title, timing;
    double pricePerSeat;
    vector<bool> seats;

    Movie(string t, string time, double p) : title(t), timing(time), pricePerSeat(p)
    {
        seats.resize(50, true);
    }

    virtual void display() const
    {
        cout << "Title: " << title << ", Timing: " << timing << ", Price: $"
             << fixed << setprecision(2) << pricePerSeat << endl;
    }

    void showAvailableSeats() const
    {
        cout << "Available seats: ";
        for (int i = 0; i < seats.size(); i++)
        {
            if (seats[i])
                cout << i + 1 << " ";
        }
        cout << endl;
    }

    void bookSeats(const vector<int> &seatNumbers)
    {
        for (int seat : seatNumbers)
        {
            seats[seat - 1] = false;
        }
    }

    void cancelSeats(const vector<int> &seatNumbers)
    {
        cout << "Cancelling seats: ";
        for (int seat : seatNumbers)
        {
            if (!seats[seat - 1])
            {
                seats[seat - 1] = true;
                cout << seat << " ";
            }
        }
        cout << endl;
    }

    bool checkBookSeats(const vector<int> &seatNumbers) const
    {
        for (int seat : seatNumbers)
        {
            if (!seats[seat - 1])
                return false;
        }
        return true;
    }

    bool validSeat(const vector<int> &seatNumbers)
    {
        for (int seat : seatNumbers)
        {
            if (seat < 1 || seat > 50)
                return true;
        }
        return false;
    }
};

class RegularMovie : public Movie
{
public:
    RegularMovie(string t, string time, double p) : Movie(t, time, p) {}
};

class PremiumMovie : public Movie
{
public:
    PremiumMovie(string t, string time, double p) : Movie(t, time, p)
    {
        pricePerSeat *= 1.5;
    }

    void display() const override
    {
        cout << "***** Premium Movie *****" << endl;
        Movie::display();
    }
};

class Ticket
{
public:
    string customerName, mobileNumber, movieTitle, movieTiming;
    set<int> bookedSeats;
    double totalPrice;

    Ticket(string name, string mobile, string title, string time, const vector<int> &seats, double pricePerSeat)
        : customerName(name), mobileNumber(mobile), movieTitle(title), movieTiming(time)
    {
        bookedSeats.insert(seats.begin(), seats.end());
        totalPrice = bookedSeats.size() * pricePerSeat;
    }

    virtual void display() const
    {
        cout << "\n--- Ticket Details ---\nName: " << customerName << "\nMobile: " << mobileNumber
             << "\nMovie: " << movieTitle << "\nTiming: " << movieTiming << "\nSeats: ";
        for (int seat : bookedSeats)
            cout << seat << " ";
        cout << "\nTotal Price: $" << fixed << setprecision(2) << totalPrice << endl;
    }

    bool checkCancel(const vector<int> &seats) const
    {
        for (int seat : seats)
        {
            if (bookedSeats.find(seat) == bookedSeats.end())
                return false;
        }
        return true;
    }

    void removeSeats(const vector<int> &seats, double pricePerSeat)
    {
        for (int seat : seats)
        {
            bookedSeats.erase(seat);
        }
        totalPrice = bookedSeats.size() * pricePerSeat;
    }

    bool allSeatsCancel(const vector<int> &seats) const
    {
        for (int seat : seats)
        {
            if (bookedSeats.find(seat) == bookedSeats.end())
                return false;
        }
        return true;
    }
    bool isAllSeatsCancel(const vector<int> &seats) const
    {
        return checkCancel(seats) && seats.size() == bookedSeats.size();
    }

    bool addseat(const vector<int> &seatNumbers, double pricePerSeat)
    {
        for (int seat : seatNumbers)
        {
            if (bookedSeats.find(seat) == bookedSeats.end())
            {
                bookedSeats.insert(seat);
            }
        }
        totalPrice = bookedSeats.size() * pricePerSeat;
        return true;
    }
};

class StandardTicket : public Ticket
{
public:
    StandardTicket(string name, string mobile, string title, string time, const vector<int> &seats, double pricePerSeat)
        : Ticket(name, mobile, title, time, seats, pricePerSeat) {}
};

class VIPTicket : public Ticket
{
public:
    VIPTicket(string name, string mobile, string title, string time, const vector<int> &seats, double pricePerSeat)
        : Ticket(name, mobile, title, time, seats, pricePerSeat)
    {
        totalPrice *= 2;
    }

    void display() const override
    {
        cout << "\n--- VIP Ticket Details ---\n";
        Ticket::display();
    }
};

class BookingSystem
{
    vector<Movie *> movies;
    vector<Ticket *> tickets;

public:
    void addMovie(Movie *movie)
    {
        movies.push_back(movie);
    }

    void showMovies() const
    {
        for (const auto &movie : movies)
        {
            movie->display();
        }
    }

    Movie *getMovie(const string &title, const string &time)
    {
        for (auto &movie : movies)
        {
            if (movie->title == title && movie->timing == time)
                return movie;
        }
        return nullptr;
    }

    void showAvailableSeats(const string &title, const string &time)
    {
        Movie *movie = getMovie(title, time);
        if (movie)
        {
            movie->showAvailableSeats();
        }
        else
        {
            cout << "Movie or timing not found.\n";
        }
    }

    void bookTicket(string name, string mobile, string title, string time, const vector<int> &seats, bool isVIP = false)
    {
        Movie *movie = getMovie(title, time);
        if (movie)
        {
            if (movie->validSeat(seats))
            {
                cout << "Booking failed: Please enter a valid seat number.\n";
                return;
            }
            if (movie->checkBookSeats(seats))
            {
                Ticket *ticket = getTicket(name, mobile, title, time);
                if (ticket)
                {   
                    ticket->addseat(seats, movie->pricePerSeat);
                    movie->bookSeats(seats);
                    else
                    {
                        movie->bookSeats(seats);
                        if (isVIP)
                        {
                            ticket = new VIPTicket(name, mobile, title, time, seats, movie->pricePerSeat);
                        }
                        else
                        {
                            ticket = new StandardTicket(name, mobile, title, time, seats, movie->pricePerSeat);
                        }
                        tickets.push_back(ticket);
                        cout << "Booking successful!\n";
                    }
                    ticket->display();
                }
                else
                {
                    cout << "Booking failed: Some seats are unavailable.\n";
                }
            }
            else
            {
                cout << "Movie or timing not found.\n";
            }
        }

        void cancelTicket(string name, string mobile, string title, const vector<int> &seats, string time)
        {
            Ticket *ticket = getTicket(name, mobile, title, time);
            if (ticket)
            {
                Movie *movie = getMovie(title, ticket->movieTiming);
                if (movie)
                {
                    if (ticket->checkCancel(seats))
                    {
                        if (ticket->isAllSeatsCancel(seats))
                        {
                            tickets.erase(remove(tickets.begin(), tickets.end(), ticket), tickets.end());
                            delete ticket;
                            cout << "All seats canceled, ticket removed.\n";
                        }
                        else
                        {

                            movie->cancelSeats(seats);
                            ticket->removeSeats(seats, movie->pricePerSeat);
                            cout << "Seats canceled successfully.\n";
                        }
                    }
                    else
                    {
                        cout << "Cancellation failed: Some seats were not booked.\n";
                    }
                }
                else
                {
                    cout << "Cancellation failed: Movie not found.\n";
                }
            }
            else
            {
                cout << "Ticket not found.\n";
            }
        }

        Ticket *getTicket(const string &name, const string &mobile, const string &title, string timing)
        {
            for (auto &ticket : tickets)
            {
                if (ticket->customerName == name && ticket->mobileNumber == mobile && ticket->movieTitle == title && ticket->movieTiming == timing)
                {
                    return ticket;
                }
            }
            return nullptr;
        }

        void retrieveTicket(const string &name, const string &title, const string &mobile, const string &timing)
        {
            Ticket *ticket = getTicket(name, mobile, title, timing);
            if (ticket)
            {
                ticket->display();
            }
            else
            {
                cout << "Ticket not found.\n";
            }
        }

        bool isValidPhoneNumber(const string &mobile)
        {
            if (mobile.length() != 10)
                return false;
            return all_of(mobile.begin(), mobile.end(), ::isdigit);
        }

        void run_choice_2()
        { // Book Ticket
            string name, mobile, title, time;
            int seat;
            vector<int> seats;
            bool isVIP = false;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter mobile: ";
            cin >> mobile;
            while (!isValidPhoneNumber(mobile))
            {
                cout << "Please enter a valid phone number: ";
                cin >> mobile;
            }
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter movie timing: ";
            getline(cin, time);
            cout << "Enter number of seats to book: ";
            int numSeats;
            cin >> numSeats;
            cout << "Enter seat numbers (space-separated): ";
            for (int i = 0; i < numSeats; i++)
            {
                cin >> seat;
                seats.push_back(seat);
            }
            cout << "Is this a VIP booking? (1 for Yes, 0 for No): ";
            cin >> isVIP;
            bookTicket(name, mobile, title, time, seats, isVIP);
        }

        void run_choice_3()
        { // Cancel Ticket
            string name, mobile, title, time;
            int seat;
            vector<int> seats;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter mobile: ";
            cin >> mobile;
            while (!isValidPhoneNumber(mobile))
            {
                cout << "Please enter a valid phone number: ";
                cin >> mobile;
            }
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter movie timing: ";
            getline(cin, time);
            cout << "Enter number of seats to cancel: ";
            int numSeats;
            cin >> numSeats;
            cout << "Enter seat numbers (space-separated): ";
            for (int i = 0; i < numSeats; i++)
            {
                cin >> seat;
                seats.push_back(seat);
            }
            cancelTicket(name, mobile, title, seats, time);
        }

        void run_choice_4()
        { // Retrieve Ticket
            string name, mobile, title, time;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter mobile: ";
            cin >> mobile;
            while (!isValidPhoneNumber(mobile))
            {
                cout << "Please enter a valid phone number: ";
                cin >> mobile;
            }
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter movie timing: ";
            getline(cin, time);
            retrieveTicket(name, title, mobile, time);
        }
    };

    int main()
    {
        BookingSystem bookingSystem;
        // Example movies added
        bookingSystem.addMovie(new RegularMovie("Avatar", "6:00 PM", 10.00));
        bookingSystem.addMovie(new PremiumMovie("Titanic", "8:00 PM", 10.00));

        int choice;
        do
        {
            cout << "\n1. Show Movies\n2. Book Ticket\n3. Cancel Ticket\n4. Retrieve Ticket\n5. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                bookingSystem.showMovies();
                break;
            case 2:
                bookingSystem.run_choice_2();
                break;
            case 3:
                bookingSystem.run_choice_3();
                break;
            case 4:
                bookingSystem.run_choice_4();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 5);

        return 0;
    }
