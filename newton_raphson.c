#include <bits/stdc++.h>
double fx[100000][3];
int nfunc=0;

double obj_fun(double x, int fno){
        double func;
        if (fno==0){
                func=pow(x,5)+10*pow(x,2)+2*x;
        }
        else{
                func=pow(x,3)-12*x+3;
        }
        return func;
}

double first_derivative(int k, double y, int fno){
        double delx, fd_x;
        if (abs(y)>0.01)
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
        if (abs(y)>0.01)
                delx=0.01*y;
        else
                delx=0.0001;
	fx[k][1]=obj_fun(y, fno);
	nfunc=nfunc+1;
        sd_x=(fx[k][0]+fx[k][2]-2*fx[k][1])/(pow(delx,2.0));
        return sd_x;
}

double abs(double value){
        if (value < 0)
                return 0.0-value;
        else
                return value;
}

double newton_raphson(double init_value,double eph,int fno){
        double arr[1000][3];
        arr[0][0]=init_value;
        int i=0;
        int k=1;
        arr[0][1]=first_derivative(i, arr[0][0], fno);
        do{
                arr[i][2]=second_derivative(i, arr[i][0], fno);
                i=i+1;
                printf("\nIteration #%d: value of x(%d)=%f", i, i, arr[i-1][0]);
                arr[i][0]=arr[i-1][0]-(arr[i-1][1]/arr[i-1][2]);
                arr[i][1]=first_derivative(i, arr[i][0], fno);

                if (abs(arr[i][1])<eph){
                        printf("\nAbsolute(f′(x(k+1))<e), so Terminate");
                        break;
                }
                

                
        }while(abs(arr[i][1])>eph);
        return arr[i][0];

        
}

int main()
{
	double init=1.0;
	printf("\nObjective function1:Q1");
        double optimal_point = newton_raphson(init,0.001,0);
        printf("\n\n\nOptimal point for the given function exists at x=%f ", optimal_point);
	printf("\nNo of function evaluations = %d\n\n\n",nfunc);
	nfunc=0;
        printf("Objective function2:Q2");
        double opti_point = newton_raphson(init,0.001,1);
        printf("\n\n\nOptimal point for the given function exists at x=%f ", opti_point);
	printf("\nNo of function evaluations = %d\n\n\n",nfunc);	
        return 0;

}
