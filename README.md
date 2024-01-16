# HashMap-Implementation

A **HashMap** is an associative container that stores elements in a key-value format. It utilizes a hash function to map keys to indices in an array, known as a bucket. This hashing technique allows for fast retrieval of values based on their associated keys. In C++, hash maps are implemented using the unordered_map container class from the Standard Template Library (STL).

![hashmap](https://github.com/anush-hambardzumyan/HashMap-Implementation/assets/66312436/9d3f2c6c-0259-4e52-8ce9-f4bb7de93d0e)

I implemented hashmap by the following way.
* the only private member of class is vector.
* each element of vector is std::pair
* first component of pair is the list size
* second component of pair is a list pointer
* list elements are the std::pair type
* first component of pair is key
* second component of pair is value

Most important parts of this implementation are hashing and rehashing mechanisms I implemented.
Hashing is happenning by the given key, and the rehashing is being called when any of lists gets the same size as the private member vector has.

-----
Implementation has following methods

| Method | ReturnType | Funtionality|
| :----- | :----: | :---- |
| put(Key,Value) | void | insert element with given key and value |
| get(Key) | Value | return the value of given key |
| remove(Key) | void | removes the key-value pair of given key |
| containsKey(Key) | bool | return true if key exists, and false in opposite situation |
| containsValue(Value) | bool | return true if value exists, and false in opposite situation |
| size()| int | return the number of key-value pairs |
| isEmpty() | bool | returns true if map has no key-value pairs, and true in opposite situation |
| clear | void | removes all the key-value pairs |
| keySet | vector | returns the set of all keys|
| valueSet | vector | returns the set of all values|
| entrySet | vector | returns the set of all key-value pairs|