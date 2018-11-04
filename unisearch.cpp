#include <bits/stdc++.h>
#include "unisearch.h"
using namespace std;

double fx[100000][3];//Declaring a 2D matrix for storing evaluated function values, first derivative and second derivative 
int nfunc=0;//variable to count number of function evaluations
vector<double> x_val, dire, x_fin;
vector<double> function;
vector<double> get_x(double x);
double absolute_value(double value);
int get_func_evals();
//five test problems
       

double obj_fun(vector<double> x, int qno){
        double fx=0.0;
     
        if (qno==1){
                for( int i=0; i<x.size(); i++){
                        fx=fx+(i+1)*x[i]*x[i];
                }
                return fx;
        }
        else if (qno==2){
                for( int i=0; i<x.size()-1; i++){
                        fx=fx+100*(x[i+1]-x[i]*x[i])*(x[i+1]-x[i]*x[i])+pow(x[i]-1, 2); 
                }
                return fx; 
    
        }
        else if (qno==3){
                for(int i=0; i<x.size(); i++){
			fx=fx+pow(x[i]-1,2);
		}
                for(int i=1; i<x.size(); i++){
			fx=fx-x[i]*x[i-1];
		}

                return fx; 
     
        }
        else if (qno==4){
                fx=pow(x[0]-1,2);
                for( int i=1; i<x.size(); i++){
                        fx=fx+pow(2*x[i]*x[i]-x[i-1],2)*(i+1);
                }
                return fx; 
            
        }   
        else if (qno==5){
                fx = 0.26*(x[0]*x[0]+x[1]*x[1])-0.48*x[0]*x[1];
                return fx; 
    
        }
	else if(qno==6){
            fx=pow(x[0]*x[0]+x[1]-11,2)+pow(x[1]*x[1]+x[0]-7,2);
	    
        }
	return fx;

} 

vector<double> get_x(double x){
	for(int i=0; i<x_val.size(); i++){
		x_fin.push_back(x_val[i]+x*dire[i]);
	}
	return x_fin;

}


//calculate first derivative for Newton-raphson method
double first_derivative(int k, double y, int fno){
        double delx, fd_x;
	//get the value of delx
        if (absolute_value(y)>0.01)
                delx=0.01*y;
        else
                delx=0.0001;
        fx[k][0]=obj_fun(get_x(y+delx), fno);//calculate f(x+del_x)
	x_fin.clear();
        fx[k][2]=obj_fun(get_x(y-delx), fno);//calculate f(x-del_x)
	x_fin.clear();
	nfunc=nfunc+2;//two function calls made above
        fd_x=(fx[k][0]-fx[k][2])/(2*delx);//first derivative
        return fd_x;
}
//calculate second derivative for Newton-raphson method
double second_derivative(int k, double y, int fno){
        double delx, sd_x;
	//get the value of del_x
        if (absolute_value(y)>0.01)
                delx=0.01*y;
        else
                delx=0.0001;
	fx[k][1]=obj_fun(get_x(y), fno);//calculate f(x)
	x_fin.clear();
	nfunc=nfunc+1;//one function call made above
        sd_x=(fx[k][0]+fx[k][2]-2*fx[k][1])/(pow(delx,2.0));//second derivative
        return sd_x;
}
//Funtion to get the absolute value of a number
double absolute_value(double value){
        if (value < 0)
                return 0.0-value;
        else
                return value;
}



//Function for Newton-Raphson method -- gradient descent method
double newton_raphson(vector<double> x_k, vector<double> s_k, double eph,int fno){
	//write the values of x in every iteration to a text file for plotting
	ofstream myfile;
	std::string name="newton_raphson";
	std::stringstream ss;
	ss << name << fno << ".txt";
	std::string filename = ss.str();
	myfile.open(filename);
	double ubound, lbound;
	x_val=x_k;
	dire=s_k;
	pair<double, double> bounds = bounding_phase(0.0, 0.5, fno);
	ubound = bounds.first;
	lbound = bounds.second;
	double init_value = (ubound+lbound)/2;	
        double arr[1000][3];//store the value of f(x), first derivative of f(x), second derivative of f(x)
        arr[0][0]=init_value;
        int i=0;
        int k=1;
        arr[0][1]=first_derivative(i, arr[0][0], fno);
        do{
		myfile << arr[i][0] << "\n";//write the value of x to text file
                arr[i][2]=second_derivative(i, arr[i][0], fno);
                i=i+1;//updating iterating variable to calculate function values for i+1
                arr[i][0]=arr[i-1][0]-(arr[i-1][1]/arr[i-1][2]);// calculate the value of x(i+1)
                arr[i][1]=first_derivative(i, arr[i][0], fno);//first derivative of f(x(i+1))

                if (absolute_value(arr[i][1])<eph){
                        break;
                }
                

                
        }while(absolute_value(arr[i][1])>eph);//terminating condition checking
	myfile << arr[i][0] << "\n";
	myfile.close();
        return arr[i][0];

        
}

//Function for bounding phase method for bracketting the optimal point
pair <double, double> bounding_phase(float a, float delta, int fno){
	//write the values of x in every iteration to a text file for plotting
	ofstream myfile;
	std::string name="bounding_phase";
	std::stringstream ss;
	ss << name << fno << ".txt";
	std::string filename = ss.str();
	myfile.open(filename);
//	printf("ethiyo");

	vector<double> funct;//store calculated function values
	vector<double> x;//store the value of x after every iteration
        int minima_achieved = 0, maxima_achieved = 0;
        double x0 = a;//intial guess x(0)
	x.push_back(x0);//updating vector x
        double x2;
        double x3;
	double f1, f2, f3;//f(x-abs(delta)), f(x), f(x + abs(delta))
	f2 = obj_fun(get_x(x0), fno);//calculate f(x)
	x_fin.clear();
	nfunc+=1;//one function call made above
	funct.push_back(f2);//updating vector funct
	int k = 0;//initializing iterating variable
        do{
//		cout<<"addadaw";	
		myfile << x0 << "\n";
		//identifying the direction in which to search
		if (k==0){

			x2 = x0 - absolute_value(delta);
			x3 = x0 + absolute_value(delta);
			f1 = obj_fun(get_x(x2), fno);
			x_fin.clear();
			f3 = obj_fun(get_x(x3), fno);
			x_fin.clear();
			nfunc+=2;
                	if (f2 <= f1 && f2 >= f3){
                        	delta = 0 + delta;
                	}
                	if (f2 >= f1 && f2 <= f3){
                        	delta = 0 - delta;
                        
                	}
		}
		x.push_back(x[k]+pow(2,k)*delta);//calculating x(k+1) and updating vector x
		k=k+1;
		x0 = x[k];//updating  value of x from x(k) to x(k+1)

		f2 = obj_fun(get_x(x0), fno);
		x_fin.clear();
		funct.push_back(f2);
		nfunc+=1;
        }while(funct[k]<funct[k-1]);//terminating condition checking
//	cout << "lalal";
	myfile << x[k] << "\n";
	myfile.close();
	pair <double, double> result;
	if (x[k]>x[k-2]){
		
		result.second = x[k];
		result.first = x[k-2];//storing the lower bound and upper bound of the bracket as a pair to return as an output
	}
	else{
		result.second = x[k-2];
        	result.first = x[k];//storing the lower bound and upper bound of the bracket as a pair to return as an output
	}
//	printf("bbb");

        return result;
}

int get_func_evals(){
	int p = nfunc;
	nfunc = 0;
	return p;
}


/*int main()
{


	//Bounding Phase
        float a, b;//initial guess, increment(delta)
        int n;
	int q;
	clock_t t;//variable to calculate computation time
	
	printf("Enter a question no to solve in the range[1,5]: ");
	scanf("%d", &q);
	printf("\n\nBounding Phase Method for bracketting the optimal point");
        printf("\nEnter the value of initial guess, x(0): ");
        scanf("%f", &a);
        printf("\nEnter the value of an increment, delta: ");
        scanf("%f", &b);
	t = clock();
        pair <double, double> bracket = bounding_phase(a, b, q);//call the bracketting method
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // converting time taken to seconds
        printf("\nOptimal point for the problem exists in the range(%f, %f)\n", bracket.first, bracket.second);
	printf("Compution time for bracketting method = %f seconds", time_taken);

	//Newton-Raphson
	double init = (bracket.first+bracket.second)/2;//initial guess for Newton-Raphson method taken as the average of bounding values from Bounding phase method
	printf("\n\nNewton-Raphson method for calculating optimal point");
	t = clock();
        double optimal_point = newton_raphson(init,0.001,q);//calling the Newton-Raphson method
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        printf("\nOptimal point for the given function exists at x = %f ", optimal_point);
	printf("Compution time for Newton-Raphson method = %f seconds", time_taken);
	
        return 0;

}*/
