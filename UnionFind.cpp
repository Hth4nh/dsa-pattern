#include <type_traits>
#include <numeric>
#include <algorithm>
#include <stdexcept>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class UnionFind {
private:
    T n = 0;
    T* root = nullptr;
    T* rootSize = nullptr;

public:
    UnionFind(T n): n(n) {
        root = new T[n];
        rootSize = new T[n];
        std::iota(root, root + n, 0);
        std::fill(rootSize, rootSize + n, 1);
    }

    UnionFind(const UnionFind<T>& other) : n(other.n) {
        root = new T[n];
        rootSize = new T[n];
        std::copy(other.root, other.root + n, root);
        std::copy(other.rootSize, other.rootSize + n, rootSize);
    }

    UnionFind(UnionFind<T>&& other) noexcept : n(other.n), root(other.root), rootSize(other.rootSize) {
        other.n = 0;
        other.root = nullptr;
        other.rootSize = nullptr;
    }

    template <typename U, typename = std::enable_if_t<std::is_same_v<std::decay_t<U>, UnionFind<T>>>>
    UnionFind& operator=(U&& other) {
        if (this != &other) {
            this->~UnionFind();
            new (this) UnionFind(std::forward<U>(other));
        }
        return *this;
    }

    ~UnionFind() {
        delete[] root;
        delete[] rootSize;
    }

    T find(T x) {
        if (x < 0 || x >= n) {
            throw std::out_of_range("Index out of bounds");
        }
        
        if (root[x] != x) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool unite(T x, T y) {
        T rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;

        if (rootSize[rootX] < rootSize[rootY]) {
            std::swap(rootX, rootY);
        }

        root[rootY] = rootX;
        rootSize[rootX] += rootSize[rootY];
        return true;
    }
};
