#pragma once
#include <string>
#include <iostream>

using namespace std::literals;

template <typename F>
void RunTestImpl(F func, const std::string& t_str) {
	func();
	std::cerr << t_str << " is OK!"s << std::endl;
}

#define RUN_TEST(func) RunTestImpl((func), #func)

void TestVector2d();

void TestVector3d();

void TestMatrix();

void FullTest();