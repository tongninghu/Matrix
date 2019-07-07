#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <pthread.h>
#include "mat.h"
#include "multiThread.h"

#define BUFFERSIZE 15
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
    data = new int[n_rows * n_cols];
    for (int i = 0; i < n_rows * n_cols; i++) {
        data[i] = ref.data[i];
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
    if (n_rows * n_cols < HEAPSIZE) {
        int * tmp = new int[n_rows * n_cols];
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                tmp[j * n_rows + i] = data[i * n_cols + j];
            }
        }
        delete [] data;
        data = tmp;
    }
    else {
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
        vector<int> readBuffer (size, 0);
        vector<int> writeBuffer;

        for (int j = 0; j < n_cols; j++) {
            for (int i = 0; i < n_rows / rows; i++) {
                fin.read((char *)&readBuffer[0], sizeof(int) * size);
                this->bufferTransposeFill(readBuffer, writeBuffer, rows, j, fout);
            }

            if (n_rows % rows != 0) {
                fin.read((char *)&readBuffer[0], sizeof(int) * (n_rows % rows) * n_cols);
                this->bufferTransposeFill(readBuffer, writeBuffer, n_rows % rows, j, fout);
            }
            fin.clear();
            fin.seekg(0, ios::beg);
        }
        if (writeBuffer.size() != 0) {
            fout.write((char *)&writeBuffer[0], sizeof(int) * writeBuffer.size());
        }
        fin.close();
        fout.close();
        remove(&filename[0]);
        filename = tempfile;
    }
    int a = n_rows;
    n_rows = n_cols;
    n_cols = a;
}

void mat::bufferTransposeFill(vector<int>& readBuffer, vector<int>& writeBuffer,
        int rows, int cols, ofstream& fout) {

    for (int i = 0; i < rows; i++) {
        if (writeBuffer.size() == BUFFERSIZE) {
            fout.write((char *)&writeBuffer[0], sizeof(int) * BUFFERSIZE);
            writeBuffer.clear();
        }
        writeBuffer.push_back(readBuffer[i * n_cols + cols]);
    }
}

void mat::t_m() {
    int * tmp = new int[n_rows * n_cols];
    pthread_t threads[num_thread];

    arg_struct Arg;
    Arg.tmp = tmp;
    Arg.A = this;

    for (int i = 0; i < num_thread; i++) {
        pthread_create(&threads[i], NULL, multiThread::transpose, (void *)&Arg);
    }

    for (int i = 0; i < num_thread; i++) {
        pthread_join(threads[i], NULL);
    }

    delete [] data;
    multiThread::core_transpose = 0;
    data = tmp;

    int a = n_rows;
    n_rows = n_cols;
    n_cols = a;
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
