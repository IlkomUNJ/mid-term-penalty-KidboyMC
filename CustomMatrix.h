#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>
#include <iomanip>

using namespace std;

class CustomMatrix{
public:
    bool mat[3][3]={0};
    CustomMatrix(){

    }

    //alternate way to instantiate the class
    CustomMatrix(bool m[3][3]){
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i=0;i< m_size;i++) {
            for(int j=0; j < sizeof(m[0]);j++){
                //cout << i << " " << j << endl;
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[3][3]){
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i=0;i< m_size;i++) {
            for(int j=0; j < sizeof(m[0]);j++){
                //cout << i << " " << j << endl;
                mat[i][j] = m[i][j];
            }
        }
    }

    void print() const {
        cout << "--- Window ---" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << (mat[i][j] ? "1 " : "0 ");
            }
            cout << endl;
        }
        cout << "--------------" << endl;
    }

    bool isEmpty() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (mat[i][j]) return false;
            }
        }
        return true;
    }

    bool operator==(const CustomMatrix& other) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (mat[i][j] != other.mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

};

#endif // CUSTOMMATRIX_H
