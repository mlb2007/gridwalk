#include "monkey.h"

namespace bm {
  // return number of possible locations 
  // for the monkey to visit
  class Visit{
    MapStore _map;
    const size_t MonkeyVal;
    
    // hide
    Visit(const Visit&);
    Visit& operator=(const Visit&);

    // check if given x, y sum of digits of x,y together <= 19
    bool isMovePossible(int x, int y)
    {
      size_t xs = SumDigits(x);
      size_t ys = SumDigits(y);
      size_t Sum = xs + ys;
      return  Sum <= MonkeyVal;
    } 

  public:   
    Visit(const int& mval = 19):MonkeyVal(mval){}
    ~Visit(){}

    // got thru all possible locations and register visitations  
    void VisitAllFrom(int x, int y)
    {
      // see if x,y is prohibited and return if so
      if(_map.isProhibited(x,y) == 1){
	//std::cout << "*** prohibited\n";
	return;
      }
      // see if x,y has been visited before and return if so
      if(_map.isVisited(x,y) == 1){
	//std::cout << "*** visited\n";
	return;
      }
      // move is prohibited, so return after insertion
      if(!isMovePossible(x,y)){
	//std::cout << "*** insert prohibited\n";
	_map.insertProhibited(x,y);
	return;
      }

      //std::cout << "*** insert visited\n";
      _map.insertVisited(x,y);
      
      // recurse
      //std::cout << "*** recurse\n";
      VisitAllFrom(x+1,y);
      VisitAllFrom(x-1,y);
      VisitAllFrom(x,y+1);
      VisitAllFrom(x,y-1);
    
      return;
      }

    // return final answer of number of visited locations
    size_t visitedCount()
    {
      return _map.visitedCount();
    }
    
  };

} // namespace

// MAIN
int main(int argc, char**argv)
{
  bm::Visit mvisit;
  mvisit.VisitAllFrom(0,0);
  size_t visited = mvisit.visitedCount();
  std::cout << visited << "\n";

  return 0;
}
