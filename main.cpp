/*
===============================================
  Project: Stack Operations and Expression Evaluator
  Course: Data Structures and Algorithms
  Dedicated to: Mr. Jibril Yusuf
  Institution: Dire Dawa University
  Date: May 2025
===============================================
*/

#include <iostream>
#include <stack>
#include <cmath>
#include <cctype>
#include <cstring>
using namespace std;

// Function to push an element to the stack
void pushElement(stack<int>& myStack) {
    int element;
    cout << "Enter element to push: ";
    cin >> element;
    myStack.push(element);
}

// Function to pop an element from the stack
void popElement(stack<int>& myStack) {
    if (!myStack.empty()) {
        cout << "Popped element: " << myStack.top() << endl;
        myStack.pop();
    } else {
        cout << "Stack is empty. Cannot pop." << endl;
    }
}

// Function to display the elements in the stack
void displayStack(stack<int> myStack) {
    cout << "Stack elements: ";
    while (!myStack.empty()) {
        cout << myStack.top() << " ";
        myStack.pop();
    }
    cout << endl;
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

// Function to convert infix expression to postfix
char* infixToPostfix(const char* infix) {
    char* postfix = new char[strlen(infix) + 1];
    stack<char> operatorStack;
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; ++i) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[postfixIndex++] = ch;
        } else if (ch == '(') {
            operatorStack.push(ch);
        } else if (ch == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix[postfixIndex++] = operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty()) operatorStack.pop(); // Remove '('
        } else if (isOperator(ch)) {
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(ch)) {
                postfix[postfixIndex++] = operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
        }
    }

    while (!operatorStack.empty()) {
        postfix[postfixIndex++] = operatorStack.top();
        operatorStack.pop();
    }

    postfix[postfixIndex] = '\0';
    return postfix;
}

// Function to evaluate postfix expression
double evaluatePostfix(const char* postfix) {
    stack<double> operandStack;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            operandStack.push(ch - '0'); // Assuming single-digit operands
        } else if (isOperator(ch)) {
            double operand2 = operandStack.top(); operandStack.pop();
            double operand1 = operandStack.top(); operandStack.pop();

            switch (ch) {
                case '+': operandStack.push(operand1 + operand2); break;
                case '-': operandStack.push(operand1 - operand2); break;
                case '*': operandStack.push(operand1 * operand2); break;
                case '/': operandStack.push(operand1 / operand2); break;
                case '^': operandStack.push(pow(operand1, operand2)); break;
            }
        }
    }

    return operandStack.top();
}

// Function to display "About Us" information
void displayAboutUs() {
    cout << "\n========== About Us ==========\n";
    cout << "We are Computer Science students and this project is a\n";
    cout << "Data Structures and Algorithms implementation focused\n";
    cout << "on stack operations, infix-to-postfix conversion, and\n";
    cout << "postfix expression evaluation.\n\n";

    cout << "Supervised by: Mr. Jibril Yusuf\n\n";

    cout << "This program was developed by:\n\n";
    cout << left;
    cout.width(25); cout << "1. Abdurahman Abdella";   cout << "ID: DDU1600032\n";
    cout.width(25); cout << "2. Ana Abdurazaq";        cout << "ID: DDU15022665\n";
    cout.width(25); cout << "3. Dego Roba";             cout << "ID: DDU1600200\n";
    cout.width(25); cout << "4. Nadiya Shigute";        cout << "ID: DDU1600575\n";
    cout.width(25); cout << "5. Yohannis Garomsa";      cout << "ID: DU1601937\n";
    cout.width(25); cout << "6. Bamlaku Ademe";         cout << "ID: RMD420\n";

    cout << "===============================\n";
}

// Function to display instructor info
void displayInstructorInfo() {
    cout << "\n====== About Instructor ======\n";
    cout << "This project was developed under the guidance of\n";
    cout << "Mr. Jibril Yusuf, an esteemed lecturer in the\n";
    cout << "Department of Computer Science at Dire-Dawa University.\n";
    cout << "His expertise and mentorship were crucial for the\n";
    cout << "completion of this work.\n";
    cout << "===============================\n";
}

int main() {
    stack<int> myStack;

    while (true) {
        cout << "\n====== Stack Menu ======";
        cout << "\n1. Push element to stack";
        cout << "\n2. Pop element from stack";
        cout << "\n3. Display stack";
        cout << "\n4. Convert infix expression to postfix";
        cout << "\n5. Evaluate postfix expression";
        cout << "\n6. Exit";
        cout << "\n7. About Us";
        cout << "\n8. About Instructor";
        cout << "\nEnter your choice (1-8): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                pushElement(myStack);
                break;
            case 2:
                popElement(myStack);
                break;
            case 3:
                displayStack(myStack);
                break;
            case 4: {
                char infixExpression[100];
                cout << "Enter infix expression: ";
                cin >> infixExpression;
                char* postfixExpression = infixToPostfix(infixExpression);
                cout << "Postfix expression: " << postfixExpression << endl;
                delete[] postfixExpression;
                break;
            }
            case 5: {
                char postfixExpression[100];
                cout << "Enter postfix expression: ";
                cin >> postfixExpression;
                double result = evaluatePostfix(postfixExpression);
                cout << "Result of evaluation: " << result << endl;
                break;
            }
            case 6:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            case 7:
                displayAboutUs();
                break;
            case 8:
                displayInstructorInfo();
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    }

    return 0;
}
