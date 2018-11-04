#include<bits/stdc++.h>
#include "unisearch.h"

using namespace std;
vector<double> subtract(vector<double> x, vector<double> y);
double dotpro(vector<double> x);
vector<double> direction(vector<double> x, vector<double> dir_prev, vector<double> fir_der_cur, vector<double> fir_der_prev);
vector<double> first_deriv( vector<double> y, int fno);
double abs_value(double value);
double dotpro2(vector<double> x, vector<double> y);
vector<double> adding(vector<double> x, vector<double> y);
vector<double> multiplying(vector<double> x, double y);

int func_evals = 0;



double abs_value(double value){
        if (value < 0) 
                return 0.0-value;
        else
                return value;
}


vector<double> first_deriv( vector<double> y, int fno){
        vector<double> fd_x;
        double delx=0, fx1=0, fx2=0;
        for(int i=0; i<y.size(); i++){
                if (abs_value(y[i])>0.01)
                        delx=0.01*y[i];
                else
                        delx=0.0001;
                y[i]=y[i]+delx;
                fx1=obj_fun(y, fno);
                y[i]=y[i]-2*delx;
                fx2=obj_fun(y, fno);
		func_evals+=2;
                //nfunc=nfunc+2;
                y[i]=y[i]+delx;
                fd_x.push_back((fx1-fx2)/(2*delx));
        }
        return fd_x;
        }

vector<double> direction(vector<double> dir_prev, vector<double> fir_der_cur, vector<double> fir_der_prev){
        vector<double> fir_der;
        double multiplier = pow(dotpro(fir_der_cur),2)/pow(dotpro(fir_der_prev),2); 
        vector<double> neg_der;
        for(int i=0; i<dir_prev.size(); i++){
                neg_der.push_back(-fir_der_cur[i]);
        }
        vector<double> sec_term = multiplying(dir_prev, multiplier); 
        vector<double> dir = adding(neg_der, sec_term);
        return dir;
}

double dotpro(vector<double> x){
        int n = x.size();
        double sum=0;
        for(int i=0; i<n; i++){
                sum=sum+x[i]*x[i];
        }
        return sqrt(sum);
}


double dotpro2(vector<double> x, vector<double> y){
        int n = x.size();

        double sum1=0, sum2=0, sum3=0;
        for(int i=0; i<n; i++){
                sum1=sum1+x[i]*x[i];
                sum2=sum2+y[i]*y[i];
                sum3=sum3+y[i]*x[i];
        }
        return acos(sum3/(sqrt(sum1)*sqrt(sum2)));

}

vector<double> subtract(vector<double> x, vector<double> y){
        vector<double> z;
        for(int i=0; i<x.size(); i++){
                z.push_back(x[i]-y[i]);
        }
        return z;
}
vector<double> adding(vector<double> x, vector<double> y){
        vector<double> z;
        for(int i=0; i<x.size(); i++){
                z.push_back(x[i]+y[i]);
        }
        return z;
}
vector<double> multiplying(vector<double> x, double y){
        vector<double> z;
        for(int i=0; i<x.size(); i++){
                z.push_back(x[i]*y);
        }
        return z;
}


vector<double> conjugate_gradient(vector<double> x_zero, double eph1, double eph2, double eph3, int fno){
        ofstream myfile, cfile;
        std::string name="cg";
        std::stringstream ss;
        ss << name << fno << ".txt";
        std::string filename = ss.str();
        myfile.open(filename, ofstream::app);
        std::string cname="ctime";
        std::stringstream css;
        css << cname << fno << ".txt";
        std::string cfilename = css.str();
        cfile.open(cfilename, ofstream::app);
	clock_t t;
	vector<double> der_xpresent = first_deriv(x_zero, fno);
        vector<double> cur_dir;
        vector<double> pre_dir;
        vector<double> x_cur;
        for(int i=0; i<x_zero.size(); i++){
                cur_dir.push_back(0-der_xpresent[i]);
        }
        double lamda = newton_raphson(x_zero, cur_dir, eph1, fno);
	func_evals+=get_func_evals();
        for(int i=0; i<x_zero.size(); i++){
                x_cur.push_back(x_zero[i]+lamda*cur_dir[i]);
        }
        pre_dir = cur_dir;

        vector<double> der_xnext = first_deriv(x_cur, fno);
        vector<double> z;
        int k=1;
        do{
		t = clock();
		myfile << x_zero[0] << " " << x_zero[1] << "\n";
                x_zero=x_cur;
                cur_dir = direction(pre_dir, der_xnext, der_xpresent);
                der_xpresent = der_xnext;
                
                if(dotpro2(cur_dir, pre_dir)<=0.4){
			cout << "RESTARTING" << "\n";
			myfile.close();
                        x_cur=conjugate_gradient(x_zero, eph1, eph2, eph3, fno);
			myfile.open(filename, ofstream::app);

                        break;
                }
                lamda = newton_raphson(x_zero, cur_dir, eph1, fno);
                x_cur.clear();
                for(int i=0; i<x_zero.size(); i++){
                        x_cur.push_back(x_zero[i]+lamda*cur_dir[i]);
                }
                der_xnext = first_deriv(x_cur, fno);
                k=k+1;
                z=subtract(x_cur, x_zero);
                cout << "\n" << x_cur[0] << " " << x_cur[1] << "\n";
                pre_dir = cur_dir;
		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC;
		cfile << time_taken << "\n";
        }while(dotpro(z)/dotpro(x_zero)>eph2 && dotpro(der_xnext)>eph3);
	myfile << x_cur[0] << " " << x_cur[1] << "\n";
	myfile.close();
	cfile.close();
	cout << "closed";

        return x_cur;
}


int main(){
        int qno, no_of_inp,p1, p2;
        double x, eph1, eph2, eph3;
        vector<double> x0;
        ifstream infile;
        infile.open("input.txt");
        infile >> qno;
        infile >> no_of_inp;
        infile >> eph1;
        infile >> eph2;
        infile >> eph3;
        p1=no_of_inp;
        p2=p1;
        ofstream myfile, cfile, ffile;
        std::string name="compare";
        std::stringstream ss;
        ss << name << qno << ".txt";
        std::string filename = ss.str();
        myfile.open(filename, ofstream::app);
        std::string cname="func";
        std::stringstream css;
        ss << cname << qno << ".txt";
        std::string cfilename = css.str();
        cfile.open(cfilename, ofstream::app);	
	clock_t t;
        std::string fname="comptime";
        std::stringstream fss;
        ss << fname << qno << ".txt";
        std::string ffilename = fss.str();
        ffile.open(ffilename, ofstream::app);
	int hh=5;	
        while(hh--){
	        while(no_of_inp--){
	                infile >> x;
	                x0.push_back(x);
	        }
	        infile.close();
	        cout << x0[0]  << x0[1] << "\n";
		t=clock();
		vector<double> minima = conjugate_gradient(x0, eph1, eph2, eph3, qno);
		t=clock()-t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC;
		
	        cout << "Optimal point for problem number " << qno << " exists at: " << "\n";
	        int i=0;
	        while(p2--){
	                if(i==p1-1){
	                        cout << "x" << i << " = " << minima[i] << "\n";
				myfile << minima[i] << " ";
	                }
	                else    
	                        cout << "x" << i << " = " << minima[i] << "\n";
				myfile << minima[i] << "\n";
	                i=i+1;
	        }
	       	cout << "No of Function Evaluations = " << func_evals << "\n";
		cfile << func_evals << "\n";
		ffile << time_taken << "\n";
		func_evals=0;
		
	}
	cfile.close();
	myfile.close();
	ffile.close();
		
	
}
