#include <iostream> // For cout<< , cin>> ...
#include <fstream>  // For file Fandling
#include <string>   // For std::string
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h> // For getch(), system("cls"), Sleep()
#include <cstring>   // For strcpy(), strncpy()
#include <vector>    // For std::vector<...>
#include <map>

using namespace std;

bool login_status = false;       // for checking user login status
bool signup_ok = false;          // for checking SignUp
string login_user;               // for set user Username
bool admin_login_status = false; // for checking Admin login status
string administrator_user;       // for set admin Username

void main_menu(); // initialize" main_mainu" function
void login_menu();

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
    float flight_price;

public:
    Flight() {}
    Flight(string f_num, string f_name, string dep_time, string arr_time, string src, string des, int seats, float price)
    {
        strcpy(flight_number, f_num.c_str());
        strcpy(flight_name, f_name.c_str());
        strcpy(departure_time, dep_time.c_str());
        strcpy(arrival_time, arr_time.c_str());
        strcpy(source, src.c_str());
        strcpy(destination, des.c_str());
        totalSeats = seats;
        availableSeats = seats;
        flight_price = price;
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
        cout << "Fare/Price: " << flight_price << "/-" << endl;
    }

    void bookSeat(int booked)
    {
        if (availableSeats > 0)
        {
            availableSeats -= booked;
            cout << "Seat booked" << endl;
        }
    }

    void cencle_bookedSeat(int n)
    {
        if (availableSeats < totalSeats)
        {
            availableSeats += n;
        }
    }

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
        flight_price = p;
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
        return flight_price;
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
};

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

    Passenger() {}
    Passenger(string n, string s, string pn, string tn, int sn, int fc, int a, int g, int iv)
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
    }

    void writeToFile_pass(ofstream &outFile) const
    {
        // for integer ke liye
        outFile.write(reinterpret_cast<const char *>(&seat_number), sizeof(seat_number));
        outFile.write(reinterpret_cast<const char *>(&flight_class), sizeof(flight_class));
        outFile.write(reinterpret_cast<const char *>(&age), sizeof(age));
        outFile.write(reinterpret_cast<const char *>(&gender), sizeof(gender));
        outFile.write(reinterpret_cast<const char *>(&is_special_fare), sizeof(is_special_fare));

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
        else if (flight_class == 2)
            cout << "Economy Class";
        else
            cout << "Premium Economy";

        cout << ", Age: " << age << ", Gender: " << (gender == 1 ? "Male" : "Female") << ", special_fare: ";

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
        cout << endl;
    }

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
};

class Reservation
{
private:
    char flight_no[20];
    char flight_name[20];
    char departure[20];
    char arrival[20];
    char flight_date[20];
    char flight_time[20];
    char flight_class[20];
    int trip; //(1,2)
    int fare;
    vector<Passenger> Pass; // Vector of Passenger objects

public:
    Reservation() {}
    Reservation(string fno, string fname, string dep, string arr, string fd, string ft, string fc, int trp, int price, vector<Passenger> passengers) : Pass(passengers), trip(trp), fare(price)
    {
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
    }

    void savetofile_rev(ofstream &file)
    {
        file.write(reinterpret_cast<const char *>(&flight_no), sizeof(flight_no));
        file.write(reinterpret_cast<const char *>(&flight_name), sizeof(flight_name));
        file.write(reinterpret_cast<const char *>(&departure), sizeof(departure));
        file.write(reinterpret_cast<const char *>(&arrival), sizeof(arrival));
        file.write(reinterpret_cast<const char *>(&flight_date), sizeof(flight_date));
        file.write(reinterpret_cast<const char *>(&flight_time), sizeof(flight_time));
        file.write(reinterpret_cast<const char *>(&flight_class), sizeof(flight_class));
        file.write(reinterpret_cast<const char *>(&trip), sizeof(trip));
        file.write(reinterpret_cast<const char *>(&fare), sizeof(fare));

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
        file.read(reinterpret_cast<char *>(&flight_no), sizeof(flight_no));
        file.read(reinterpret_cast<char *>(&flight_name), sizeof(flight_name));
        file.read(reinterpret_cast<char *>(&departure), sizeof(departure));
        file.read(reinterpret_cast<char *>(&arrival), sizeof(arrival));
        file.read(reinterpret_cast<char *>(&flight_date), sizeof(flight_date));
        file.read(reinterpret_cast<char *>(&flight_time), sizeof(flight_time));
        file.read(reinterpret_cast<char *>(&flight_class), sizeof(flight_class));
        file.read(reinterpret_cast<char *>(&trip), sizeof(trip));
        file.read(reinterpret_cast<char *>(&fare), sizeof(fare));

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
        cout << "Flight No: " << flight_no << endl;
        cout << "Departure: " << departure << endl;
        cout << "Arrival: " << arrival << endl;
        cout << "Flight Date: " << flight_date << endl;
        cout << "Flight Time: " << flight_time << endl;
        cout << "Flight Class: " << flight_class << endl;
        cout << "Trip: " << ((trip == 1) ? "One Way" : "Round Way") << endl;
        cout << "Fare: " << fare << endl;

        cout << "Passengers: " << endl;
        for (const Passenger &p : Pass)
        {
            p.display_pass();
        }
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
    int get_fare()
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
};

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
    cout << "\t\t\t\033[1;47;35m                                 ~ nishant Airlines \033[0m\t\t\n\n\n\n\n\n\n";
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
        cout << "\n\t\t\033[32m Login Success \033[0m \n\n";
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

float calculateTotalFare(string airline, float basePrice, float baggageWeight, bool windowSeat, string paymentMode, bool travelInsurance)
{
    float taxRate;
    float extraBaggageCost = 0;
    float seatCharge = 0;
    float convenienceFee = 0;
    float insuranceFee = 0;

    // Tax Rate based on airline
    if (airline == "IndiGo")
        taxRate = 0.18;
    else if (airline == "Air India")
        taxRate = 0.22;
    else if (airline == "SpiceJet")
        taxRate = 0.15;
    else if (airline == "Vistara")
        taxRate = 0.20;
    else
    {
        cout << "Unknown airline.\n";
        return -1;
    }

    // Baggage cost: First 14 kg free
    if (baggageWeight > 14)
    {
        extraBaggageCost = (baggageWeight - 14) * 300;
    }

    // Window seat charge
    if (windowSeat)
    {
        seatCharge = 250;
    }

    // Convenience Fee
    if (paymentMode == "credit")
    {
        convenienceFee = 200;
    }
    else if (paymentMode == "debit")
    {
        convenienceFee = 100;
    }
    else
    {
        cout << "Invalid payment mode.\n";
        return -1;
    }

    // Travel Insurance
    if (travelInsurance)
    {
        insuranceFee = 150;
    }

    float taxAmount = basePrice * taxRate;
    float total = basePrice + taxAmount + extraBaggageCost + seatCharge + convenienceFee + insuranceFee;

    // Summary
    cout << "\n----- Fare Breakdown -----\n";
    cout << "Base Fare: ₹" << basePrice << endl;
    cout << "Tax (" << taxRate * 100 << "%): ₹" << taxAmount << endl;
    cout << "Extra Baggage Charges: ₹" << extraBaggageCost << endl;
    cout << "Window Seat Charge: ₹" << seatCharge << endl;
    cout << "Convenience Fee (" << paymentMode << "): ₹" << convenienceFee << endl;
    cout << "Travel Insurance: ₹" << insuranceFee << endl;
    cout << "--------------------------\n";
    cout << "Total Fare: ₹" << total << endl;

    return total;
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

    // making Flight object f1
    Flight f1(f_num, f_name, departure_time, arrival_time, source, destination, capacity, price);
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
    cout << "\t 5. Log Out \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 6. Exit \n";
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
    else if (option == 5) // Log Out
    {
        cout << "\n\t\x1B[32m-- Logout Successfull --\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        login_menu();
    }
    else if (option == 6) // Exit
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

    cout << "\t  Flight No.\t Flight Name  \tDeparture Time \t\t\t    Arrive Time\t     Price (Based on select Class)\n";

    cout << "\t ------------------------------------------------------------------------------------------------\n";
    int flight_count = 1;
    ifstream file("flight.dat", ios::binary | ios::in);
    Flight f1;
    map<string, string> flightMap;

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
                cout << flight_count << ".\t" << char(179) << "   " << f1.get_flight_number() << "          " << f1.get_flight_name() << "       [\x1B[36m" << from << "\033[0m] " << f1.get_departure_time() << "\x1B[35m     -- " << diffHours << "hr" << diffMinutes << "min --     \033[0m" << f1.get_arrival_time() << " [\x1B[36m" << to << "\033[0m]   \x1B[32m" << total_fare_perPerson << "/-\033[0m \x1B[33m    BOOK NOW\033[0m\n";
                print_line("\t", char(192), char(196), char(217), 98);

                flightMap[f1.get_flight_number()] = f1.get_flight_name();
                flightMap.insert(make_pair(f1.get_flight_number(), f1.get_flight_name()));

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
        string get_flight_name_for_price;
        while (1)
        {
            cout << "Enter the Flight No. You want to book : ";
            cin >> booked_flight_no;
            // cout << "Enter the Flight Name You want to book : ";
            // cin >> get_flight_name_for_price;
            get_flight_name_for_price = flightMap[booked_flight_no];
            cout << "----->>>>" << get_flight_name_for_price << endl;
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

        // --------------------------------------
        // ✅ Enhanced Fare Calculation Section
        // --------------------------------------

        float baggageWeight;
        string seatPreference;
        string paymentMethod;
        char insuranceOption;

        // Get user inputs
        cout << "\nEnter your baggage weight in KG: ";
        cin >> baggageWeight;
        cin.ignore(); // Clear newline

        cout << "Do you want a window seat? (yes/no): ";
        getline(cin, seatPreference);

        cout << "Payment method (credit/debit): ";
        getline(cin, paymentMethod);

        cout << "Do you want to add travel insurance for ₹250? (y/n): ";
        cin >> insuranceOption;

        // -------- Fare Breakdown --------
        float basePrice = f1.get_price();
        float classMultiplier = 1.0;

        // Adjust base fare based on class
        if (clas == 1)
        {
            classMultiplier = 2.0;
        } // Business
        else if (clas == 2)
        {
            classMultiplier = 1.5;
        } // First
        else if (clas == 4)
        {
            classMultiplier = 1.2;
        } // Premium Economy

        basePrice *= classMultiplier;

        // Excess Baggage Calculation
        /* float baggageCharge = 0;
         if (baggageWeight > 14)
         {
             baggageCharge = (baggageWeight - 14) * 300;
         }*/

        // Flight name to extra baggage charge per kg
        map<string, int> baggageChargesPerKg;
        baggageChargesPerKg["Indigo"] = 300;
        baggageChargesPerKg["AirBus"] = 350;
        baggageChargesPerKg["SpiceJet"] = 320;
        baggageChargesPerKg["Vistara"] = 400;
        baggageChargesPerKg["Go_First"] = 280;

        // Check if flight exists in the map
        if (baggageChargesPerKg.find(get_flight_name_for_price) == baggageChargesPerKg.end())
        {
            cout << "Invalid flight selected!" << endl;
            return;
        }

        float baggageCharge = 0;
        const int freeLimit = 14;

        if (baggageWeight > freeLimit)
        {
            float excessWeight = baggageWeight - freeLimit;
            baggageCharge = excessWeight * baggageChargesPerKg[get_flight_name_for_price];
        }

        cout << "Flight: " << get_flight_name_for_price << endl;
        cout << "Excess Baggage Charge: ₹" << baggageCharge << endl;

        // Seat Preferene Fee
        float seatCharge = (seatPreference == "yes") ? 200 : 0;

        // Convenience Fee
        float convenienceFee = (paymentMethod == "credit") ? 150 : 100;

        // Insurance Fee
        float insuranceFee = (insuranceOption == 'y' || insuranceOption == 'Y') ? 250 : 0;

        // Final Fare
        float totalFare = basePrice + baggageCharge + seatCharge + convenienceFee + insuranceFee;
        float tax = totalFare * 0.10;
        totalFare += tax;

        // ---------- Print Fare Breakdown ----------
        cout << "\n\x1B[34m----- Fare Breakdown -----\033[0m\n";
        cout << "Base Fare (class adjusted): ₹" << basePrice << endl;
        cout << "Excess Baggage Charges     : ₹" << baggageCharge << endl;
        cout << "Window Seat Charge         : ₹" << seatCharge << endl;
        cout << "Convenience Fee            : ₹" << convenienceFee << " (" << paymentMethod << ")\n";
        cout << "Travel Insurance Fee       : ₹" << insuranceFee << endl;
        cout << "Travel Tax                 : ₹" << tax << endl;
        cout << "-------------------------------\n";
        cout << "\x1B[32mTotal Fare                 : ₹" << totalFare << "\033[0m\n";

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
            cout << "Enter Gen der of Passenger (1. Male 2. Female) : ";
            cin >> gender;

            ticket_n = booked_flight_no + to_string(seat_no) + to_string(clas) + to_string(age) + to_string(i); // generate unique Ticket no.

            Passenger p1(first_name, last_name, passport_no, ticket_n, seat_no, clas, age, gender, special_fare);
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

        //------------------------------Create fare on the base of Flight Class---------------------------------
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
        else // Economy class
        {
            total_fare_perPerson = f1.get_price();
        }

        //------------------------------ Create Reservation Class Object "reserv" ----------------------------
        Reservation reserv(booked_flight_no, f1.get_flight_name(), from, to, date, f1.get_departure_time(), f_class, trip, total_fare_perPerson, pass);
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
                f1.bookSeat(no_of_Passengers);
                file.seekp(-static_cast<int>(sizeof(f1)), ios::cur);
                file.write((char *)&f1, sizeof(f1));
                file.close();
                break;
            }
        }
        file.close();
        //-------------------------------------------------------------------

        // ofstream file2("ticket.txt");
        // file2 << "-------- NISHANT-AIRLINES ----------" << endl;
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

        cout << "\n\nPress any key to continue ... " << endl;
        getch();
        // system("pause"); // or (we can use also)
        system("cls");
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
        cout << "1. Choice Bookings " << endl;
    int choice;
    cout << "Choice : ";
    cin >> choice;
    bool found_ticket;
    if (choice == 1)
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
                    f1.cencle_bookedSeat(no_of_passenger);
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
    cout << "\t 3. My Bookings \n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 4. Log Out\n";
    print_line("\t ", '\xcd', '\xcd', '\xcd', 30);
    cout << "\t 5. Exit \n";
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
    else if (option == 3) // My Booking
    {
        system("cls");
        My_Bookings();
        main_menu();
    }
    else if (option == 4) // logout karne le liye
    {
        login_status = false;
        cout << "\n\t\x1B[32m--Logout Successfull--\033[0m\t\t\n";
        Sleep(2000);
        system("cls");
        login_menu();
    }
    else if (option == 5) // Exit
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
    // welcome();
    // welcome_animation();
    login_menu();

    return 0;
}
