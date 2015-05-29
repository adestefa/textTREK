#include "Map.h"


    // constructors!
    Path::Path() {
        rows[10];
        cols[10];
    }
    Path::Path(int row, int col) {
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
