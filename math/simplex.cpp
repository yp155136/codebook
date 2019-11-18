/*
maximize Cx under
Ax <=b
x >= 0
b >= 0
n variables
m constraints
A is m by n
*/
const int MAX = 45;
int n, m;
double arr[MAX][MAX];
bool pro(){
    double mi = 0;
    int x = 1;
    for(int i = 1; i <= n + m; i ++)    if(arr[0][i] < mi){
        mi = arr[0][i];
        x = i;
    }
    if(abs(mi) < eps)   return 0;   // sigma <= 0
    mi = INF;   // theta
    int y = 0;
    for(int i = 1; i <= m; i ++){
        if(arr[i][x] > eps && arr[i][n + m + 1] / arr[i][x] < mi) {
                mi = arr[i][n + m + 1] / arr[i][x];
                y = i;
        }
    }
    assert(y);
    double weed = arr[y][x];
    for(int i = 1; i <= n + m + 1 ; ++ i)
        arr[y][i] /= weed;
    // now arr[y][n + m + 1] == theta
    for(int i = 0; i <= m; i ++){
        if(i == y)  continue;
        double f = arr[i][x];
        for(int j = 1; j <= m + n + 1; j ++)
            arr[i][j] -= f * arr[y][j];
    }
    return 1;
}
int main(){
    cin >> n;
    cin >> m;
    memset(arr, 0, sizeof arr);
    // input C
    for(int i = 1 ; i <= n; i++ ){
        cin >> arr[0][i];
        arr[0][i] = - arr[0][i];
    }
    for(int i = 1; i <= m; i++){
        // input A
        for(int j = 1; j <= n; j++)
            cin >> arr[i][j];
        arr[i][n + i] = 1;
        // input b
        cin >> arr[i][n + m + 1];
    }
    while(pro());
    cout << arr[0][n + m + 1] << "\n";
    return 0;
}
