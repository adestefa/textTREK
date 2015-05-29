#include "Map.h"


    // constructors!
    Map::Map() {
        rows[10];
        cols[10];
    }
    Map::Map(int row, int col) {
        rows[0] = row;
        cols[0] = col;
    }



  int getRow(index) {
    return rows[index];
  }

  int getCol(index) {
    return cols[index];
  }


  int rows[10];
  int cols[10];
