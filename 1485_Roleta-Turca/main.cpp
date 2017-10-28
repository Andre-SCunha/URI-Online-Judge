#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
 
    int S, B, n;
    while(cin >> S >> B){
        if(S==0)
            break;
        vector<int> roll, balls, A[2];
        for (int i = 0; i< S; i++){
            cin >> n;
            roll.push_back(n);
            A[0].push_back(0);
            A[1].push_back(0);
        }
        for (int i = 0; i< B; i++){
            cin >> n;
            balls.push_back(n);
        }
        int min;
        for (int i = 0; i<S; i++){
            for(int j = 0; j<B; j++){
                for(int k = j*2; k<S-1-2*(B-1-j); k++){
                    A[j%2][k] = (roll[(i+k)%S] + roll[(i+k+1)%S])*balls[j];
                    if(j > 0)
                        A[j%2][k] += A[(j-1)%2][k-2];
                    if(k != j*2)
                        A[j%2][k] = A[j%2][k] < A[j%2][k-1]? A[j%2][k] : A[j%2][k-1];
                }
            }
            if(i==0)
                min = A[(B-1)%2][S-2];
            else
                min = min<A[(B-1)%2][S-2]?min:A[(B-1)%2][S-2];
        }
        cout << -min << endl;
    }
 
    return 0;
}