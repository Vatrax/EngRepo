// INSA.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Tuple {
    public:
        int lp;
        int pti;
};

int tasks, machines, ops;
int *t, *p, *m, *r, *q, *pt, *pk, *nt, *nk, *lp, *status;
vector<int>* machineOps;
vector<Tuple> tuples;
long before;
int dummy; //for skipping tokens

void printOpsOnMachines();
void printTable();
bool comp(Tuple, Tuple);
inline long getMilliSeconds();

bool comp(Tuple f, Tuple s) {
    return (f.pti > s.pti);
}

void nastTech() {
    for(int i=0; i<ops; i++) {
        if(i+1>=ops || t[i]!=t[i+1]) {
            nt[i] = 0;
        }
        else {
            nt[i] = i+2;
        }
    }
    cout << "Policzono nastêpników technologicznych oraz Q" << endl;
}

void poprzTech() {
    for(int i=ops-1; i>=0; i--) {
        if( i<=0 || t[i]!=t[i-1] ) {
            pt[i] = 0;
        }
        else {
            pt[i] = i;
        }
    }
    cout << "Policzono poprzedników technologicznych oraz Q" << endl;
}

void generateRQ(vector<int> ts) {
    int size = ts.size();
    for(int i=0; i<size; i++) {
        r[ts[i]-1] = max(r[pk[ts[i]-1]-1] ? r[pk[ts[i]-1]-1] : 0, r[pt[ts[i]-1]-1] ? r[pt[ts[i]-1]-1] : 0) + p[ts[i]-1];
        q[ts[size-i-1]-1] = max(q[nk[ts[size-i-1]-1]-1] ? q[nk[ts[size-i-1]-1]-1] : 0, q[nt[ts[size-i-1]-1]-1]  ? q[nt[ts[size-i-1]-1]-1] : 0) + p[ts[size-i-1]-1];

    }
}

void lPoprz() {
    for(int i=0; i<ops; i++) {
        lp[i] = 0 + (pk[i] ? 1 : 0) + (pt[i] ? 1 : 0);
    }
}

vector<int> topolSeq2() {
    for(int i=0; i<ops; i++) status[i] = 0; //nie bylo
    vector<int> seq;
    bool empty = false;
    int i=0;
    bool loop = true;
    while(loop) {
        if(i==0) {
            empty = true;
        }
        if(lp[i]>=1) {
            empty = false;
        }
        if(status[i]==1) {
            status[i] = 2;
            if(i<ops-1) lp[i+1]--;
            for(int j=0; j<ops; j++) {
                if(pk[j]==i+1) {
                    lp[j]--;
                }
            }

        }
        if(lp[i]==0 && status[i]==0) {
            seq.push_back(i+1);
            status[i] = 1; //bylo
        }
        i++;
        if(i>=ops) {
            if(empty)
                loop = false;
            i = 0;
        }
        //printTable();
        //sleep(1);
    }
    return seq;
}

vector<Tuple> sortByPti() {
    stable_sort(tuples.begin(), tuples.end(), comp);
    return tuples;
}

vector<int> topolSeq() {
    vector<int> seq;
    bool empty = false;
    int i=0;
    bool loop = true;
    while(loop) {
        if(i==0) {
            empty = true;
        }
        if(lp[i]==-1) {
            if(i<ops-1) {
                lp[i+1]--;
                lp[i] = -2;
            }
        }
        if(lp[i]==0) {
            seq.push_back(i+1);
            lp[i] = -1;
            for(int j=0; j<ops; j++) {
                if(pk[j]==i+1) {
                    lp[j]--;
                }
            }
        }
        if(lp[i]>=1) {
            empty = false;
        }
        i++;
        if(i>=ops) {
            if(empty)
                loop = false;
            i = 0;
        }
    }
    return seq;
}

void removeFromTuples(int task) {
    for(unsigned int i=0; i<tuples.size(); i++) {
        if(task==tuples[i].lp) {
            tuples.erase(tuples.begin()+i);
            return;
        }
    }
}

void putOnMachine(int mach, int task, vector<int> seq) {
    removeFromTuples(task);
    vector<int>* machKol = &machineOps[mach-1];
    if(machKol->empty()) {
        machKol->push_back(task);
        return;
    }
    int* points = new int[machKol->size()+1];
    for(unsigned int i=0; i<machKol->size()+1; i++) {
        int ptask = p[task-1];

        int ptech = pt[task-1];
        int rptech = 0;
        if(ptech>0)
            rptech = r[ptech-1];

        int rpkol = 0;
        if(i>0) {
            int pkol = machKol->at(i-1);
            rpkol = r[pkol-1];
        }

        int rmax = rptech>rpkol ? rptech : rpkol;

        //printf("RT = %03d, RK %03d\n", rptech, rpkol);
        int qntech = 0;
        int ntech = nt[task-1];
        if(ntech>0)
            qntech = q[ntech-1];

        int qnkol = 0;
        if(i<machKol->size()) {
            int nkol = machKol->at(i);
            qnkol = q[nkol-1];
        }

        int qmax = qntech>qnkol ? qntech : qnkol;

        //printf("QT = %03d, QK %03d\n", qntech, qnkol);

        points[i] = ptask + rmax + qmax;
        //cout << "POINT = " << points[i] << endl;
    }
    int min = 0;
    int val = points[0];
    for(unsigned int j=1; j<machKol->size()+1; j++) {
        if(points[j] < val) {
            min = j;
            val = points[j];
        }
    }

    //cout << "Wrzucam " << task << " operacjê na miejsce " << min << " na maszynie " << mach << endl;
    machKol->insert(machKol->begin()+min, task);
    pk[task-1] = 0;
    if(min>0) pk[task-1] = machKol->at(min-1);
    if(min>0) nk[machKol->at(min-1)-1] = task;
    if(min<machKol->size()-1) pk[machKol->at(min+1)-1] = task;
    nk[task-1] = 0;
    if(min<machKol->size()-1) nk[task-1] = machKol->at(min+1);
    //printTable();
}

void putOps() {
    vector<int> topolOrder;
    while(!tuples.empty()) {
        sortByPti();
        lPoprz();
        //printTable();
        //printOpsOnMachines();
        topolOrder = topolSeq2();
        generateRQ(topolOrder);
        int mach = m[tuples[0].lp-1];
        //cout << "Wrzucam " << tuples[0].lp << " operacjê do maszyny " << mach << endl;
        putOnMachine(mach, tuples[0].lp, topolOrder);
        //printOpsOnMachines();
    }
    //printTable();
    printOpsOnMachines();
}

void printOpsOnMachines() {
    cout << endl;
    int max = 0;
    for(int i=0; i<machines; i++) {
        if(machineOps[i].size() > max)
            max = machineOps[i].size();
    }
    printf(" MAC | Ops\n");
    cout << "-----" << endl;
    for(int i=0; i<machines; i++) {
        printf(" %03d |", i+1);
        for(unsigned int j=0; j<machineOps[i].size(); j++) {
            printf(" %03d", machineOps[i][j]);
        }
        cout << endl;
    }
}

void printTable() {
    cout << endl;
    printf(" Lp. | tas | ma. | pti | nt. | pte | nk. | pk. | lp. | rr. | qq. | sta\n");
    printf("-----------------------------------------------------------------------\n");
    for(int i=0; i<ops; i++) {
        printf(" %03d | %03d | %03d | %03d | %03d | %03d | %03d | %03d | %03d | %03d | %03d | %03d\n",
        i+1, t[i], m[i], p[i], nt[i], pt[i], nk[i], pk[i], lp[i], r[i], q[i], status[i]);
        if(i+1<ops && t[i]!=t[i+1]) {
            printf("-----------------------------------------------------------------------\n");
        }
    }
    cout << endl;
}

int _tmain(int argc, _TCHAR* argv[]) {
 
        ifstream infile("data00.txt");

        infile >> tasks;
        infile >> machines;
        infile >> ops;

        t = new int[ops];
        p = new int[ops];
        m = new int[ops];
        r = new int[ops];
        q = new int[ops];
        pt = new int[ops];
        pk = new int[ops];
        nt = new int[ops];
        nk = new int[ops];
        lp = new int[ops];
        status = new int[ops];
        machineOps = new vector<int>[machines];

        int op = 0;
        for(int i=0; i<tasks; i++) {
            int o = 0;
            infile >> o;
            for(int j=0; j<o; j++) {
                t[op] = i+1;
                infile >> m[op];
                infile >> p[op];
                op++;
            }
        }
        /**
         * END DATA READING
         * BEGIN PREPROCESSING
         */
        for(int i=0; i<ops; i++) {
            Tuple t;
            t.lp = i+1;
            t.pti = p[i];
            tuples.push_back(t);
        }
        nastTech();
        poprzTech();
        /**
         * END PREPROCESSING
         * BEGIN INSA
         */
        putOps();
        infile.close();
		system("PAUSE");
}
