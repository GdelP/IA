#pragma once
#include <stdexcept>
#include <set>
#include <vector>
#include <ctime>

template<typename State, typename GenerateSuccesorsT, typename SolveRepeatedElementsT>
State GeneralSearch_ForOneSoution(State& initialState,
				  GenerateSuccesorsT const& GenerateSuccesors,
				  SolveRepeatedElementsT const& SolveRepeatedElements) //throw std::logic_error
{
  std::vector<State> aOpenStates, aClosedStates;
  aOpenStates.reserve(10000);
  aClosedStates.reserve(10000);
  aOpenStates.push_back(initialState);
  State aActual = *(aOpenStates.begin()); /// TODO Copy
  do {
	aActual = (aOpenStates.back()); /// TODO Copy
    aOpenStates.pop_back();
    aClosedStates.push_back(aActual);
    std::vector<State> sons = GenerateSuccesors(aActual);
    SolveRepeatedElements(sons, aOpenStates, aClosedStates);
    aOpenStates.insert(aOpenStates.end(), sons.begin(), sons.end());
  } while(!aActual.IsSolution() && !aOpenStates.empty());
  if(!aActual.IsSolution()) {
    throw std::logic_error("GeneralSearch has been unable to find a solution.");
  }
  return aActual;
}
