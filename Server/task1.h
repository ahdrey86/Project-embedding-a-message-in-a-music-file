#ifndef TASK1_H
#define TASK1_H
#include <QObject>
#include <cmath>

double evaluateFunction(const QString& equation, double x);
double evaluateDerivative(const QString& equation, double x);
QString newtonMethod(QString number_var, QString a, QString b, QString eps);

#endif // TASK1_H
