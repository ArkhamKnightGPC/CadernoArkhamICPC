//Golf Bot SPOJ
//FAST FOURIER TRANSFORM
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
const int MAXN = 4e5+7;
typedef complex<double> Complex;
const double PI = acos(-1);
inline vector<Complex> permutacao(const vector<Complex>& a){
	int n = a.size();
	int logn = __builtin_ctz(n);
	vector<Complex> v(n);
	for(int k=0; k<n; k++){
		int rev = 0;
		for(int j=0; j<logn; j++)
			if(k&(1<<j))rev |= (1<<(logn-j-1));
		v[rev] = a[k];
	}
	return v;
}
inline vector<Complex> FFT(vector<Complex> a, const int r){
	int n = a.size();
	int logn = __builtin_ctz(n);
	vector<Complex> v = permutacao(a);
	for(int s=1; s<=logn; s++){
		int m = (1<<s);
		Complex wm(cos(2.0*r*PI/m), sin(2.0*r*PI/m));
		for(int k=0; k<n; k+=m){
			Complex w = 1;
			for(int j=0; 2*j < m; j++){
				Complex t = w*v[k+j+m/2];
				Complex u = v[k+j];
				v[k+j] = u + t;
				v[k+j+m/2] = u - t;
				w *= wm;
			}
		}
	}
	if(r == -1)
		for(Complex& c : v)c /= n;
	return v;
}
inline vector<Complex> multiplica(vector<Complex> a, vector<Complex> b){
	if(a.size() < b.size())swap(a,b);
	int n = a.size();
	while(b.size() < n)
		b.pb(0);
	while((n&(n-1)) != 0){
		n++;
		a.pb(0); b.pb(0);
	}
	vector<Complex> dfta = FFT(a, 1);
	vector<Complex> dftb = FFT(b, 1);
	vector<Complex> c(n);
	for(int k=0; k<n; k++)
		c[k] = dfta[k]*dftb[k];
	c = FFT(c, -1);
	return c;
}
int buraco[MAXN], tacada[MAXN];
int main(){
    fastio;
    int n; cin>>n;
    vector<Complex> v0(MAXN);
    for(int i=0; i<MAXN; i++)v0[i]=0;
    vector<Complex> v1(MAXN);
    for(int i=0; i<MAXN; i++)v1[i]=0;
    v0[0] = 1;
    for(int i=0; i<n; i++){
        int di; cin>>di;
        tacada[i] = di;
        v0[di] = 1; v1[di] = 1;
    }
    int m; cin>>m;
    for(int i=0; i<m; i++){
        int di; cin>>di;
        buraco[i] = di;
    }
    vector<Complex> a1 = multiplica(v0, v0);//soma de duas tacadas = distancia
    int ans = 0;
    vector<Complex> v2(MAXN);
    for(int i=0; i<MAXN; i++)v2[i]=0;
    for(int i=0; i<m; i++){
        if((int)round(a1[buraco[i]].real()) > 0){//encontramos pelo menos 1 jeito de obter a distancia
            ans++;
        }
    }
    cout<<ans<<endl;
}
