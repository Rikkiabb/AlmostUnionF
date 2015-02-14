#include <iostream>
#include <vector>

using namespace std;

int findroot(int p, int structure[]);

int main() {
    int n = 0;
    while(cin >> n){
        
        int structure[n];
        int count[n];
        int sum[n];
        bool hasMoved[n];
        for(int i = 0; i < n; i++){ // Initialize the arrays
            structure[i] = i;
            sum[i] = i + 1;
            count[i] = 1;
            hasMoved[i] = false;
        }
        
        int m = 0;
        scanf("%d", &m);
        
        for(int j = 0; j < m; j++){
            
            int c = 0, p = 0, q = 0;
            scanf("%d", &c);
            if(c == 1 || c == 2){ // If c is 1 or 2, then we need to get to variables, otherwise only one
                scanf("%d%d", &p, &q);
                p--, q--; // because the arrays are zero based
                int rootp = 0;
                int rootq = 0;
                hasMoved[p] = true;
                hasMoved[q] = true;
                rootp = findroot(p, structure);
                rootq = findroot(q, structure);
                if(c == 1){ // Union p and q
                    if(structure[p] == structure[q]){ // They are in the same set, do nothing
                    } else {
                        if(count[rootp] >= count[rootq]){ // We always connect to the larger array
                            if(count[rootq] == 1){ // The smaller array has only one element, don't need to worry about others
                                structure[rootq] = structure[rootp];
                                count[rootp] += count[rootq];
                                sum[rootp] += sum[rootq];
                            } else {
                                sum[rootq] = rootq + 1;
                                count[rootq] = 1;
                                for(int b = 0; b < n; b++){ // Connect all elements from smaller array to root of bigger array
                                    if(structure[b] == rootq){
                                        structure[b] = structure[rootp];
                                        sum[rootp] += sum[b];
                                        count[rootp]++;
                                    }
                                }
                                
                            }
                        } else { // rootq is a larger array
                            if(count[rootp] == 1){
                                structure[rootp] = structure[rootq];
                                count[rootq] += count[rootp];
                                sum[rootq] += sum[rootp];
                            } else {
                                
                                sum[rootp] = rootp + 1;
                                count[rootp] = 1;
                                for(int b = 0; b < n; b++){
                                    if(structure[b] == rootp){
                                        structure[b] = structure[rootq];
                                        sum[rootq] += sum[b];
                                        count[rootq]++;
                                    }
                                }
                                
                                
                            }
                        }
                        
                    }
                }
                
                if(c == 2){ // move p to the same set as q
                    if(structure[p] == structure[q]){ // are in the same set, do nothing
                    } else {
                        if(hasMoved[p]) { // Element hasen't moved so we need not worry about other elements
                            if(p == structure[p]){ // p is root
                                int remember = 0;
                                
                                for(int o = 0; o < n; o++){ // Find first child of p
                                    if(structure[o] == p && p != o){ // find new root
                                        remember = o;
                                        structure[o] = o;
                                        break;
                                    }
                                }
                                
                                for(int o = 0; o < n; o++){
                                    
                                    if(structure[o] == p && p != o){ // Find all other childs of p and connect to new root
                                        structure[o] = remember;
                                        count[remember]++;
                                        sum[remember] += sum[o];
                                    }
                                    
                                }
                                
                                // The actual move
                                sum[p] = p + 1;
                                count[p] = 1;
                                structure[p] = structure[rootq];
                                count[rootq]++;
                                sum[rootq] += sum[p];
                                
                                
                            } else { // If p is not root
                                
                                structure[p] = structure[rootq];
                                count[rootq]++;
                                sum[rootq] += sum[p];
                                
                                count[rootp]--;
                                sum[rootp] -= sum[p];
                                
                            }
                            
                        } else {
                            
                            structure[p] = structure[rootq];
                            count[rootq]++;
                            sum[rootq] += p + 1;
                            
                        }
                    }
                }
            } else { // Prints the sum of a set and number of elements
                scanf("%d", &p);
                p--;
                p = findroot(p, structure);
                printf("%d %d\n", count[p], sum[p]);
            }
            
        }
        
    }
    return 0;
}
int findroot(int p, int structure[]){
    if(structure[p] == p){
        return p;
    }
    else{
        return findroot(structure[p], structure);
    }
}