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
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1; // For non-operators
}

// Function to convert infix expression to postfix expression
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
            operatorStack.pop(); // Pop '('
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

// Function to evaluate a postfix expression
double evaluatePostfix(const char* postfix) {
    stack<double> operandStack;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char ch = postfix[i];
        if (isalnum(ch)) {
            operandStack.push(ch - '0'); // Convert char to int
        } else if (isOperator(ch)) {
            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();

            switch (ch) {
                case '+':
                    operandStack.push(operand1 + operand2);
                    break;
                case '-':
                    operandStack.push(operand1 - operand2);
                    break;
                case '*':
                    operandStack.push(operand1 * operand2);
                    break;
                case '/':
                    operandStack.push(operand1 / operand2);
                    break;
                case '^':
                    operandStack.push(pow(operand1, operand2));
                    break;
            }
        }
    }

    return operandStack.top();
}

int main() {
    stack<int> myStack; // stack to demonstrate basic stack operations

    // Menu for user interaction
    while (true) {
        cout << "\n1. Push element to stack";
        cout << "\n2. Pop element from stack";
        cout << "\n3. Display stack";
        cout << "\n4. Convert infix expression to postfix";
        cout << "\n5. Evaluate postfix expression";
        cout << "\n6. Exit";
        cout << "\nEnter your choice (1-6): ";

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
                char infixExpression[100]; // Adjust the size as needed
                cout << "Enter infix expression: ";
                cin >> infixExpression;
                char* postfixExpression = infixToPostfix(infixExpression);
                cout << "Postfix expression: " << postfixExpression << endl;
                delete[] postfixExpression;
                break;
            }
            case 5: {
                char postfixExpression[100]; // Adjust the size as needed
                cout << "Enter postfix expression: ";
                cin >> postfixExpression;
                double result = evaluatePostfix(postfixExpression);
                cout << "Result of evaluation: " << result << endl;
                break;
            }
            case 6:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    }

    return 0;
}

