#include "NQueens.hpp"
#include <vector>
#include <thread>
#include <mutex>

namespace NQueens {
  template<int N>
  struct Backtracking {
	  Backtracking() : mFoundSolution(false), mSolution() { }
	  /// @return Solution was found
	  bool FindSolution(State<N> const& currentSolution) {
		  if(currentSolution.IsSolution()) {
			  mFoundSolution=true;
			  mSolution = currentSolution;
			  return true;
		  }


		  /// Generate next solutions in-line
		  {
			NQueens::Precision const x = (currentSolution.empty()) ? 0 : (currentSolution.LastXOccupied()+1);
			NQueens::Precision const oldY = (currentSolution.empty()) ? 0 : (currentSolution.LastYOccupied());
			NQueens::Precision const initialY = (oldY +1)%N;
			NQueens::Precision const lastY = (oldY==-1) ? 0 : oldY;
			NQueens::Precision y = initialY;
			do {
				Queen const candidate(x,y);
				bool const killed = currentSolution.Kills(candidate);
				if(!killed) {
					State<N> const newState(currentSolution, candidate);
					/*if(newState.IsSolution()) {
						mFoundSolution=true;
						mSolution = newState;
						return true;
					} else {*/
						if(FindSolution(newState))
							return true;
					//}
				}
				y = (y+1)%N;
			} while(y!=lastY);
		  }
		  return false;
	  }

	  State<N> const& GetSolution() const { return mSolution; }
  protected:
	  bool mFoundSolution;
	  State<N> mSolution;
  };

  
  template<int N>
  struct Backtracking_MT {
	  Backtracking_MT() : mFoundSolution(false), mSolution() { }
	  /// @return Solution was found
	  bool FindSolution(State<N> const& currentSolution) {
		  if(mFoundSolution) return true;

		  if(currentSolution.IsSolution()) {
			  mFoundSolution=true;
			  mSolution = currentSolution;
			  return true;
		  }

		  std::vector<State<N>> nextSolutions;
		  Operator_PutOne<N>()(currentSolution, nextSolutions);
		  if(nextSolutions.empty()) return false;
		  ///Multithreaded search
		  for(std::size_t p=0; p<nextSolutions.size(); ++p) {
			  if(mThreads.size()<std::thread::hardware_concurrency()) {
				  mThreads.emplace_back([=](){
					Backtracking<N> simpleB;
					simpleB.FindSolution();
				  });
			  }
		  }
		  for(auto const& st : nextSolutions) {
			  Backtracking(st);
		  }
	  }

	  State<N> const& GetSolution() const { return mSolution; }
  protected:
	  bool mFoundSolution;
	  State<N> mSolution;

	  std::vector<std::thread> mThreads;
  };
}