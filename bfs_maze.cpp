//author : Vikram (LimitZero)
//TC of bfs : O(nodes + edges)
//TC of this code : O(n*m + 2*(m-1)*(n-1)
//Final TC : O(n*m)

#include<bits/stdc++.h>
using namespace std;
 /*
 6 6  
 S . # . . .
 . . # . . .
 # . # . # .
 # . . . # .
 # # # # # .
 F . . . . . 

 In this code , (min moves to reach F from S) + (dis matrix) 
 + (path to reach F from S)
 */
using pii = pair<int , int>;
const int INF=100;
int n,m;
vector<vector<char>> arr;
vector<vector<int>> vis;
vector<vector<int>> dis;
vector<vector<pii>> par;

int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};

bool check(int x,int y){
    if(x>=0&&x<n && y>=0&&y<m && arr[x][y]!='#'){      /
        return 1;
    }
    return 0;
}

vector<pii> neighbours(pii node){
    vector<pii> neigh;
    for(int k=0;k<4;k++){
        int x=node.first+dx[k];
        int y=node.second+dy[k];            //check for every direction
        if(check(x,y)==1){
            neigh.push_back({x,y});
        }
    }
    return neigh;
}

void bfs(pii sc_node){
    vis.assign(n,vector<int>(m,0));//visited or not
    dis.assign(n,vector<int>(m,INF));//distance array
    par.assign(n,vector<pii>(m,{-1,-1}));// parent of each node
    queue<pii> q;
    vis[sc_node.first][sc_node.second]=1;
    dis[sc_node.first][sc_node.second]=0;
    par[sc_node.first][sc_node.second]={-1,-1};
    q.push(sc_node);
    
    while(!q.empty()){
        pii node=q.front();
        q.pop();
        for(auto v:neighbours(node)){
            if(vis[v.first][v.second]!=1){
                vis[v.first][v.second]=1;
                dis[v.first][v.second]=dis[node.first][node.second]+1;
                par[v.first][v.second]=node;
                q.push(v);
            }
        }
    }
}
void solve(){
    cin >> n >> m;
    arr.resize(n);
    pii st,en;
    for(int i=0;i<n;i++){
        arr[i].resize(m);
        for(int j=0;j<m;j++){
            cin >> arr[i][j];
            if(arr[i][j]=='S'){
                st={i,j};            //Finding start and end
            }
            else if(arr[i][j]=='F'){
                en={i,j};
            }
        }
    }
    bfs(st);                        //doing bfs on start
    if(dis[en.first][en.second]==INF){
        cout << "Cannot Reach"<<endl;
    }else{
        cout << "Min Moves : " << dis[en.first][en.second] << endl;
    for(int i=0;i<n;i++){                                                
        for(int j=0;j<m;j++){
            cout << dis[i][j] << '\t';                                //printing distance array
        }
        cout << endl;
    }
        
        vector<pii> path;
        pii cur=en;
        while(cur!=make_pair(-1,-1)){
            path.push_back(cur);
            cur=par[cur.first][cur.second];
        }
        reverse(path.begin(),path.end());
        for(auto v:path){
            cout << v.first << " "<<v.second<<endl;           //printing path to reach F from S
        }
    }
}

int main(){
    solve();
    return 0;
}
