// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NQueens.hpp"
#include <iostream>
#include "Backtracking.hpp"

template<typename Callable>
void TimeIt(Callable const& c) {
	clock_t const aTime = clock();
	c();
	clock_t const aTimeEnd = clock();
	std::cout << "Timing: " << float(aTimeEnd-aTime)/CLOCKS_PER_SEC << "\n" << std::endl;
}

template<int NN>
void ExecAll() {
	std::cout << "Running experiment for " << NN << "..." << std::endl;

	if(NN>25) {
		/*
		std::cout << "  Brute-force search: ";
		TimeIt([&](){
			try { std::cout << NQueens::GeneralSearch1<NN>() << std::endl;}
			catch (std::exception& e) { std::cout<< e.what() << std::endl; };
		});
		*/
	}

	std::cout << "  Back-tracking search: ";
	NQueens::Backtracking<NN> b;
	TimeIt([&](){
		try { 	
			NQueens::State<NN> initialState;
			b.FindSolution(initialState);
			std::cout << b.GetSolution() << std::endl;}
		catch (std::exception& e) { std::cout<< e.what() << std::endl; };
	});
}

int _tmain(int argc, _TCHAR* argv[]) {
  //std::cout << NQueens::GeneralSearch1<2>() << std::endl;
  //std::cout << NQueens::GeneralSearch1<3>() << std::endl;
  ExecAll<1>();
  ExecAll<2>();
  ExecAll<3>();
  ExecAll<4>();
  ExecAll<5>();
  ExecAll<6>();
  ExecAll<7>();
  ExecAll<8>();
  ExecAll<9>();
  ExecAll<10>();
  ExecAll<11>();
  ExecAll<12>();
  ExecAll<13>();
  ExecAll<14>();
  ExecAll<15>();
  ExecAll<16>();
  ExecAll<17>();
  ExecAll<18>();
  ExecAll<19>();
  ExecAll<20>();
  ExecAll<21>();
  ExecAll<22>();
  ExecAll<23>();
  ExecAll<24>();
  ExecAll<25>();
  ExecAll<26>();
  ExecAll<27>();
  ExecAll<28>();
  ExecAll<29>();
  ExecAll<30>();
  ExecAll<31>();
  ExecAll<32>();
  ExecAll<33>();
  ExecAll<34>();
  ExecAll<35>();
  ExecAll<36>();
  ExecAll<37>();
  ExecAll<38>();
  ExecAll<39>();
  ExecAll<40>();
  ExecAll<41>();
  ExecAll<42>();
  ExecAll<43>();
  ExecAll<44>();
  ExecAll<45>();
  ExecAll<46>();
  ExecAll<47>();
  ExecAll<48>();
  ExecAll<49>();
  ExecAll<50>();
  //char c;
  //std::cin >> c;
  return 0;
}

