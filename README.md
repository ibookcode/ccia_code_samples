# C++ Concurrency in Action - Second Edition

**Author**: Anthony Williams
**Website**: https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition
**Source code**: https://github.com/anthonywilliams/ccia_code_samples

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

listing_3.12.cpp

### 3.3.2 Protecting rarely updated data structures

listing_3.13.cpp

## 4 Synchronizing concurrent operations

### 4.1 Waiting for an event or other condition

#### 4.1.1 Waiting for a condition with condition variables

listing_4.1.cpp

#### 4.1.2 Building a thread-safe queue with condition variables

listing_4.2.cpp

listing_4.3.cpp

listing_4.4.cpp

listing_4.5.cpp

### 4.2 Waiting for one-off events with futures

#### 4.2.1 Returning values from background tasks

listing_4.6.cpp

listing_4.7.cpp

#### 4.2.2 Associating a task with a future

listing_4.8.cpp

listing_4.9.cpp

#### 4.2.3 Making (std::)promises

listing_4.10.cpp

### 4.3 Waiting with a time limit

#### 4.3.3 Time points

listing_4.11.cpp

### 4.4 Using synchronization of operations to simplify code

#### 4.4.1 Functional programming with futures

listing_4.12.cpp

listing_4.13.cpp

listing_4.14.cpp

#### 4.4.2 Synchronizing operations with message passing

listing_4.15.cpp

listing_4.16.cpp

#### 4.4.3 Continuation-style concurrency with the Concurrency TS

listing_4.17.cpp

#### 4.4.4 Chaining continuations

listing_4.18.cpp

listing_4.19.cpp

listing_4.20.cpp

listing_4.21.cpp

#### 4.4.5 Waiting for more than one future

listing_4.22.cpp

listing_4.23.cpp

#### 4.4.6 Waiting for the first future in a set with when_any

listing_4.24.cpp
