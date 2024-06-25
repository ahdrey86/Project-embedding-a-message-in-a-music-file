#include <QString>
#include <cmath>
#include "task1.h"

double evaluateFunction(const QString& equation, double x) {
    if (equation == "12 + x") {
        return 12.0 + x;
    } else if (equation == "12 + x*x") {
        return 12.0 + x * x;
    } else if (equation == "12x + 1") {
        return 12.0 * x + 1.0;
    } else {
        return NAN;
    }
}

double evaluateDerivative(const QString& equation, double x) {
    if (equation == "12 + x") {
        return 1.0;
    } else if (equation == "12 + x*x") {
        return 2.0 * x;
    } else if (equation == "12x + 1") {
        return 12.0;
    } else {
        return NAN;
    }
}

QString newtonMethod(QString number_var, QString a, QString b, QString eps) {
    const QStringList function_str1 = {"12 + x", "12 + x*x", "12x + 1"};
    QString equation = function_str1[number_var.toInt()];
    double x0 = a.toDouble();
    double epsilon = eps.toDouble();
    int max_iterations = 1000;
    for (int i = 0; i < max_iterations; ++i) {
        double fx = evaluateFunction(equation, x0);
        double dfx = evaluateDerivative(equation, x0);
        if (qAbs(dfx) < epsilon) {
            break;
        }
        double x1 = x0 - fx / dfx;
        if (qAbs(x1 - x0) < epsilon) {
            return QString::number(x1);
        }
        x0 = x1;
    }

    return "None";
}
