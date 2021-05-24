#ifndef _STACK_
#define _STACK_

#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
  int length;
  T* x;
  int ind;
public:
  TStack(int size=100);
  TStack(TStack<T>& _v);
  ~TStack();

  TStack<T>& operator =(const TStack<T>& _v);

  void Push(T d);
  T Get();

  bool IsEmpty() const;
  bool IsFull() const;

  int MinElem();
  int MaxElem();

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStack<T1> &A);


  int Length();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1> &A) {
  for (int i = 0; i < A.ind; i++) {
    ostr << A.x[i] << " ";
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1> &A) {
    int count;
    istr >> count;
  for (int i = 0; i < count; i++) 
  {
      T1 d;
      istr >> d;
      A.Push(d);
  }
  return istr;
}

template<class T>
inline TStack<T>::TStack(int size)
{
    if (size > 0)
    {
        this->length = size;
        x = new T[length];
        for (int i = 0; i < length; i++)
            x[i] = 0;
        this->ind = 0;
    }
    else
        throw new exception;
}

template <class T>
TStack<T>::TStack(TStack<T>& _v)
{
  length = _v.length;
  ind = _v.ind;
  x = new T [length];
  for (int i = 0; i < length;i+=1)
    x[i] = _v.x[i];
}

template <class T>
TStack<T>::~TStack()
{
  length = 0;
  if (x != NULL)
      delete[] x;
  else
      throw new exception;
  x = 0;
}

template <class T>
TStack<T>& TStack<T>::operator =(const TStack<T>& _v)
{
  if (this == &_v)
    return *this;

  this->length = _v.length;
  delete[] x;
  this->x = new T [length];
  for (int i = 0; i < length; i++)
    x[i] = _v.x[i];
  this->ind = _v.ind;
  return *this;
}

template<class T>
inline void TStack<T>::Push(T d)
{
    if (ind >= length)
        throw new exception;

    x[ind] = d;
    ind++;
}

template<class T>
inline T TStack<T>::Get()
{
    if (ind == 0)
        throw new exception;

    T d = x[ind - 1];
    ind--;
    return d;
}

template<class T>
inline bool TStack<T>::IsEmpty() const
{
    return ind == 0;
}

template<class T>
inline bool TStack<T>::IsFull() const
{
    return ind == length;
}

template<class T>
inline int TStack<T>::MinElem()
{
    int res = x[0];
    for (int i = 1; i < length; i++)
        if (x[i] < res)
            res = x[i];
    return res;
}

template<class T>
inline int TStack<T>::MaxElem()
{
    int res = x[0];
    for (int i = 1; i < length; i++)
        if (x[i] > res)
            res = x[i];
    return res;
}

template <class T>
int TStack<T>::Length()
{
  return length;
}


#endif