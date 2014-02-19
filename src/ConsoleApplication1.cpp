// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NQueens.hpp"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[]) {
  //std::cout << NQueens::GeneralSearch1<2>() << std::endl;
  //std::cout << NQueens::GeneralSearch1<3>() << std::endl;
#define NQGS(NN) \
	std::cout << "Running experiment for " << NN << "..." << std::endl; \
	try { std::cout << NQueens::GeneralSearch1<NN>() << std::endl;} \
	catch (std::exception& e) { std::cout<<e.what(); }; \
	std::cout << std::endl;
  NQGS(1);
  NQGS(2);
  NQGS(3);
  NQGS(4);
  NQGS(5);
  NQGS(6);
  NQGS(7);
  NQGS(8);
  char c;
  std::cin >> c;
  return 0;
}

