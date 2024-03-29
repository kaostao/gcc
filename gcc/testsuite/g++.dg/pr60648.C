/* { dg-do compile } */
/* { dg-do compile { target i?86-*-* x86_64-*-* } } */
/* { dg-options "-O3 -fPIC -m32" }  */

enum component
{
  Ex,
  Ez,
  Hy,
  Permeability
};
enum derived_component
{};
enum direction
{
  X,
  Y,
  Z,
  R,
  P,
  NO_DIRECTION
};
derived_component a;
component *b;
component c;
direction d;
inline direction fn1 (component p1)
{
  switch (p1)
    {
    case 0:
      return Y;
    case 1:
      return Z;
    case Permeability:
      return NO_DIRECTION;
    }
  return X;
}

inline component fn2 (direction p1)
{
  switch (p1)
    {
    case 0:
    case 1:
      return component ();
    case Z:
    case R:
      return component (1);
    case P:
      return component (3);
    }
}

void fn3 ()
{
  direction e;
  switch (0)
  case 0:
  switch (a)
    {
    case 0:
      c = Ex;
      b[1] = Hy;
    }
  e = fn1 (b[1]);
  b[1] = fn2 (e);
  d = fn1 (c);
}



