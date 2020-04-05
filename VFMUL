//FFT

#include<bits/stdc++.h>

using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
typedef complex<double> Complex;
const double PI = acos(-1);
//const => funcao nao altera vetor
//& => nem faz copia
vector<Complex> permutacao(const vector<Complex>& a){
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
vector<Complex> FFT(vector<Complex> a, const int r){
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
vector<Complex> multiplica(vector<Complex> a, vector<Complex> b){
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
vector<Complex> pol(string s){
	vector<Complex> a;
	int n = s.size();
	for(int i=0; i<n; i++)a.pb(s[i]-'0');
	reverse(a.begin(), a.end());
	//multiplicacao pode dobrar numero de digitos
	for(int i=0; i<n; i++)a.pb(0);
	return a;
}
int main(){
	fastio;
	int tc; cin>>tc;
	while(tc--){
		string s1,s2;
		cin >> s1 >> s2;
		vector<Complex> a,b,c;
		a = pol(s1); b = pol(s2);
		c = multiplica(a, b);
		vector<int> ans;
		for(Complex& i : c)ans.pb((int)round(i.real()));
		//precisamos cuidar dos vai-um
		for(int i=0; i<ans.size()-1; i++){
			ans[i+1] += ans[i]/10;
			ans[i] = ans[i]%10;
		}
		//precisamos tirar zeros a esquerda
		int tam = ans.size();
		while(ans[tam-1] == 0 && tam > 1){
			ans.pop_back(); tam--;
		}
		reverse(ans.begin(), ans.end());//para imprimir
		for(int& i : ans)cout<<i;
		cout<<endl;
	}
}
