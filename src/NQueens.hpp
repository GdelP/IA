#pragma once
#include "GeneralSearch.hpp"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <array>

namespace NQueens {
	typedef unsigned char Precision;
  struct Queen {
	  Queen() : mX(0), mY(0) {}
	  Queen(Precision const x, Precision const y) : mX(x), mY(y) {}
    bool Kills(Queen const& other) const {
      return mX==other.mX ||
			 mY==other.mY ||
			 (std::abs(int(mX)-int(other.mX))==std::abs(int(mY)-int(other.mY))); }
    friend std::ostream& operator<<(std::ostream& out, Queen const& state) {
		out << "[" << int(state.mX) << "," << int(state.mY) << "]";
		return out;
	}
	
	bool operator==(Queen const& other) const {
		return mX==other.mX && mY==other.mY; }
	
	inline Precision const& X() const { return mX;}
	inline Precision const& Y() const { return mY;}
  protected:
    Precision mX;
	Precision mY;
  };
  ///Deprecated
  template<int N>
  struct StateMatrix {
	  StateMatrix() : mQueens() {
	  }
	  StateMatrix(StateMatrix<N>&& ot) : mQueens(std::move(ot.mQueens)) {}
	  ~StateMatrix() {
		  std::cout << "StateMatrix destroyed" << std::endl;
	  }
	void insert(Queen const& other) {
		Precision const xOr = other.X();
		Precision const yOr = other.Y();
		for(Precision x=0; x<N; ++x) {
			mQueens[x][yOr]++;
			for(Precision y=0; y<N; ++y) {

			}
		}
		for(Precision y=0; y<N; ++y)
			mQueens[xOr][y]++;
	}
    bool Kills(Queen const& other) const {
	}
    friend std::ostream& operator<<(std::ostream& out, StateMatrix<N> const& state) {
      out << "{";
      for(Queen const& q: state.mQueens)
	out << q << ", ";
      return out << "}";
    }

	bool has(Queen const& ot) const {
	}
	bool operator==(StateMatrix<N> const& other) const {
	}
	bool empty() const {  }
  protected:
    std::array<std::array<Precision,N>,N> mQueens;
  };


  template<int N>
  struct State {
	  State() {
		  mQueens.reserve(N);
	  }
	  State(State<N> const& ot) : mQueens(ot.mQueens) {}
	  State(State<N> const& ot, Queen const& q) : mQueens(ot.mQueens) {
		  mQueens.push_back(q);
	  }
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
	bool empty() const { return mQueens.empty(); }
	Precision LastXOccupied() const {
		//if(mQueens.empty()) return -1;
		return mQueens.back().X();
	}
	Precision LastYOccupied() const {
		//if(mQueens.empty()) return -1;
		return mQueens.back().Y();
	}
  protected:
    std::vector<Queen> mQueens;
  };

  template<int N>
  struct Operator_PutOne {
    void operator()(State<N> const& initialState, std::vector<State<N>>& stateVector) {
		int const x = (initialState.empty()) ? 0 : (initialState.LastXOccupied()+1);
		int const oldY = (initialState.empty()) ? 0 : (initialState.LastYOccupied());
		int const initialY = (oldY +1)%N;
		int const lastY = (oldY==-1) ? 0 : oldY;
		int y = initialY;
		do {
			Queen const candidate(x,y);
			bool const killed = initialState.Kills(candidate);
			if(!killed) {
				State<N> newState(initialState);
				newState.insert(candidate);
				stateVector.push_back(newState);
			}
			y = (y+1)%N;
		} while(y!=lastY);
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
      });
  };
}
