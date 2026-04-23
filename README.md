# Cinema Ticket Booking System

A comprehensive, console-based C++ application for managing cinema ticket bookings. This project was developed as a 1st Semester Final Project for Programming Fundamentals (PF).

## Features

The system features a fully interactive main menu with the following capabilities:

1. **View All Movies:** Browse a list of all currently showing movies along with their runtime, language, genre, rating, and base ticket prices.
2. **Search Movies:** Easily search the database for movies by Name, Genre, Language, or Rating.
3. **View Movie Details:** Get in-depth information about a specific movie, including its cast, director, synopsis, and what type of screen it is showing on (e.g., IMAX, 4DX).
4. **Book Tickets:** Select a movie and showtime, view a live seating chart, and choose your exact seat. The system automatically calculates the final price based on the screen type multiplier.
5. **View Booking History:** Look up previous bookings by entering your customer name to view all details of your active and cancelled tickets.
6. **Cancel Booking:** Cancel a ticket by providing the unique Booking ID, which frees up the seat for other customers.
7. **View Screen Information:** See details about the cinema's screens (IMAX, VIP, Regular, etc.), their price multipliers, and which movie is assigned to them.
8. **View Available Seats:** Quickly glance at the seating chart for any specific movie and showtime to see which seats are booked ('X') and which are available ('O').

## Technologies Used
* **Language:** C++
* **Standard:** C++11 (Required for `to_string()` functionality)
* **Concepts Used:** Arrays, Loops, Conditionals, Functions, Time tracking (`<ctime>`), String Manipulation.

## How to Compile & Run

### Using Dev-C++
1. Open `your_file.cpp` in Dev-C++.
2. Go to **Tools > Compiler Options**, check the box for "Add the following commands when calling the compiler", and type `-std=c++11`.
3. Press `F11` (or click Execute > Compile & Run).

### Using the Command Line / PowerShell
If you have a C++ compiler installed (like the one included with Dev-C++), you can compile and run it from your terminal:

```powershell
# Navigate to your project folder
cd "path/to/your/project"

# Compile the C++ file (Make sure your compiler is added to your PATH or use the exact path to g++)
g++ -std=c++11 "your_file.cpp" -o output_program.exe

# Run the executable
./output_program.exe
```

## Structure & Data
The project currently manages state in-memory during runtime utilizing 1D, 2D, 3D, and 4D arrays to efficiently track customers, movies, available showtimes, and multi-dimensional seating charts across different screens.
