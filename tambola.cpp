#include<bits/stdc++.h>
//#include<sqlite3ext.h>
//#include <json/json.h> 


using namespace std;
#include "sqlite3.h"



vector<vector<int>> tk(3,vector<int>(9));
int max_slots = 15;
vector<vector<int>>  tb(3,vector<int>(9));
//int i, j, k;

int ticket[3][9];
int i, j, k;
vector<int> aa={0,1,2,3,4,5,6,7,8};
vector<vector<int>> nums={{1,2,3,4,5,6,7,8,9},{10,11,12,13,14,15,16,17,18,19},{20,21,22,23,24,25,26,27,28,29},
                    {30,31,32,33,34,35,36,37,38,39},{40,41,42,43,44,45,46,47,48,49},{50,51,52,53,54,55,56,57,58,59},
                    {60,61,62,63,64,65,66,67,68,69},{70,71,72,73,74,75,76,77,78,79},{80,81,82,83,84,85,86,87,88,89,90}};


void fillRandomly() {
    int filled = 0;
    for (i = 0; i < 9; i++) {
        // keeping 1 number in column (base case)
        j = rand() % 3;
        tb[j][i] = 1;
        filled++;
    }

    
}

void fillRandomly1() {
    int c=0;
    int check=0;

    for (i = 0; i < 3; i++) {
        // keeping 5 number in row (base case)
        random_device rd;
        mt19937 g(rd());
        shuffle(aa.begin(),aa.end(),g);

        for(int k=0;k<9 && check<5;k++){

            int id=aa[k];

            if(nums[id].size()>0)
            c=rand() % (nums[id].size());
            else c=-1;

            if(nums[id].size()>0){

                int temp= nums[id][c];

                //cout<<temp<<' ';
                nums[id].erase(nums[id].begin()+c);

                tk[i][id] = temp;
                check++;
            }
            //tb[i][aa[k]] = 1;
        }
        check=0;
        c=0;
    }

}

void orderTicket() {
    int temp = 0;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 3; j++) {
            // Using Bubble sort to sort columns
            if (tk[j][i] != 0) {
                for (k = j; k < 3; k++) {
                    if (tk[k][i] < tk[j][i] && tk[k][i] != 0) {
                        temp = tk[j][i];
                        tk[j][i] = tk[k][i];
                        tk[k][i] = temp;
                    }
                }
            }
        }
    }
}

void removeRedundancy() {
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 3; j++) {
            if (tk[j][i] != 0) {
                for (k = j + 1; k < 3; k++) {
                    if (tk[k][i] != 0) {
                        while (tk[k][i] == tk[j][i]) {
                            tk[j][i] = tb[j][i] * (rand() % (10) + (10 * i));
                        }
                    }
                }
            }
        }
    }
}

void clearPrev() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
            tb[i][j] = 0;
            tk[i][j] = 0;
        }
    }
}

void printTicket(vector<vector<int>> mat) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
            cout << setw(4) << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout <<endl;
}

void generateTicket() {
    //fillRandomly();
    //cout<<2<<endl;
    int c=0;

    fillRandomly1();
    //cout<<3<<endl;
    /*
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {

            //k=nums[j][i];
            if(nums[j].size()>0)
            c=rand() % (nums[j].size());
            else c=-1;

            if(nums[j].size()>0){

                int temp= tb[i][j] * nums[j][c];

                cout<<temp<<' ';
                nums[j].erase(nums[j].begin()+c);

                //int temp=tb[i][j] * (rand() % (10) + (10 * j));
                
                //if(temp)
                tk[i][j] = temp;
                //else ticket[i][j]=temp+1;
            }
        }
    }
    */
    //cout<<4<<endl;

    
   // removeRedundancy();
    orderTicket();
    printTicket(tk);
    clearPrev();
    
}

int main(){

    int n;
    //cin>>n;

    sqlite3 *db;
    int rc = sqlite3_open("./tick.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return rc;
    }

    vector<vector<vector<int>>> r(n);
    //srand(time(0));

    n=6;
    while(n--){
        //cout<<1<<endl;
        generateTicket();
    }

    return 0;
}
