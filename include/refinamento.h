#ifndef REFINAMENTO_H
#define REFINAMENTO_H

// ========== Métodos de refinamento ==========
// método de newton-raphson
double newton(double d0, double e1, double e2, int maxIter, double a);
// método de newton modificado
double newton_modificado(double d0, double e1, double e2, int maxIter, double a);
// método da secante tradicional
double secante(double x0, double x1, double e1, double e2, int maxIter, double a);

#endif