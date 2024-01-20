#include<bits/stdc++.h>

using namespace std;    

vector<vector<int>> tk(3,vector<int>(9));
//vector<vector<int>>  tb(3,vector<int>(9));
vector<vector<vector<int>>> r;

int i, j, k;
vector<int> aa={0,1,2,3,4,5,6,7,8};
vector<vector<int>> nums={{1,2,3,4,5,6,7,8,9},{10,11,12,13,14,15,16,17,18,19},{20,21,22,23,24,25,26,27,28,29},
                    {30,31,32,33,34,35,36,37,38,39},{40,41,42,43,44,45,46,47,48,49},{50,51,52,53,54,55,56,57,58,59},
                    {60,61,62,63,64,65,66,67,68,69},{70,71,72,73,74,75,76,77,78,79},{80,81,82,83,84,85,86,87,88,89,90}};



void fillr() {
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

            if (tk[j][i] != 0) {
                for (k = j; k < 3; k++) {
                    if (tk[k][i] < tk[j][i] && tk[k][i] != 0) {
                        swap(tk[j][i],tk[k][i]);
                    }
                }
            }
        }
    }
}

void clearTk() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
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
    fillr();
    //cout<<2<<endl;

    orderTicket();

    r.push_back(tk);

    //printTicket(tk);
    clearTk();
    
}

int main(){

    int n;

    cout<<"Enter The number of tickets you want to Make (N) : ";
    cin>>n;

    cout<<endl;

    while(n--){
        generateTicket();
    }

    cout<<"------------Tickets created succesfully-------------\n";
    cout<<"----------------------------------------------------"<<endl;
    cout<<endl;

    int ck;
    cout<<endl;

    while(1){
        cout<<"Enter the number of ticket you want to view or enter 0 to view all : ";
        cin>>ck;

        if(ck!=0){
            cout<<endl;
            cout<<"T"<<ck<<':'<<endl;
            
            printTicket(r[ck-1]);
        }
        else{
            cout<<endl;
            int count=1;
            for(auto res : r){
                cout<<"T"<<count++<<':'<<endl;                
                printTicket(res);
                
            }
        }

        cout<<"Enter 1 to continue else 0 : ";
        bool ch;
        cin>>ch;

        if(!ch) break;
    }
    

    return 0;
}
