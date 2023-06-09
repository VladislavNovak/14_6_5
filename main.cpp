#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

const int CANVAS_SIZE = 12;
enum Range { LINE = 0, CELL = 1, MIN_VALUE = 0, MAX_VALUE = 1 };

void printInfo(const int (&canvas)[CANVAS_SIZE][CANVAS_SIZE]) {
    cout << endl;
    cout << "\t";
    for (size_t i = 0; i < CANVAS_SIZE; ++i) cout << i << "  ";
    cout << "\n\n";
    for (size_t line = 0; line < CANVAS_SIZE; ++line) {
        for (size_t cell = 0; cell < CANVAS_SIZE; ++cell) {
            if (cell == 0) cout << line << ":\t";
            cout << canvas[line][cell] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// заполняет матрицу указанным значением
void initialCanvas(int (&canvas)[CANVAS_SIZE][CANVAS_SIZE], int initValue = 1) {
    for (auto &line : canvas) {
        for (int &cell : line) cell = initValue;
    }
}

// Возвращает введенную пользователем цифру
int getUserDigit() {
    int input = 0;

    // Пока не будет введено нормальное число, выполняем цикл
    while (!(cin >> input)){
        cout << "Error. Enter a number: ";
        // Сбрасываем коматозное состояние cin
        cin.clear();
        // Очищаем поток ввода
        fflush(stdin);
    }

    return input;
}

// Возвращает результат пользовательского ввода в виде диапазона { [lineMin] - [lineMax], [cellMin] - [cellMax] }
void setRange(int (&range)[2][2]) {
    int userInput[2][2] = { 0 };

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            while(true) {
                cout << "Enter value (0 - " << (CANVAS_SIZE - 1) << ") ";
                cout << "for the " << (j == 0 ? "line" : "cell") << " (point " << i << "): ";
                int input = getUserDigit();

                if (input >= 0 && input < CANVAS_SIZE) {
                    userInput[i][j] = input;
                    break;
                }

                cout << "Error. Try again" << endl;
            }
        }
    }

    range[Range::LINE][Range::MIN_VALUE] = userInput[0][0] < userInput[1][0] ? userInput[0][0] : userInput[1][0];
    range[Range::LINE][Range::MAX_VALUE] = userInput[0][0] > userInput[1][0] ? userInput[0][0] : userInput[1][0];
    range[Range::CELL][Range::MIN_VALUE] = userInput[0][1] < userInput[1][1] ? userInput[0][1] : userInput[1][1];
    range[Range::CELL][Range::MAX_VALUE] = userInput[0][1] > userInput[1][1] ? userInput[0][1] : userInput[1][1];
}

// Возвращает матрицу canvas с обнуленным диапазоном заданным range
void burstBubbleOnCanvas(int (&canvas)[CANVAS_SIZE][CANVAS_SIZE], const int (&range)[2][2]) {
    for (size_t line = range[Range::LINE][Range::MIN_VALUE]; line <= range[Range::LINE][Range::MAX_VALUE]; ++line) {
        for (size_t cell = range[Range::CELL][Range::MIN_VALUE]; cell <= range[Range::CELL][Range::MAX_VALUE]; ++cell) {
            canvas[line][cell] = 0;
        }
    }
}

// Если в матрице присутствует хотя бы одна ячейка равная 1, возвращает true
bool hasCanvasNotEmpty(const int (&canvas)[CANVAS_SIZE][CANVAS_SIZE]) {
    for (const auto &line : canvas) {
        for (int cell : line) {
            if (cell == 1) return true;
        }
    }

    return false;
}

int main() {
    int canvas[CANVAS_SIZE][CANVAS_SIZE] = { 0 };
    initialCanvas(canvas);

    cout << "\n\t--------The game has begun!--------" << endl;

    while(hasCanvasNotEmpty(canvas)) {
        int range[2][2] = { 0 };

        printInfo(canvas);

        setRange(range);

        burstBubbleOnCanvas(canvas, range);

        printInfo(canvas);
    }

    cout << "\t-------All bubbles are burst-------" << endl;
    cout << "\t------------GAME OVER!-------------" << endl;
}