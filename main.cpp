// Anastasiya Bazyk
#include <iostream>
using namespace std;

void search(int x, int height, int edge,int  *level,int *levelEnd, bool *touched ) {
    int middle = edge / 2;

    if (x > 0 && x >= middle) {
        int curr = x - height;

        if (curr >= edge) {
            *touched = false;
        } else {
            if (curr <= 0) {
                *level = 0;
                if (x >= edge) {
                    *levelEnd = edge;
                } else {
                    *levelEnd = x + 1;
                }
            } else {
                *level = curr;
                if (x >= edge) {
                    *levelEnd = edge;
                } else {
                    *levelEnd = x + 1;
                }
            }
        }
    }
    if (x >= 0 && x < middle) {
        int curr = x + height;
        if (curr >= edge) {
            *level = x;
            *levelEnd = edge;
        } else {
            *level = x;
            *levelEnd = curr + 1;
        }
    }
    if (x < 0) {
        int curr = x + height;
        if (curr < 0) {
            *touched = false;
        } else {
            if (curr >= edge) {
                *level = 0;
                *levelEnd = edge;
            } else {
                *level = 0;
                *levelEnd = curr + 1;
            }
        }
    }
}
void Bareiss(long long int m[32][32], int n ){

    int sign = 1;
    bool isZero = false;
    long long int help[n];

    for(int k = 0; k < n - 1 ; k++){
        if(m[k][k] == 0){
            int i = 0;
            for(i = k + 1; i < n; i++){
                // swap
                if(m[i][k] != 0){
                    for(int l = 0 ;l < n; l++){
                        help[l] = m[i][l];
                    }
                    for(int l = 0 ; l < n; l++){
                        m[i][l] = m[k][l];
                        m[k][l] = help[l];
                    }
                    sign = -sign;
                    break;
                }
            }
            if(i == n){
                isZero = true;
                break;
            }
        }
        for(int i = k + 1 ; i < n; i++){
            for(int j = k + 1; j < n; j++){
                m[i][j] = m[k][k] * m[i][j] - m[i][k] * m[k][j];
                if(k != 0){
                    m[i][j]=m[i][j] / m[k-1][k-1];
                }
            }
        }
    }
    if(isZero){
        cout << 0 << endl;
    }
    else{
        cout <<  m[n-1][n-1] * sign << endl;
    }
}
int main() {

    int edge = 0;

    cin >> edge;

    int cube[edge][edge][edge];
    for (int panel = 0; panel < edge; panel++) {
        for (int lines = 0; lines < edge; lines++) {
            for (int columns = 0; columns < edge; columns++) {
                int point = 0;
                cin >> point;
                cube[lines][columns][panel] = point;
            }
        }
    }
    char operation;

    cin >> operation;

    while (operation != 'E') {
        if (operation == 'C') {
            int x = 0; int y = 0; int z = 0;
            long long sum = 0;
            int height = 0;
            int width = 0;
            int depth = 0;
            bool touched = true;
            int level = 0;
            int levelEnd = edge;
            int panel = 0;
            int panelEnd = edge;
            int vertical = 0;
            int verticalEnd = edge;

            cin >> x >> y >> z >> height >> width >> depth;

            search(x, height, edge, &level, &levelEnd, &touched);

            search(y, width, edge, &vertical, &verticalEnd, &touched);

            search(z, depth, edge, &panel, &panelEnd, &touched);

            if (touched) {
                for (int i = panel; i < panelEnd; i++) {
                    for (int j = level; j < levelEnd; j++) {
                        for (int k = vertical; k < verticalEnd; k++) {
                            sum += cube[j][k][i];
                        }
                    }
                }
            }
            cout << sum << endl;
        }
        if (operation == 'O') {
            int x = 0; int y = 0; int z = 0;
            long long sum = 0;
            int r = 0;
            bool touched = true;
            int level = 0; int vertical = 0;  int panel = 0;
            int levelEnd = edge;
            int verticalEnd = edge;
            int panelEnd = edge;

            cin >> x >> y >> z >> r;

            search(x, r, edge, &level, &levelEnd, &touched);

            search(y, r, edge, &vertical, &verticalEnd, &touched);

            search(z, r, edge, &panel, &panelEnd, &touched);

            if (touched) {
                for (int i = panel; i < panelEnd; i++) {
                    for (int j = level; j < levelEnd; j++) {
                        for (int k = vertical; k < verticalEnd; k++) {
                            int help = ((j - x) * (j - x)) + ((k - y) * (k - y)) + ((i - z) * (i - z));
                            if (help <= r * r) {
                                sum += cube[j][k][i];
                            }
                        }
                    }
                }
            }
            cout << sum << endl;
        }
        if (operation == 'T') {
            int x = 0; int y = 0; int z = 0;
            long long sum = 0;
            int e = 0;
            bool touched = true;  
            int level = 0;
            int levelEnd = edge;
            int vertical = 0;
            int verticalEnd = edge;
            int panel = 0;
            int panelEnd = edge;

            cin >> x >> y >> z >> e;

            search(x, e, edge, &level, &levelEnd, &touched);

            search(y, e, edge, &vertical, &verticalEnd, &touched);

            search(z, e, edge, &panel, &panelEnd, &touched);

            if (touched) {
                for (int i = panel; i < panelEnd; i++) {
                    for (int j = level; j < levelEnd; j++) {
                        for (int k = vertical; k < verticalEnd; k++) {
                            int a = (j - x);
                            if (a < 0) {
                                a = -a;
                            }
                            int b = (k - y);
                            if (b < 0) {
                                b = -b;
                            }
                            int c = (i - z);
                            if (c < 0) {
                                c = -c;
                            }
                            int help = a + b + c;
                            if (help <= e) {
                                sum += cube[j][k][i];
                            }

                        }
                    }
                }
            }
            cout << sum << endl;
        }
        if (operation == 'D') {
            char letter;  int number = 0;
            long long int m[32][32];

            cin >> letter >> number;

            if (letter == 'l') {
                // level
                for (int i = 0; i < edge; i++) {
                    for (int j = 0; j < edge; j++) {
                        m[i][j] = cube[number][j][i];
                    }
                }
                Bareiss(m, edge);
            }
            if (letter == 'v') {
                // vertical
                for (int i = 0; i < edge; i++) {
                    for (int j = 0; j < edge; j++) {
                        m[i][j] = cube[j][number][i];
                    }
                }
                Bareiss(m, edge);
            }
            if (letter == 'p') {
                for (int i = 0; i < edge; i++) {
                    for (int j = 0; j < edge; j++) {
                        m[i][j] = cube[i][j][number];
                    }
                }
                Bareiss(m, edge);
            }
        }
        cin >> operation;
    }
    return 0;
}
