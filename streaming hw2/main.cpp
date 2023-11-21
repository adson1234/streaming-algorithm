#include <iostream>
#include <vector>

using namespace std;
const int maxn=10000;
int p[3][maxn+1];    //parent

vector<vector<int > > adjlist;

int FIND_SET(int func_num, int x){
    if (x!=p[func_num][x]){
        p[func_num][x]=FIND_SET(func_num,p[func_num][x]);
    }
    return p[func_num][x];
}

void UNION(int func_num, int x,int y){
    p[func_num][FIND_SET(func_num,x)]=FIND_SET(func_num,y);
}

bool ap[maxn+1];    //is articulation point
bool visit[maxn+1];
int discover[maxn+1];  //discover Time
int Low[maxn+1];   //smallest value of a subtree rooted at v to which it can climb up by a back edge
int pred[maxn+1];  //parent
int Time;
void RDFS_Compute_Low(int v) {
    visit[v]=true;
    ap[v]=false;
    Low[v]=discover[v] = ++Time;
    for(int i=0;i<adjlist[v].size();i++){    //for each w in Adj(v)
        int w=adjlist[v][i];
        if (visit[w] == false) {

            pred[w]=v;
            RDFS_Compute_Low(w);
            // When RDFS_Compute_Low(w) returns,
            // Low[w] stores the
            // lowest value it can climb up
            // for a subtree rooted at w.
            Low[v] = min(Low[v], Low[w]);
            if (Low[w]>=discover[v]) ap[v]=true;
        } else{
            // {v, w} is a back edge
            Low[v] = min(Low[v], discover[w]);
        }
    }
}

int main()
{
    int n,m;
    cin >> n >>m;

    //vector<vector<int > > adjlist(n, vector<int > );
    adjlist.resize(n+1);
    for(int i=0;i<=n;i++){
        p[1][i]=i;
        p[2][i]=i;
    }

    int u,v;
    for(int i=1;i<=m;i++){
        cin >> u >> v;

        if (FIND_SET(1,u)!= FIND_SET(1,v)){
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);

            UNION(1,u,v);
        }else if (FIND_SET(2,u)!= FIND_SET(2,v)){
            bool multiedge=false;
            for(int j=0;j<adjlist[u].size();j++){
                int w=adjlist[u][j];
                if (w == v) {
                    multiedge=true;
                }
            }
            if (multiedge==false){
                adjlist[u].push_back(v);
                adjlist[v].push_back(u);

                UNION(2,u,v);
            }
        }
    }

    for(int i=1;i<=maxn;i++){
        visit[i]=false;
        pred[i]=0;
    }
    Time=0;
    int root=n;
    RDFS_Compute_Low(root);    //root

    vector<int> arti_list; //the list of all articulation points
    int counts=0;
    for(int i=0;i<adjlist[root].size();i++){
        int w=adjlist[root][i];
        if (pred[w] == root) {
            counts++;
        }
    }
    if (counts>1)  arti_list.push_back(root);     //root has less than one subtree => root is articulation point

    for(int j=1;j<=n;j++){  //Any other internal vertex v in the DFS tree is an articulation point if v has a child w such that Low[w] ≥ discover[v].
        if (j!=root && visit[j]==true && ap[j]){
            arti_list.push_back(j);
        }
    }
    if (arti_list.empty()){
        cout << "None" << endl;
    }else{
        for(int i=0;i<arti_list.size();i++){
            cout << arti_list[i] << endl;
        }
    }
    //cout<<Low[4]<<" "<<Low[5]<<" "<<Low[8]<<" "<<endl;
    return 0;
}
