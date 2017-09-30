HashMap is a C++ implementation of a fixed-size hashmap (size specified by user upon instantiation). It handles collisions with linear probing.

It associates string keys with arbitrary data object references, represented by pointers to a templated Value type.

Example usage:

//hm maps strings to pointers to strings, with a capacity of 10 key/value pairs.
HashMap<std::string> hm(10);

All functions are named as specified at http://kpcbfellows.com/engineering/apply, besides delete(), which has a conflict with C++ keyword `delete`. It is named deleteKey() instead.

To compile the source and run tests, run `$sh hashMapRun` from the project directory. `hashMapRun` is essentially a lightweight makefile. If you'd like to verify that I don't leak any memory, feel free to comment out the two lines currently running and uncomment the two currently commented lines to build with debug flags and analyze with valgrind.

A few clarifications on implementation details:
-The phrasing of the prompt ("...associates string keys with arbitrary data object references") was a little ambiguous to me. I have chosen to map strings to Value pointers, where Value is a templated typename. I originally was going to map to Value references, but chose not to, since I felt that "return... null" isn't well defined for functions get() and deleteKey(). Returning NULL leads to major ambiguities if the mapped type are ints or bools, and nullptr is much more explicit.

-In function deleteKey(), the usage of the word 'value' in "...returning the value on success..." was unclear to me. As I'm mapping to pointers instead of references, I took 'value' to mean the mapped Value* returned by get(key), not the dereferenced value of the Value* before deleting it. This means that if deleteKey() succeeds, its return value is a pointer to the memory address freed by deleteKey(), and dereferencing this pointer is undefined behavior.
