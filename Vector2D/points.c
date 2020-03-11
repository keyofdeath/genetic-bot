#include <math.h>
#include "points.h"

/// @return le vecteur p-q
Point Point_sub( Point p, Point q )
{
  p.x[ 0 ] -= q.x[ 0 ]; 
  p.x[ 1 ] -= q.x[ 1 ]; 
  return p;
}

/// @return le vecteur p+q
Point Point_add( Point p, Point q )
{
  p.x[ 0 ] += q.x[ 0 ]; 
  p.x[ 1 ] += q.x[ 1 ]; 
  return p;
}

/// @return le vecteur c.p (multiplication scalaire d'un vecteur)
Point Point_mul( double c, Point p )
{
  p.x[ 0 ] *= c;
  p.x[ 1 ] *= c;
  return p;
}

/// @return le produit scalaire p * q
double Point_dot( Point p, Point q )
{
  return p.x[ 0 ] * q.x[ 0 ] + p.x[ 1 ] * q.x[ 1 ];
}

/// @return la norme au carré du vecteur p.
double Point_norm2( Point p )
{
  return Point_dot( p, p );
}

/// @return la norme du vecteur p.
double Point_norm( Point p )
{
  return sqrt( Point_norm2( p ) );
}

/// @return la distance entre les deux points p et q, qui est aussi la norme de p-q.
double Point_distance( Point p, Point q )
{
  return Point_norm( Point_sub( p, q ) );
}

/// @return le vecteur de norme 1 aligné avec le vecteur p.
Point Point_normalize( Point p )
{
  return Point_mul( 1.0/Point_norm( p ), p );
}

/// @return la distance entre (x1,y1) et (x2,y2).
double distance( double x1, double y1, double x2, double y2 )
{
  return sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) );
}

/// @return Converti l'angle en radian
double to_Rand(double angle){
    return (3.14159265359 * angle) / 180.0;
}

///@return Renvoie 1 si le point p et entre p1 et p2
int Point_in_range(Point p1, Point p2, Point p){

    return p1.x[0] <= p.x[0] && p.x[0] <= p2.x[0] && p1.x[1] <= p.x[1] && p.x[1] <= p2.x[1];

}

/**
 * Deplasse le point en fonction de l'angle donnée et de la distance donnée
 * @param angle angle de deplassement
 * @param distToAdd distance a se déplasser
 * @param p
 */
void Point_add_angle(double angle, double distToAdd, Point* p){

    double rad;
    // Point PdistToAdd;
    rad = to_Rand(angle);
    p->x[0] += distToAdd * cos(rad);
    p->x[1] -= distToAdd * sin(rad);

}

/// @return cree un nouveaux point
Point newPoint(double x, double y){

    Point p;
    p.x[0] = x;
    p.x[1] = y;
    return p;
}

