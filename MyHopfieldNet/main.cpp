#include <bits/stdc++.h>
using  namespace std;

class HopfieldNet{
public:
    HopfieldNet(int n, vector<vector<int> > v){
        model = v;
        N = n;
    }
    vector<vector<int> > weight;
    vector<vector<int> > model;
    int N; // длина каждого входного вектора

    void create_weight(){
        weight.resize(N, vector<int>(N, 0));

        for (int k = 0; k < model.size(); ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i == j) {
                        weight[i][j] = 0;
                    }
                    else {
                        weight[i][j] += model[k][i] * model[k][j];
                    }
                }
            }
        }
    }

    int activation(int x){
        if(x >= 0)
            return 1;
        return -1;
    }

    int recognize(vector<int> x){
        int it = 0;
        vector<int> prepred(N, 0);
        vector<int> pred(N, 0);

        while(it < 1000) {
            it++;
            prepred = pred;
            pred = x;
            x = compos(x);
            for(int i = 0; i < N; i++)
                x[i] = activation(x[i]);
            if(x == pred || x == prepred)
                break;
        }

        for(int i = 0; i < model.size(); i++){
            if(x == model[i]) {
                return i;
            }
        }



        return  -1;
    }

    vector <int> compos(vector<int> v){ //умножение матрицы на вектор
        vector<int> ans;
        for(int i = 0; i < weight.size(); i++){
            int sum = 0;
            for (int j = 0; j < N; ++j) {
                sum += weight[i][j] * v[j];
            }
            ans.push_back(sum);
        }
        return ans;

    }
};

int main() {
    //freopen("input.txt", "r", stdin);
    ifstream fin("input2.txt");
    int n, m; //количество векторов, их длина
    fin >> n >> m;
    vector<vector<int> > v;
    vector<int> cur;
    for (int i = 0; i < n; ++i) {
        cur.clear();
        cur.resize(m, 0);
        for (int j = 0; j < m; ++j) {
             fin >> cur[j];
        }
        v.push_back(cur);

    }

    HopfieldNet net(m, v);
    net.create_weight();

    ifstream finn("test2.txt");

    int a, b;
    finn >> a >> b;

    vector<int> test;

    for(int i = 0; i < a; i++){
        test.clear();
        test.resize(b, 0);
        for(int j = 0; j < b; j++){
            finn >> test[j];
        }
        cout << net.recognize(test) << endl;
    }
}