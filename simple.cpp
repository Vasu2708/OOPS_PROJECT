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
        seats.resize(50, true); // 50 seats initially available
    }

    void display() const
    {
        cout << "Title: " << title << ", Timing: " << timing << ", Price: $" << fixed << setprecision(2) << pricePerSeat << endl;
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
            seats[seat - 1] = false; // Mark seat as booked
        }
    }

    void cancelSeats(const vector<int> &seatNumbers)
    {
        cout << "Cancelling seats: ";
        for (int seat : seatNumbers)
        {
            if (!seats[seat - 1]) // Only cancel if the seat is booked
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
            if (!seats[seat - 1]) // Check if the seat is already booked
                return false;
        }
        return true;
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

    void display() const
    {
        cout << "\n--- Ticket Details ---\nName: " << customerName << "\nMobile: " << mobileNumber
             << "\nMovie: " << movieTitle << "\nTiming: " << movieTiming << "\nSeats: ";
        for (int seat : bookedSeats)
            cout << seat << " ";
        cout << "\nTotal Price: $" << fixed << setprecision(2) << totalPrice << endl;
    }

    bool operator==(const Ticket &other) const
    {
        return customerName == other.customerName &&
               mobileNumber == other.mobileNumber &&
               movieTitle == other.movieTitle &&
               movieTiming == other.movieTiming;
    }

    void removeSeats(const vector<int> &seatNumbers, double pricePerSeat)
    {
        for (int seat : seatNumbers)
        {
            bookedSeats.erase(seat);
        }
        updatePrice(pricePerSeat);
    }

    void updatePrice(double pricePerSeat)
    {
        totalPrice = bookedSeats.size() * pricePerSeat;
    }

    bool checkCancel(const vector<int> &seatNumbers) const
    {
        for (int seat : seatNumbers)
        {
            if (bookedSeats.find(seat) == bookedSeats.end())
            {
                return false;
            }
        }
        return true;
    }

    bool allSeatsCancel(const vector<int> &seatNumbers) const
    {
        return checkCancel(seatNumbers) && seatNumbers.size() == bookedSeats.size();
    }
};


class BookingSystem
{
    vector<Movie> movies;
    vector<Ticket> tickets;

public:
    void addMovie(string title, string timing, double price)
    {
        movies.push_back(Movie(title, timing, price));
    }

    void showMovies() const
    {
        for (const auto &movie : movies)
        {
            movie.display();
        }
    }

    Movie *getMovie(const string &title, const string &time)
    {
        for (auto &movie : movies)
        {
            if (movie.title == title && movie.timing == time)
                return &movie;
        }
        return nullptr; // Movie not found
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

    void bookTicket(string name, string mobile, string title, string time, const vector<int> &seats)
    {
        Movie *movie = getMovie(title, time);
        if (movie)
        {
            if (movie->checkBookSeats(seats)) // Check if seats are available
            {
                movie->bookSeats(seats);
                tickets.push_back(Ticket(name, mobile, title, time, seats, movie->pricePerSeat));
                cout << "Booking successful!\n";
                tickets.back().display();
            }
            else
            {
                cout << "Booking failed: Some seats unavailable.\n";
            }
        }
        else
        {
            cout << "Movie or timing not found.\n";
        }
    }

    void cancelTicket(string name, string mobile, string title, const vector<int> &seats)
    {
        Ticket *ticket = getTicket(name, mobile, title);
        if (ticket)
        {
            Movie *movie = getMovie(title, ticket->movieTiming);
            if (movie)
            {
                if (ticket->checkCancel(seats))
                {
                    if (ticket->allSeatsCancel(seats))
                    {
                    tickets.erase(remove(tickets.begin(), tickets.end(), *ticket), tickets.end());
                    }
                    else
                    {
                        movie->cancelSeats(seats);
                        ticket->removeSeats(seats, movie->pricePerSeat);
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

    Ticket *getTicket(const string &name, const string &mobile, const string &title)
    {
        for (auto &ticket : tickets)
        {
            if (ticket.customerName == name && ticket.mobileNumber == mobile && ticket.movieTitle == title)
            {
                return &ticket; // Found the ticket
            }
        }
        return nullptr; // Ticket not found
    }

    void retrieveTicket(const string &name, const string &title, const string &mobile)
    {
        const Ticket *ticket = getTicket(name, mobile, title);
        if (ticket)
        {
            ticket->display();
        }
        else
        {
            cout << "Ticket not found.\n";
        }
        return;
    }
bool isValidPhoneNumber(const string &mobile)
{
    if (mobile.length() != 10)
        return false;
    return all_of(mobile.begin(), mobile.end(), ::isdigit);
}

    void run_choice_2() // Book Ticket
    {
        string name, mobile, title, time;
        int seat;
        vector<int> seats;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter mobile: ";
        cin >> mobile;
        while(!isValidPhoneNumber(mobile)){
            cout<<"please Enter valid phone no :"<< endl;
            cin>>mobile;
        }
        cout << "Enter movie title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter movie timing: ";
        getline(cin, time);
        cout << "Enter seat numbers (end with -1): ";
        while (cin >> seat && seat != -1)
            seats.push_back(seat);
        bookTicket(name, mobile, title, time, seats);
    }

    void run_choice_3() // Cancel Ticket
    {
        string name, mobile, title;
        int seat;
        vector<int> seats;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter mobile: ";
        cin >> mobile;
        while(!isValidPhoneNumber(mobile)){
            cout<<"please Enter valid phone no "<< endl;
            cin>>mobile;
        }
        cout << "Enter movie title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter seat numbers to cancel (end with -1): ";
        while (cin >> seat && seat != -1)
            seats.push_back(seat);
        cancelTicket(name, mobile, title, seats);
    }

    void run_choice_4() // Show Available Seats
    {
        cout << "Enter the movie title: ";
        string title;
        cin.ignore();
        getline(cin, title);
        cout << "Enter the movie timing: ";
        string time;
        getline(cin, time);
        showAvailableSeats(title, time);
    }

    void run_choice_5() // Retrieve Ticket
    {
        string name, mobile, title;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter movie title: ";
        getline(cin, title);
        cout << "Enter mobile: ";
        cin >> mobile;
        retrieveTicket(name, title, mobile);
    }
};

int main()
{
    BookingSystem system;
    system.addMovie("Avengers", "10:00 AM", 10.0);
    system.addMovie("Inception", "1:00 PM", 12.0);

    int choice;
    do
    {
        cout << "\n1. Show Movies\n2. Book Ticket\n3. Cancel Ticket\n4. Show Available Seats\n5. Retrieve Ticket\n6. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.showMovies();
            break;
        case 2:
            system.run_choice_2();
            break;
        case 3:
            system.run_choice_3();
            break;
        case 4:
            system.run_choice_4();
            break;
        case 5:
            system.run_choice_5();
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
