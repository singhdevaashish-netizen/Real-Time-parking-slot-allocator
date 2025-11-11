#include <iostream>
#include <string>
using namespace std;

// ====================== STRUCTURES =========================

// Parking slot (Array element)
struct Slot {
    int id;
    bool isOccupied;
    Slot(int i = 0) {
        id = i;
        isOccupied = false;
    }
};

// Vehicle node for linked list
struct Vehicle {
    string number;
    int slotId;
    Vehicle* next;
    Vehicle(string num, int id) {
        number = num;
        slotId = id;
        next = nullptr;
    }
};

// ====================== LINKED LIST =========================
class ParkedList {
    Vehicle* head;
public:
    ParkedList() { head = nullptr; }

    // Add a vehicle to the parked list
    void addVehicle(string num, int id) {
        Vehicle* newV = new Vehicle(num, id);
        if (!head) head = newV;
        else {
            Vehicle* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newV;
        }
    }

    // Remove a vehicle by number
    void removeVehicle(string num) {
        if (!head) return;
        if (head->number == num) {
            Vehicle* del = head;
            head = head->next;
            delete del;
            return;
        }
        Vehicle* temp = head;
        while (temp->next && temp->next->number != num)
            temp = temp->next;
        if (temp->next) {
            Vehicle* del = temp->next;
            temp->next = temp->next->next;
            delete del;
        }
    }

    // Helper: Get vehicle number at a given slot
    string getVehicleAtSlot(int id) {
        Vehicle* temp = head;
        while (temp) {
            if (temp->slotId == id)
                return temp->number;
            temp = temp->next;
        }
        return "";
    }

    // Display all parked vehicles
    void display() {
        Vehicle* temp = head;
        cout << "Parked Vehicles: ";
        if (!temp) { cout << "None\n"; return; }
        while (temp) {
            cout << "[" << temp->number << " in Slot " << temp->slotId << "] ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ====================== QUEUE =========================
class VehicleQueue {
    string arr[10];
    int front, rear;
public:
    VehicleQueue() { front = rear = -1; }

    bool isEmpty() { return front == -1; }
    bool isFull() { return (rear + 1) % 10 == front; }

    void enqueue(string num) {
        if (isFull()) {
            cout << "Waiting queue full!\n";
            return;
        }
        if (isEmpty()) front = 0;
        rear = (rear + 1) % 10;
        arr[rear] = num;
    }

    string dequeue() {
        if (isEmpty()) return "";
        string val = arr[front];
        if (front == rear) front = rear = -1;
        else front = (front + 1) % 10;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Waiting Queue: None\n"; return; }
        cout << "Waiting Queue: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % 10;
        }
        cout << endl;
    }
};

// ====================== STACK =========================
class ActionStack {
    string actions[20];
    int top;
public:
    ActionStack() { top = -1; }

    void push(string act) {
        if (top < 19) actions[++top] = act;
    }

    string pop() {
        if (top == -1) return "";
        return actions[top--];
    }
};

// ====================== MAIN SYSTEM =========================
class ParkingSystem {
    Slot slots[5]; // Array of 5 parking slots
    ParkedList parked;
    VehicleQueue queue;
    ActionStack history;

public:
    ParkingSystem() {
        for (int i = 0; i < 5; i++)
            slots[i] = Slot(i + 1);
    }

    // Park a vehicle
    void parkVehicle(string num) {
        for (int i = 0; i < 5; i++) {
            if (!slots[i].isOccupied) {
                slots[i].isOccupied = true;
                parked.addVehicle(num, slots[i].id);
                history.push("PARK " + num);
                cout << "Vehicle " << num << " parked in Slot " << slots[i].id << endl;
                return;
            }
        }
        cout << "No slot available! Added to waiting queue.\n";
        queue.enqueue(num);
    }

    // Remove a vehicle
    void removeVehicle(string num) {
        bool found = false;
        for (int i = 0; i < 5; i++) {
            string parkedNum = parked.getVehicleAtSlot(i + 1);
            if (slots[i].isOccupied && parkedNum == num) {
                found = true;
                slots[i].isOccupied = false;
                parked.removeVehicle(num);
                cout << "Vehicle " << num << " removed from Slot " << i + 1 << endl;
                history.push("REMOVE " + num);

                // Assign waiting vehicle if available
                if (!queue.isEmpty()) {
                    string nextCar = queue.dequeue();
                    cout << "Assigning Slot " << i + 1 << " to " << nextCar << endl;
                    slots[i].isOccupied = true;
                    parked.addVehicle(nextCar, i + 1);
                    history.push("PARK " + nextCar);
                    cout << "Vehicle " << nextCar << " parked in Slot " << i + 1 << endl;
                }
                break;
            }
        }
        if (!found)
            cout << "Vehicle not found!\n";
    }

    // Display system status
    void displayStatus() {
        cout << "\n====== PARKING STATUS ======\n";
        for (int i = 0; i < 5; i++) {
            cout << "Slot " << i + 1 << ": "
                 << (slots[i].isOccupied ? "Occupied" : "Free") << endl;
        }
        parked.display();
        queue.display();
        cout << "============================\n";
    }

    // Undo last action (only undo park for simplicity)
    void undoLastAction() {
        string act = history.pop();
        if (act == "") {
            cout << "No actions to undo.\n";
            return;
        }
        if (act.find("PARK") == 0) {
            string num = act.substr(5);
            removeVehicle(num);
            cout << "Undid parking of " << num << endl;
        } else if (act.find("REMOVE") == 0) {
            cout << "(Undo of remove not implemented for simplicity)\n";
        }
    }
};

// ====================== MAIN MENU =========================
int main() {
    ParkingSystem ps;
    int choice;
    string num;

    do {
        cout << "\n====== REAL-TIME PARKING SLOT ALLOCATOR ======\n";
        cout << "1. Park Vehicle\n2. Remove Vehicle\n3. Show Status\n4. Undo Last Action\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter vehicle number: ";
            cin >> num;
            ps.parkVehicle(num);
            break;
        case 2:
            cout << "Enter vehicle number: ";
            cin >> num;
            ps.removeVehicle(num);
            break;
        case 3:
            ps.displayStatus();
            break;
        case 4:
            ps.undoLastAction();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
