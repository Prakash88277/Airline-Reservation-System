#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h> // For getch(), system("cls"), Sleep()
#include <cstring>   // For strcpy(), strncpy()
#include <vector>    // For std::vector<...>
#include <queue>     // For priority queue
#include <ctime>     // For time calculations
#include <cstdlib>   // For random number generation
#include <algorithm> // For algorithms
#include <map>       // For map data structure
#include <iomanip>   // For setw()

using namespace std;

bool login_status = false;       // for checking user login status
bool signup_ok = false;          // for checking SignUp
string login_user;               // for set user Username
bool admin_login_status = false; // for checking Admin login status
string administrator_user;       // for set admin Username
// First, declare functions at the top of your file
void Update_Passenger_Details();

// Priority Queue for managing booking priority
struct BookingPriority
{
    string bookingId;
    int priority;
    time_t bookingTime;

    bool operator<(const BookingPriority &other) const
    {
        return priority < other.priority;
    }
};

priority_queue<BookingPriority> bookingQueue;

// User tier system for frequent flyer points
enum UserTier
{
    REGULAR = 1,
    SILVER = 2,
    GOLD = 3,
    PLATINUM = 4
};

// Dynamic pricing factors
struct PricingFactors
{
    float basePrice;
    float demandMultiplier;
    float timeMultiplier;
    float classMultiplier;
    float tierDiscount;
};

void main_menu();
void login_menu();
void Modify_Ticket();

// Enhanced Flight class with dynamic pricing
class Flight
{
protected:
    char flight_number[20];
    char flight_name[20];
    char departure_time[20];
    char arrival_time[20];
    char source[20];
    char destination[20];
    int totalSeats;
    int availableSeats;
    float base_price;
    time_t departureDateTime; // Store departure date and time

public:
    Flight() {}
    Flight(string f_num, string f_name, string dep_time, string arr_time, string src, string des, int seats, float price, int day, int month, int year)
    {
        strcpy(flight_number, f_num.c_str());
        strcpy(flight_name, f_name.c_str());
        strcpy(departure_time, dep_time.c_str());
        strcpy(arrival_time, arr_time.c_str());
        strcpy(source, src.c_str());
        strcpy(destination, des.c_str());
        totalSeats = seats;
        availableSeats = seats;
        base_price = price;

        // Set departure date and time
        tm departure_tm = {};
        departure_tm.tm_year = year - 1900;
        departure_tm.tm_mon = month - 1;
        departure_tm.tm_mday = day;

        // Parse departure time (assuming format HH:MM)
        string dep_hour = dep_time.substr(0, 2);
        string dep_min = dep_time.substr(3, 2);
        departure_tm.tm_hour = stoi(dep_hour);
        departure_tm.tm_min = stoi(dep_min);

        departureDateTime = mktime(&departure_tm);
    }

    // Dynamic pricing calculation
    float calculateDynamicPrice(int seatClass, UserTier userTier = REGULAR)
    {

        time_t now = time(nullptr);
        int daysToDeparture = (departureDateTime - now) / (24 * 3600);

        // Demand factor: price increases as seats become scarce
        float demandFactor = 1.0 + (1.0 - (float)availableSeats / totalSeats) * 0.5;

        // Time factor: price increases as departure approaches
        float timeFactor = 1.0;
        if (daysToDeparture <= 7)
            timeFactor = 1.5;
        else if (daysToDeparture <= 14)
            timeFactor = 1.3;
        else if (daysToDeparture <= 21)
            timeFactor = 1.2;
        else if (daysToDeparture <= 28)
            timeFactor = 1.1;

        // Class multiplier
        float classMultiplier = 1.0;
        switch (seatClass)
        {
        case 1:
            classMultiplier = 2.0;
            break; // Business
        case 2:
            classMultiplier = 1.5;
            break; // First
        case 4:
            classMultiplier = 1.2;
            break; // Premium Economy
        default:
            classMultiplier = 1.0;
            break; // Economy
        }

        // Tier discount
        float tierDiscount = 1.0;
        switch (userTier)
        {
        case PLATINUM:
            tierDiscount = 0.8;
            break;
        case GOLD:
            tierDiscount = 0.85;
            break;
        case SILVER:
            tierDiscount = 0.9;
            break;
        default:
            tierDiscount = 1.0;
            break;
        }

        return base_price * demandFactor * timeFactor * classMultiplier * tierDiscount;
    }

    void display_flight()
    {
        cout << "Flight Number: " << flight_number << endl;
        cout << "Flight Name: " << flight_name << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Total Seats: " << totalSeats << endl;
        cout << "Available Seats: " << availableSeats << endl;
        cout << "Departure Time: " << departure_time << endl;
        cout << "Arrival Time: " << arrival_time << endl;
        cout << "Base Fare: " << base_price << "/-" << endl;

        // Show dynamic pricing for different classes
        cout << "Dynamic Pricing:" << endl;
        cout << "  Economy: " << calculateDynamicPrice(3) << "/-" << endl;
        cout << "  Premium Economy: " << calculateDynamicPrice(4) << "/-" << endl;
        cout << "  Business: " << calculateDynamicPrice(1) << "/-" << endl;
        cout << "  First: " << calculateDynamicPrice(2) << "/-" << endl;
    }

    bool bookSeat(int booked, int seatClass, UserTier userTier = REGULAR)
    {
        if (availableSeats >= booked)
        {
            availableSeats -= booked;
            cout << "Seat booked successfully. Dynamic price: " << calculateDynamicPrice(seatClass, userTier) << "/-" << endl;
            return true;
        }
        cout << "Insufficient seats available." << endl;
        return false;
    }

    void cancelBookedSeat(int n)
    {
        if (availableSeats + n <= totalSeats)
        {
            availableSeats += n;
            cout << "Seats cancelled and made available again." << endl;
        }
    }

    // ... existing code ...
    void add_source(string src)
    {
        strcpy(source, src.c_str());
    }

    void add_destination(string des)
    {
        strcpy(destination, des.c_str());
    }

    void update_departure_time(string t)
    {
        strcpy(departure_time, t.c_str());
    }

    void update_arrival_time(string arival)
    {
        strcpy(arrival_time, arival.c_str());
    }

    void update_price(float p)
    {
        base_price = p;
    }
    void update_seats(float s)
    {
        availableSeats = s;
    }

    int get_available_Seats()
    {
        return availableSeats;
    }
    int get_totalSeats()
    {
        return totalSeats;
    }
    float get_price()
    {
        return base_price;
    }
    string get_flight_number()
    {
        return flight_number;
    }
    string get_flight_name()
    {
        return flight_name;
    }
    string get_departure_time()
    {
        return departure_time;
    }
    string get_arrival_time()
    {
        return arrival_time;
    }
    string get_source()
    {
        return source;
    }
    string get_destination()
    {
        return destination;
    }
    time_t get_departure_date_time()
    {
        return departureDateTime;
    }
};

// Enhanced Passenger class with meal and baggage options
class Passenger
{
public:
    char name[10];
    char surname[10];
    char passport_number[10];
    char ticket_number[10];
    int seat_number;
    int flight_class;
    int age;
    int gender;
    int is_special_fare;
    int meal_preference; // 1: Vegetarian, 2: Non-vegetarian, 3: Special diet
    int baggage_weight;  // in kg
    int frequent_flyer_points;

    Passenger() {}
    Passenger(string n, string s, string pn, string tn, int sn, int fc, int a, int g, int iv, int meal = 1, int baggage = 20)
    {
        // Use strncpy to prevent buffer overflow
        strncpy(name, n.c_str(), sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0'; // Ensure null termination

        strncpy(surname, s.c_str(), sizeof(surname) - 1);
        surname[sizeof(surname) - 1] = '\0';

        strncpy(passport_number, pn.c_str(), sizeof(passport_number) - 1);
        passport_number[sizeof(passport_number) - 1] = '\0';

        strncpy(ticket_number, tn.c_str(), sizeof(ticket_number) - 1);
        ticket_number[sizeof(ticket_number) - 1] = '\0';

        seat_number = sn;
        flight_class = fc;
        age = a;
        gender = g;
        is_special_fare = iv;
        meal_preference = meal;
        baggage_weight = baggage;
        frequent_flyer_points = 0;
    }

    // void set_name(const string& name) {
    //     fname = name;
    // }

    void writeToFile_pass(ofstream &outFile) const
    {
        // for integer ke liye
        outFile.write(reinterpret_cast<const char *>(&seat_number), sizeof(seat_number));
        outFile.write(reinterpret_cast<const char *>(&flight_class), sizeof(flight_class));
        outFile.write(reinterpret_cast<const char *>(&age), sizeof(age));
        outFile.write(reinterpret_cast<const char *>(&gender), sizeof(gender));
        outFile.write(reinterpret_cast<const char *>(&is_special_fare), sizeof(is_special_fare));
        outFile.write(reinterpret_cast<const char *>(&meal_preference), sizeof(meal_preference));
        outFile.write(reinterpret_cast<const char *>(&baggage_weight), sizeof(baggage_weight));
        outFile.write(reinterpret_cast<const char *>(&frequent_flyer_points), sizeof(frequent_flyer_points));

        // for string  ke liye
        outFile.write(reinterpret_cast<const char *>(&name), sizeof(name));
        outFile.write(reinterpret_cast<const char *>(&surname), sizeof(surname));
        outFile.write(reinterpret_cast<const char *>(&passport_number), sizeof(passport_number));
        outFile.write(reinterpret_cast<const char *>(&ticket_number), sizeof(ticket_number));
    }

    void readFromFile_pass(ifstream &inFile)
    {
        inFile.read(reinterpret_cast<char *>(&seat_number), sizeof(seat_number));
        inFile.read(reinterpret_cast<char *>(&flight_class), sizeof(flight_class));
        inFile.read(reinterpret_cast<char *>(&age), sizeof(age));
        inFile.read(reinterpret_cast<char *>(&gender), sizeof(gender));
        inFile.read(reinterpret_cast<char *>(&is_special_fare), sizeof(is_special_fare));
        inFile.read(reinterpret_cast<char *>(&meal_preference), sizeof(meal_preference));
        inFile.read(reinterpret_cast<char *>(&baggage_weight), sizeof(baggage_weight));
        inFile.read(reinterpret_cast<char *>(&frequent_flyer_points), sizeof(frequent_flyer_points));

        inFile.read(reinterpret_cast<char *>(&name), sizeof(name));
        inFile.read(reinterpret_cast<char *>(&surname), sizeof(surname));
        inFile.read(reinterpret_cast<char *>(&passport_number), sizeof(passport_number));
        inFile.read(reinterpret_cast<char *>(&ticket_number), sizeof(ticket_number));
    }

    void display_pass() const
    {
        cout << "Name: " << name << " " << surname << ", Passport No: " << passport_number
             << ", Ticket No: " << ticket_number
             << ", Seat No: " << seat_number << ", Flight Class: ";
        if (flight_class == 1)
            cout << "Business Class";
        else if (flight_class == 2)
            cout << "First Class";
        else if (flight_class == 4)
            cout << "Premium Economy";
        else
            cout << "Economy Class";

        cout << ", Age: " << age << ", Gender: " << (gender == 1 ? "Male" : "Female") << ", Special Fare: ";

        if (is_special_fare == 2)
            cout << "Student";
        else if (is_special_fare == 3)
            cout << "Senior Citizen";
        else if (is_special_fare == 4)
            cout << "Armed Forces";
        else if (is_special_fare == 5)
            cout << "Doctor and Nurses";
        else
            cout << "Regular";

        cout << ", Meal: " << (meal_preference == 1 ? "Vegetarian" : meal_preference == 2 ? "Non-vegetarian"
                                                                                          : "Special diet");
        cout << ", Baggage: " << baggage_weight << "kg";
        cout << ", Points: " << frequent_flyer_points << endl;
    }

    // ... existing getter methods ...
    int get_seat_no()
    {
        return seat_number;
    }
    int get_age()
    {
        return age;
    }
    int get_special_fare()
    {
        return is_special_fare;
    }
    string get_fname()
    {
        return name;
    }
    string get_lname()
    {
        return surname;
    }
    string get_passport_no()
    {
        return passport_number;
    }
    string get_ticket_no()
    {
        return ticket_number;
    }
    string get_gender()
    {
        return gender == 1 ? "Male" : "Female";
    }
    int get_meal_preference()
    {
        return meal_preference;
    }
    int get_baggage_weight()
    {
        return baggage_weight;
    }
    int get_frequent_flyer_points()
    {
        return frequent_flyer_points;
    }
    void add_frequent_flyer_points(int points)
    {
        frequent_flyer_points += points;
    }
};

// Enhanced Reservation class with booking ID and priority
class Reservation
{
private:
    char booking_id[20];
    char flight_no[20];
    char flight_name[20];
    char departure[20];
    char arrival[20];
    char flight_date[20];
    char flight_time[20];
    char flight_class[20];
    int trip; //(1,2)
    float fare;
    int priority;
    time_t booking_time;
    vector<Passenger> Pass; // Vector of Passenger objects

public:
    Reservation() {}
    Reservation(string bid, string fno, string fname, string dep, string arr, string fd, string ft, string fc, int trp, float price, vector<Passenger> passengers, int prio = 1) : Pass(passengers), trip(trp), fare(price), priority(prio)
    {
        strncpy(booking_id, bid.c_str(), sizeof(booking_id) - 1);
        booking_id[19] = '\0';

        strncpy(flight_no, fno.c_str(), sizeof(flight_no) - 1);
        flight_no[19] = '\0';

        strncpy(flight_name, fname.c_str(), sizeof(flight_name) - 1);
        flight_name[19] = '\0';

        strncpy(departure, dep.c_str(), sizeof(departure) - 1);
        departure[19] = '\0';

        strncpy(arrival, arr.c_str(), sizeof(arrival) - 1);
        arrival[19] = '\0';

        strncpy(flight_date, fd.c_str(), sizeof(flight_date) - 1);
        flight_date[19] = '\0';

        strncpy(flight_time, ft.c_str(), sizeof(flight_time) - 1);
        flight_time[19] = '\0';

        strncpy(flight_class, fc.c_str(), sizeof(flight_class) - 1);
        flight_class[19] = '\0';

        booking_time = time(nullptr);
    }

    void savetofile_rev(ofstream &file)
    {
        file.write(reinterpret_cast<const char *>(&booking_id), sizeof(booking_id));
        file.write(reinterpret_cast<const char *>(&flight_no), sizeof(flight_no));
        file.write(reinterpret_cast<const char *>(&flight_name), sizeof(flight_name));
        file.write(reinterpret_cast<const char *>(&departure), sizeof(departure));
        file.write(reinterpret_cast<const char *>(&arrival), sizeof(arrival));
        file.write(reinterpret_cast<const char *>(&flight_date), sizeof(flight_date));
        file.write(reinterpret_cast<const char *>(&flight_time), sizeof(flight_time));
        file.write(reinterpret_cast<const char *>(&flight_class), sizeof(flight_class));
        file.write(reinterpret_cast<const char *>(&trip), sizeof(trip));
        file.write(reinterpret_cast<const char *>(&fare), sizeof(fare));
        file.write(reinterpret_cast<const char *>(&priority), sizeof(priority));
        file.write(reinterpret_cast<const char *>(&booking_time), sizeof(booking_time));

        // Save the size of the vector
        size_t passengerCount = Pass.size();
        file.write(reinterpret_cast<const char *>(&passengerCount), sizeof(passengerCount));

        // Save each passenger
        for (Passenger &p : Pass)
        {
            p.writeToFile_pass(file);
        }
    }

    void readfromfile_rev(ifstream &file)
    {
        file.read(reinterpret_cast<char *>(&booking_id), sizeof(booking_id));
        file.read(reinterpret_cast<char *>(&flight_no), sizeof(flight_no));
        file.read(reinterpret_cast<char *>(&flight_name), sizeof(flight_name));
        file.read(reinterpret_cast<char *>(&departure), sizeof(departure));
        file.read(reinterpret_cast<char *>(&arrival), sizeof(arrival));
        file.read(reinterpret_cast<char *>(&flight_date), sizeof(flight_date));
        file.read(reinterpret_cast<char *>(&flight_time), sizeof(flight_time));
        file.read(reinterpret_cast<char *>(&flight_class), sizeof(flight_class));
        file.read(reinterpret_cast<char *>(&trip), sizeof(trip));
        file.read(reinterpret_cast<char *>(&fare), sizeof(fare));
        file.read(reinterpret_cast<char *>(&priority), sizeof(priority));
        file.read(reinterpret_cast<char *>(&booking_time), sizeof(booking_time));

        size_t passengerCount; // Read the size of the vector
        file.read(reinterpret_cast<char *>(&passengerCount), sizeof(passengerCount));
        Pass.resize(passengerCount); // Resize the vector and read each  object

        for (size_t i = 0; i < passengerCount; ++i)
        {
            Pass[i].readFromFile_pass(file);
        }
    }

    void display()
    {
        cout << "Booking ID: " << booking_id << endl;
        cout << "Flight No: " << flight_no << endl;
        cout << "Departure: " << departure << endl;
        cout << "Arrival: " << arrival << endl;
        cout << "Flight Date: " << flight_date << endl;
        cout << "Flight Time: " << flight_time << endl;
        cout << "Flight Class: " << flight_class << endl;
        cout << "Trip: " << ((trip == 1) ? "One Way" : "Round Way") << endl;
        cout << "Fare: " << fare << endl;
        cout << "Priority: " << priority << endl;

        cout << "Passengers: " << endl;
        for (const Passenger &p : Pass)
        {
            p.display_pass();
        }
    }

    // ... existing getter methods ...
    string get_booking_id()
    {
        cout << "--->>> Book Id: " << booking_id << endl;
        return booking_id;
    }
    string get_departure()
    {
        return departure;
    }

    string get_arrival()
    {
        return arrival;
    }

    string get_flight_date()
    {
        return flight_date;
    }

    string get_flight_time()
    {
        return flight_time;
    }
    int get_trip()
    {
        return trip;
    }
    float get_fare()
    {
        return fare;
    }
    int get_no_of_passenger()
    {
        return Pass.size();
    }

    string get_flight_class()
    {
        return flight_class;
    }

    string get_flight_name()
    {
        return flight_name;
    }

    string get_flight_no()
    {
        return flight_no;
    }

    vector<Passenger> get_pass_vector()
    {
        return Pass;
    }

    int get_priority()
    {
        return priority;
    }

    time_t get_booking_time()
    {
        return booking_time;
    }

    // Setter methods for modifying reservation details
    void set_flight_no(string fno)
    {
        strncpy(flight_no, fno.c_str(), sizeof(flight_no) - 1);
        flight_no[19] = '\0';
    }

    void set_flight_name(string fname)
    {
        strncpy(flight_name, fname.c_str(), sizeof(flight_name) - 1);
        flight_name[19] = '\0';
    }

    void set_departure(string dep)
    {
        strncpy(departure, dep.c_str(), sizeof(departure) - 1);
        departure[19] = '\0';
    }

    void set_arrival(string arr)
    {
        strncpy(arrival, arr.c_str(), sizeof(arrival) - 1);
        arrival[19] = '\0';
    }

    void set_flight_date(string fd)
    {
        strncpy(flight_date, fd.c_str(), sizeof(flight_date) - 1);
        flight_date[19] = '\0';
    }

    void set_flight_time(string ft)
    {
        strncpy(flight_time, ft.c_str(), sizeof(flight_time) - 1);
        flight_time[19] = '\0';
    }

    void set_flight_class(string fc)
    {
        strncpy(flight_class, fc.c_str(), sizeof(flight_class) - 1);
        flight_class[19] = '\0';
    }

    void set_fare(float new_fare)
    {
        fare = new_fare;
    }

    void set_trip(int new_trip)
    {
        trip = new_trip;
    }
};

class review {
    string fno;
    vector<int> ratings;

public:
    review() {}

    review(const string &flightNo, int rating) {
        fno = flightNo;
        ratings.push_back(rating);
    }

    string getFlightNo() const {
        return fno;
    }

    void addRating(int rating) {
        ratings.push_back(rating);
    }

    void displayRatings() const {
        if (ratings.empty()) {
            cout << "No ratings yet for flight " << fno << ".\n";
            return;
        }
        double avg = 0.0;
        for (int r : ratings) avg += r;
        avg /= ratings.size();
        cout << "\nAverage rating: " << avg << "\n";
    }

    void writeToFile(ofstream &fout) const {
        fout << fno << " " << ratings.size();
        for (int r : ratings) {
            fout << " " << r;
        }
        fout << "\n";
    }

    void readFromFile(ifstream &fin) {
        ratings.clear();
        fin >> fno;
        if (fin.eof() || !fin) return;

        int count;
        fin >> count;
        for (int i = 0; i < count; ++i) {
            int rating;
            fin >> rating;
            ratings.push_back(rating);
        }
    }

    vector<int> getRatings() const {
    return ratings;
}

};

void reviewMenu() {
    vector<review> allReviews;
    ifstream fin("reviews.txt");

    while (true) {
        review r;
        r.readFromFile(fin);
        if (fin.eof() || !fin) break;
        allReviews.push_back(r);
    }
    fin.close();

    int choice;
    do {
        cout << "\n---- Review Menu ----\n";
        cout << "1. Submit Review\n";
        cout << "2. Check Review of a Flight\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string fno;
            int rating;
            cout << "Enter flight number: ";
            cin >> fno;
            cout << "Enter rating (1 to 5): ";
            cin >> rating;

            bool found = false;
            for (auto &r : allReviews) {
                if (r.getFlightNo() == fno) {
                    r.addRating(rating);
                    found = true;
                    break;
                }
            }

            if (!found) {
                review newReview(fno, rating);
                allReviews.push_back(newReview);
            }

            ofstream fout("reviews.txt");
            for (const auto &r : allReviews) {
                r.writeToFile(fout);
            }
            fout.close();

            cout << "Review submitted successfully!\n";
        }
        else if (choice == 2) {
            string fno;
            cout << "Enter flight number to check reviews: ";
            cin >> fno;

            bool found = false;
            for (const auto &r : allReviews) {
                if (r.getFlightNo() == fno) {
                    r.displayRatings();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "No reviews found for this flight.\n";
            }
        }
        else{
            cout << "\n\nPress any key to continue ... " << endl;
            getch();
            main_menu();
            system("cls");
           break;
        }

    } while (choice != 3);
}

string reviewMenu2(const string& fnoo) {
    vector<review> allReviews;
    ifstream fin("reviews.txt");

    while (true) {
        review r;
        r.readFromFile(fin);
        if (fin.eof() || !fin) break;
        allReviews.push_back(r);
    }
    fin.close();

    for (const auto& r : allReviews) {
        if (r.getFlightNo() == fnoo) {
            if (!r.getRatings().empty()) {
                double avg = 0;
                for (int val : r.getRatings()) avg += val;
                avg /= r.getRatings().size();

                // Return formatted average rating string
                ostringstream oss;
                oss << " \x1B[36m[Rating: " << fixed << setprecision(1) << avg<<"]";
                return oss.str();
            } else {
                return " \x1B[36m[Rating: N/A]\033[0m";
            }
        }
    }
    return " \x1B[36m[No reviews]\033[0m";
}


// Simulated booking function (without threading)
void simulatedBooking(string flightNumber, int seats, int seatClass, UserTier userTier)
{
    cout << "User attempting to book " << seats << " seats on flight " << flightNumber << endl;

    // Find flight and book seats
    fstream file("flight.dat", ios::in | ios::out | ios::binary);
    if (file.is_open())
    {
        Flight f1;
        while (file.read((char *)&f1, sizeof(f1)))
        {
            if (f1.get_flight_number() == flightNumber)
            {
                if (f1.bookSeat(seats, seatClass, userTier))
                {
                    cout << "Successfully booked " << seats << " seats" << endl;

                    // Add to priority queue
                    BookingPriority bp;
                    bp.bookingId = "BK" + to_string(time(nullptr)) + to_string(rand() % 1000);
                    bp.priority = userTier;
                    bp.bookingTime = time(nullptr);
                    bookingQueue.push(bp);
                }
                else
                {
                    cout << "Failed to book seats - insufficient availability" << endl;
                }
                break;
            }
        }
        file.close();
    }
}

// Function to simulate multiple users booking simultaneously
void simulateMultiUserBooking()
{
    cout << "\n=== Simulating Multi-User Booking ===" << endl;

    string flightNumbers[] = {"AI101", "AI102", "AI103"};

    // Simulate multiple users booking sequentially
    for (int i = 0; i < 5; i++)
    {
        string flightNum = flightNumbers[i % 3];
        int seats = (i % 3) + 1;
        int seatClass = (i % 4) + 1;
        UserTier tier = static_cast<UserTier>((i % 4) + 1);

        cout << "\n--- User " << (i + 1) << " ---" << endl;
        simulatedBooking(flightNum, seats, seatClass, tier);
        Sleep(1000); // Simulate processing time
    }

    cout << "\nMulti-user booking simulation completed!" << endl;
    cout << "Press any key to continue..." << endl;
    getch();
}

// Function to generate popular routes report
void generatePopularRoutesReport()
{
    cout << "\n=== Popular Routes Report ===" << endl;

    map<string, int> routeBookings;

    // Read all reservations to count bookings per route
    ifstream file("reservation.dat", ios::binary);
    if (file.is_open())
    {
        Reservation r;
        while (file.peek() != EOF)
        {
            r.readfromfile_rev(file);
            string route = r.get_departure() + " -> " + r.get_arrival();
            routeBookings[route]++;
        }
        file.close();
    }

    // Sort routes by booking count
    vector<pair<string, int>> sortedRoutes;
    for (const auto &route : routeBookings)
    {
        sortedRoutes.push_back(route);
    }

    sort(sortedRoutes.begin(), sortedRoutes.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.second > b.second;
         });

    cout << "\nTop 5 Most Popular Routes:\n";
    cout << "Route\t\t\tBookings\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < min(5, (int)sortedRoutes.size()); i++)
    {
        cout << sortedRoutes[i].first << "\t\t" << sortedRoutes[i].second << endl;
    }

    cout << "\nPress any key to continue..." << endl;
    getch();
}

// ... existing code ...

void welcome() // Welcome Page
{
    ifstream fileopen("AnimationFiles/welcometext.txt"); // Open Welcome text file in Animation Folder
    string line;
    while (getline(fileopen, line)) // Read each line from the file then print
        cout << line << endl;

    // after display all lines of Welcome.txt file the take any input than move forword
    cout << "Press any key to continue ... " << endl;
    getch();
    // system("pause"); // or (we can use also)
    system("cls");
    fileopen.close();
}

void welcome_animation() // for show Flight Animation...
{

    // opens all files
    ifstream f1("AnimationFiles/a1.txt");
    ifstream f2("AnimationFiles/a2.txt");
    ifstream f3("AnimationFiles/a3.txt");
    ifstream f4("AnimationFiles/a4.txt");
    ifstream f5_0("AnimationFiles/a5_0.txt");
    ifstream f5_1("AnimationFiles/a5_1.txt");
    ifstream f5_2("AnimationFiles/a5_2.txt");
    ifstream f5_3("AnimationFiles/a5_3.txt");
    ifstream f5_4("AnimationFiles/a5_4.txt");
    ifstream f5_5("AnimationFiles/a5_5.txt");
    ifstream f6("AnimationFiles/a6.txt");
    ifstream f7("AnimationFiles/a7.txt");
    ifstream f8("AnimationFiles/a8.txt");
    ifstream f9("AnimationFiles/a9.txt");
    ifstream f10("AnimationFiles/a10.txt");
    ifstream f11("AnimationFiles/a11.txt");

    string line;
    //------------------Show Files One By One And Display -------------------------------
    while (getline(f1, line))
        cout << line << endl;
    Sleep(250);    // After show Pause for 0.250 seccond...
    system("cls"); // Clear All screen after display one file ....
                   //-------------------------------------------------
    while (getline(f2, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f3, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f4, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f5_0, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f5_1, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f5_2, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f5_3, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f5_4, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f5_5, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f6, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f7, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f8, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f9, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f10, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    while (getline(f11, line))
        cout << line << endl;
    Sleep(250);
    system("cls");
    //-------------------------------------------------
    // close all file
    f1.close();
    f2.close();
    f3.close();
    f4.close();
    f5_0.close();
    f5_1.close();
    f5_2.close();
    f5_3.close();
    f5_4.close();
    f5_5.close();
    f6.close();
    f7.close();
    f8.close();
    f9.close();
    f10.close();
    f11.close();
}

void print_line(string space, char start, char mid, char end, int length, string end_endl = "\n") // Function to print a line with given characters and length
{
    cout << space << start;
    for (int i = 0; i < length; i++)
        cout << mid;
    cout << end << end_endl;
}

void Exit_msg()
{
    system("cls");
    cout << "\n\n\n\n\n\n\t\t\t\033[1;47;35m                                                    \033[0m\t\t\n";
    cout << "\t\t\t\033[1;47;35m --------------  THANKYOU FOR VISITING  ----------- \033[0m\t\t\n";
    cout << "\t\t\t\033[1;47;35m                                 ~ SVVV Airlines \033[0m\t\t\n\n\n\n\n\n\n";
    exit(0);
}

void login() //  User login function
{
    string username, password;
    cout << "\n\nEnter your username: ";
    cin >> username;
    cout << "Enter your Password: ";
    cin >> password;

    ifstream file("login_detail.txt"); // login Details are saves in "login_detail.txt" file
    if (!file)
    {
        cout << "\n\t\x1B[31mServer Error!! (file not open)\n\033[0m\t\t\n"; // if File not open, pause 2sec and clear screen then return
        Sleep(2000);
        system("cls");
        return;
    }

    string line;

    while (file.eof() == 0) // for searching user name or password
    {
        file >> line;
        if (line == username) // if user name found the move forword
        {
            file >> line;
            if (line == password)
            {
                // if username and password both are found then set username in "login_user" variable for showing username in main manue
                // and then set true in "login_status" for checking login succes or not
                login_status = true;
                login_user = username;
                break;
            }
        }
        else // if username not found then get full remaining line for moveing to file pointer to be end of line
            getline(file, line);
    }

    file.close(); // after user found close file properly

    // checking login status if user found the print massage "Login Success" with green colour then move to "main_manu" function
    // if user not found the print massage "Invalid username or password" with Red color the return to login mainu
    if (login_status)
    {
        cout << "\n\t\033[32m Login Success \033[0m \n\n";
        Sleep(1500);
        system("cls");
        main_menu();
        return;
    }
    else
    {
        cout << "\n\t\x1B[31m Invalid username or password \033[0m";
        Sleep(2000);
        system("cls");
        return;
    }
}

void Add_New_Flight()
{
    // Take all flight data from user
    string f_num, f_name, source, destination, departure_time, arrival_time;
    int capacity;
    float price;
    cin.ignore(); // because skiping first input if this not use then start taking input "flight name" directly
    cout << "\nEnter Flight Number: ";
    getline(cin, f_num);
    cout << "\nEnter Flight Name: ";
    getline(cin, f_name);
    cout << "\nEnter Flight source: ";
    cin >> source;
    cout << "\nEnter Flight destination: ";
    cin >> destination;
    cout << "\nEnter Flight Departure Time(24:00): ";
    cin >> departure_time;

    cout << "\nEnter Flight Arrival Time(24:00): ";
    cin >> arrival_time;

    cout << "\nEnter Flight capacity: ";
    cin >> capacity;
    cout << "\nEnter Price: ";
    cin >> price;

    // Get departure date for dynamic pricing
    cout << "\nEnter Departure Date (DD MM YYYY): ";
    int day, month, year;
    cin >> day >> month >> year;

    // making Flight object f1 with enhanced constructor
    Flight f1(f_num, f_name, departure_time, arrival_time, source, destination, capacity, price, day, month, year);
    // open "flight.dat" binary file (.dat) in append mode ("ios::app")
    ofstream outfile("flight.dat", ios::binary | ios::app);

    if (outfile.is_open())
    {
        // Write f1 flight object in binary file
        outfile.write((char *)&f1, sizeof(f1));
        // then close file
        outfile.close();
        // print massage "New Flight Added Successfully"
        cout << "\n\x1B[32m New Flight Added Successfully\033[0m\t\t\n\n";
        // display f1 object details
        f1.display_flight();
        // get any input for ending of function
        cout << "\n\nPress any key to continue ... " << endl;
        getch();
        // system("pause"); // or (we can use also)
        system("cls");
    }
    else // if file not open
    {
        cout << "\n\t\x1B[31m !Error opening file Unable to add new flight \033[0\n";
        Sleep(1300);
        system("cls");
        return;
    }
}

void Display_All_Flight(int conti = 0)
{
    // conti argument use for not asking "Press any key to continue ..." if argument comming ("1") from function then not asking
    // because if all flight display for in "Update_flight_Detail()" function for only show all flights not return

    ifstream infile("flight.dat", ios::binary | ios::in);
    if (infile.is_open())
    {
        Flight f1;
        while (infile.read(reinterpret_cast<char *>(&f1), sizeof(f1)))
        {
            cout << "\n";
            f1.display_flight();
            cout << "\n";
        }
        infile.close();

        if (!conti) // If only (conti = 0 ) not (conti=1)
        {
            cout << "\n\nPress any key to continue ... " << endl;
            getch();
            // system("pause"); // or (we can use also)
            system("cls");
            return;
        }
    }
    else
    { //  if file not open
        cout << "\n\t\x1B[31mServer Error!! (file not open)\n\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        return;
    }
}

void Update_flight_Detail()
{
    system("cls");
    cout << "\n\033[3;43;30m--- Update Flight Details --- \033[0m\n\n";
    cout << "1. Enter Flight Number" << endl
         << "2. Choice Flights " << endl;
    int choice;
    cout << "Choice : ";
    cin >> choice;
    if (choice == 2)
    {
        cout << "\n\n";
        Display_All_Flight(1); //"Press any key to continue ..."  ye nahi puche isliye 1 arg bhaja
    }
    else if (choice != 2 && choice != 1)
    {
        cout << "\n\t\x1B[31m Invalid Choice!!\n\033[0\n";
        Sleep(2000);
        system("cls");
        return;
    }
    cout << "\n\nPlease Enter the Flight Number: ";
    string flight_number;
    bool found = false;
    cin >> flight_number;
    fstream file;
    file.open("flight.dat", ios::in | ios::out | ios::binary);
    Flight f1;
    file.seekg(0, ios::beg);
    while (file.read((char *)&f1, sizeof(f1)))
    {
        if (f1.get_flight_number() == flight_number)
        {
            found = true;
            while (1)
            {
                cout << "\nWhich of the following you Update ?\n";
                cout << "1. Update Source Place\n";
                cout << "2. Update Destination Place\n";
                cout << "3. Update Departure Time\n";
                cout << "4. Update Arrival Time\n";
                cout << "5. Update Flight Fare\n";
                cout << "6. Update Available Seats\n";
                cout << "7. Go Back\n";

                int choice;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "\nPlease Enter the new Source Place: ";
                    string source_place;
                    cin >> source_place;
                    f1.add_source(source_place);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    // file.write(reinterpret_cast<const char*>(&f1), sizeof(f1)); //or
                    file.write((char *)&f1, sizeof(f1));
                    cout << "\n\n\x1B[32m--- New Source Place Added succes :\033[0m" << source_place << "\n\n";
                    cout << "\033[1;47;35m Updated Flight :\033[0m\t\t\n";
                    f1.display_flight();
                    file.close();
                    cout << "\n\nPress any key to continue ... " << endl;
                    getch();
                    // system("pause"); // or (we can use also)
                    system("cls");
                    return;
                }
                else if (choice == 2)
                {
                    cout << "\nPlease Enter the new Destination Place: ";
                    string destination_place;
                    cin >> destination_place;
                    f1.add_destination(destination_place);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    file.write((char *)&f1, sizeof(f1));
                    cout << "\n\x1B[32mNew Destination Place Added succes : \033[0m" << destination_place << "\n";
                    cout << "\033[1;47;35m Updated Flight :\033[0m\t\t\n";
                    f1.display_flight();
                    file.close();
                    cout << "\n\nPress any key to continue ... " << endl;
                    getch();
                    // system("pause"); // or (we can use also)
                    system("cls");
                    return;
                }
                else if (choice == 3)
                {
                    cout << "\nPlease Enter the new Departure Time(24:00): ";
                    string departure_time;
                    cin >> departure_time;
                    f1.update_departure_time(departure_time);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    file.write((char *)&f1, sizeof(f1));
                    cout << "\n\x1B[32m New Departure Time Update succes :\033[0m" << departure_time << "\n";
                    cout << "\033[1;47;35m Updated Flight :\033[0m\t\t\n";
                    f1.display_flight();
                    file.close();
                    cout << "\n\nPress any key to continue ... " << endl;
                    getch();
                    // system("pause"); // or (we can use also)
                    system("cls");
                    return;
                }
                else if (choice == 4)
                {
                    cout << "\nPlease Enter the new Arrival Time(24:00): ";
                    string arrival_time;
                    cin >> arrival_time;
                    f1.update_arrival_time(arrival_time);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    file.write((char *)&f1, sizeof(f1));
                    cout << "\n\x1B[32m New Arrival Time Update succes :\033[0m" << arrival_time << "\n";
                    cout << "\033[1;47;35m Updated Flight :\033[0m\t\t\n";
                    f1.display_flight();
                    file.close();
                    cout << "\n\nPress any key to continue ... " << endl;
                    getch();
                    // system("pause"); // or (we can use also)
                    system("cls");
                    return;
                }
                else if (choice == 5)
                {
                    cout << "\nPlease Enter the New Flight Fare: ";
                    float price;
                    cin >> price;
                    f1.update_price(price);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    file.write((char *)&f1, sizeof(f1));
                    cout << "\n\x1B[32m New Flight Fare Update succes :\033[0m" << price << "/-\n";
                    cout << "\033[1;47;35m Updated Flight :\033[0m\t\t\n";
                    f1.display_flight();
                    file.close();
                    cout << "\n\nPress any key to continue ... " << endl;
                    getch();
                    // system("pause"); // or (we can use also)
                    system("cls");
                    return;
                }
                else if (choice == 6)
                {
                    cout << "\nPlease Enter the new number of Available Seats: ";
                    int new_available_seats;
                    cin >> new_available_seats;
                    if (new_available_seats < 0 || new_available_seats > f1.get_totalSeats())
                    {
                        cout << "\n\x1B[31mInvalid number of seats! It must be between 0 and " << f1.get_totalSeats() << ".\033[0m\n";
                        Sleep(1300);
                        system("cls");
                        continue;
                    }
                    f1.update_seats(new_available_seats);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    file.write((char *)&f1, sizeof(f1));
                    cout << "\n\x1B[32m Available Seats updated successfully to :\033[0m" << new_available_seats << "\n";
                    cout << "\033[1;47;35m Updated Flight :\033[0m\t\t\n";
                    f1.display_flight();
                    file.close();
                    cout << "\n\nPress any key to continue ... " << endl;
                    getch();
                    system("cls");
                    return;
                }
                else if (choice == 7)
                {
                    file.close();
                    system("cls");
                    return;
                }
                else
                {
                    cout << "\x1B[31mInvalid Choice!! Please Enter Valid Choice \033[0m\n";
                    Sleep(1300);
                    system("cls");
                }
            }
        }
    }
    if (!found)
    {
        cout << "\n\n\t\t\x1B[31mFlight not found!  \033[0m\n\n";
    }
    file.close();
    Sleep(1500);
    system("cls");
}

void Add_Announcement()
{
    ofstream file("flight_announcement.txt", ios::app);

    if (!file)
    {
        cout << "\n\t\x1B[31m Server Error!! (file not open) \n\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        return;
    }
    cout << "\n\033[1m\033[37m\033[1;47;35m" << " Add Flight Announcements : " << "\033[0m" << endl;

    while (1)
    {
        cin.ignore();
        string line;
        cout << "Enter The Announcements : \n";
        getline(cin, line);
        file << line << endl;
        int choice;
        cout << "\nEnter '1' for Add more Announcements , '0' Go Back : ";
        cin >> choice;
        if (choice == 0)
            break;
    }

    file.close();
    cout << "\n\n Press any key to continue ... " << endl;
    getch();
    // system("pause"); // or (we can use also)
    system("cls");
}

void admin_menu()
{

    print_line("\n   ", '\xcd', '\xcd', '\xcd', 43);
    cout << "\t    AIRLINE RESERVATION SYSTEM\n";
    print_line("   ", '\xcd', '\xcd', '\xcd', 43, "\n\n");

    print_line("   ", '\xcd', '\xcd', '\xcd', 7, " ");
    cout << "Administrator Authority";
    print_line(" ", '\xcd', '\xcd', '\xcd', 9, "\n\n");
    cout << "\t\t\t\x1B[33m   Admin: " << administrator_user << "\033[0m\n";

    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 1. Add New Flight\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 2. Display All Flight\n ";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 3. Update flight Detail\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 4. Add Announcement \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 5. Popular Routes Report \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 6. Log Out \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 7. Exit \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);

    print_line("\n   ", '\xcd', '\xcd', '\xcd', 43);

    cout << "   Option : ";
    int option;
    cin >> option;

    if (option == 1) // Add New Flight
    {
        Add_New_Flight();
        admin_menu();
    }
    else if (option == 2) // Display All Flight
    {
        Display_All_Flight();
        admin_menu();
    }
    else if (option == 3) // Update flight Detail
    {
        Update_flight_Detail();
        admin_menu();
    }
    else if (option == 4) // Add Announcement
    {
        Add_Announcement();
        admin_menu();
    }
    else if (option == 5) // Popular Routes Report
    {
        generatePopularRoutesReport();
        admin_menu();
    }
    else if (option == 6) // Log Out
    {
        cout << "\n\t\x1B[32m-- Logout Successfull --\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        login_menu();
    }
    else if (option == 7) // Exit
    {
        Exit_msg();
    }
    else
    {
        cout << "\n\t\t\x1B[31mInvalid Input!!\033[0m\t\t";
        Sleep(1300);
        system("cls");
        admin_menu();
    }
}

void admin_login()
{
    string username, password;
    cout << "\n\nEnter your Admin username: ";
    cin >> username;
    cout << "Enter your Administrator Password: ";
    cin >> password;

    ifstream file("admin_login_detail.txt");
    if (!file)
    {
        cout << "\n\t\x1B[31mServer Error!! (file not open)\n\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        return;
    }
    string line;

    while (file.eof() == 0)
    {
        file >> line;
        if (line == username)
        {
            file >> line;
            if (line == password)
            {
                admin_login_status = true;
                administrator_user = username;
                break;
            }
        }
        else
            getline(file, line);
    }

    file.close();
    if (admin_login_status)
    {
        cout << "\n\t\033[32m Administrator Login Success\033[0m \n\n";
        Sleep(1500);
        system("cls");
        admin_menu();
        return;
    }
    else
    {
        cout << "\n\t\x1B[31mInvalid Administrator username or password \033[0m";
        Sleep(2000);
        system("cls");
        return;
    }
}

void Available_flight(string from, string to, int day, int month, int year, int clas, int trip, int special_fare)
{
    system("cls");
    vector<review> allReviews;
    ifstream fin("reviews.txt");
    while (true)
    {
        review r;
        r.readFromFile(fin);
        if (fin.eof() || !fin)
            break;
        allReviews.push_back(r);
    }
    fin.close();

    string up_from = from;
    string up_to = to;
    for (int i = 0; i < up_from.length(); i++)
    {
        up_from[i] = toupper(up_from[i]);
    }
    for (int i = 0; i < up_to.length(); i++)
    {
        up_to[i] = toupper(up_to[i]);
    }
    cout << "\n\033[1;47;35m Available Flights :   \t\033[0m";
    cout << "\tFrom \x1B[31m" << up_from << "\033[0m To \x1B[31m" << up_to << "\033[0m  on ";
    cout << "\x1B[33m" << day << " ";
    if (month == 1)
        cout << "January";
    else if (month == 2)
        cout << "February";
    else if (month == 3)
        cout << "March";
    else if (month == 4)
        cout << "April";
    else if (month == 5)
        cout << "May";
    else if (month == 6)
        cout << "June";
    else if (month == 7)
        cout << "July";
    else if (month == 8)
        cout << "August";
    else if (month == 9)
        cout << "September";
    else if (month == 10)
        cout << "October";
    else if (month == 11)
        cout << "November";
    else
        cout << "December";
    cout << " " << year << "\033[0m\n\n\n";

    cout << "\t  Flight No.\t Flight Name  \tDeparture Time \t\t\t    Arrive Time\t   Price (Based on select Class)\tRating(out of5)\n";
    cout << "\t ------------------------------------------------------------------------------------------------\n";
    int flight_count = 1;
    ifstream file("flight.dat", ios::binary | ios::in);
    Flight f1;
    bool found_f = false; // agar koi flight nahi mili to
    if (file.is_open())
    {
        while (file.read((char *)&f1, sizeof(f1)))
        {
            if (f1.get_source() == from && f1.get_destination() == to)
            {
                found_f = true;
                //-------------for--departure--time--------------------
                string str_dep_hr_t = f1.get_departure_time();
                string hr_dep_firstTwoDigits = str_dep_hr_t.substr(0, 2);
                int dep_hour = stoi(hr_dep_firstTwoDigits); // Convert to integer

                string str_dep_min_t = f1.get_departure_time();
                string min_dep_lastTwoDigits = str_dep_min_t.substr(str_dep_min_t.length() - 2);
                int dep_min = stoi(min_dep_lastTwoDigits); // Convert to integer

                string str_arr_hr_t = f1.get_arrival_time();
                string hr_arr_firstTwoDigits = str_arr_hr_t.substr(0, 2);
                int arr_hour = stoi(hr_arr_firstTwoDigits); // Convert to integer

                string str_arr_min_t = f1.get_arrival_time();
                string min_arr_lastTwoDigits = str_arr_min_t.substr(str_arr_min_t.length() - 2);
                int arr_min = stoi(min_arr_lastTwoDigits); // Convert to integer

                //-------------get--time----------------------------
                int totalMinutes1 = dep_hour * 60 + dep_min;
                int totalMinutes2 = arr_hour * 60 + arr_min;

                int differenceInMinutes = totalMinutes2 - totalMinutes1;

                int diffHours = differenceInMinutes / 60;   // Get the number of hours
                int diffMinutes = differenceInMinutes % 60; // Get the remaining minutes

                float total_fare_perPerson;
                if (clas == 1) // for Bussines class
                {
                    total_fare_perPerson = f1.get_price() * 2; // (for Bussines class) double price of Economy class
                }
                else if (clas == 2) // for First class
                {
                    int addprice = f1.get_price() * 0.5; // add more 50% of flight price
                    total_fare_perPerson = f1.get_price() + addprice;
                }
                else if (clas == 4) // for Premium Economy
                {
                    int addprice = f1.get_price() * 0.2; // add more 20% of flight price
                    total_fare_perPerson = f1.get_price() + addprice;
                }
                else
                { // Economy class
                    total_fare_perPerson = f1.get_price();
                }

               print_line("\t", char(218), char(196), char(191), 98);
                string fnoo=f1.get_flight_number();
                cout << flight_count << ".\t" << char(179) << "   " << f1.get_flight_number() << "          " << f1.get_flight_name() << "       [\x1B[36m" << from << "\033[0m] " << f1.get_departure_time() << "\x1B[35m     -- " << diffHours << "hr" << diffMinutes << "min --     \033[0m" << f1.get_arrival_time() << " [\x1B[36m" << to << "\033[0m]   \x1B[32m" << total_fare_perPerson << "/-\033[0m \x1B[33m    BOOK NOW\033[0m\t\t\t"<<reviewMenu2(fnoo)<<"\n";
                print_line("\t", char(192), char(196), char(217), 98);

                flight_count++;
            }

        }
        if (!found_f)
        {
            cout << "\n\n\t\t\t\033[1;47;35m No flights available from : \033[0m" << "\033[3;43;30m " << up_from << " \033[0m" << "\033[1;47;35m to \033[0m" << "\033[3;43;30m " << up_to << " \033[0m\n\n\n";
            file.close();

            cout << "\n\nPress any key to continue ... " << endl;
            getch();
            // system("pause"); // or (we can use also)
            system("cls");
            return;
        }

        file.close();

        cout << "\n\t------------------------------------------\033[3;43;30m Book Flight \033[0m--------------------------------------------\n\n";
        string booked_flight_no;
        // string booked_flight_name;
        while (1)
        {
            cout << "Enter the Flight No. You want to book : ";
            cin >> booked_flight_no;
            bool find = false;
            ifstream file("flight.dat", ios::binary | ios::in);
            while (file.read((char *)&f1, sizeof(f1)))
            {
                if (f1.get_flight_number() == booked_flight_no)
                {
                    find = true;
                    // booked_flight_name = f1.get_flight_name();
                    break;
                }
            }
            if (!find)
            {
                cout << "\n\t\x1B[31mInvalid Flight No. Please Enter corect Flight No.\n\033[0m\t\t\n";
            }
            else
            {
                break;
            }
        }
        file.close();

        //------------------print available flight seates------------------
        cout << "\n\t\t\t---------------------\033[3;43;30m Available Seats Chart \033[0m---------------------\n\n";

        int curr_seat = f1.get_available_Seats();
        int t_seat = f1.get_totalSeats();

        int split = 5;
        if (t_seat <= 100)
            split = 5;
        else if (t_seat <= 400)
            split = 10;
        else if (t_seat <= 800)
            split = 20;
        else
            split = 30;

        int count = 0;
        cout << "\t\t";
        for (int i = 1; i <= t_seat; i++)
        {
            if (count < (t_seat - curr_seat))
            {
                cout << "  \x1B[31m" << char(254) << " \033[0m" << i << " "; // red seats
                count++;
            }
            else
            {
                cout << "  \x1B[32m" << char(254) << " \033[0m" << i << " "; // green seats
            }

            if (i % split == 0 && i != t_seat)
            {
                cout << "\n\t\t";
            }
        }

        print_line("\n", '-', '-', '-', 104);
        cout << "\n  \x1B[32m" << char(254) << " \033[0m Available Seat" << "\t\t Total Seats: \x1B[33m" << t_seat << "\033[0m\n";
        cout << "  \x1B[31m" << char(254) << " \033[0m Seat Full " << "\t\t\t Available Seats: \x1B[33m" << curr_seat << "\033[0m\n\n";
        print_line("", '-', '-', '-', 104, "\n\n");

        while (1)
        {
            cout << "Enter The choice : 1.\x1B[35m Book Now\033[0m\n\t\t   2.\x1B[35m GO Back \033[0m\n";
            int choice;
            cout << "Choice : ";
            cin >> choice;
            if (choice == 1)
            {
                break;
            }
            else if (choice == 2)
            {
                system("cls");
                return;
            }
            else
            {
                cout << "\n\t\x1B[31mInvalid Choice Please Enter corect choice\033[0m\t\t\n\n";
            }
        }

        if (curr_seat <= 0)
        {
            cout << "\n\t\x1B[31m Regret!  Seats are Not Available \033[0m\t\t\n\n";
            system("pause");
            system("cls");
            return;
        }

        cout << "\n------------------------------------------\033[3;43;30m Passenger Details \033[0m---------------------------------------------\n\n";

        string first_name, last_name, passport_no, ticket_n;
        int age, gender, no_of_Passengers;

        vector<Passenger> pass;

        while (1)
        {

            cout << "Enter the no. of Passengers : ";
            cin >> no_of_Passengers;
            if (no_of_Passengers > 0 && no_of_Passengers <= curr_seat)
            {
                break;
            }
            else if (no_of_Passengers > curr_seat)
            {
                cout << "\n\t\x1B[31m Sorry! \033[0m" << "\x1B[32m" << no_of_Passengers << "\033[0m" << "\x1B[31m Seats are Not Available \033[0m\t\t\n\n";
            }
            else
            {
                cout << "\n\t\x1B[31m Invalid Input Please Enter Valid Input \033[0m\t\t\n\n";
            }
        }

        int seat_no = (t_seat - curr_seat) + 1;

        for (int i = 1; i <= no_of_Passengers; i++)
        {

            cout << "\nEnter First Name of Passenger " << i << " : ";
            cin >> first_name;
            cout << "Enter Last Name of Passenger " << i << " : ";
            cin >> last_name;
            cout << "Enter Passport No. of Passenger " << i << " : ";
            cin >> passport_no;
            while (1)
            {
                cout << "Enter Age of Passenger " << i << " : ";
                cin >> age;
                if (age < 0 || age > 100)
                    cout << "\n\t\x1B[31m Invalid Age Please Enter Valid Age \033[0m\n\n";
                else
                    break;
            }
            cout << "Enter Gender of Passenger (1. Male 2. Female) : ";
            cin >> gender;

            // Meal preference selection
            cout << "Select Meal Preference:\n";
            cout << "1. Vegetarian\n";
            cout << "2. Non-vegetarian\n";
            cout << "3. Special diet\n";
            int meal_pref;
            cin >> meal_pref;

            // Baggage selection
            cout << "Enter Baggage Weight (in kg, max 30kg): ";
            int baggage_weight;
            cin >> baggage_weight;
            if (baggage_weight > 30)
            {
                cout << "Baggage weight exceeds limit. Setting to 30kg.\n";
                baggage_weight = 30;
            }

            ticket_n = booked_flight_no + to_string(seat_no) + to_string(clas) + to_string(age) + to_string(i); // generate unique Ticket no.

            Passenger p1(first_name, last_name, passport_no, ticket_n, seat_no, clas, age, gender, special_fare, meal_pref, baggage_weight);
            seat_no++;
            ofstream file("passenger.dat", ios::binary | ios::app);
            p1.writeToFile_pass(file);
            pass.push_back(p1);
            file.close();
            cout << "\n\033[1;47;35m  Display Passenger Details \t\033[0m\n";
            p1.display_pass();
        }
        //------------------class----------------------------------------
        string f_class;
        if (clas == 1)
            f_class = "Business Class";
        else if (clas == 2)
            f_class = "First Class";
        else if (clas == 4)
            f_class = "Premium Economy";
        else
            f_class = "Economy Class";

        string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

        //------------------------------Dynamic Pricing Calculation---------------------------------
        // Get user tier (for now defaulting to REGULAR, can be enhanced with user login system)
        UserTier userTier = REGULAR;

        // Calculate dynamic price based on demand, time, class, and user tier
        float total_fare_perPerson = f1.calculateDynamicPrice(clas, userTier);

        // Add baggage charges if exceeding free allowance
        float baggage_charge = 0;
        for (size_t i = 0; i < pass.size(); i++)
        {
            if (pass[i].get_baggage_weight() > 20)
            {                                                               // Free allowance is 20kg
                baggage_charge += (pass[i].get_baggage_weight() - 20) * 10; // $10 per kg extra
            }
        }
        total_fare_perPerson += baggage_charge;

        //------------------------------ Create Reservation Class Object "reserv" ----------------------------
        // Generate unique booking ID
        string booking_id = "BK" + to_string(time(nullptr)) + to_string(rand() % 1000);

        // Add to priority queue
        BookingPriority bp;
        bp.bookingId = booking_id;
        bp.priority = userTier;
        bp.bookingTime = time(nullptr);
        bookingQueue.push(bp);

        Reservation reserv(booking_id, booked_flight_no, f1.get_flight_name(), from, to, date, f1.get_departure_time(), f_class, trip, total_fare_perPerson, pass, userTier);
        ofstream file1("reservation.dat", ios::binary | ios::app);
        reserv.savetofile_rev(file1); // store all data of obj in binary file
        file1.close();

        string get_departure = from;
        string get_arrival = to;
        string get_flight_time = f1.get_departure_time();
        string booked_flight_name = f1.get_flight_name();
        float fare = total_fare_perPerson;

        //-----------------Update the No. of seats in booked Flight -------------------------------
        fstream file("flight.dat", ios::in | ios::out | ios::binary);
        file.seekg(0, ios::beg);
        while (file.read((char *)&f1, sizeof(f1)))
        {
            if (f1.get_flight_number() == booked_flight_no)
            {
                f1.bookSeat(no_of_Passengers, clas, REGULAR);
                file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                file.write((char *)&f1, sizeof(f1));
                file.close();
                break;
            }
        }
        file.close();
        //-------------------------------------------------------------------

        // ofstream file2("ticket.txt");
        // file2 << "-------- SVVV-AIRLINES ----------" << endl;
        // file2 << "Ticket no. : " << " " << ticket_n << endl;
        // file2 << "Flight no. : " << booked_flight_no << endl;
        // file2 << "from : " << from << " To : " << to << endl;
        // file2 << "Seat no. : " << (t_seat - curr_seat) + 1 << endl;
        // file2 << "Name : " << first_name << " " << last_name << endl;
        // file2 << "Gender : " << gender << endl;
        // file2 << "Age : " << age <<"\n\n";
        // file2.close();

        //-----------------------------------------------------------------------

        // Changing into Upper Case
        for (auto &x : get_departure)
            x = toupper(x);
        for (auto &x : get_arrival)
            x = toupper(x);

        //-----------------------------------------------------------------------
        cout << "\n\t\t\t      --------------------- \033[1;47;35m Your Booked Tickets \033[0m ---------------------\n";

        print_line("\n\n\t", char(218), char(196), char(191), 104);
        cout << "\t|                               From \x1B[31m" << get_departure << "\033[0m to \x1B[31m" << get_arrival << "\033[0m on \x1B[33m" << date << "  " << get_flight_time << "                          \033[0m\t |\n";
        print_line("\t", '|', char(196), '|', 104);

        cout << "\t|  Flight No   : \x1B[36m" << booked_flight_no << "\033[0m                              Flight Class : \x1B[35m" << f_class << "\033[0m    Trip : \x1B[35m" << ((trip == 1) ? "One Way   " : "Round Trip") << "\033[0m       |\n";
        cout << "\t|  Flight Name : \x1B[36m" << booked_flight_name << "\033[0m                            Travellers   : \x1B[32m" << pass.size() << "\033[0m" << " \t         Flight Fare : \x1B[32m" << fare << "/-\033[0m    |\n";

        print_line("\t", '|', '-', '|', 104);
        cout << "\t| Passengers Name     |     Ticket No.     |    Seat No.    |   PassPort NO.    |     Gender  |   Age    |\n";
        cout << "\t|                                                                                                        |\n";
        for (int i = 0; i < pass.size(); i++)
        {
            int l1 = 17 - ((pass[i].get_fname()).length() + (pass[i].get_lname()).length()); // for maintain spaces
            cout << "\t| " << i + 1 << ". " << pass[i].get_fname() << " " << pass[i].get_lname();
            print_line("", ' ', ' ', ' ', l1, "   ");
            cout << pass[i].get_ticket_no() << "              " << pass[i].get_seat_no() << ((pass[i].get_seat_no() < 9) ? " " : "") << "               " << pass[i].get_passport_no() << "              " << pass[i].get_gender() << "       " << pass[i].get_age() << "     |\n";
        }

        float discount;
        if (special_fare == 2)
            discount = 500;
        else if (special_fare == 3)
            discount = 1000;
        else if (special_fare == 4)
            discount = 1200;
        else if (special_fare == 5)
            discount = 1200;
        else
            discount = 0;

        print_line("\t", '|', '-', '|', 104);

        cout << "\t|                                                           Fare of (" << pass.size() << " Travellers) : \x1B[31m" << fare * pass.size() << "/-\033[0m" << ((fare * pass.size() > 9999) ? "\t\t " : "\t\t ") << "|\n";
        cout << "\t|                                                                        Discount  : \x1B[31m" << discount << "/-\033[0m" << ((discount > 449) ? "\t\t " : "\t\t ") << "|\n";
        cout << "\t|                                                              Total Payable Amount: \x1B[32m" << fare * pass.size() - discount << "/-\033[0m" << ((fare * pass.size() - discount > 9999) ? "\t\t " : "\t\t ") << "|\n";
        print_line("\t", char(192), char(196), char(217), 104);
        reviewMenu();
        return;
    }
    else
    {
        cout << "\n\t\x1B[31mServer Error!! (file not open)\n\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        return;
    }
}

void Book_Flight_Ticket()
{
    cout << "\n\033[1;47;35m      Enter Flight Detail     \033[0m\n\n";
    cin.ignore();
    string departure, arrival;
    cout << "Enter the Departure Place: ";
    // getline(cin, departure);
    cin >> departure;
    cout << "Enter the Arrival Place: ";
    // getline(cin, arrival);
    cin >> arrival;
    cout << "Enter the Departure Date (DD/MM/YYYY): ";
    int day, month, year;
    char c;
    scanf("%d%c%d%c%d", &day, &c, &month, &c, &year);

    while (1)
    { // for check valid day
        if (day > 31 || day < 1)
        {
            cout << "\n\t\x1B[31m Invalid *Day* \033[0m\n\n";
            cout << "Enter valid 'DAY' (1-31) : ";
            cin >> day;
        }
        else
        {
            break;
        }
    }
    while (1)
    { // for check valid month
        if (month > 12 || month < 1)
        {
            cout << "\n\t\x1B[31m Invalid *Month* \033[0m\n\n";
            cout << "Enter valid 'MONTH' (1-12) : ";
            cin >> month;
        }
        else
        {
            break;
        }
    }

    time_t now = time(0);      // Get the current time
    tm *ltm = localtime(&now); // Convert to local time

    int yr = 1900 + ltm->tm_year; // tm_year is years since 1900
    // cout << "Current Year: " << yr << std::endl;

    while (1) // for check valid years
    {
        if (year != yr)
        {
            cout << "\n\t\x1B[31m Invalid *Year* \033[0m\n\n";
            cout << "Enter valid 'Year' (" << yr << ") : ";
            cin >> year;
        }
        else
        {
            break;
        }
    }

    cout << "\nChoices Class :\n";
    cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << "  " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << "  " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << "  " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
    cout << char(186) << "\x1B[33m 1. Business Class \033[0m" << char(186) << "  " << char(186) << "\x1B[35m  2. First Class   \033[0m" << char(186) << "  " << char(186) << "\x1B[32m 3. Economy Class  \033[0m" << char(186) << "  " << char(186) << "\x1B[31m 4. Premium Economy \033[0m" << char(186) << endl;
    cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "  " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "  " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "  " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "\n";

    int clas;

    while (1)
    {
        cout << "\nChoice : ";
        cin >> clas;
        if (clas < 0 || clas > 4)
        {
            cout << "\n\t\x1B[31mInvalid Choice Please Enter valid choice \033[0m\n";
        }
        else
        {
            break;
        }
    }

    cout << "\n\n\033[1;47;35m Select a special fare: \033[0m" << "\033[3;43;30m 1. Regular       \033[0m" << "\033[3;42;32m 2. Student                 \033[0m" << "\033[3;43;30m 3. Senior Citizen  \033[0m" << "\033[3;42;32m 4. Armed Forces    \033[0m" << "\033[3;43;30m 5. Doctor and Nurses  \033[0m  ";
    cout << "\n\033[1;47;35m   * EXTRA SAVINGS *    \033[0m" << "\033[3;43;30m    Regular fares \033[0m" << "\033[3;42;32m    Extra discounts/baggage \033[0m" << "\033[3;43;30m    Up to $500 off  \033[0m" << "\033[3;42;32m    Up to $600 off  \033[0m" << "\033[3;43;30m    Up to $600 off     \033[0m \n\n";

    int special_fare;
    while (1)
    {
        cout << "Choice : ";
        cin >> special_fare;
        if (special_fare < 0 || special_fare > 5)
        {
            cout << "\n\t\x1B[31mInvalid Choice Please Enter valid choice \033[0m\n\n";
        }
        else
        {
            break;
        }
    }

    cout << "\nEnter Your 'Trip' type :    1.\x1B[35m" << char(248) << "One Way \033[0m 2.\x1B[35m" << char(248) << "Round Trip\033[0m\n";
    int trip_type;
    while (1)
    {
        cout << "Choice : ";
        cin >> trip_type;
        if (trip_type != 1 && trip_type != 2)
        {
            cout << "\n\t\x1B[31mInvalid Choice Please Enter valid choice \033[0m\n\n";
        }
        else
        {
            break;
        }
    }

    Available_flight(departure, arrival, day, month, year, clas, trip_type, special_fare);
    main_menu();
}

bool My_Bookings(int dis = 0)
{
    if (!dis)
    {
        system("cls");
    }
    cout << "\n\t\t\t      --------------------- \033[1;47;35m My Bookings \033[0m ---------------------\n";

    Reservation R1;
    ifstream file("reservation.dat", ios::binary | ios::in);
    if (!file)
    {
        cerr << " Error opening file! " << endl;
        Sleep(2000);
        return 0;
    }

    bool ticket_found = false;

    while (file.peek() != EOF)
    {

        R1.readfromfile_rev(file);
        ticket_found = true;
        int trip = R1.get_trip();
        vector<Passenger> pass_obj = R1.get_pass_vector();

        int is_special_fare = pass_obj[1].get_special_fare();

        float fare = R1.get_fare();

        string get_departure = R1.get_departure();
        string get_arrival = R1.get_arrival();
        // upper case me change karne ke liye
        for (auto &x : get_departure)
            x = toupper(x);
        for (auto &x : get_arrival)
            x = toupper(x);

        print_line("\n\n\t", char(218), char(196), char(191), 104);
        cout << "\t|                               From \x1B[31m" << get_departure << "\033[0m to \x1B[31m" << get_arrival << "\033[0m on \x1B[33m" << R1.get_flight_date() << "  " << R1.get_flight_time() << "                          \033[0m\t |\n";
        print_line("\t", '|', char(196), '|', 104);

        cout << "\t|  Flight No   : \x1B[36m" << R1.get_flight_no() << "\033[0m                              Flight Class : \x1B[35m" << R1.get_flight_class() << "\033[0m    Trip : \x1B[35m" << ((trip == 1) ? "One Way   " : "Round Trip") << "\033[0m       |\n";
        cout << "\t|  Flight Name : \x1B[36m" << R1.get_flight_name() << "\033[0m                            Travellers   : \x1B[32m" << pass_obj.size() << "\033[0m" << " \t         Flight Fare : \x1B[32m" << fare << "/-\033[0m    |\n";

        print_line("\t", '|', '-', '|', 104);

        cout << "\t| Passengers Name     |     Ticket No.     |    Seat No.    |    PassPort NO.    |    Gender  |   Age    |\n";
        cout << "\t|                                                                                                        |\n";
        for (int i = 0; i < pass_obj.size(); i++)
        {
            int l1 = 17 - ((pass_obj[i].get_fname()).length() + (pass_obj[i].get_lname()).length()); // for maintain spaces
            cout << "\t| " << i + 1 << ". " << pass_obj[i].get_fname() << " " << pass_obj[i].get_lname();
            print_line("", ' ', ' ', ' ', l1, "   ");
            cout << pass_obj[i].get_ticket_no() << "              " << pass_obj[i].get_seat_no() << ((pass_obj[i].get_seat_no() < 9) ? " " : "") << "               " << pass_obj[i].get_passport_no() << "              " << pass_obj[i].get_gender() << "       " << pass_obj[i].get_age() << "     |\n";
        }

        float discount;
        if (is_special_fare == 2)
            discount = 500;
        if (is_special_fare == 3)
            discount = 1000;
        if (is_special_fare == 4)
            discount = 1200;
        else
            discount = 0;

        print_line("\t", '|', '-', '|', 104);

        cout << "\t|                                                           Fare of (" << pass_obj.size() << " Travellers) : \x1B[31m" << fare * pass_obj.size() << "/-\033[0m" << ((fare * pass_obj.size() > 9999) ? "\t\t " : "\t\t ") << "|\n";
        cout << "\t|                                                                        Discount  : \x1B[31m" << discount << "/-\033[0m" << ((discount > 449) ? "\t\t " : "\t\t ") << "|\n";
        cout << "\t|                                                              Total Payable Amount: \x1B[32m" << fare * pass_obj.size() - discount << "/-\033[0m" << ((fare * pass_obj.size() - discount > 9999) ? "\t\t " : "\t\t ") << "|\n";

        print_line("\t", char(192), char(196), char(217), 104);
    }

    if (!ticket_found && !dis)
    {
        cout << "\n\n\n\t\t        --------------------- \033[1;47;34m No Any Booking Available \033[0m ---------------------\n\n\n";
    }
    file.close();
    if (!dis)
    {
        cout << "\n\nPress any key to continue ... " << endl;
        getch();
        // system("pause"); // or (we can use also)
        system("cls");
        return 0;
    }
    else
    {
        return ticket_found;
    }
}

void Cancel_Ticket()
{
    system("cls");
    cout << "\n\033[3;43;30m--- Flight Ticket Cancellation --- \033[0m\n\n";
    cout << "1. Enter Reservation Details you want to Cancel " << endl
         << "2. Choice Bookings " << endl;
    int choice;
    cout << "Choice : ";
    cin >> choice;
    bool found_ticket;
    if (choice == 2)
    {
        cout << "\n\n";
        found_ticket = My_Bookings(1); //"Press any key to continue ..."  ye nahi puche isliye 1 arg bhaja
    }
    else if (choice != 2 && choice != 1)
    {
        cout << "\n\t\x1B[31m Invalid Choice!!\n\033[0m\n";
        Sleep(2000);
        system("cls");
        return;
    }
    else // for choice '1'
    {
        found_ticket = My_Bookings(1);
        system("cls");
        cout << "\033[3;43;30m--- Flight Ticket Cancellation --- \033[0m\n\n";
    }

    if (found_ticket)
    {
        cout << "\n\nPlease Enter the Flight Number And Date of Reservation (DD:MM:YYYY) You Want to Cencel : \n\n";
        string flight_number;
        string date;
        cout << "Flight Number : ";
        cin >> flight_number;
        cout << "Date of Reservation (DD/MM/YYYY) : ";
        cin >> date;

        ofstream Temp("Temp.dat", ios::binary | ios::app);
        ifstream infile("reservation.dat", ios::binary);

        if (!infile.is_open() || !Temp.is_open())
        {
            cerr << "Error opening file." << endl;
            return;
        }

        Reservation R1;
        bool found = false;
        int no_of_passenger = 0;
        int one = 1;
        while (infile.read(reinterpret_cast<char *>(&R1), sizeof(R1)))
        {
            if (R1.get_flight_no() == flight_number && R1.get_flight_date() == date)
            {
                found = true;
                if (one == 1) // only ones time run
                {
                    // R1.readfromfile_rev(infile);
                    no_of_passenger = R1.get_no_of_passenger();
                    cout << "NO. of passenger: " << no_of_passenger << "\n";
                    one = 0;
                }
            }
            else
            {
                Temp.write(reinterpret_cast<char *>(&R1), sizeof(R1));
            }
        }

        Temp.close();
        infile.close();

        if (found)
        {
            remove("reservation.dat");
            rename("Temp.dat", "reservation.dat");

            //-----------------Update the No. of seats in booked Flight -------------------------------
            fstream file("flight.dat", ios::in | ios::out | ios::binary);
            file.seekg(0, ios::beg);
            Flight f1;
            while (file.read((char *)&f1, sizeof(f1)))
            {
                if (f1.get_flight_number() == flight_number)
                {
                    // f1.bookSeat(no_of_Passengers);
                    f1.cancelBookedSeat(no_of_passenger);
                    file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    file.write((char *)&f1, sizeof(f1));
                    file.close();
                    break;
                }
            }
            file.close();

            cout << "\n\n\t\x1B[32m Reservation with flight number\033[0m \x1B[31m" << flight_number << "\033[0m \x1B[32mAnd Flight Date \033[0m\x1B[31m" << date << "\033[0m\x1B[32m deleted successfully. \033[0m" << endl;

            cout << "\n\t\x1B[32m Flight Ticket Cencled Successfully!! \033[0m\n";
        }
        else
        {
            remove("Temp.dat");
            cout << "\n\n\t\x1B[31m Reservation with flight number\033[0m \x1B[32m" << flight_number << "\033[0m \x1B[31mAnd Flight Date \033[0m\x1B[32m" << date << "\033[0m\x1B[31m not found.\033[0m" << endl;
        }
    }
    else
    {
        cout << "\n\n\n\t\t        --------------------- \033[1;47;34m No Any Booking Available \033[0m ---------------------\n\n\n";
    }
    cout << "\n\nPress any key to continue ... " << endl;
    getch();
    // system("pause"); // or (we can use also)
    system("cls");
    return;
}

/*void Modify_Ticket()
{
    system("cls");
    cout << "\n\033[3;43;30m--- Flight Ticket Modification --- \033[0m\n\n";
    cout << "1. Enter Reservation Details you want to Modify " << endl
         << "2. Choice Bookings " << endl;
    int choice;
    cout << "Choice : ";
    cin >> choice;
    bool found_ticket;
    if (choice == 2)
    {
        cout << "\n\n";
        found_ticket = My_Bookings(1); //"Press any key to continue ..."  ye nahi puche isliye 1 arg bhaja
    }
    else if (choice != 2 && choice != 1)
    {
        cout << "\n\t\x1B[31m Invalid Choice!!\n\033[0m\n";
        Sleep(2000);
        system("cls");
        return;
    }
    else // for choice '1'
    {
        found_ticket = My_Bookings(1);
        system("cls");
        cout << "\033[3;43;30m--- Flight Ticket Modification --- \033[0m\n\n";
    }

    if (found_ticket)
    {
        cout << "\n\nPlease Enter the Flight Number And Date of Reservation (DD/MM/YYYY) You Want to Modify : \n\n";
        string flight_number;
        string date;
        cout << "Flight Number : ";
        cin >> flight_number;
        cout << "Date of Reservation (DD/MM/YYYY) : ";
        cin >> date;

        // Find the reservation to modify
        ifstream infile("reservation.dat", ios::binary);
        if (!infile.is_open())
        {
            cerr << "Error opening reservation file." << endl;
            return;
        }

        Reservation R1;
        bool found = false;
        int reservation_position = 0;

        // Find the reservation
        while (infile.peek() != EOF)
        {
            R1.readfromfile_rev(infile);
            if (R1.get_flight_no() == flight_number && R1.get_flight_date() == date)
            {
                found = true;
                break;
            }
            reservation_position++;
        }
        infile.close();

        if (found)
        {
            cout << "\n\x1B[32mReservation Found!\033[0m\n";
            cout << "Current Details:\n";
            cout << "Flight: " << R1.get_flight_no() << " (" << R1.get_flight_name() << ")\n";
            cout << "Route: " << R1.get_departure() << " to " << R1.get_arrival() << "\n";
            cout << "Date: " << R1.get_flight_date() << " at " << R1.get_flight_time() << "\n";
            cout << "Class: " << R1.get_flight_class() << "\n";
            cout << "Current Fare: $" << R1.get_fare() << "\n\n";

            // Show modification options
            cout << "What would you like to modify?\n";
            cout << "1. Flight Number (Select from available flights)\n";
            cout << "2. Departure Location\n";
            cout << "3. Arrival Location\n";
            //cout << "4. Date\n";
            cout << "5. Time\n";
            cout << "6. Flight Class\n";
            cout << "7. Trip Type (One Way/Round Trip)\n";
            cout << "8. Cancel Modification\n";

            int modify_choice;
            cout << "Enter your choice (1-8): ";
            cin >> modify_choice;

            if (modify_choice >= 1 && modify_choice <= 7)
            {
                // Store original values for seat adjustment
                string original_flight_no = R1.get_flight_no();
                int original_passengers = R1.get_no_of_passenger();
                string original_class = R1.get_flight_class();

                // Free up seats from original flight and show visual change
                fstream flight_file("flight.dat", ios::in | ios::out | ios::binary);
                if (flight_file.is_open())
                {
                    Flight f1;
                    while (flight_file.read((char *)&f1, sizeof(f1)))
                    {
                        if (f1.get_flight_number() == original_flight_no)
                        {
                            cout << "\n\x1B[33mFreeing seats from original flight " << original_flight_no << "...\033[0m\n";
                            cout << "Seats changing from \x1B[31mRED (Occupied)\033[0m to \x1B[32mGREEN (Available)\033[0m\n";
                            f1.cancelBookedSeat(original_passengers);
                            flight_file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                            flight_file.write((char *)&f1, sizeof(f1));
                            break;
                        }
                    }
                    flight_file.close();
                }

                // Apply modifications
                switch (modify_choice)
                {
                    case 1: // Flight Number - Show available flights for selection
                    {
                        cout << "\n\x1B[36m=== Available Flights for Selection ===\033[0m\n\n";

                        // Display all available flights
                        ifstream flight_display("flight.dat", ios::binary);
                        if (!flight_display.is_open())
                        {
                            cout << "\n\x1B[31mError opening flight file!\033[0m\n";
                            return;
                        }

                        Flight display_flight;
                        vector<Flight> available_flights;
                        int flight_count = 0;

                        cout << "No. | Flight No | Flight Name      | From      | To        | Date       | Time   | Available Seats | Price\n";
                        cout << "----|-----------|------------------|-----------|-----------|------------|--------|-----------------|-------\n";

                        while (flight_display.read((char *)&display_flight, sizeof(display_flight)))
                        {
                            if (display_flight.get_available_Seats() >= original_passengers)
                            {
                                flight_count++;
                                available_flights.push_back(display_flight);

                                cout << setw(3) << flight_count << " | ";
                                cout << setw(9) << display_flight.get_flight_number() << " | ";
                                cout << setw(16) << display_flight.get_flight_name() << " | ";
                                cout << setw(9) << display_flight.get_source() << " | ";
                                cout << setw(9) << display_flight.get_destination() << " | ";
                                cout << setw(10) << "DD/MM/YYYY" << " | ";
                                cout << setw(6) << display_flight.get_departure_time() << " | ";
                                cout << setw(15) << display_flight.get_available_Seats() << " | ";
                                cout << "$" << display_flight.calculateDynamicPrice(1, REGULAR) << "\n";
                            }
                        }
                        flight_display.close();

                        if (available_flights.empty())
                        {
                            cout << "\n\x1B[31mNo flights available with sufficient seats!\033[0m\n";
                            return;
                        }

                        int selected_flight;
                        cout << "\nEnter the flight number (1-" << flight_count << ") to select: ";
                        cin >> selected_flight;

                        if (selected_flight < 1 || selected_flight > flight_count)
                        {
                            cout << "\n\x1B[31mInvalid flight selection!\033[0m\n";
                            return;
                        }

                        Flight selected = available_flights[selected_flight - 1];
                        string new_flight_no = selected.get_flight_number();

                        cout << "\n\x1B[32mSelected Flight: " << new_flight_no << " (" << selected.get_flight_name() << ")\033[0m\n";
                        cout << "Seats changing from \x1B[32mGREEN (Available)\033[0m to \x1B[31mRED (Occupied)\033[0m\n";

                        R1.set_flight_no(new_flight_no);
                        R1.set_flight_name(selected.get_flight_name());
                        R1.set_departure(selected.get_source());
                        R1.set_arrival(selected.get_destination());
                        break;
                    }
                    case 2: // Departure Location
                    {
                        cout << "Enter new Departure Location: ";
                        string new_departure;
                        cin >> new_departure;
                        R1.set_departure(new_departure);
                        break;
                    }
                    case 3: // Arrival Location
                    {
                        cout << "Enter new Arrival Location: ";
                        string new_arrival;
                        cin >> new_arrival;
                        R1.set_arrival(new_arrival);
                        break;
                    }
                    case 4: // Date
                    {
                        cout << "Enter new Date (DD/MM/YYYY): ";
                        string new_date;
                        cin >> new_date;
                        R1.set_flight_date(new_date);
                        break;
                    }
                    case 5: // Time
                    {
                        cout << "Enter new Time (HH:MM): ";
                        string new_time;
                        cin >> new_time;
                        R1.set_flight_time(new_time);
                        break;
                    }
                    case 6: // Flight Class
                    {
                        cout << "Select new Flight Class:\n";
                        cout << "1. Economy\n";
                        cout << "2. Premium Economy\n";
                        cout << "3. Business\n";
                        cout << "4. First Class\n";
                        int new_class_choice;
                        cin >> new_class_choice;

                        string new_class;
                        switch (new_class_choice)
                        {
                            case 1: new_class = "Economy"; break;
                            case 2: new_class = "Premium Economy"; break;
                            case 3: new_class = "Business"; break;
                            case 4: new_class = "First Class"; break;
                            default:
                                cout << "\n\x1B[31mInvalid class choice!\033[0m\n";
                                return;
                        }
                        R1.set_flight_class(new_class);
                        break;
                    }
                    case 7: // Trip Type
                    {
                        cout << "Select Trip Type:\n";
                        cout << "1. One Way\n";
                        cout << "2. Round Trip\n";
                        int new_trip;
                        cin >> new_trip;
                        if (new_trip == 1 || new_trip == 2)
                        {
                            R1.set_trip(new_trip);
                        }
                        else
                        {
                            cout << "\n\x1B[31mInvalid trip choice!\033[0m\n";
                            return;
                        }
                        break;
                    }
                }

                // Recalculate fare with dynamic pricing
                string new_flight_no = R1.get_flight_no();
                fstream flight_file_recalc("flight.dat", ios::in | ios::out | ios::binary);
                if (flight_file_recalc.is_open())
                {
                    Flight f1;
                    while (flight_file_recalc.read((char *)&f1, sizeof(f1)))
                    {
                        if (f1.get_flight_number() == new_flight_no)
                        {
                            // Determine seat class for pricing
                            int seat_class = 1; // Economy
                            if (R1.get_flight_class() == "Premium Economy") seat_class = 2;
                            else if (R1.get_flight_class() == "Business") seat_class = 3;
                            else if (R1.get_flight_class() == "First Class") seat_class = 4;

                            // Calculate new fare
                            float new_fare = f1.calculateDynamicPrice(seat_class, REGULAR);

                            // Add baggage charges
                            vector<Passenger> passengers = R1.get_pass_vector();
                            float baggage_charge = 0;
                            for (size_t i = 0; i < passengers.size(); i++)
                            {
                                if (passengers[i].get_baggage_weight() > 20)
                                {
                                    baggage_charge += (passengers[i].get_baggage_weight() - 20) * 10;
                                }
                            }
                            new_fare += baggage_charge;

                            R1.set_fare(new_fare);

                            // Book seats on new flight
                            f1.bookSeat(original_passengers, seat_class, REGULAR);
                            flight_file_recalc.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                            flight_file_recalc.write((char *)&f1, sizeof(f1));
                            break;
                        }
                    }
                    flight_file_recalc.close();
                }

                // Update the reservation in the file
                ifstream infile_update("reservation.dat", ios::binary);
                ofstream temp_file("temp_reservation.dat", ios::binary);

                if (!infile_update.is_open() || !temp_file.is_open())
                {
                    cerr << "Error opening files for update." << endl;
                    return;
                }

                Reservation temp_res;
                int current_position = 0;
                bool updated = false;

                while (infile_update.peek() != EOF)
                {
                    temp_res.readfromfile_rev(infile_update);
                    if (current_position == reservation_position)
                    {
                        // Write the modified reservation
                        R1.savetofile_rev(temp_file);
                        updated = true;
                    }
                    else
                    {
                        // Write the original reservation
                        temp_res.savetofile_rev(temp_file);
                    }
                    current_position++;
                }

                infile_update.close();
                temp_file.close();

                if (updated)
                {
                    remove("reservation.dat");
                    rename("temp_reservation.dat", "reservation.dat");

                    cout << "\n\x1B[32mReservation modified successfully!\033[0m\n";
                    cout << "New Details:\n";
                    cout << "Flight: " << R1.get_flight_no() << " (" << R1.get_flight_name() << ")\n";
                    cout << "Route: " << R1.get_departure() << " to " << R1.get_arrival() << "\n";
                    cout << "Date: " << R1.get_flight_date() << " at " << R1.get_flight_time() << "\n";
                    cout << "Class: " << R1.get_flight_class() << "\n";
                    cout << "New Fare: $" << R1.get_fare() << "\n";
                }
                else
                {
                    remove("temp_reservation.dat");
                    cout << "\n\x1B[31mError updating reservation!\033[0m\n";
                }
            }
            else if (modify_choice == 8)
            {
                cout << "\nModification cancelled.\n";
            }
            else
            {
                cout << "\n\x1B[31mInvalid choice!\033[0m\n";
            }
        }
        else
        {
            cout << "\n\n\t\x1B[31m Reservation with flight number\033[0m \x1B[32m" << flight_number << "\033[0m \x1B[31mAnd Flight Date \033[0m\x1B[32m" << date << "\033[0m\x1B[31m not found.\033[0m" << endl;
        }
    }
    else
    {
        cout << "\n\n\n\t\t        --------------------- \033[1;47;34m No Any Booking Available \033[0m ---------------------\n\n\n";
    }

    cout << "\n\nPress any key to continue ... " << endl;
    getch();
    system("cls");
    return;
}*/
// Modified Flight Ticket Modification System with Enhanced Logic

void Modify_Ticket()
{
    system("cls");
    cout << "\n\033[3;43;30m--- Flight Ticket Modification --- \033[0m\n\n";
    cout << "1. Enter Reservation Details you want to Modify " << endl
         << "2. Choice Bookings " << endl;
    int choice;
    cout << "Choice : ";
    cin >> choice;
    bool found_ticket;

    if (choice == 2)
    {
        cout << "\n\n";
        found_ticket = My_Bookings(1);
        cout << "\033[3;43;30m--- Flight Ticket Modification --- \033[0m\n\n";
    }
    else if (choice != 2 && choice != 1)
    {
        cout << "\n\t\x1B[31m Invalid Choice!!\n\033[0m\n";
        Sleep(2000);
        system("cls");
        return;
    }
    else
    {
        found_ticket = My_Bookings(1);
        system("cls");
        cout << "\033[3;43;30m--- Flight Ticket Modification --- \033[0m\n\n";
    }

    if (!found_ticket)
    {
        cout << "\n\n\n\t\t        --------------------- \033[1;47;34m No Any Booking Available \033[0m ---------------------\n\n\n";
        cout << "\n\nPress any key to continue ... " << endl;
        getch();
        system("cls");
        return;
    }

    // Input booking ID to uniquely identify ticket (more secure)
    string booking_id;
    cout << "\nEnter Booking ID to Modify: ";
    cin >> booking_id;

    // Search for booking
    ifstream infile("reservation.dat", ios::binary);
    if (!infile.is_open())
    {
        cerr << "Error opening reservation file." << endl;
        return;
    }

    Reservation R1;
    bool found = false;
    int reservation_position = 0;

    while (infile.peek() != EOF)
    {
        R1.readfromfile_rev(infile);
        if (R1.get_booking_id() == booking_id)
        {
            found = true;
            break;
        }
        reservation_position++;
    }
    infile.close();

    if (!found)
    {
        cout << "\n\x1B[31mBooking ID not found!\033[0m\n";
        cout << "\n\nPress any key to continue ... ";
        getch();
        system("cls");
        return;
    }

    // Display current details
    cout << "\n\x1B[32mReservation Found!\033[0m\n";
    cout << "Flight: " << R1.get_flight_no() << " (" << R1.get_flight_name() << ")\n";
    cout << "Route: " << R1.get_departure() << " to " << R1.get_arrival() << "\n";
    cout << "Date: " << R1.get_flight_date() << " at " << R1.get_flight_time() << "\n";
    cout << "Class: " << R1.get_flight_class() << "\n";
    cout << "Fare: $" << R1.get_fare() << "\n\n";

    cout << "What would you like to modify?\n";
    cout << "1. Change Flight\n2. Change Passenger Details\n3. Cancel Modification\nChoice: ";
    int modify_type;
    cin >> modify_type;

    if (modify_type == 3)
    {
        cout << "\nModification cancelled.\n";
        return;
    }

    string original_flight = R1.get_flight_no();
    int passengers = R1.get_no_of_passenger();
    string seat_class = R1.get_flight_class();

    if (modify_type == 1)
    {
        // Free previous seat
        fstream flight_file("flight.dat", ios::in | ios::out | ios::binary);
        if (flight_file.is_open())
        {
            Flight f1;
            while (flight_file.read((char *)&f1, sizeof(f1)))
            {
                if (f1.get_flight_number() == original_flight)
                {
                    f1.cancelBookedSeat(passengers);
                    flight_file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                    flight_file.write((char *)&f1, sizeof(f1));
                    break;
                }
            }
            flight_file.close();
        }

        // Select new flight
        vector<Flight> available;
        ifstream flight_display("flight.dat", ios::binary);
        Flight temp_f;
        int count = 0;

        while (flight_display.read((char *)&temp_f, sizeof(temp_f)))
        {
            if (temp_f.get_available_Seats() >= passengers)
            {
                count++;
                available.push_back(temp_f);
                cout << count << ". " << temp_f.get_flight_number() << " - " << temp_f.get_flight_name() << " from " << temp_f.get_source() << " to " << temp_f.get_destination() << endl;
            }
        }
        flight_display.close();

        if (available.empty())
        {
            cout << "\n\x1B[31mNo flights with available seats.\033[0m\n";
            return;
        }

        cout << "\nSelect new flight (1-" << count << "): ";
        int sel;
        cin >> sel;
        if (sel < 1 || sel > count)
        {
            cout << "Invalid selection!\n";
            return;
        }

        Flight chosen = available[sel - 1];
        R1.set_flight_no(chosen.get_flight_number());
        R1.set_flight_name(chosen.get_flight_name());
        R1.set_departure(chosen.get_source());
        R1.set_arrival(chosen.get_destination());
        R1.set_flight_time(chosen.get_departure_time());

        // Class conversion
        int seat_code = 1;
        if (seat_class == "Premium Economy")
            seat_code = 2;
        else if (seat_class == "Business")
            seat_code = 3;
        else if (seat_class == "First Class")
            seat_code = 4;

        float fare = chosen.calculateDynamicPrice(seat_code, REGULAR);
        float baggage_fee = 0;
        for (auto &p : R1.get_pass_vector())
        {
            if (p.get_baggage_weight() > 14)
                baggage_fee += (p.get_baggage_weight() - 14) * 10;
        }

        fare += baggage_fee;
        R1.set_fare(fare);

        // Book new seat
        fstream book_file("flight.dat", ios::in | ios::out | ios::binary);
        if (book_file.is_open())
        {
            Flight temp;
            while (book_file.read((char *)&temp, sizeof(temp)))
            {
                if (temp.get_flight_number() == chosen.get_flight_number())
                {
                    temp.bookSeat(passengers, seat_code, REGULAR);
                    book_file.seekp(-static_cast<int>(sizeof(temp)), ios::cur);
                    book_file.write((char *)&temp, sizeof(temp));
                    break;
                }
            }
            book_file.close();
        }
    }
    else if (modify_type == 2)
    {

        // cout << "Enter Passenger Modifed Name: ";
        // string new_name;
        // cin >> new_name;
        // vector<Passenger> p = R1.get_pass_vector();
        // p[0].set_name(new_name); // For simplicity
        // R1.set_pass_vector(p);
        Update_Passenger_Details();
    }

    // Update file
    ifstream infile_u("reservation.dat", ios::binary);
    ofstream temp("temp_reservation.dat", ios::binary);
    Reservation temp_res;
    int pos = 0;

    while (infile_u.peek() != EOF)
    {
        temp_res.readfromfile_rev(infile_u);
        if (pos == reservation_position)
            R1.savetofile_rev(temp);
        else
            temp_res.savetofile_rev(temp);
        pos++;
    }
    infile_u.close();
    temp.close();
    remove("reservation.dat");
    rename("temp_reservation.dat", "reservation.dat");

    cout << "\n\x1B[32mTicket successfully modified!\033[0m\n";
    cout << "Updated Fare: $" << R1.get_fare() << endl;
    cout << "\n\nPress any key to continue ... ";
    getch();
    system("cls");
}

void Update_Passenger_Details()
{
    system("cls");
    cout << "\n--- Update Passenger Details ---\n";
    cout << "Enter Ticket Number of Passenger to Update: ";
    string ticket_no;
    cin >> ticket_no;

    fstream file("passenger.dat", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Error opening passenger.dat\n";
        Sleep(1500);
        system("cls");
        return;
    }

    Passenger p;
    bool found = false;
    streampos pos;
    while (!file.eof())
    {
        pos = file.tellg();
        // p.readFromFile_pass(file);
        void readFromFile_pass(std::ifstream & inFile);
        if (file.eof())
            break; // avoid duplicate last record due to while (!file.eof())
        if (p.get_ticket_no() == ticket_no)
        {
            found = true;

            cout << "\nPassenger found:\n";
            p.display_pass();

            int choice;
            do
            {
                cout << "\nWhich detail do you want to update?\n";
                cout << "1. First Name\n2. Last Name\n3. Passport Number\n4. Age\n5. Gender\n6. Done\nEnter choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    string new_name;
                    cout << "Enter new First Name: ";
                    cin >> new_name;
                    strncpy(p.name, new_name.c_str(), sizeof(p.name) - 1);
                    p.name[sizeof(p.name) - 1] = '\0';
                }
                else if (choice == 2)
                {
                    string new_surname;
                    cout << "Enter new Last Name: ";
                    cin >> new_surname;
                    strncpy(p.surname, new_surname.c_str(), sizeof(p.surname) - 1);
                    p.surname[sizeof(p.surname) - 1] = '\0';
                }
                else if (choice == 3)
                {
                    string new_passport;
                    cout << "Enter new Passport Number: ";
                    cin >> new_passport;
                    strncpy(p.passport_number, new_passport.c_str(), sizeof(p.passport_number) - 1);
                    p.passport_number[sizeof(p.passport_number) - 1] = '\0';
                }
                else if (choice == 4)
                {
                    int new_age;
                    cout << "Enter new Age: ";
                    cin >> new_age;
                    p.age = new_age;
                }
                else if (choice == 5)
                {
                    int new_gender;
                    cout << "Enter new Gender (1=Male, 2=Female): ";
                    cin >> new_gender;
                    p.gender = new_gender;
                }
            } while (choice != 6);

            // Go back and write the record
            file.seekp(pos);
            // p.writeToFile_pass(file);
            void writeToFile_pass(std::ofstream & outFile);

            cout << "\nPassenger details updated!\n";
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Passenger not found with Ticket Number: " << ticket_no << endl;

    cout << "Press any key to continue...\n";
    getch();
    system("cls");
}

void main_menu()
{
    system("cls");
    print_line("\n   ", '\xcd', '\xcd', '\xcd', 43);
    cout << "\t    AIRLINE RESERVATION SYSTEM\n";
    print_line("   ", '\xcd', '\xcd', '\xcd', 43, "\n\n");

    print_line("   ", '\xcd', '\xcd', '\xcd', 13, " ");
    cout << "MENU OPTIONS";
    print_line(" ", '\xcd', '\xcd', '\xcd', 14, "\n\n");
    cout << "\t\t\t\x1B[33m   user id: @" << login_user << "\033[0m\n";

    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 1. Book Flight Ticket/Reservation\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 2. Cancel Ticket/Reservation\n ";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 3. Modify Ticket/Reservation\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 4. My Bookings \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 5. Multi-User Booking Simulation\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 6. Reviews\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 7. Log Out\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 8. Exit \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);

    print_line("\n   ", '\xcd', '\xcd', '\xcd', 43);

    cout << "   Option : ";

    int option;
    cin >> option;

    if (option == 1) // Book Flight Ticket
    {
        system("cls");
        Book_Flight_Ticket();
    }
    else if (option == 2) // Cancel Ticket/Reservation
    {
        system("cls");
        Cancel_Ticket();
        main_menu();
    }
    else if (option == 3) // Modify Ticket/Reservation
    {
        system("cls");
        Modify_Ticket();
        main_menu();
    }
    else if (option == 4) // My Booking
    {
        system("cls");
        My_Bookings();
        main_menu();
    }
    else if (option == 5) // Multi-User Booking Simulation
    {
        system("cls");
        simulateMultiUserBooking();
        main_menu();
    }
    else if(option==6)
    {
        reviewMenu();
    }
    else if (option == 7) // logout karne le liye
    {
        login_status = false;
        cout << "\n\t\x1B[32m--Logout Successfull--\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        login_menu();
    }
    else if (option == 8) // Exit
    {
        Exit_msg();
    }
    else
    {
        cout << "\n\t\t\x1B[31m Invalid Input!! \033[0m\t\t";
        Sleep(1300);
        system("cls");
        main_menu();
    }
}

void signup()
{
    string name, username, pass, mob;
    cin.ignore();
    cout << "Enter Your Name: ";
    getline(cin, name);
    cout << "Create Your username: ";
    getline(cin, username);
    cout << "Create Your password: ";
    getline(cin, pass);
    while (1)
    {
        cout << "Enter Your 10 digit Mobile Number: ";
        getline(cin, mob);
        if (mob.length() != 10)
            cout << "\n\t\x1B[31mInvalid Number! Please Enter Valid Number\n\033[0m\t\t\n";
        else
            break;
    }

    ofstream file;
    file.open("login_detail.txt", ios::app);
    if (!file)
        cout << "\n\t\x1B[31mServer Error!! (file not open)\n\033[0m\t\t\n";
    file << username << " " << pass << " " << name << " " << mob << endl;
    file.close();
    cout << "\n\t\x1B[32m------------ Registration Success -----------\033[0m \n";
    signup_ok = true; // bool status
    Sleep(2000);
    system("cls");
    return;
}

void flight_announcement()
{
    ifstream file("flight_announcement.txt");
    if (!file)
    {
        cout << "\n\t\x1B[31mServer Error!! (file not open)\n\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        return;
    }
    cout << "\n\033[1m\033[37m\033[1;47;35m" << "Flight Announcements" << "\033[0m" << endl;
    string line;

    while (getline(file, line))
    {
        cout << "\x1B[33m" << line << "\033[0m" << endl;
    }
    file.close();
    cout << "\n\nPress any key to continue ... " << endl;
    getch();
    // system("pause"); // or (we can use also)
    system("cls");
}

void details()
{
    cout << "\n\033[1;47;35m Details : \033[0m\n\n";
    cout << "An airline is a company that provides air transport services for traveling passengers or freight.\n"
         << "Airlines use aircraft to supply these services and may form partnerships or alliances with other airlines for codeshare agreements,\n"
         << "in which they both offer and operate the same flight. Generally, airline companies are recognized with an air\n"
         << "operating certificate or license issued by a governmental aviation body. Airlines may be scheduled or charter operators.";
    cout << "...etc.\n\n";
    cout << "Press any key to continue ... " << endl;
    getch();
    // system("pause"); // or (we can use also)
    system("cls");
    return;
}

void login_menu()
{
    print_line("\n   ", '\xcd', '\xcd', '\xcd', 43);
    cout << "\t    AIRLINE RESERVATION SYSTEM\n";
    print_line("   ", '\xcd', '\xcd', '\xcd', 43, "\n\n");

    print_line("   ", '\xcd', '\xcd', '\xcd', 13, " ");
    cout << "LOGIN OPTIONS";
    print_line(" ", '\xcd', '\xcd', '\xcd', 13, "\n\n");

    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);
    cout << "\t 1. Login\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);
    cout << "\t 2. Sign Up \n ";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);
    cout << "\t 3. Flight Announcements \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);
    cout << "\t 4. Details \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);
    cout << "\t 5. Login as Administrator\n";

    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);
    cout << "\t 6. Exit\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 28);

    print_line("\n   ", '\xcd', '\xcd', '\xcd', 43);

    if (signup_ok)
    {
        cout << "\t\x1B[35m  -- Now you can Login --\033[0m\n";
        signup_ok = false;
    }

    cout << "   Option : ";
    int option;
    cin >> option;

    if (option == 1)
    {
        login();
        if (!login_status)
        {
            login_menu();
        }
    }
    else if (option == 2)
    {
        signup();
        login_menu();
    }
    else if (option == 3)
    {
        flight_announcement();
        login_menu();
    }
    else if (option == 4)
    {
        details();
        login_menu();
    }
    else if (option == 5)
    {
        admin_login();
        if (!admin_login_status)
        {
            login_menu();
        }
    }
    else if (option == 6)
    {
        system("cls");
        Exit_msg();
    }
    else
    {
        cout << "\n\t\t\x1B[31mInvalid Input!!\033[0m\t\t";
        Sleep(1000);
        system("cls");
        login_menu();
    }
}

int main()
{
    system("cls");
    welcome();

    login_menu();

    return 0;
}
