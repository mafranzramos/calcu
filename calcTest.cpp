#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int MAX_SIZE = 100;
const int HISTORY_SIZE = 10;

struct HistoryEntry {
    string fullExpression;
    string pointer;
    int result;
};

void parseExpression(const string& expression, int values[], char operators[], int& numValues, int& numOperators) {
    string token;
    numValues = 0;
    numOperators = 0;

    for (int i = 0; i < expression.length(); i++) {
        if (isspace(expression[i]))
            continue;

        if (isdigit(expression[i])) {
            token += expression[i];
        }
        else {
            if (!token.empty()) {
                values[numValues] = stoi(token);
                token.clear();
                numValues++;
            }

            if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
                operators[numOperators] = expression[i];
                numOperators++;
            }
            else {
                cout << "Invalid expression!" << endl;
                return;
            }
        }
    }

    if (!token.empty()) {
        values[numValues] = stoi(token);
        numValues++;
    }
}

int performOperation(int num1, int num2, char operation) {
    if (operation == '+') {
        return num1 + num2;
    }
    else if (operation == '-') {
        return num1 - num2;
    }
    else if (operation == '*') {
        return num1 * num2;
    }
    else if (operation == '/') {
        if (num2 == 0) {
            cout << "UNDEFINED" << endl;
        }
        else {
            return num1 / num2;
        }
    }
    else {
        return 0;
    }
    return 0;
}

int evaluateExpression(int values[], char operators[], int numValues, int numOperators) {
    if (numValues == 0) {
        return 0;
    }

    int result = values[0];
    int j = 1;

    for (int i = 0; i < numOperators; i++) {
        char op = operators[i];

        switch (op) {
        case '+':
            result = performOperation(result, values[j], op);
            break;
        case '-':
            result = performOperation(result, values[j], op);
            break;
        case '*':
            result = performOperation(result, values[j], op);
            break;
        case '/':
            result = performOperation(result, values[j], op);
            break;
        default:
            break;
        }

        j++;
    }

    return result;
}

void showHistory(const HistoryEntry history[], int historyIndex) {
    cout << "\t\t#HISTORY#" << endl;
    for (int i = 0; i < historyIndex; i++) {
        cout << "Expression: " << history[i].fullExpression << endl;
        cout << "Pointer: " << &history[i].fullExpression << endl;
        cout << endl;
    }
}

int main() {
    string expression;
    HistoryEntry history[HISTORY_SIZE];
    int historyIndex = 0;
    char back = 'y';
    int values[MAX_SIZE];
    char operators[MAX_SIZE];
    int numValues = 0;
    int numOperators = 0;

    do {
        cout << "\t\t#CALCULATOR#" << endl;
        cout << "\tPress 'h' to show history." << endl;
        cout << "\tPress 'x' to quit." << endl << endl;
        cout << "Enter expression: " << endl;
        getline(cin, expression);

        if (expression == "h") {
            showHistory(history, historyIndex);
            cout << "Continue calculating[Y/N]: ";
            cin >> back;
            cin.ignore();
            system("CLS");
        } else {
            parseExpression(expression, values, operators, numValues, numOperators);
            int result = evaluateExpression(values, operators, numValues, numOperators);

            cout << "= " << result << endl;
            cout << "\t Continue[Y/N]: ";
            cin >> back;
            cin.ignore();
            system("CLS");

            history[historyIndex].fullExpression = expression + " = " + to_string(result);
            historyIndex = (historyIndex + 1) % HISTORY_SIZE;
        }
    } while (tolower(back) == 'y');

    return 0;
}
