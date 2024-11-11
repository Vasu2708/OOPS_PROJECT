#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip> // for std::fixed and std::setprecision

using namespace std;

// Class for a Movie
class Movie {
public:
    string title;
    string genre;
    int duration; 
    string timing;
    double price;

    Movie(string t, string g, int d, string time, double p)
        : title(t), genre(g), duration(d), timing(time), price(p) {}

    void displayMovieDetails() const {
        cout << "Title: " << title << ", Genre: " << genre 
             << ", Duration: " << duration << " min, Timing: " 
             << timing << ", Price: $" << fixed << setprecision(2) << price << endl;
    }
};


class Theater {
private:
    vector<int> availableSeats;

public:
    Theater(int totalSeats) {
        for (int i = 1; i <= totalSeats; ++i) {
            availableSeats.push_back(i);
        }
    }

    void displayAvailableSeats(const string& timing) {
        cout << "Available seats for timing " << timing << ": ";
        for (int seat : availableSeats) {
            cout << seat << " ";
        }
        cout << endl;
    }

    bool bookSeats(const string& timing, const vector<int>& seatNumbers) {
        for (int seat : seatNumbers) {
            if (find(availableSeats.begin(), availableSeats.end(), seat) == availableSeats.end()) {
                return false; 
            }
        }
       
        for (int seat : seatNumbers) {
            availableSeats.erase(remove(availableSeats.begin(), availableSeats.end(), seat), availableSeats.end());
        }
        return true; 
    }

    bool cancelSeats(const string& timing, const vector<int>& seatNumbers) {
        for (int seat : seatNumbers) {
            availableSeats.push_back(seat); 
        }
        return true; 
    }
};

class payment {
protected:
    double amount;
public:
    payment(double amt) : amount(amt) {}
    virtual void processPayment() const = 0; 
};

class CashPayment : public payment {
public:
    CashPayment(double amt) : payment(amt) {}

    void processPayment() const override {
        cout << "Payment of $" << fixed << setprecision(2) << amount << " received in cash.\n";
    }
};

class CreditCardPayment : public payment {
public:
    CreditCardPayment(double amt) : payment(amt) {}

    void processPayment() const override {
        string pin;
        while (true) {
            cout << "Enter your 4-digit credit card PIN: ";
            cin >> pin;
            if (validatePin(pin)) {
                cout << "Payment of $" << fixed << setprecision(2) << amount << " processed successfully via credit card.\n";
                break;
            } else {
                cout << "Invalid PIN. Please enter a 4-digit number.\n";
            }
        }
    }

private:
    bool validatePin(const string& pin) const {
        return pin.length() == 4 && all_of(pin.begin(), pin.end(), ::isdigit);
    }
};


class Ticket {
public:
    string customerName;
    string mobileNumber;
    string movieTitle;
    string movieTiming;
    vector<int> seatNumbers;
    double totalPrice;

    Ticket(string name, string mobile, string title, string timing, vector<int> seats, double price)
        : customerName(name), mobileNumber(mobile), movieTitle(title), movieTiming(timing),
          seatNumbers(seats), totalPrice(price) {}

    void displayTicket() const {
        cout << "\n--- Ticket Details ---\n";
        cout << "Customer Name: " << customerName << "\n"
             << "Mobile Number: " << mobileNumber << "\n"
             << "Movie Title: " << movieTitle << "\n"
             << "Movie Timing: " << movieTiming << "\n"
             << "Seat Numbers: ";
        for (int seat : seatNumbers) {
            cout << seat << " ";
        }
        cout << "\nTotal Price: $" << fixed << setprecision(2) << totalPrice << endl;
    }
};

// Class for managing the entire booking system
class BookingSystem {
private:
    vector<Movie> movies;
    Theater theater;
    vector<Ticket> bookedTickets;

public:
    BookingSystem() : theater(50) {} // Assuming the theater has 50 seats

    // Add a movie to the system
    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    // Show movies sorted by timing
    void showMoviesToday() const {
        cout << "\nMovies Today (Sorted by Timing):\n";
        vector<Movie> sortedMovies = movies;
        sort(sortedMovies.begin(), sortedMovies.end(), [](const Movie& a, const Movie& b) {
            return a.timing < b.timing; // Sort by timing
        });
        for (const auto& movie : sortedMovies) {
            movie.displayMovieDetails();
        }
    }

    // Check currently available seats for a movie and timing
    bool checkAvailableSeats(const string& movieTitle, const string& timing) {
        bool movieFound = false;
        for (const auto& movie : movies) {
            if (movie.title == movieTitle && movie.timing == timing) {
                movieFound = true;
                theater.displayAvailableSeats(timing);
                return true;
            }
        }
        if (!movieFound) {
            cout << "Movie not found or invalid timing.\nPlease check movie details." << endl;
            return false;
        }
    }

    // Book tickets
    void bookTicket(const string& customerName, const string& mobileNumber, const string& movieTitle, const string& timing, const vector<int>& seatNumbers) {
        bool movieFound = false;
        for (const auto& movie : movies) {
            if (movie.title == movieTitle && movie.timing == timing) {
                movieFound = true;
                double totalPrice = seatNumbers.size() * movie.price; //
                if (theater.bookSeats(timing, seatNumbers)) {
                    Ticket ticket(customerName, mobileNumber, movieTitle, timing, seatNumbers, totalPrice);
                    bookedTickets.push_back(ticket);
                    cout << "Ticket(s) booked successfully!\n";
                    ticket.displayTicket();
                } else {
                    cout << "Failed to book ticket(s): Some seats are unavailable or invalid.\n";
                }
                return;
            }
        }
        if (!movieFound) {
            cout << "Movie not found or invalid timing.\nPlease check movie details." << endl;
        }
    }

    // Cancel tickets
    void cancelTicket(const string& customerName, const string& mobileNumber, const string& movieTitle, const string& timing, const vector<int>& seatNumbers) {
        bool ticketFound = false;
        for (auto it = bookedTickets.begin(); it != bookedTickets.end(); ++it) {
            // Check if the ticket details match for cancellation
            if (it->customerName == customerName && it->mobileNumber == mobileNumber && it->movieTitle == movieTitle && it->movieTiming == timing) {
                bool allSeatsFound = true;
                for (int seatNumber : seatNumbers) {
                    if (find(it->seatNumbers.begin(), it->seatNumbers.end(), seatNumber) == it->seatNumbers.end()) {
                        allSeatsFound = false;
                        break;
                    }
                }
                if (allSeatsFound) {
                    if (theater.cancelSeats(timing, seatNumbers)) {
                        // Update the total price after cancellation
                        double pricePerSeat = 0.0; // Initialize price per seat
                        for (const auto& movie : movies) {
                            if (movie.title == movieTitle && movie.timing == timing) {
                                pricePerSeat = movie.price; // Get the price for the movie
                                break;
                            }
                        }

                        // Remove canceled seat numbers from the ticket
                        for (int seatNumber : seatNumbers) {
                            it->seatNumbers.erase(remove(it->seatNumbers.begin(), it->seatNumbers.end(), seatNumber), it->seatNumbers.end());
                        }

                        // Update totalPrice based on remaining booked seats
                        it->totalPrice = it->seatNumbers.size() * pricePerSeat;

                        cout << "Ticket(s) cancelled successfully.\n";
                        it->displayTicket(); // Display updated ticket information
                    } else {
                        cout << "Failed to cancel ticket(s): Some seats were not booked.\n";
                    }
                    ticketFound = true;
                } else {
                    cout << "Error: Some seats you entered were not booked under your name.\n";
                }
                break;
            }
        }
        if (!ticketFound) {
            cout << "Ticket not found. Please check your details.\n";
        }
    }

   
    void retrieveTicketDetails(const string& customerName, const string& mobileNumber) const {
        bool ticketFound = false;
        for (const auto& ticket : bookedTickets) {
            if (ticket.customerName == customerName && ticket.mobileNumber == mobileNumber) {
                ticket.displayTicket();
                ticketFound = true;
            }
        }
        if (!ticketFound) {
            cout << "No tickets found for the provided name and mobile number.\n";
        }
    }

    // Validate mobile number
    bool validateMobileNumber(const string& mobileNumber) const {
        if (mobileNumber.length() != 10) return false; // Check length
        for (char c : mobileNumber) {
            if (!isdigit(c)) return false; // Check for digits
        }
        return true;
    }
};

// Main Function
int main() {
    BookingSystem system;

    // Adding movies to the system
    system.addMovie(Movie("Avengers", "Action", 180, "10:00 AM", 10.0));
    system.addMovie(Movie("Inception", "Sci-Fi", 150, "1:00 PM", 12.0));
    system.addMovie(Movie("Interstellar", "Sci-Fi", 170, "4:00 PM", 15.0));
    system.addMovie(Movie("Titanic", "Romance", 195, "7:00 PM", 8.0));

    int choice;
    do {
        cout << "\n--- Movie Ticket Booking System ---\n";
        cout << "1. Show Movies Today\n";
        cout << "2. Check Available Seats\n";
        cout << "3. Book a Ticket\n";
        cout << "4. Cancel a Ticket\n";
        cout << "5. Retrieve Ticket Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            system.showMoviesToday();
        } else if (choice == 2) {
            string movieTitle, timing;
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, movieTitle);
            cout << "Enter movie timing: ";
            getline(cin, timing);
            system.checkAvailableSeats(movieTitle, timing);
        } else if (choice == 3) {
            string customerName, mobileNumber, movieTitle, timing;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, customerName);
            
            // Validate mobile number
            while (true) {
                cout << "Enter your mobile number (10 digits): ";
                cin >> mobileNumber;
                if (system.validateMobileNumber(mobileNumber)) {
                    break;
                } else {
                    cout << "Please enter a valid mobile number." << endl;
                }
            }

            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, movieTitle);
            cout << "Enter movie timing: ";
            getline(cin, timing);
            bool checking = system.checkAvailableSeats(movieTitle, timing);
            if(!checking) {
                cout << "Please  cheack movie name and timeing of movie.\n";
                continue;
            }
            cout << "Enter seat numbers (separated by spaces, e.g., 1 2 3): ";
            vector<int> seatNumbers;
            string input;
            getline(cin, input);
            istringstream iss(input);
            int seatNumber;
            while (iss >> seatNumber) {
                seatNumbers.push_back(seatNumber);
            }
            system.bookTicket(customerName, mobileNumber, movieTitle, timing, seatNumbers);
        } else if (choice == 4) {
            string customerName, mobileNumber, movieTitle, timing;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, customerName);
            
            // Validate mobile number
            while (true) {
                cout << "Enter your mobile number (10 digits): ";
                cin >> mobileNumber;
                if (system.validateMobileNumber(mobileNumber)) {
                    break;
                } else {
                    cout << "Please enter a valid mobile number." << endl;
                }
            }

            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, movieTitle);
            cout << "Enter movie timing: ";
            getline(cin, timing);

            cout << "Enter seat numbers to cancel (separated by spaces, e.g., 1 2 3): ";
            vector<int> seatNumbers;
            string input;
            getline(cin, input);
            istringstream iss(input);
            int seatNumber;
            while (iss >> seatNumber) {
                seatNumbers.push_back(seatNumber);
            }
            system.cancelTicket(customerName, mobileNumber, movieTitle, timing, seatNumbers);
        } else if (choice == 5) {
            string customerName, mobileNumber;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter your mobile number: ";
            cin >> mobileNumber;
            system.retrieveTicketDetails(customerName, mobileNumber);
        }
    } while (choice != 6);

    return 0;
}
