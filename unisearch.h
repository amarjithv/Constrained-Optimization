#include<bits/stdc++.h>
using namespace std;
int get_func_evals();
double obj_fun(vector<double> x, int qno);
vector<double> get_x(double x);
double first_derivative(int k, double y, int fno);
double second_derivative(int k, double y, int fno);
double absolute_value(double value);
double newton_raphson(vector<double> x_k, vector<double> s_k, double eph,int fno);
pair <double, double> bounding_phase(float a, float delta, int fno);

