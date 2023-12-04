//
// Created by mobin on 03/12/23.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H
#include <iostream>
#include <memory>

template <typename T> class vector {
public:
  class Iterator {
  private:
    vector<T> *vecptr;
    int index;

  public:
    Iterator(int i, vector<T> *vec) {
      vecptr = vec;
      index = i;
    }
    T &operator*() const { return (*vecptr)[index]; }
    Iterator &operator++() {
      if (index != vecptr->current_size) {
        index++;
      }
      return *this;
    }
    bool operator==(const Iterator &other) const {
      return (index == other.index && vecptr = other.vecptr);
    }
    bool operator!=(const Iterator &other) const {
      return (index != other.index || vecptr != other.vecptr);
    }
  };
  vector() {
    u_array = std::make_unique<T[]>(10);

    total_size = 10;
    current_size = 0;
  }
  vector(int i) {
    u_array = std::make_unique<T[]>(i);
    total_size = i;
    current_size = 0;
  }
  vector(int i, T t) {
    u_array = std::make_unique<T[]>(i);
    total_size = i;
    current_size = i;
    for (int i = 0; i < current_size; i++) {
      u_array[i] = t;
    }
  }
  vector(const vector &other) {
    u_array = std::make_unique<T[]>(other.total_size);
    current_size = other.current_size;
    total_size = other.total_size;
    for (int i = 0; i < current_size; i++) {
      u_array[i] = other[i];
    }
  }
  vector(vector &&other) noexcept {
    u_array = std::move(other.u_array);
    current_size = other.current_size;
    total_size = other.total_size;
    other.current_size = 0;
    other.total_size = 0;
  }
  vector &operator=(const vector &other) {
    std::unique_ptr<T[]> temp = std::make_unique<T[]>(other.total_size);
    for (int i = 0; i < other.current_size; i++) {
      temp[i] = other[i];
    }
    u_array = std::move(temp);
    current_size = other.current_size;
    total_size = other.total_size;

    return *this;
  }
  vector &operator=(vector &&other) noexcept {
    u_array = std::move(other.u_array);
    current_size = other.current_size;
    total_size = other.total_size;
    other.current_size = 0;
    other.total_size = 0;
    return *this;
  }

  bool operator==(const vector &other) const {
    if (current_size != other.current_size) {
      return false;
    }
    for (int i = 0; i < current_size; i++) {
      if ((*this)[i] != other[i]) {
        return false;
      }
    }
    return true;
  }
  T &operator[](int i) const { return this->u_array[i]; }

  void push_back(T t) {
    if (current_size == total_size) {
      resize(total_size * 2);
    }
    u_array[current_size] = t;
    current_size++;
  }
  T pop_back() {
    current_size--;
    return u_array[current_size];
  }
  int size() { return current_size; }
  void print() {
    for (int i = 0; i < current_size; i++) {
      std::cout << u_array[i] << " ";
    }
  }

  Iterator begin() { return Iterator(0, this); }
  Iterator end() { return Iterator(current_size, this); }

private:
  std::unique_ptr<T[]> u_array;
  int current_size;
  int total_size;

  void resize(int new_size) {
    if (new_size <= 0)
      return;
    std::unique_ptr<T[]> temp = std::make_unique<T[]>(new_size);
    int min_current_size_and_new_size =
        new_size < current_size ? new_size : current_size;
    for (int i = 0; i < min_current_size_and_new_size; i++) {
      temp[i] = u_array[i];
    }
    u_array = std::move(temp);
    current_size = min_current_size_and_new_size;
    total_size = new_size;
  }
};

#endif // VECTOR_VECTOR_H
