#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input-file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    int P, R;
    fin >> P >> R;

    vector<int> total(R), available(R);
    vector<vector<int>> allocation(P, vector<int>(R));
    vector<vector<int>> maxm(P, vector<int>(R));
    vector<vector<int>> need(P, vector<int>(R));


    for (int j = 0; j < R; j++) {
        fin >> total[j];
    }


    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            fin >> allocation[i][j];
    }


    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            fin >> maxm[i][j];
    }

    fin.close();


    for (int j = 0; j < R; j++) {
        int sum = 0;
        for (int i = 0; i < P; i++)
            sum += allocation[i][j];
        available[j] = total[j] - sum;
    }

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - allocation[i][j];
    }

    cout << "Processes: " << P << ", Resources: " << R << "\n\n";

    cout << "Total resources: ";
    for (int j = 0; j < R; j++) cout << total[j] << " ";
    cout << "\n\n";

    cout << "Allocation matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < R; j++) cout << allocation[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "Max matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < R; j++) cout << maxm[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "Need matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < R; j++) cout << need[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "Available: ";
    for (int j = 0; j < R; j++) cout << available[j] << " ";
    cout << "\n\n";

    vector<int> work = available;
    vector<bool> finish(P, false);
    vector<int> safeSeq;
    safeSeq.reserve(P);

    bool foundProcess;

    do {
        foundProcess = false;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canRun = true;


                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {

                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    safeSeq.push_back(i);
                    foundProcess = true;
                }
            }
        }

    } while (foundProcess);


    bool safe = true;
    for (bool f : finish) {
        if (!f) { safe = false; break; }
    }

    if (safe) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < P; i++) {
            cout << "P" << safeSeq[i];
            if (i < P - 1) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "System is NOT in a safe state.\n";
    }

    return 0;
}
