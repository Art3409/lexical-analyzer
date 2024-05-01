#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
using namespace std;

// Типы лексем
enum TokenType {
    IDENTIFIER,
    CONSTANT,
    ASSIGNMENT,
    PLUS,
    MINUS,
    UMONOJENIE,
    DELENIE,
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMICOLON,
    END_OF_FILE,
    UNKNOWN
};
//***********************************************************//
// Структура для представления лексемы
struct Token {
    TokenType type;
    string value;
};
//***********************************************************//

//***********************************************************//
// Функция для проверки, является ли символ разделителем
bool isDelimiter(char ch) {
    return ch == ';' || ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || isspace(ch);
}
//***********************************************************//

//***********************************************************//
// Функция для получения следующей лексемы из строки
Token getNextToken(const string& str, size_t& pos) {
    Token token;
    token.type = UNKNOWN;
    token.value = "";

    while (pos < str.length() && isspace(str[pos])) {
        pos++;
    }

    if (pos == str.length()) {
        token.type = END_OF_FILE;
        return token;
    }

    if (str[pos] == ';') {
        token.type = SEMICOLON;
        token.value = ";";
        pos++;
    }
    else if (str.substr(pos, 2) == ":=") {
        token.type = ASSIGNMENT;
        token.value = ":=";
        pos += 2;
    }
    else if (str[pos] == '+') {
        token.type = PLUS;
        token.value = "+";
        pos++;
    }
    else if (str[pos] == '-') {
        token.type = MINUS;
        token.value = "-";
        pos++;
    }
    else if (str[pos] == '*') {
        token.type = UMONOJENIE;
        token.value = "*";
        pos++;
    }
    else if (str[pos] == '/') {
        token.type = DELENIE;
        token.value = "/";
        pos++;
    }
    else if (str[pos] == '(') {
        token.type = LEFT_PAREN;
        token.value = "(";
        pos++;
    }
    else if (str[pos] == ')') {
        token.type = RIGHT_PAREN;
        token.value = ")";
        pos++;
    }
    else if (isalpha(str[pos])) {
        while (pos < str.length() && !isDelimiter(str[pos])) {
            token.value += str[pos];
            pos++;
        }
        token.type = IDENTIFIER;
    }
    else if (isdigit(str[pos])) {
        while (pos < str.length() && !isDelimiter(str[pos])) {
            if(isdigit(str[pos]) || str[pos]=='a' || str[pos]=='b'|| str[pos]=='c' || str[pos]=='d' || str[pos]=='e' || str[pos]=='f'){
                token.value += str[pos];
            }
            pos++;
        }
        token.type = CONSTANT;
    }
    else {
        // Неизвестный символ
        token.value = str[pos];
        pos++;
    }

    return token;
}
//***********************************************************//

//***********************************************************//
// Функция для анализа выражения
int analyzeExpressionAndPrint(const string& expr, int i) {
    size_t pos = 0;
    Token token;

    while ((token = getNextToken(expr, pos)).type != END_OF_FILE) {
        switch (token.type) {
        case IDENTIFIER:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Идентификатор: |" <<token.value << endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case CONSTANT:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Константа: |" << token.value << endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case ASSIGNMENT:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Оператор присваивания: |" << token.value << endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case PLUS:
        case MINUS:
        case UMONOJENIE:
        case DELENIE:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Арифметический оператор: |" << token.value << endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case LEFT_PAREN:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Левая круглая скобка: |" << token.value<< endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case RIGHT_PAREN:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Правая круглая скобка: |" << token.value<< endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case SEMICOLON:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Точка с запятой: |" << token.value<< endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        case UNKNOWN:
            cout <<setw(2)<<i<<" |"<<setw(30)<<right<< "Неизвестный символ: |" << token.value << endl;
            cout<<"———————————————————————————————————————————————"<<endl;
            i=i+1;
            break;
        default:
            break;
        }
    }
    return i;
}
//***********************************************************//

//***********************************************************//
// main функция
int main() {

    setlocale(LC_CTYPE, "rus");
    int i=1;
    //std::system("chcp 1251");

    ifstream inputFile1("text.txt");
    if (!inputFile1) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile1, line)) {

        // Анализируем выражение, если строка не является пустой после удаления комментариев
        if (!line.empty()) {
            cout << "Анализируем выражение: " << line << endl;
        }
    }
    ifstream inputFile2("text.txt");
    cout<<"———————————————————————————————————————————————"<<endl;
    while (getline(inputFile2, line)) {

        // Анализируем выражение, если строка не является пустой после удаления комментариев
        if (!line.empty()) {
            i=analyzeExpressionAndPrint(line,i);
        }
    }
    inputFile1.close();
    inputFile2.close();
    return 0;
}
//***********************************************************//
