#include <iostream>

template <class T>
class Matrice {
    int dim;
    T** mat;
    void alocareMemorie();
    void dealocareMemorie();
    template <class T2>
    void copiere(const Matrice<T2>& other);
    template <class T2>
    friend class Matrice;
public:
    Matrice();
    Matrice(const Matrice& other);
    ~Matrice();
    Matrice& operator =(const Matrice& other);
    bool operator ==(const Matrice& other) const;
    bool operator !=(const Matrice& other) const;
    Matrice operator +(const Matrice& other) const;
    Matrice& operator +=(const Matrice& other);
    Matrice operator -(const Matrice& other) const;
    Matrice& operator -=(const Matrice& other);
    Matrice operator *(const Matrice& other) const;
    Matrice& operator *=(const Matrice& other);
    T operator !() const;
    Matrice<double> operator ^(int putere) const;
    operator Matrice<double>() const;
    Matrice transpusa() const;
    Matrice<double> inversa() const;
    template <class T2>
    friend std::istream& operator >>(std::istream& ist, Matrice<T2>& mat);
    template <class T2>
    friend std::ostream& operator <<(std::ostream& ost, const Matrice<T2>& mat);
};


int main() {

	return 0;
}

template<class T>
void Matrice<T>::alocareMemorie()
{
    if (dim == 0)
        return;

    mat = new T*[dim];
    for (int i = 0; i < dim; i++)
        mat[i] = new T[dim];
}

template<class T>
void Matrice<T>::dealocareMemorie()
{
    if (mat == nullptr)
        return;
    for (int i = 0; i < dim; i++)
        delete[] mat[i];
    delete[] mat
}

template<class T>
template<class T2>
void Matrice<T>::copiere(const Matrice<T2>& other)
{
    dealocareMemorie();
    dim = other.dim;
    alocareMemorie();
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            mat[i][j] = other.mat[i][j];
}

template<class T>
Matrice<T>::Matrice() : dim(0), mat(nullptr) {}

template<class T>
Matrice<T>::Matrice(const Matrice& other) : dim(0), mat(nullptr)
{
    copiere(other); 
}

template<class T>
Matrice<T>::~Matrice()
{
    dealocareMemorie();
}

template <class T>
Matrice<T>& Matrice<T>::operator =(const Matrice<T>& other) {
    copiere(other);
    return *this;
}

template<class T>
bool Matrice<T>::operator==(const Matrice& other) const
{
    if (dim != other.dim)
        throw "Nu se pot compara doua matrici de dimensiuni diferite!\n";

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            if (mat[i][j] != other.mat[i][j])
                return false;
    return true;
}

template<class T>
bool Matrice<T>::operator!=(const Matrice& other) const
{
    return !(*this == other);
}

template <class T>
Matrice<T> Matrice<T>::operator +(const Matrice<T>& other) const
{
    if (dim != other.dim)
        throw "Nu se pot aduna 2 matrici de dimensiuni diferite!\n";
    else if (dim == 0)
        throw "Nu se poate calcula suma a doua matrici neinitializate!\n";

    Matrice result;
    result.dim = dim;
    result.alocareMemorie();
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
    return result;
}

template<class T>
Matrice<T>& Matrice<T>::operator+=(const Matrice& other)
{
    return *this = *this + other;
}

template<class T>
Matrice<T> Matrice<T>::operator-(const Matrice& other) const
{
    if (dim != other.dim)
        throw "Nu se pot aduna 2 matrici de dimensiuni diferite!\n";
    else if (dim == 0)
        throw "Nu se poate calcula suma a doua matrici neinitializate!\n";

    Matrice result;
    result.dim = dim;
    result.alocareMemorie();
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            result.mat[i][j] = mat[i][j] - other.mat[i][j];
    return result;
}

template<class T>
Matrice<T>& Matrice<T>::operator-=(const Matrice& other)
{
    return *this = *this - other;
}

template<class T>
Matrice<T> Matrice<T>::operator*(const Matrice& other) const
{
    if (dim != other.dim)
        throw "Nu se pot aduna 2 matrici de dimensiuni diferite!\n";
    else if (dim == 0)
        throw "Nu se poate calcula suma a doua matrici neinitializate!\n";

    Matrice result;
    result.dim = dim;
    result.alocareMemorie();
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            for (int k = 0; k < dim; k++)
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
    return result;
}

template<class T>
Matrice<T>& Matrice<T>::operator*=(const Matrice& other)
{
    return *this = *this * other;
}

template<class T>
T Matrice<T>::operator!() const
{
    return T();
}








