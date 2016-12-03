#ifndef _MAZEALG_CPP_
#define _MAZEALG_CPP_

//edit these to modify how the maze generates
#define paths 6//number of paths created
#define MAX_X 30//number of units wide
#define MAX_Y 30//number of units tall
#define deadends 3//number of deadend paths generated, these are generated independantly of the paths
#define entrancex 12//it is assumed that the entrance is on the bottom edge, this controls where on said edge
#define exitx 7//same as above
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

//pathx and pathy are only used in the generate_maze function, don't worry about them
void pathx(bool (*maze)[MAX_X][MAX_Y], int point1x, int y, int point2x){
  if(point1x < point2x){
    for(int c = point1x; c < point2x; c++){
      (*maze)[c][y] = false;
      //cout << c << ' ' << y << '\n';
    }
  }
  else{
    for(int c = point1x; c > point2x; c--){
      (*maze)[c][y] = false;
      //cout << c << ' ' << y << '\n';
    }
  }
}
void pathy(bool (*maze)[MAX_X][MAX_Y], int x, int point1y, int point2y){
  if(point1y < point2y){
    for(int c = point1y; c < point2y; c++){
      (*maze)[x][c] = false;
      //cout << x << ' ' << c << '\n';
    }
  }
  else{
    for(int c = point1y; c > point2y; c--){
      (*maze)[x][c] = false;
      //cout << x << ' ' << c << '\n';
    }
  }
}

//Call the function using generate_maze(&varname); where varname is an array of bools initialized to all true, with dimensions MAX_X and MAX_Y
void generate_maze(bool (*maze)[MAX_X][MAX_Y]){
  srand(time(NULL));
  int point1x, point1y, point2x, point2y;
  bool xfirst = false;
  point1x = entrancex;
  point1y = 0;
  int xpoints[paths];
  int ypoints[paths];
  for(int c = 0; c < paths; c++){
    bool newpoint;//this is to make sure the paths don't generate too close to each other, xpoints and ypoints track what x and y values have already been used, and if the points are within 1 of one that has been already used, the paths would have a chance of being adjacent to each other, creating a double wide path, so this should prevent that
    do{
      newpoint = true;
      point2x = rand() % (MAX_X - 2) + 1;//less than MAX_X, but greater than 0
      //cout << newxpoint << '\n';
      for(int q = 0; q < c; q++){
        cout << "test " << point2x << " against " << xpoints[q] << " and " << xpoints[q] + 1 << " and " << xpoints[q] - 1 << '\n';
        //cout << (point2x == xpoints[c]) << '\n';
        //cout << (point2x == (xpoints[c] + 1)) << '\n';
        //cout << (point2x == (xpoints[c] - 1)) << '\n';
        if(point2x == (xpoints[q] + 1)){
          newpoint = false;
          cout << "regenerating\n";
        }
        if(point2x == (xpoints[q] - 1)){
          newpoint = false;
          cout << "regenerating\n";
        }
        if(point2x == xpoints[q]){
          newpoint = false;
          cout << "regenerating\n";
        }
      }
    }while(!newpoint);

    do{
      newpoint = true;
      point2y = rand() % (MAX_Y - 2) + 1;//less than MAX_Y, but greater than 0
      //cout << newypoint << '\n';
      for(int q = 0; q < c; q++){
        cout << "test " << point2y << " against " << ypoints[q] <<  " and " << ypoints[q] + 1 << " and " << ypoints[q] - 1 << '\n';
        if(point2y == (ypoints[q] + 1)){
          newpoint = false;
          cout << "regenerating\n";
        }
        if(point2y == (ypoints[q] - 1)){
          newpoint = false;
          cout << "regenerating\n";
        }
        if(point2y == ypoints[q]){
          newpoint = false;
          cout << "regenerating\n";
        }
      }
    }while(!newpoint);
        
    cout << "Set :" << point2x << ' ' << point2y << '\n';
    if(xfirst){
      pathx(maze,point1x,point1y,point2x);
      pathy(maze,point2x,point1y,point2y);
    }
    else{
      pathy(maze,point1x,point1y,point2y);
      pathx(maze,point1x,point2y,point2x);
    }
    xfirst = rand() % 2;
    xpoints[c] = point2x;
    ypoints[c] = point2y;
    point1x = point2x;
    point1y = point2y;
  }
  int deadendxs[deadends];
  int deadendys[deadends];
  for(int c = 0; c < deadends; c++){
    int startpoint = rand() % paths;
    point1x = xpoints[startpoint];
    point1y = ypoints[startpoint];
    bool newpoint;//this is to make sure the paths don't generate too close to each other
    do{
      newpoint = true;
      point2x = rand() % (MAX_X - 2) + 1;//less than MAX_X, but greater than 0
      //cout << newxpoint << '\n';
      for(int q = 0; q < paths; q++){
        if(point2x == (xpoints[q]+1)){
          newpoint = false;
        }
        if(point2x == (xpoints[q]-1)){
          newpoint = false;
        }
        if(point2x == xpoints[q]){
          newpoint = false;
        }
      }
      for(int r = 0; r < c; r++){
        if(point2x == deadendxs[r]){
          newpoint = false;
        }
        if(point2x == (deadendxs[r]+1)){
          newpoint = false;
        }
        if(point2x == (deadendxs[r]-1)){
          newpoint = false;
        }
      }
    }while(!newpoint);
    do{
      newpoint = true;
      point2y = rand() % (MAX_Y - 2) + 1;//less than MAX_Y, but greater than 0
      for(int q = 0; q < paths; q++){
        if(point2y == (ypoints[q]+1)){
          newpoint = false;
        }
        if(point2y == (ypoints[q]-1)){
          newpoint = false;
        }
        if(point2y == ypoints[q]){
          newpoint = false;
        }
      }
      for(int r = 0; r < c; r++){
        if(point2y == deadendys[r]){
          newpoint = false;
        }
        if(point2y == (deadendys[r]+1)){
          newpoint = false;
        }
        if(point2y == (deadendys[r]-1)){
          newpoint = false;
        }
      }
    }while(!newpoint);
    cout << "Start " << point1x << ' ' << point1y << '\n';
    cout << "Dead :" << point2x << ' ' << point2y << '\n';
    xfirst = rand() % 2;
    if(xfirst){
      pathx(maze,point1x,point1y,point2x);
      pathy(maze,point2x,point1y,point2y);
    }
    else{
      pathy(maze,point1x,point1y,point2y);
      pathx(maze,point1x,point2y,point2x);
    }
    deadendxs[c] = point2x;
    deadendys[c] = point2y;
  }
  pathx(maze,xpoints[paths-1],ypoints[paths-1],exitx);
  pathy(maze,exitx,ypoints[paths-1],MAX_Y);
}
    
#endif
