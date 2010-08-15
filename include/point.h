#ifndef PG_POINT_H
#define PG_POINT_H

#include <cstdio>
#include <cmath>

class point {
public:
  point();
  point(int x, int y);
  point(const point& p);

  virtual ~point() {}

  int get_x() {return x;}
  int get_y() {return y;}
  void set_x(int x) {this->x = x;}
  void set_y(int y) {this->y = y;}

  float distance();
  float distance(point &p);

  bool operator==(point &p)     { return (x==p.x && y == p.y); }
  bool operator!=(point &p)     { return !(x==p.x && y == p.y); }

  point& operator+=(point p)    { x+=p.x; y+=p.y; return *this; }
  point& operator-=(point p)    { x-=p.x; y-=p.y; return *this; }
  point& operator*=(int scalar) { x*=scalar; y*=scalar; return *this; }
  point& operator/=(int scalar) { x/=scalar; y/=scalar; return *this; }

  friend point operator+(point&, point&);
  friend point operator-(point&, point&);
  friend point operator*(point&, int scalar);
  friend point operator/(point&, int scalar);

protected:
  int x, y;
};

#endif


