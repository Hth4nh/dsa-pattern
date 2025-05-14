#include <cassert>
#include <initializer_list>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T, T MOD = T{}>
class Matrix {
    static_assert(std::is_arithmetic_v<T>);

private:
    T** _data = nullptr;
    size_t _rows = 0, _cols = 0;

    void calloc(size_t _rows, size_t _cols) {
        if (_data != nullptr) {
            free();
        }

        _data = new T*[_rows];
        this->_rows = _rows;
        this->_cols = _cols;

        for (size_t i = 0; i < _rows; i++) {
            _data[i] = new T[_cols]();
        }
    }

    void free() {
        for (size_t i = 0; i < rows(); i++) {
            delete[] _data[i];
        }

        delete[] _data;
        _data = nullptr;
        _rows = _cols = 0;
    }

public:
    Matrix(size_t _rows, size_t _cols, T val = 0) {
        calloc(_rows, _cols);
        if (val) fill(val);
    }

    Matrix(initializer_list<initializer_list<T>> init) {
        calloc(init.size(), init.begin()->size());

        size_t i = 0;
        for (auto& row: init) {
            assert(row.size() == cols());
            memcpy(_data[i++], row.begin(), sizeof(T) * cols());
        }
    }

    Matrix(const Matrix& other) {
        calloc(other.rows(), other.cols());

        for (size_t i = 0; i < rows(); i++) {
            memcpy(_data[i], other[i], sizeof(T) * cols());
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        if (rows() != other.rows() || cols() != other.cols()) {
            calloc(other.rows(), other.cols());
        }

        for (size_t i = 0; i < rows(); i++) {
            memcpy(_data[i], other[i], sizeof(T) * cols());
        }

        return *this;
    }

    ~Matrix() {
        free();
    }

    static Matrix identity(size_t n) {
        Matrix res(n, n);

        for (size_t i = 0; i < n; i++) {
            res[i][i] = 1;
        }

        return res;
    }

    void fill(T val) {
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                _data[i][j] = val;
            }
        }
    }

    Matrix multiply(const Matrix& other) const {
        assert(cols() == other.rows());
        Matrix res(rows(), other.cols());

        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < other.cols(); j++) {
                for (size_t k = 0; k < cols(); k++) {
                    if constexpr (MOD != 0) {
                        res[i][j] = (res[i][j] + 1LL * _data[i][k] * other[k][j]) % MOD;
                    } 
                    else {
                        res[i][j] += _data[i][k] * other[k][j];
                    }
                }
            }
        }

        return res;
    }

    Matrix operator*(const Matrix& other) const {
        return multiply(other);
    }

    Matrix& operator*=(const Matrix& other) {
        *this = multiply(other);
        return *this;
    }

    Matrix pow(long long expo) const {
        assert(rows() == cols());
        Matrix res = identity(rows());
        Matrix base = *this;

        while (expo > 0) {
            if (expo & 1) res *= base;
            base *= base;
            expo >>= 1;
        }

        return res;
    }

    size_t rows() const {
        return _rows;
    }

    size_t cols() const {
        return _cols;
    }

    T** data() const {
        return _data;
    }

    T* operator[](size_t i) {
        return _data[i];
    }

    const T* operator[](size_t i) const {
        return _data[i];
    }
};
