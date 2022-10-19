#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Создание файла
int createTextFile(string namef) {
    ofstream tf(namef);
    if (!tf) return 1;
    cout << "Введите кол-во строк: ";
    int n;
    cin >> n;
    cout << "водите содержимое каждой строки построчно: ";
    string s;
    cin.get();
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        if ((i + 1) != n)
            tf << s << '\n';
        else tf << s;
    }
    tf.close();
    return 0;
}

//вывод содержимого файла
void printTextFile(string namef) {
    ifstream tf(namef);
    cout << "Содержимое файла: \n";
    string s;
    while (!tf.eof()) {
        getline(tf, s);
        cout << s << endl;
    }
    tf.close();
}

//Добавление новой записи  файл
void addTextInFile(string namef, string text) {
    ofstream tf(namef, ios::app);
    tf << text;
    tf.close();
}

//поиск числа по порядковому номеру
int searchNum(string namef, int n) {
    ifstream tf(namef);
    int num = 0;
    int k;
    while (!tf.eof()) {
        tf >> k;
        if (num == n) {
            tf.close();
            return k;
        }
        else num++;
    }
    tf.close();
    return -1;
}

//Кол-во чисел в файле
int numOfDigit(string namef) {
    ifstream tf(namef);
    int num = 0;
    while (!tf.eof()) {
        tf.get();
        num++;
    }
    tf.close();
    return num;
}

//Запись чисел из файла в массив
void createArray(string namef, vector<int>& vec) {
    ifstream tf(namef);
    int num;
    while (!tf.eof()) {
        tf >> num;
        vec.push_back(num);
    }
    tf.close();
}

//Поиск наибольшего общего делителя
int searchNOD(vector<int>& vec) {
    int NOD, i, flag;
    NOD = vec[0]; // Предпологаем, что первый элемент массива - это НОД.
    for (i = 1; i < vec.size(); i++)
        if (NOD > vec[i]) { // Если предполгаемый НОД больше след. элемент массива, 
            NOD = vec[i]; // тогда след.элемент - НОД.
        }
    flag = 1; // Флаг на true
    while (flag == 1) { // Пока флаг = true делаем.
        flag = 0; // Флаг = false.
        for (i = 0; i < vec.size(); i++)
            if (vec[i] % NOD != 0) { // Если след. элемент массива делится на предпологаемый НОД без остатка,
                flag = 1;
            }  // тогда ставим флаг на true.
        NOD--; // Здесь уменьшаем значение НОД. 
    }
    NOD++; // Здесь увеличиваем значение НОД.
    return NOD;
}

//Создание нового файла из исходного
void createNewTextFile(string newnamef, int Nod, vector<int>& vec) {
    ofstream newtf(newnamef);
    for (int i = 0; i < vec.size(); i++) {
        newtf << vec[i] / Nod << " ";
    }
    newtf.close();
}

int main()
{
    setlocale(LC_ALL, "ru");
    string name, newname;
    vector<int> vec;
    int NOD = 1;
    cout << "Хотите вы ли создать новый файл(y/n): ";
    char answer;
    cin >> answer;
    if (answer == 'y') {
        cout << "Введите название файла: ";
        cin >> name;
        int error = createTextFile(name);
        if (error) {
            cout << "Ошибка создания файла!";
            return 0;
        }
    }
    else {
        name = "programTextFile.txt";
        ifstream programTF(name);
        if (!programTF.is_open()) {
            cout << "Файл не открылся!";
            return 0;
        }
    }
    printTextFile(name);
    createArray(name, vec);
    NOD = searchNOD(vec);
    cout << "Введите название для нового файла: ";
    cin >> newname;
    createNewTextFile(newname, NOD, vec);
    vec.clear();
    printTextFile(newname);
    return 0;
}