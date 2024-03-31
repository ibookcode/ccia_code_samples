# C++ Concurrency in Action - Second Edition

## 2 Managing threads

### 2.1 Basic thread management

#### 2.1.1 Launching a thread

listing_2.1.cpp

#### 2.1.3 Waiting in exceptional circumstances

listing_2.2.cpp

listing_2.3.cpp

#### 2.1.4 Running threads in the background

listing_2.4.cpp

### 2.3 Transferring ownership of a thread

listing_2.5.cpp

listing_2.6.cpp

listing_2.7.cpp

listing_2.8.cpp

### 2.4 Choosing the number of threads at runtime

listing_2.9.cpp

## 3 Sharing data between threads

### 3.2 Protecting shared data with mutexes

#### 3.2.1 Using mutexes in C++

listing_3.1.cpp

### 3.2.2 Structuring code for protecting shared data

listing_3.2.cpp

### 3.2.3 Spotting race conditions inherent in interfaces

listing_3.3.cpp

listing_3.4.cpp

listing_3.5.cpp

### 3.2.4 Deadlock: the problem and a solution

listing_3.6.cpp

### 3.2.5 Further guidelines for avoiding deadlock

listing_3.7.cpp

listing_3.8.cpp

### 3.2.6 Flexible locking with std::unique_lock

listing_3.9.cpp

### 3.2.8 Locking at an appropriate granularity

listing_3.10.cpp

## 3.3 Alternative facilities for protecting shared data

### 3.3.1 Protecting shared data during initialization

listing_3.11.cpp
