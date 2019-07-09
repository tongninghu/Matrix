#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <pthread.h>
#include "mat.h"
#include "matOperations.h"
#include "multiThread.h"

#define BUFFERSIZE 50
#define HEAPSIZE 100
using namespace std;

mat::mat (): data(NULL) {
    data = NULL;
    counter = 0;
    n_rows = 0;
    n_cols = 0;
    filename = "";
}

mat::mat(int row, int col) {
    n_rows = row;
    n_cols = col;
    counter = 0;
    if (row * col < HEAPSIZE) {
        data = new int[row * col];
        filename = "";
    }
    else {
        data = NULL;
        int file_index = rand() % 100;
        filename = "./file/" + to_string(file_index) + ".txt";

        while (ifstream(filename)) {
            file_index = rand() % 100;
            filename = "./file/" + to_string(file_index) + ".txt";
        }

        ofstream fout(filename, ios::binary);
        vector<int> buffer(BUFFERSIZE, 0);
        this->bufferFill(fout, buffer);
        fout.close();
    }
}

mat::~mat() {
    if (data) {
        delete [] data;
    }
    if (filename != "") {
        if(remove(&filename[0]) != 0)
            perror( "Error deleting file" );
        else
            puts( "File successfully deleted" );
    }
}


void mat::print() {
    if (n_rows * n_cols < HEAPSIZE) {
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                cout << setw(6) << right << data[i * n_cols + j];
            }
            cout << endl;
        }
    }
    else {
        ifstream fin(filename, ios::binary);
        vector<int> buffer (BUFFERSIZE);
        int count = 0;

        for (int i = 0; i < (n_rows * n_cols)/BUFFERSIZE; i++) {
            fin.read((char *)&buffer[0], sizeof(int) * BUFFERSIZE);
            this->bufferPrint(buffer, BUFFERSIZE, count);
        }

        if ((n_rows * n_cols) % BUFFERSIZE != 0) {
            fin.read((char *)&buffer[0], sizeof(int) * ((n_rows * n_cols) % BUFFERSIZE));
            this->bufferPrint(buffer, (n_rows * n_cols) % BUFFERSIZE, count);
        }
        fin.close();
    }
    cout << endl;
}

void mat::bufferPrint(vector<int>& buffer, int size, int& count) {
    for (int i = 0; i < size; i++) {
        cout << setw(6) << right << buffer[i];
        if (++count % n_cols == 0) cout << endl;
    }
}

void mat::set_size(int row, int col) {
    delete [] data;
    data = new int[row * col];
    counter = 0;
    n_rows = row;
    n_cols = col;
}


void mat::fill(int num) {
    if (n_rows * n_cols < HEAPSIZE) {
        for (int i = 0; i < n_rows * n_cols; i++) {
            data[i] = num;
        }
    }
    else {
        ofstream fout(filename, ios::binary);
        vector<int> buffer(BUFFERSIZE, num);
        this->bufferFill(fout, buffer);
        fout.close();
    }
    counter = n_rows * n_cols;
}

void mat::fillRand(int minValue, int maxValue) {
    if (n_rows * n_cols < HEAPSIZE) {
        for (int i = 0; i < n_rows * n_cols; i++) {
            data[i] = rand() % maxValue + minValue;
        }
    }
    else {
        ofstream fout(filename, ios::binary);
        vector<int> buffer(BUFFERSIZE);
        this->bufferFill(fout, buffer, true, minValue, maxValue);
        fout.close();
    }
}


void mat::bufferFill(ofstream& fout, vector<int>& buffer, bool random, int minValue,
            int maxValue) {

    for (int i = 0; i < (n_rows * n_cols)/BUFFERSIZE; i++) {
        if (random)
          generate(buffer.begin(), buffer.end(),
            [maxValue, minValue](){return (rand() % maxValue + minValue);});
        fout.write((char *)&buffer[0], sizeof(int) * BUFFERSIZE);
    }

    if ((n_rows * n_cols) % BUFFERSIZE != 0) {
        if (random)
          generate(buffer.begin(), buffer.end(),
            [maxValue, minValue](){return (rand() % maxValue + minValue);});
        fout.write((char *)&buffer[0], sizeof(int) * ((n_rows * n_cols) % BUFFERSIZE));
    }
}

mat& mat::operator<< (const int input) {
    if (counter < n_rows * n_cols) {
        data[counter++] = input;
    }
    return *this;
}

mat& mat::operator= (const mat& ref) {
    n_rows = ref.n_rows;
    n_cols = ref.n_cols;
    counter = ref.counter;

    if (n_rows * n_cols < HEAPSIZE) {
        data = new int[n_rows * n_cols];
        for (int i = 0; i < n_rows * n_cols; i++) {
            data[i] = ref.data[i];
        }
    }
    else {
        data = NULL;
        if (filename == "") {
            int file_index = rand() % 100;
            filename = "./file/" + to_string(file_index) + ".txt";

            while (ifstream(filename)) {
                file_index = rand() % 100;
                filename = "./file/" + to_string(file_index) + ".txt";
            }
        }

        ifstream fin(ref.filename, ios::binary);
        ofstream fout(filename, ios::binary);
        int buf[BUFFERSIZE];

        do {
           fin.read((char *)&buf[0], BUFFERSIZE);
           fout.write((char *)&buf[0], fin.gcount());
        } while (fin.gcount() > 0);

        fin.close();
        fout.close();
    }
    return *this;
}

row mat::operator[] (const int index) {
    if (index < n_rows) {
        row A;
        A.data = &data[index * n_cols];
        A.length = n_cols;
        return A;
    }
    else {
        cout << "Out of range!" << endl;
    }
}

bool mat::compare(const mat& ref) {
    if (n_rows != ref.n_rows || n_cols != ref.n_cols) {
        return false;
    }
    else {
      for (int i = 0; i < n_rows * n_cols; i++)
          if (data[i] != ref.data[i]) return false;

    }
    return true;
}

int mat::getElement(int row, int col) {
    if (row >= n_rows || col >= n_cols) {
        cout << "Out of range!" << endl;
    }
    else if (n_rows * n_cols < HEAPSIZE) {
        return data[row * n_cols + col];
    }
    else {
          int r = 0;
          ifstream fin(filename, ios::binary);
          fin.seekg((row * n_cols + col) * sizeof(int));
          fin.read((char *)&r, sizeof(int));
          fin.close();
          return r;
    }
}

void mat::t() {
    int file_index = rand() % 100;
    string tempfile = "./file/" + to_string(file_index) + ".txt";

    while (ifstream(tempfile)) {
        file_index = rand() % 100;
        tempfile = "./file/" + to_string(file_index) + ".txt";
    }

    ofstream fout(tempfile, ios::binary);
    ifstream fin(filename, ios::binary);
    int size = BUFFERSIZE / n_cols * n_cols;
    int rows = BUFFERSIZE / n_cols;
    int readBuffer [size];
    int writeBuffer [n_rows];
    int * temp = new int[n_rows * n_cols];
    bool toFile = ((n_rows * n_cols >= HEAPSIZE) ? true : false);

    for (int j = 0; j < n_cols; j++) {
        int *output = (toFile)? writeBuffer : &temp[j * n_rows];

        for (int i = 0; i < n_rows / rows; i++) {
            if (toFile) fin.read((char *)&readBuffer[0], sizeof(int) * size);
            int *input = (toFile)? &readBuffer[0] : &data[i * size];

            bufferTranspose(input, output, rows, rows, i, j);
        }

        if (n_rows % rows != 0) {
            if (toFile) fin.read((char *)&readBuffer[0], sizeof(int) * (n_rows % rows) * n_cols);
            int *input = (toFile)? &readBuffer[0] : &data[n_rows / rows * size];

            bufferTranspose(input, output, n_rows % rows, rows, n_rows / rows, j);
        }

        if (toFile) fout.write((char *)&output[0], sizeof(int) * n_rows);

        fin.clear();
        fin.seekg(0, ios::beg);
    }

    if (toFile) {
        remove(&filename[0]);
        filename = tempfile;
        delete [] temp;
    }
    else {
      delete [] data;
      data = temp;
      remove(&tempfile[0]);
    }
    fin.close();
    fout.close();
    int tmp = n_rows;
    n_rows = n_cols;
    n_cols = tmp;
}

void mat::bufferTranspose(int * input, int * output, int n_rows, int n_rows2, int row, int col) {

    for (int i = 0; i < n_rows; i++) {
        output[i + n_rows2 * row] = input[i * n_cols + col];
    }
}


row::row(): data(NULL) {
    length = 0;
}

int& row::operator[] (const int index) {
    if (index < length) {
        return data[index];
    }
    else {
        cout << "Out of range!" << endl;
    }
}
