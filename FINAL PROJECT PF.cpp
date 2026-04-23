#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;


const int MAX_MOVIES = 20;
const int MAX_SCREENS = 5;
const int ROWS = 10;
const int SEATS_PER_ROW = 15;
const int MAX_BOOKINGS = 200;
const int MAX_SHOWTIMES = 6;
const int MAX_CUSTOMERS = 100;


string movieNames[MAX_MOVIES];
string movieLanguages[MAX_MOVIES];
string movieGenres[MAX_MOVIES];
int movieDurations[MAX_MOVIES];
double moviePrices[MAX_MOVIES];
string movieRatings[MAX_MOVIES];
string movieDescriptions[MAX_MOVIES];
string movieDirectors[MAX_MOVIES];
string movieCasts[MAX_MOVIES][5];  
bool movieSeats[MAX_MOVIES][MAX_SHOWTIMES][ROWS][SEATS_PER_ROW];
string movieShowtimes[MAX_MOVIES][MAX_SHOWTIMES];
int movieAvailableSeats[MAX_MOVIES][MAX_SHOWTIMES];


double screenPriceMultipliers[MAX_SCREENS];
string screenTypes[MAX_SCREENS];
int screenAssignments[MAX_MOVIES];  


int bookingIds[MAX_BOOKINGS];
string bookingCustomerNames[MAX_BOOKINGS];
int bookingMovieIndices[MAX_BOOKINGS];
int bookingShowtimeIndices[MAX_BOOKINGS];
int bookingRows[MAX_BOOKINGS];
int bookingSeats[MAX_BOOKINGS];
double bookingAmounts[MAX_BOOKINGS];
string bookingDates[MAX_BOOKINGS];
string bookingTimes[MAX_BOOKINGS];
bool bookingStatus[MAX_BOOKINGS];  


string customerNames[MAX_CUSTOMERS];
string customerEmails[MAX_CUSTOMERS];
string customerPhones[MAX_CUSTOMERS];
int customerBookingCounts[MAX_CUSTOMERS];
double customerTotalSpending[MAX_CUSTOMERS];


int movieCount = 0;
int bookingCount = 0;
int customerCount = 0;
int currentBookingId = 1001;  


void initializeScreenData() {
    screenTypes[0] = "IMAX";
    screenPriceMultipliers[0] = 1.5;
    
    screenTypes[1] = "4DX";
    screenPriceMultipliers[1] = 1.8;
    
    screenTypes[2] = "Dolby Atmos";
    screenPriceMultipliers[2] = 1.3;
    
    screenTypes[3] = "Regular";
    screenPriceMultipliers[3] = 1.0;
    
    screenTypes[4] = "VIP";
    screenPriceMultipliers[4] = 2.0;
}


void initializeMovieData() {
    // Movie 1
    movieNames[movieCount] = "Inception Returns";
    movieLanguages[movieCount] = "English";
    movieGenres[movieCount] = "Sci-Fi/Action";
    movieDurations[movieCount] = 165;
    moviePrices[movieCount] = 14.99;
    movieRatings[movieCount] = "PG-13";
    movieDescriptions[movieCount] = "A mind-bending journey through dreams within dreams...";
    movieDirectors[movieCount] = "Christopher Nolan";
    movieCasts[movieCount][0] = "Leonardo DiCaprio";
    movieCasts[movieCount][1] = "Joseph Gordon-Levitt";
    movieCasts[movieCount][2] = "Ellen Page";
    movieCasts[movieCount][3] = "Tom Hardy";
    movieCasts[movieCount][4] = "Ken Watanabe";
    movieShowtimes[movieCount][0] = "10:00 AM";
    movieShowtimes[movieCount][1] = "1:30 PM";
    movieShowtimes[movieCount][2] = "4:45 PM";
    movieShowtimes[movieCount][3] = "8:00 PM";
    screenAssignments[movieCount] = 0;  // IMAX
    movieCount++;

    // Movie 2
    movieNames[movieCount] = "The Last Symphony";
    movieLanguages[movieCount] = "English";
    movieGenres[movieCount] = "Drama";
    movieDurations[movieCount] = 142;
    moviePrices[movieCount] = 12.99;
    movieRatings[movieCount] = "PG";
    movieDescriptions[movieCount] = "A touching story of a musician's final performance...";
    movieDirectors[movieCount] = "David Fincher";
    movieCasts[movieCount][0] = "Morgan Freeman";
    movieCasts[movieCount][1] = "Emma Stone";
    movieCasts[movieCount][2] = "Michael Caine";
    movieCasts[movieCount][3] = "Rachel McAdams";
    movieCasts[movieCount][4] = "Gary Oldman";
    movieShowtimes[movieCount][0] = "11:15 AM";
    movieShowtimes[movieCount][1] = "2:45 PM";
    movieShowtimes[movieCount][2] = "6:00 PM";
    movieShowtimes[movieCount][3] = "9:15 PM";
    screenAssignments[movieCount] = 2;  // Dolby Atmos
    movieCount++;

    // Movie 3
    movieNames[movieCount] = "Quantum Horizon";
    movieLanguages[movieCount] = "English";
    movieGenres[movieCount] = "Science Fiction";
    movieDurations[movieCount] = 155;
    moviePrices[movieCount] = 15.99;
    movieRatings[movieCount] = "PG-13";
    movieDescriptions[movieCount] = "An epic space adventure beyond the known universe...";
    movieDirectors[movieCount] = "James Cameron";
    movieCasts[movieCount][0] = "Chris Pratt";
    movieCasts[movieCount][1] = "Zoe Saldana";
    movieCasts[movieCount][2] = "Oscar Isaac";
    movieCasts[movieCount][3] = "Charlize Theron";
    movieCasts[movieCount][4] = "Idris Elba";
    movieShowtimes[movieCount][0] = "10:30 AM";
    movieShowtimes[movieCount][1] = "2:00 PM";
    movieShowtimes[movieCount][2] = "5:30 PM";
    movieShowtimes[movieCount][3] = "9:00 PM";
    screenAssignments[movieCount] = 1;  // 4DX
    movieCount++;

    // Initialize all seats as available
    for(int m = 0; m < movieCount; m++) {
        for(int s = 0; s < MAX_SHOWTIMES; s++) {
            for(int i = 0; i < ROWS; i++) {
                for(int j = 0; j < SEATS_PER_ROW; j++) {
                    movieSeats[m][s][i][j] = false;  // false means available
                }
            }
            movieAvailableSeats[m][s] = ROWS * SEATS_PER_ROW;
        }
    }
}

// Get current date as string
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "/" +
                 to_string(1 + ltm->tm_mon) + "/" +
                 to_string(ltm->tm_mday);
    return date;
}

// Get current time as string
string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string time = to_string(ltm->tm_hour) + ":" +
                 to_string(ltm->tm_min);
    return time;
}

// Display main menu
void displayMainMenu() {
    cout << "\n======= CINEMA TICKET BOOKING SYSTEM =======\n";
    cout << "1. View All Movies\n";
    cout << "2. Search Movies\n";
    cout << "3. View Movie Details\n";
    cout << "4. Book Tickets\n";
    cout << "5. View Booking History\n";
    cout << "6. Cancel Booking\n";
    cout << "7. View Screen Information\n";
    cout << "8. View Available Seats\n";
    cout << "9. Exit\n";
    cout << "==========================================\n";
    cout << "Enter your choice: ";
}
// Display all movies
void displayMovies() {
    cout << "\n====== CURRENT MOVIES ======\n";
    for(int i = 0; i < movieCount; i++) {
        cout << i + 1 << ". " << movieNames[i] << " (" << movieDurations[i] << " mins)\n";
        cout << "   Language: " << movieLanguages[i] << " | Genre: " << movieGenres[i] << "\n";
        cout << "   Rating: " << movieRatings[i] << " | Screen: " << screenTypes[screenAssignments[i]] << "\n";
        cout << "   Price: $" << fixed << setprecision(2) << moviePrices[i] << "\n";
        cout << "   Showtimes: ";
        for(int j = 0; j < MAX_SHOWTIMES && movieShowtimes[i][j] != ""; j++) {
            cout << movieShowtimes[i][j] << " ";
        }
        cout << "\n---------------------------\n";
    }
}

// Search movies by various criteria
void searchMovies() {
    cout << "\n====== SEARCH MOVIES ======\n";
    cout << "1. Search by Name\n";
    cout << "2. Search by Genre\n";
    cout << "3. Search by Language\n";
    cout << "4. Search by Rating\n";
    int choice;
    cin >> choice;
    cin.ignore();

    string searchTerm;
    cout << "Enter search term: ";
    getline(cin, searchTerm);

    bool found = false;
    cout << "\nSearch Results:\n";
    for(int i = 0; i < movieCount; i++) {
        bool match = false;
        switch(choice) {
            case 1:
                if(movieNames[i].find(searchTerm) != string::npos) match = true;
                break;
            case 2:
                if(movieGenres[i].find(searchTerm) != string::npos) match = true;
                break;
            case 3:
                if(movieLanguages[i].find(searchTerm) != string::npos) match = true;
                break;
            case 4:
                if(movieRatings[i].find(searchTerm) != string::npos) match = true;
                break;
        }
        if(match) {
            found = true;
            cout << "\n" << i + 1 << ". " << movieNames[i] << "\n";
            cout << "   Genre: " << movieGenres[i] << " | Language: " << movieLanguages[i] << "\n";
            cout << "   Rating: " << movieRatings[i] << "\n";
        }
    }
    if(!found) cout << "No matches found.\n";
}

// Display detailed information about a specific movie
void displayMovieDetails() {
    cout << "\nEnter movie number (1-" << movieCount << "): ";
    int choice;
    cin >> choice;
    
    if(choice < 1 || choice > movieCount) {
        cout << "Invalid movie number.\n";
        return;
    }
    
    int idx = choice - 1;
    cout << "\n====== MOVIE DETAILS ======\n";
    cout << "Title: " << movieNames[idx] << "\n";
    cout << "Director: " << movieDirectors[idx] << "\n";
    cout << "Cast:\n";
    for(int i = 0; i < 5 && movieCasts[idx][i] != ""; i++) {
        cout << "- " << movieCasts[idx][i] << "\n";
    }
    cout << "Description: " << movieDescriptions[idx] << "\n";
    cout << "Duration: " << movieDurations[idx] << " minutes\n";
    cout << "Language: " << movieLanguages[idx] << "\n";
    cout << "Genre: " << movieGenres[idx] << "\n";
    cout << "Rating: " << movieRatings[idx] << "\n";
    cout << "Screen: " << screenTypes[screenAssignments[idx]] << "\n";
    cout << "Base Price: $" << fixed << setprecision(2) << moviePrices[idx] << "\n";
    cout << "Final Price: $" << moviePrices[idx] * screenPriceMultipliers[screenAssignments[idx]] << "\n";
    
    cout << "\nShowtimes:\n";
    for(int i = 0; i < MAX_SHOWTIMES && movieShowtimes[idx][i] != ""; i++) {
        cout << i + 1 << ". " << movieShowtimes[idx][i];
        cout << " (" << movieAvailableSeats[idx][i] << " seats available)\n";
    }
}

// Display seating arrangement for a movie and showtime
void displaySeats(int movieIdx, int showtimeIdx) {
    cout << "\n===== SCREEN THIS WAY =====\n\n";
    cout << "    ";
    for(int j = 0; j < SEATS_PER_ROW; j++) {
        cout << setw(2) << j + 1 << " ";
    }
    cout << "\n";
    
    for(int i = 0; i < ROWS; i++) {
        cout << char('A' + i) << "   ";
        for(int j = 0; j < SEATS_PER_ROW; j++) {
            if(movieSeats[movieIdx][showtimeIdx][i][j]) {
                cout << " X ";
            } else {
                cout << " O ";
            }
        }
        cout << "\n";
    }
    cout << "\nX - Booked | O - Available\n";
}

// Check if a seat is valid and available
bool isValidSeat(int movieIdx, int showtimeIdx, int row, int seat) {
    if(row < 0 || row >= ROWS || seat < 0 || seat >= SEATS_PER_ROW) {
        return false;
    }
    return !movieSeats[movieIdx][showtimeIdx][row][seat];
}
// Process ticket booking
void bookTickets() {
    if(bookingCount >= MAX_BOOKINGS) {
        cout << "Sorry, booking system is full.\n";
        return;
    }

    // Get customer details
    cout << "\nEnter customer name: ";
    string name;
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter email: ";
    string email;
    getline(cin, email);
    
    cout << "Enter phone: ";
    string phone;
    getline(cin, phone);

    // Store or update customer information
    int customerIdx = -1;
    for(int i = 0; i < customerCount; i++) {
        if(customerNames[i] == name && customerEmails[i] == email) {
            customerIdx = i;
            break;
        }
    }
    if(customerIdx == -1 && customerCount < MAX_CUSTOMERS) {
        customerIdx = customerCount++;
        customerNames[customerIdx] = name;
        customerEmails[customerIdx] = email;
        customerPhones[customerIdx] = phone;
        customerBookingCounts[customerIdx] = 0;
        customerTotalSpending[customerIdx] = 0.0;
    }

    // Select movie and showtime
    displayMovies();
    cout << "\nEnter movie number: ";
    int movieChoice;
    cin >> movieChoice;
    if(movieChoice < 1 || movieChoice > movieCount) {
        cout << "Invalid movie selection.\n";
        return;
    }
    int movieIdx = movieChoice - 1;

    cout << "\nAvailable showtimes:\n";
    for(int i = 0; i < MAX_SHOWTIMES && movieShowtimes[movieIdx][i] != ""; i++) {
        cout << i + 1 << ". " << movieShowtimes[movieIdx][i] << "\n";
    }
    cout << "Enter showtime number: ";
    int showtimeChoice;
    cin >> showtimeChoice;
    int showtimeIdx = showtimeChoice - 1;

    if(showtimeIdx < 0 || showtimeIdx >= MAX_SHOWTIMES || movieShowtimes[movieIdx][showtimeIdx] == "") {
        cout << "Invalid showtime selection.\n";
        return;
    }

    // Display seating and get seat selection
    displaySeats(movieIdx, showtimeIdx);
    cout << "\nEnter row (A-J): ";
    char rowChar;
    cin >> rowChar;
    int row = toupper(rowChar) - 'A';

    cout << "Enter seat number (1-" << SEATS_PER_ROW << "): ";
    int seat;
    cin >> seat;
    seat--;

    if(!isValidSeat(movieIdx, showtimeIdx, row, seat)) {
        cout << "Invalid or already booked seat.\n";
        return;
    }

    // Calculate total price
    double totalPrice = moviePrices[movieIdx] * screenPriceMultipliers[screenAssignments[movieIdx]];

    // Confirm booking
    cout << "\nBooking Summary:\n";
    cout << "Movie: " << movieNames[movieIdx] << "\n";
    cout << "Showtime: " << movieShowtimes[movieIdx][showtimeIdx] << "\n";
    cout << "Seat: " << rowChar << seat + 1 << "\n";
    cout << "Price: $" << fixed << setprecision(2) << totalPrice << "\n";
    cout << "\nConfirm booking (Y/N)? ";
    char confirm;
    cin >> confirm;

    if(toupper(confirm) == 'Y') {
        // Update seat status
        movieSeats[movieIdx][showtimeIdx][row][seat] = true;
        movieAvailableSeats[movieIdx][showtimeIdx]--;

        // Record booking
        int bookingIdx = bookingCount++;
        bookingIds[bookingIdx] = currentBookingId++;
        bookingCustomerNames[bookingIdx] = name;
        bookingMovieIndices[bookingIdx] = movieIdx;
        bookingShowtimeIndices[bookingIdx] = showtimeIdx;
        bookingRows[bookingIdx] = row;
        bookingSeats[bookingIdx] = seat;
        bookingAmounts[bookingIdx] = totalPrice;
        bookingDates[bookingIdx] = getCurrentDate();
        bookingTimes[bookingIdx] = getCurrentTime();
        bookingStatus[bookingIdx] = true;

        // Update customer statistics
        customerBookingCounts[customerIdx]++;
        customerTotalSpending[customerIdx] += totalPrice;

        cout << "\nBooking confirmed! Your booking ID is: " << bookingIds[bookingIdx] << "\n";
    }
}

// Cancel existing booking
void cancelBooking() {
    cout << "\nEnter booking ID: ";
    int bookingId;
    cin >> bookingId;

    // Find booking
    int bookingIdx = -1;
    for(int i = 0; i < bookingCount; i++) {
        if(bookingIds[i] == bookingId && bookingStatus[i]) {
            bookingIdx = i;
            break;
        }
    }

    if(bookingIdx == -1) {
        cout << "Booking not found or already cancelled.\n";
        return;
    }

    // Display booking details
    cout << "\nBooking Details:\n";
    cout << "Movie: " << movieNames[bookingMovieIndices[bookingIdx]] << "\n";
    cout << "Showtime: " << movieShowtimes[bookingMovieIndices[bookingIdx]][bookingShowtimeIndices[bookingIdx]] << "\n";
    cout << "Seat: " << char('A' + bookingRows[bookingIdx]) << bookingSeats[bookingIdx] + 1 << "\n";
    cout << "Amount: $" << fixed << setprecision(2) << bookingAmounts[bookingIdx] << "\n";

    cout << "\nConfirm cancellation (Y/N)? ";
    char confirm;
    cin >> confirm;

    if(toupper(confirm) == 'Y') {
        // Update seat status
        int movieIdx = bookingMovieIndices[bookingIdx];
        int showtimeIdx = bookingShowtimeIndices[bookingIdx];
        int row = bookingRows[bookingIdx];
        int seat = bookingSeats[bookingIdx];
        
        movieSeats[movieIdx][showtimeIdx][row][seat] = false;
        movieAvailableSeats[movieIdx][showtimeIdx]++;
        bookingStatus[bookingIdx] = false;

        // Update customer information
        for(int i = 0; i < customerCount; i++) {
            if(customerNames[i] == bookingCustomerNames[bookingIdx]) {
                customerBookingCounts[i]--;
                customerTotalSpending[i] -= bookingAmounts[bookingIdx];
                break;
            }
        }

        cout << "Booking cancelled successfully.\n";
    }
}
// View booking history
void viewBookingHistory() {
    cout << "\nEnter customer name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    bool found = false;
    cout << "\n====== BOOKING HISTORY ======\n";
    for(int i = 0; i < bookingCount; i++) {
        if(bookingCustomerNames[i] == name) {
            found = true;
            cout << "\nBooking ID: " << bookingIds[i] << "\n";
            cout << "Movie: " << movieNames[bookingMovieIndices[i]] << "\n";
            cout << "Date: " << bookingDates[i] << "\n";
            cout << "Time: " << bookingTimes[i] << "\n";
            cout << "Showtime: " << movieShowtimes[bookingMovieIndices[i]][bookingShowtimeIndices[i]] << "\n";
            cout << "Seat: " << char('A' + bookingRows[i]) << bookingSeats[i] + 1 << "\n";
            cout << "Amount: $" << fixed << setprecision(2) << bookingAmounts[i] << "\n";
            cout << "Status: " << (bookingStatus[i] ? "Active" : "Cancelled") << "\n";
            cout << "-------------------------\n";
        }
    }
    if(!found) cout << "No bookings found.\n";
}

// View screen information
void viewScreenInfo() {
    cout << "\n====== SCREEN INFORMATION ======\n";
    for(int i = 0; i < MAX_SCREENS; i++) {
        cout << "\nScreen " << i + 1 << ": " << screenTypes[i] << "\n";
        cout << "Price Multiplier: " << screenPriceMultipliers[i] << "x\n";
        cout << "Currently showing: ";
        bool showing = false;
        for(int j = 0; j < movieCount; j++) {
            if(screenAssignments[j] == i) {
                cout << movieNames[j] << "\n";
                showing = true;
                break;
            }
        }
        if(!showing) cout << "No movie assigned\n";
    }
}

// Main function
int main() {
    // Initialize data
    initializeScreenData();
    initializeMovieData();
    
    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                displayMovies();
                break;
            case 2:
                searchMovies();
                break;
            case 3:
                displayMovieDetails();
                break;
            case 4:
                bookTickets();
                break;
            case 5:
                viewBookingHistory();
                break;
            case 6:
                cancelBooking();
                break;
            case 7:
                viewScreenInfo();
                break;
            case 8: {
                cout << "\nEnter movie number: ";
                int movieChoice;
                cin >> movieChoice;
                cout << "Enter showtime number: ";
                int showtimeChoice;
                cin >> showtimeChoice;
                if(movieChoice >= 1 && movieChoice <= movieCount) {
                    if(showtimeChoice >= 1 && showtimeChoice <= MAX_SHOWTIMES && movieShowtimes[movieChoice - 1][showtimeChoice - 1] != "") {
                        displaySeats(movieChoice - 1, showtimeChoice - 1);
                    } else {
                        cout << "Invalid showtime.\n";
                    }
                } else {
                    cout << "Invalid movie.\n";
                }
                break;
            }
        
            case 9:
                cout << "\nThank you for using the Cinema Ticket Booking System!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 9);
    
    return 0;
}