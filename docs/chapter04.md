# Chapter 4. Synchronizing concurrent operations

## 4.1 Waiting for an event or other condition

### 4.1.1 Waiting for a condition with condition variables

[listing_4.1.cpp](../listings/listing_4.1.cpp)

### 4.1.2 Building a thread-safe queue with condition variables

[listing_4.2.cpp](../listings/listing_4.2.cpp)

[listing_4.3.cpp](../listings/listing_4.3.cpp)

[listing_4.4.cpp](../listings/listing_4.4.cpp)

[listing_4.5.cpp](../listings/listing_4.5.cpp)

## 4.2 Waiting for one-off events with futures

### 4.2.1 Returning values from background tasks

[listing_4.6.cpp](../listings/listing_4.6.cpp)

[listing_4.7.cpp](../listings/listing_4.7.cpp)

### 4.2.2 Associating a task with a future

[listing_4.8.cpp](../listings/listing_4.8.cpp)

[listing_4.9.cpp](../listings/listing_4.9.cpp)

### 4.2.3 Making (std::)promises

[listing_4.10.cpp](../listings/listing_4.10.cpp)

## 4.3 Waiting with a time limit

### 4.3.3 Time points

[listing_4.11.cpp](../listings/listing_4.11.cpp)

## 4.4 Using synchronization of operations to simplify code

### 4.4.1 Functional programming with futures

[listing_4.12.cpp](../listings/listing_4.12.cpp)

[listing_4.13.cpp](../listings/listing_4.13.cpp)

[listing_4.14.cpp](../listings/listing_4.14.cpp)

### 4.4.2 Synchronizing operations with message passing

[listing_4.15.cpp](../listings/listing_4.15.cpp)

[listing_4.16.cpp](../listings/listing_4.16.cpp)

### 4.4.3 Continuation-style concurrency with the Concurrency TS

[listing_4.17.cpp](../listings/listing_4.17.cpp)

### 4.4.4 Chaining continuations

[listing_4.18.cpp](../listings/listing_4.18.cpp)

[listing_4.19.cpp](../listings/listing_4.19.cpp)

[listing_4.20.cpp](../listings/listing_4.20.cpp)

[listing_4.21.cpp](../listings/listing_4.21.cpp)

### 4.4.5 Waiting for more than one future

[listing_4.22.cpp](../listings/listing_4.22.cpp)

[listing_4.23.cpp](../listings/listing_4.23.cpp)

### 4.4.6 Waiting for the first future in a set with when_any

[listing_4.24.cpp](../listings/listing_4.24.cpp)