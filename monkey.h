#ifndef __MONKEY_H__
#define __MONKEY_H__
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <tr1/unordered_map>
#include <algorithm>

namespace bm { // my namespace
  // find the absolute sum of digits of given num 
  // useful func so put it in global scope within namespace
  size_t SumDigits(const int& num, const int& base = 10)
  {
    //std::cout << "I come here\n";
    assert(base != 0);
    // return this result
    size_t res = 0; 
    //
    int absnum = abs(num);
    int quo = 0; //quotient
    int rem = 0; //reminder
    while(true){
      quo = (int)(absnum/base);
      rem = absnum - (quo*base);
      //std::cout << "quo:" << quo << " rem:" << rem << "\n";
      res += rem;
      if(quo == 0)
	break;
      absnum = quo;
    }
    return res;
  }

  // typedef x,y coordinate pair
  typedef std::pair<int,int> Coord;

  // idea of cantor pairing from www.stackoverflow.com
  // generate hash function given a pair of integers, including negative
  // numbers
  class hashfunc {
  public:
    size_t operator()(const Coord& pair_xy) const
    {
      int sx = pair_xy.first;
      int sy = pair_xy.second;
      int x = abs(sx);
      int y = abs(sy);
      assert(x >=0 && y >=0);
      size_t h = 0;
      // cantor pairing function f(Z,Z) -> N
      size_t hx = (size_t)((x+y)*(x+y+1)/2) + y;
      //
      if(sx >= 0 && sy >= 0)
	h = hx*2; 
      else
	h = (hx*2)-1;
      
      //std::cout << "Hash value for:(" << sx << "," 
      //	<< sy << ")is:" << h << "\n";
      
      return h;
    }
  };

  // using hashmap to expedite look up.
  // could have used map as well but with little slower lookup
  typedef std::tr1::unordered_map<Coord,int,hashfunc> hashMap;  
  
  // a utility class to keep tab of visited and prohibited places
  // the places visited/prohibited are stored in hash map  
  class MapStore {
    hashMap visitedMap; // valid positions that can be visited
    hashMap prohibitedMap; // invalid positions 
    
    // hide
    MapStore(const MapStore&);
    MapStore& operator=(const MapStore&);
    
  public:
    MapStore():visitedMap(),prohibitedMap(){}
    ~MapStore() {}
  
    // look up to see if given x,y pair has been visited before or not
    bool isVisited(int x, int y)
    {
      return (visitedMap.find(Coord(x,y)) != visitedMap.end());
    }
    // look up to see if given x,y pair has been visited before or not
    bool isProhibited(int x, int y) 
    {
      return (prohibitedMap.find(Coord(x,y)) != prohibitedMap.end());
    }
    // insert into visited hashmap, no check to see
    // if already element exists or not
    void insertVisited(int x, int y)
    {
      visitedMap[Coord(x,y)] = 1;
    }
    // insert into prohibited hashmap
    void insertProhibited(int x, int y)
    {
      prohibitedMap[Coord(x,y)] = 1;
    }
    // size of visited map
    size_t visitedCount() {
      return visitedMap.size();
    }
    // size of prohibited map (not used)
    size_t prohibitedCount() {
      return prohibitedMap.size();
    }

  }; // MapStore



} //namespace

#endif //__MONKEY_H__
