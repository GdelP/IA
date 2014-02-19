#pragma once
#include "GeneralSearch.hpp"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cmath>

namespace NQueens {
  struct Queen {
	  Queen() : mX(0), mY(0) {}
	  Queen(unsigned int const x, unsigned int const y) : mX(x), mY(y) {}
	  ~Queen() {
		  //std::cout << "Queen destroyed" << std::endl;
	  }
    bool Kills(Queen const& other) const {
      return mX==other.mX || mY==other.mY || (std::abs(mX-other.mX)==std::abs(mY-other.mY)); }
    friend std::ostream& operator<<(std::ostream& out, Queen const& state) {
		out << "[" << state.mX << "," << state.mY << "]";
		return out;
	}
	
	bool operator==(Queen const& other) const {
		return mX==other.mX && mY==other.mY; }
  protected:
    int mX, mY;
  };

  template<int N>
  struct State {
	  State() {
	  }
	  State(State<N> const& ot) : mQueens(ot.mQueens) {}
	  State(State<N>&& ot) : mQueens(std::move(ot.mQueens)) {}
	  ~State() {
		  //std::cout << "State destroyed" << std::endl;
	  }
    bool IsSolution() const {
      bool ret=(mQueens.size()==N);
      for(auto it = mQueens.begin(), end=mQueens.end(); it!=end; ++it) {
	auto it2 = it; it2++;
	for(; it2!=end; ++it2) {
	  ret &= !((*it2).Kills(*it));
	}
      }
      return ret;
    }
	void insert(Queen const& other) {
		mQueens.push_back(other);
	}
    bool Kills(Queen const& other) const {
		assert(this);
		return std::any_of(this->mQueens.cbegin(), this->mQueens.cend(), [&other](Queen const& q) {
			return q.Kills(other); });
	}
    friend std::ostream& operator<<(std::ostream& out, State<N> const& state) {
      out << "{";
      for(Queen const& q: state.mQueens)
	out << q << ", ";
      return out << "}";
    }

	bool has(Queen const& ot) const {
		bool r=false;
		for(Queen const& q:mQueens)
			r |= (ot==q);
		return r;
	}
	bool operator==(State<N> const& other) const {
		bool eq=(mQueens.size()==other.mQueens.size());
		for(Queen const& q: mQueens) {
			eq &= other.has(q);
		}
		for(Queen const& q: other.mQueens) {
			eq &= has(q);
		}
		return eq;
	}
  protected:
    std::vector<Queen> mQueens;
  };

  template<int N>
  struct Operator_PutOne {
    void operator()(State<N> const& initialState, std::vector<State<N>>& stateVector) {
      for(unsigned int x=0; x<N; ++x) {
	for(unsigned int y=0; y<N; ++y) {
	  Queen candidate(x,y);
	  bool killed = initialState.Kills(candidate);
	  if(!killed) {
	    State<N> newState(initialState);
	    newState.insert(candidate);
	    stateVector.push_back(newState);
	  }
	}
      }
    }
  };

  template<int N>
  State<N> GeneralSearch1() {
 	  State<N> first;
    return GeneralSearch_ForOneSoution(first
	   , [](State<N> const& aActual) { 
	std::vector<State<N>> successors;
	Operator_PutOne<N>()(aActual, successors);
	return successors;
      }, [](std::vector<State<N>>& sons, std::vector<State<N>> const& aOpenStates, std::vector<State<N>> const& aClosedStates) -> void {
		  for(auto const& st:aOpenStates) {
			  sons.resize(std::distance(sons.begin(), std::remove(sons.begin(), sons.end(), st)));
		  }
		  for(auto const& st:aClosedStates) {
			  sons.resize(std::distance(sons.begin(), std::remove(sons.begin(), sons.end(), st)));
			  //sons.erase(std::remove(sons.begin(), sons.end(), st), sons.end());
		  }
	//Do nothing
      }, [](State<N> const& aState) -> bool {
		  return aState.IsSolution();
      });
  };
}
