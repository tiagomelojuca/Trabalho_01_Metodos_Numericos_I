#ifndef REFINAMENTO_H
#define REFINAMENTO_H

double newton(double d0, double e1, double e2, int maxIter, double a);

double newton_modificado(double d0, double e1, double e2, int maxIter, double a);

double secante(double x0, double x1, double e1, double e2, int maxIter, double a);

#endif