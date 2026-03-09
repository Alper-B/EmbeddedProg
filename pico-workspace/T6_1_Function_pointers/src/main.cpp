/**
 * @file main.cpp
 * @brief Template implementation for function pointers and std::function.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 6 Task 6.1: Function Pointers.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#include <cassert>
#include <functional>
#include <iostream>

/**
 * Task Description (Module 6 Task 6.1: Function Pointers)
 *
 * Goal:
 * - Use ``std::function`` as a callback wrapper for free functions and
 *   class member functions.
 *
 * Requirements:
 * 1. Implement global ``function1`` and ``function2``.
 *    - function1(a, b) returns a + b + 1
 *    - function2(a, b) returns a * b + 1
 * 2. Implement class ``MyClass`` with member functions:
 *    - function1(a, b) returns a + b
 *    - function2(a, b) returns a * b
 * 3. In ``main()``, declare ``std::function<int(int, int)> cb``.
 * 4. Assign ``cb`` to each callable (global/member) and print results.
 */

int function1(int a, int b) {
    return a + b + 1;
}

int function2(int a, int b) {
    return a * b + 1;
}

class MyClass {
public:
    int function1(int a, int b) {
        return a + b;
    }
    
    int function2(int a, int b) {
        return a * b;
    }
};

int main() {
	MyClass mObj;
	assert(function1(0, 0) == 1);
	assert(function2(0, 0) == 1);
	assert(mObj.function1(0, 0) == 0);
	assert(mObj.function2(0, 0) == 0);

	// Don't modify the code above. You can use the functions and the class as you wish
	// ---------------------------------------------------------------------------------
	// Start your implementation below

	// TODO: declare std::function callback named cb with the correct signature
	std::function<int(int, int)> cb;

	// IMPORTANT: keep the std::cout output lines and text unchanged.
	// The automatic grader validates exact stdout output.

	// Assign cb to global function1
	// TODO: assign cb to global function1
	cb = function1;
	std::cout << "callback(1, 2) with global function1 returns " << cb(1, 2) << std::endl;

	// Assign cb to global function2
	// TODO: assign cb to global function2
	cb = function2;
    std::cout << "callback(1, 2) with global function2 returns "
              << cb(1, 2)
              << std::endl;

	// Assign cb to MyClass::function1
	// TODO: bind/capture MyClass::function1 so cb(1, 2) works
	cb = [&mObj](int a, int b) { return mObj.function1(a, b); };
	std::cout << "callback(1, 2) with MyClass::function1 returns "
              << cb(1, 2)
              << std::endl;

	// Assign cb to MyClass::function2
	// TODO: bind/capture MyClass::function2 so cb(1, 2) works
	cb = [&mObj](int a, int b) { return mObj.function2(a, b); };
	std::cout << "callback(1, 2) with MyClass::function2 returns "
              << cb(1, 2)
              << std::endl;

	return 0;
}
