#include <vector>
#include <cassert>
#include <initializer_list>

using namespace std;

const int MOD = 1e9 + 7;

template<typename T>
class Matrix {
public:
    vector<vector<T>> data;
    int rows, cols;

    Matrix(int rows, int cols, T val = 0): rows(rows), cols(cols) {
        data.assign(rows, vector<T>(cols, val));
    }

    Matrix(initializer_list<initializer_list<T>> init) {
        rows = init.size();
        cols = init.begin()->size();
        data.reserve(rows);
      
        for (auto& row: init) {
            assert(row.size() == cols);
            data.emplace_back(row);
        }
    }

    static Matrix identity(int n) {
        Matrix res(n, n);

        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }

        return res;
    }

    Matrix operator*(const Matrix& other) const {
        assert(cols == other.rows);

        Matrix res(rows, other.cols);
      
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    res[i][j] = (res[i][j] + 1LL * data[i][k] * other[k][j]) % MOD;
                }
            }
        }

        return res;
    }

    Matrix& operator*=(const Matrix& other) {
        *this = (*this) * other;
        return *this;
    }

    Matrix pow(long long expo) const {
        assert(rows == cols);

        Matrix res = identity(rows);
        Matrix base = *this;

        while (expo > 0) {
            if (expo & 1) res *= base;
            base *= base;
            expo >>= 1;
        }

        return res;
    }

    vector<T>& operator[](int i) {
        return data[i];
    }

    const vector<T>& operator[](int i) const {
        return data[i];
    }
};
