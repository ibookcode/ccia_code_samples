# Chapter 3. Sharing data between threads

## 3.2 Protecting shared data with mutexes

### 3.2.1 Using mutexes in C++

[listing_3.1.cpp](../listings/listing_3.1.cpp)

### 3.2.2 Structuring code for protecting shared data

[listing_3.2.cpp](../listings/listing_3.2.cpp)

### 3.2.3 Spotting race conditions inherent in interfaces

[listing_3.3.cpp](../listings/listing_3.3.cpp)

[listing_3.4.cpp](../listings/listing_3.4.cpp)

[listing_3.5.cpp](../listings/listing_3.5.cpp)

### 3.2.4 Deadlock: the problem and a solution

[listing_3.6.cpp](../listings/listing_3.6.cpp)

### 3.2.5 Further guidelines for avoiding deadlock

[listing_3.7.cpp](../listings/listing_3.7.cpp)

[listing_3.8.cpp](../listings/listing_3.8.cpp)

### 3.2.6 Flexible locking with std::unique_lock

[listing_3.9.cpp](../listings/listing_3.9.cpp)

### 3.2.8 Locking at an appropriate granularity

[listing_3.10.cpp](../listings/listing_3.10.cpp)

## 3.3 Alternative facilities for protecting shared data

### 3.3.1 Protecting shared data during initialization

[listing_3.11.cpp](../listings/listing_3.11.cpp)

[listing_3.12.cpp](../listings/listing_3.12.cpp)

### 3.3.2 Protecting rarely updated data structures

[listing_3.13.cpp](../listings/listing_3.13.cpp)