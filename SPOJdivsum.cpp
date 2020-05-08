/*SPOJ DIVSUM
  Using linear sieve to compute multiplicative function
  in this case function is sum of divisors*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5e5+7;
ll func[MAXN];//multiplicative function
ll cnt[MAXN];//cnt[i] = all factors in factorization of i due to smallest prime divisor cnt[8]=8, cnt[28]=4, cnt[10]=2
bool composite[MAXN];
vector<ll> primes;
int main(){
    func[1] = 1;//same for all multiplicative functions
    cnt[1] = 1;
    for(ll i=2; i<MAXN; i++){
        if(!composite[i]){//base case: value of function at prime   
            func[i] = i+1;
            cnt[i] = i;
            primes.push_back(i);
        }
        //now we visit all numbers num such that i*(smallest prime divisor) == num
        //each num only has one smallest prime divisor => each num is visited only once
        for(int j=0; j<(int)primes.size() && i*primes[j]<MAXN; j++){
            ll num = i*primes[j];
            composite[num] = true;
            if(i%primes[j] == 0){//i*primes[j+1] will also have primes[j] as divisor, but then primes[j+1] is not smallest prime divisor, so we break!
                cnt[num] = primes[j]*cnt[i];
                //func[num] = func[num/cnt[num]]*func[cnt[num]]
                //but we cant do this because if cnt[num]==num we get 0, so compute func[cnt[num]] explicitly
                ll aux = (cnt[num]*primes[j] - 1LL)/(primes[j]-1LL);
                //for sum of divisors f(p^k) = 1+p+...+p^k = (p^(k+1) - 1)/(p-1)
                func[num] = func[num/cnt[num]]*aux;
                break;
            }else{
                cnt[num] = primes[j];
                func[num] = func[i]*func[primes[j]];
            }
        }
    }
    int tc; scanf("%d", &tc);
    while(tc--){
        ll n; scanf("%lld", &n);
        printf("%lld\n", func[n] - n);
    }
}
