#include <iostream>
#include <string>
#include <vector>

void printMenu()
{
    std::cout << "\n=== C++ CLI Application ===" << std::endl;
    std::cout << "1. Hello World" << std::endl;
    std::cout << "2. Echo Input" << std::endl;
    std::cout << "3. Simple Calculator" << std::endl;
    std::cout << "4. List Demo" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

void helloWorld()
{
    std::cout << "\nHello, World!" << std::endl;
    std::cout << "This is a C++ CLI application running on Windows." << std::endl;
}

void echoInput()
{
    std::cout << "\nEnter some text: ";
    std::cin.ignore(); // Clear the input buffer
    std::string input;
    std::getline(std::cin, input);
    std::cout << "You entered: " << input << std::endl;
}

void simpleCalculator()
{
    std::cout << "\n=== Simple Calculator ===" << std::endl;
    double a, b;
    char operation;

    std::cout << "Enter first number: ";
    std::cin >> a;

    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> operation;

    std::cout << "Enter second number: ";
    std::cin >> b;

    double result = 0;
    bool valid = true;

    switch (operation)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (b != 0)
        {
            result = a / b;
        }
        else
        {
            std::cout << "Error: Division by zero!" << std::endl;
            valid = false;
        }
        break;
    default:
        std::cout << "Error: Invalid operation!" << std::endl;
        valid = false;
        break;
    }

    if (valid)
    {
        std::cout << "Result: " << a << " " << operation << " " << b << " = " << result << std::endl;
    }
}

void listDemo()
{
    std::cout << "\n=== List Demo ===" << std::endl;
    std::vector<std::string> items;
    std::string input;

    std::cout << "Enter items (type 'done' to finish):" << std::endl;

    while (true)
    {
        std::cout << "Item: ";
        std::cin >> input;

        if (input == "done")
        {
            break;
        }

        items.push_back(input);
    }

    std::cout << "\nYour list contains:" << std::endl;
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::cout << (i + 1) << ". " << items[i] << std::endl;
    }

    if (items.empty())
    {
        std::cout << "No items were added." << std::endl;
    }
}

int main()
{
    std::cout << "C++ CLI Application for Windows" << std::endl;
    std::cout << "===============================" << std::endl;

    bool running = true;

    while (running)
    {
        printMenu();

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            helloWorld();
            break;

        case 2:
            echoInput();
            break;

        case 3:
            simpleCalculator();
            break;

        case 4:
            listDemo();
            break;

        case 5:
            std::cout << "\nGoodbye!" << std::endl;
            running = false;
            break;

        default:
            std::cout << "\nInvalid choice. Please try again." << std::endl;
            break;
        }

        if (running)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }

    return 0;
}