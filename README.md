Real-Time Parking Slot Allocator (C++ Project)

Overview
The "Real-Time Parking Slot Allocator" is a console and web-based simulation project built in C++, demonstrating the practical use of Data Structures and Algorithms (DSA).  
It efficiently manages parking slots, handles a waiting queue, and updates the parking status dynamically in real time.

This project was developed as part of the **Data Structures and Algorithms (DSA)** course requirement to showcase the application of arrays, linked lists, stacks, and queues.

Features
- Dynamic allocation of parking slots  
- Queue management when parking is full  
- Automatic reallocation when a slot is freed  
- Display of real-time slot status  
- Record of last actions using stack (undo support)  
- Minimal Web UI (optional visualization)

Data Structures Used
--Array-> Represents the parking slots 
--Queue-> Manages waiting vehicles (FIFO order)  
--Linked List-> Stores details of parked vehicles
--Stack-> Records the latest operations for undo 
--Class & Objects-> Implements modular OOP design 

 Classes Overview
--'Vehicle'-> Represents a vehicle’s details 
--'ParkingSlot'-->Represents each individual slot
--'Queue-> Handles waiting vehicles 
--'Stack-> Tracks operations
--'ParkingLot-> Controls the overall system logic
