#include <bits/stdc++.h>
//#include <conio.h>
//#include <Python.h>

using namespace std;

double fx[100000][3];
int nfunc=0;
vector<double> function;

double absolute_value(double value);

double obj_fun(double x, int fno){
        double func;
        if (fno==1){
                func=pow(x,5)+10*pow(x,2)+2*x;
        }
        else if(fno==2){
                func=pow(x,3)-12*x+3;
        }
        else if(fno==3){
                func=pow(x,3)+5*x*x-3;
        }
        else if(fno==4){
                func=x*x+54/x;
        }
        else if(fno==5){
                func=3*x*x+12/(pow(x,3))-5;
        }
	
        return func;
}

double first_derivative(int k, double y, int fno){
        double delx, fd_x;
        if (absolute_value(y)>0.01)
                delx=0.01*y;
        else
                delx=0.0001;
        fx[k][0]=obj_fun(y+delx, fno);
        fx[k][2]=obj_fun(y-delx, fno);
	nfunc=nfunc+2;
        fd_x=(fx[k][0]-fx[k][2])/(2*delx);
        return fd_x;
}

double second_derivative(int k, double y, int fno){
        double delx, sd_x;
        if (absolute_value(y)>0.01)
                delx=0.01*y;
        else
                delx=0.0001;
	fx[k][1]=obj_fun(y, fno);
	nfunc=nfunc+1;
        sd_x=(fx[k][0]+fx[k][2]-2*fx[k][1])/(pow(delx,2.0));
        return sd_x;
}

double absolute_value(double value){
        if (value < 0)
                return 0.0-value;
        else
                return value;
}

double newton_raphson(double init_value,double eph,int fno){
	ofstream myfile;
	std::string name="newton_raphson";
	std::stringstream ss;
	ss << name << fno << ".txt";
	std::string filename = ss.str();
	myfile.open(filename);
        double arr[1000][3];
        arr[0][0]=init_value;
        int i=0;
        int k=1;
        arr[0][1]=first_derivative(i, arr[0][0], fno);
        do{
		myfile << arr[i][0] << "\n";
                arr[i][2]=second_derivative(i, arr[i][0], fno);
                i=i+1;
                printf("\nIteration #%d: value of x(%d)=%f", i, i, arr[i-1][0]);
                arr[i][0]=arr[i-1][0]-(arr[i-1][1]/arr[i-1][2]);
                arr[i][1]=first_derivative(i, arr[i][0], fno);

                if (absolute_value(arr[i][1])<eph){
                        printf("\nAbsolute(f′(x(k+1))<e), so Terminate");
                        break;
                }
                

                
        }while(absolute_value(arr[i][1])>eph);
	myfile.close();
	printf("\nNo of function evaluations = %d", nfunc);
        return arr[i][0];

        
}


pair <double, double> bounding_phase(float a, float delta, int fno){
	ofstream myfile;
	std::string name="bounding_phase";
	std::stringstream ss;
	ss << name << fno << ".txt";
	std::string filename = ss.str();
	myfile.open(filename);
	myfile << a << "\n";
	vector<double> funct;
	vector<double> x;
        int minima_achieved = 0, maxima_achieved = 0;
        double x0 = a;
	x.push_back(x0);
        double x2;
        double x3;
	double f1, f2, f3;
	f2 = obj_fun(x0, fno);
	nfunc+=1;
	funct.push_back(f2);
	int k = 0;
        do{
		
		myfile << x0 << "\n";
		if (k==0){

			x2 = x0 - absolute_value(delta);
			x3 = x0 + absolute_value(delta);
			f1 = obj_fun(x2, fno);
			f3 = obj_fun(x3, fno);
			nfunc+=2;
                	if (f2 <= f1 && f2 >= f3){
                        	delta = 0 + delta;
                	}
                	if (f2 >= f1 && f2 <= f3){
                        	delta = 0 - delta;
                        
                	}
		}
		x.push_back(x[k]+pow(2,k)*delta);
		k=k+1;
		x0 = x[k];
		f2 = obj_fun(x0, fno);
		funct.push_back(f2);
		nfunc+=1;
        }while(funct[k]<funct[k-1]);
	myfile << x[k] << "\n";
	myfile.close();
        pair <double, double> result(x[k-2], x[k]);
	printf("\nNo of function evaluations = %d", nfunc);
	nfunc = 0;
        return result;
}


int main()
{



        float a, b;
        int n;
	int q;
	printf("Enter a question no to solve in the range[1,5]:");
	scanf("%d", &q);
        printf("\nEnter the value of initial guess, a:");
        scanf("%f", &a);
        printf("\nEnter the value of an increment, delta:");
        scanf("%f", &b);
        pair <double, double> bracket = bounding_phase(a, b, q);
        printf("\n(%f, %f)\n", bracket.first, bracket.second);


//	char filename[] = "plot.py";
//	FILE* fp;
//	Py_Initilize();
//	fp = _Py_fopen(filename, "r");
//	PyRun_SimpleFile(fp, filename);
//	Py_Finalize();

	double init = (bracket.first+bracket.second)/2;
	printf("\nObjective function1:Q1");
        double optimal_point = newton_raphson(init,0.001,q);
        printf("\n\n\nOptimal point for the given function exists at x=%f ", optimal_point);
	printf("\nNo of function evaluations = %d\n\n\n",nfunc);
	nfunc=0;
        return 0;

}
