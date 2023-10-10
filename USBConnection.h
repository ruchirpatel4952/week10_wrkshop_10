#ifndef USBCONNECTION_H
#define USBCONNECTION_H

#include <stack>
#include <memory>

class USBConnection {
private:
    int ID;

    // Constructor is made private to restrict object creation outside the class
    USBConnection(int id) : ID(id) {}

public:
    // Static stack to keep track of available IDs
    static std::stack<int> ids;

    // Function to create a new USBConnection object and return a unique_ptr if a port is available
    static std::unique_ptr<USBConnection> CreateUsbConnection() {
        if (!ids.empty()) {
            int id = ids.top();
            ids.pop();
            return std::unique_ptr<USBConnection>(new USBConnection(id));
        }
        return nullptr; // No available port
    }

    // Function to get the ID of the USBConnection
    int get_id() const {
        return ID;
    }

    // Destructor to return the used ID to the stack
    ~USBConnection() {
        ids.push(ID);
    }
};

// Initialize the stack with available IDs
std::stack<int> USBConnection::ids({3, 2, 1});

#endif // USBCONNECTION_H
