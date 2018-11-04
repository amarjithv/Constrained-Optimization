#include <bits/stdc++.h>

using namespace std;

double funct(double x){
        double f = x*x + 2*x +1;
        return f;
}

pair <double, double> bounding_phase(float a, float b, int n){
        double del_x = (b-a)/n;
        int minima_achieved = 0, maxima_achieved = 0;
        double x1 = a;
        double x2 = x1 + del_x;
        double x3 = x2 + del_x;
        do{
                if (funct(x1) >= funct(x2) && funct(x2) <= funct(x3)){
                        minima_achieved = 1;
                        break;
                }
                if (funct(x1) <= funct(x2) && funct(x2) >= funct(x3)){
                        maxima_achieved = 1;
                        break;
                }

                x1 = x2;
                x2 = x3;
                x3 = x2 + del_x;
        }while(x3 <= b);
        if (minima_achieved == 1)
                printf("\n Point of minima exists in the interval (%f, %f)", x1, x3);
        else if (maxima_achieved == 1)
                printf("\n Point of maxima exists in the interval (%f, %f)", x1, x3);
        else{
                printf("No optimum point exists in the interval (%f, %f) or a boundary point is the optimal point ", a, b);
        }
        pair <double, double> result(x1, x3);
        return result;
}

int main(){
        float a, b;
        int n;
        printf("\nEnter the value of lower bound, a:");
        scanf("%f", &a);
        printf("\nEnter the value of upper bound, b:");
        scanf("%f", &b);
        printf("\nNo of intermediate points:");
        scanf("%d", &n);
        pair <double, double> bracket = bounding_phase(a, b, n);
        printf("\n(%f, %f)\n", bracket.first, bracket.second);
}
