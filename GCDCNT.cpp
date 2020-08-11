#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree <int, null_type, less<int> , rb_tree_tag, tree_order_statistics_node_update> ordered_set;
const int MAXN = 1e5+7;
ordered_set mult[MAXN];
vector<int> primos, divvprim;
bool composto[MAXN];
int n, a[MAXN],q;
void generate(int num){//generate vector of prime divvisor (divvprim)
    int ip = 0;
    //printf("LETS DO IT %d : ", num);
    while(primos[ip]*primos[ip] <= num){
        if(num%primos[ip] == 0){
           // printf("%d ", primos[ip]);
            divvprim.push_back(primos[ip]);
        }
        while(num%primos[ip] == 0){
            num = num/primos[ip];
        }
        ip++;
    }
    if(num > 1){
        divvprim.push_back(num);
        //printf("%d ", num);
    }
    //printf("\n");
}
int divv = 1;
int val; bool add;
void upt(int idx){
    if(idx == divvprim.size()){
        //printf("GEREI %d para %d\n", divv, val);
        if(add)mult[divv].insert(val);
        else mult[divv].erase(val);
    }else{
        divv *= divvprim[idx];
        upt(idx+1);
        divv = divv/divvprim[idx];
        upt(idx+1);
    }
}
int pega = 0;
int ans = 0, li,ri;
void incl_exc(int idx){
    if(idx == divvprim.size()){
        if(pega%2 == 0){
            //cout<<"ADD "<<divv<<"   "<<mult[divv].size()<<endl;
            ans += mult[divv].order_of_key(ri+1) - mult[divv].order_of_key(li);
        }else{
            //cout<<"REMOVE "<<divv<<"   "<<mult[divv].size()<<endl;
            ans -= mult[divv].order_of_key(ri+1) - mult[divv].order_of_key(li);
        }
    }else{
        divv = divv*divvprim[idx]; pega++;
        incl_exc(idx + 1);
        divv = divv/divvprim[idx]; pega--;
        incl_exc(idx + 1);
    }
}
int main(){
    for(int i=2; i<MAXN; i++){
        if(composto[i])continue;
        primos.push_back(i);
        for(int j=2*i; j<MAXN; j+=i)composto[j]=true;
    }
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%d", &a[i]);
        divvprim.clear();
        generate(a[i]);
        val = i; add = true;
        upt(0);
    }
    scanf("%d", &q);
    while(q--){
        int tp; scanf("%d", &tp);
        if(tp==1){
            int x,y; scanf("%d %d", &x, &y);
            
            divvprim.clear();
            generate(a[x]);
            val = x; add = false;
            upt(0);

            divvprim.clear();
            generate(y);
            val = x; add = true;
            upt(0);

            a[x] = y;
        }else{
            int gi; scanf("%d %d %d", &li, &ri, &gi);

            divvprim.clear();
            generate(gi);
            ans = 0;
            incl_exc(0);

            printf("%d\n", ans);
        }
    }
}