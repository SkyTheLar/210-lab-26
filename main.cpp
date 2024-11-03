/*****************************************************

COMSC 210 | Lab 25 | Skylar Robinson | IDE Used: Eclipse

******************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int RACE_NUM = 4, TRIAL_NUM = 15;
//parallel array to race results
const string races [RACE_NUM] = {"Read", "Sort", "Insert", "Delete"};

int main() {
	//initialize vector, list, and set
	vector<string> vector;
	list<string> list;
	set<string> set;

	//initialize results arrays
	double vectorRs[RACE_NUM][TRIAL_NUM + 1], listRs[RACE_NUM][TRIAL_NUM + 1], setRs[RACE_NUM][TRIAL_NUM + 1];

	//run race loop
	for (int i = 0; i < TRIAL_NUM; i++){
        //open file
	   	ifstream in;
	   	in.open("codes.txt");

	   	//declare temp string
	   	string temp;

	   	//read to vector
	   	auto start = high_resolution_clock::now();

	   	while (in >> temp)
	   		vector.push_back(temp);

	   	auto stop = high_resolution_clock::now();
	   	auto duration = duration_cast<milliseconds>(stop - start);
	   	vectorRs[0][i] = duration.count();

	   	//reset file
	   	in.clear();
	   	in.seekg(0);

    	//read to list
	   	start = high_resolution_clock::now();

    	while (in >> temp)
	   		list.push_back(temp);

    	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
	   	listRs[0][i] = duration.count();

	   	//reset file
	   	in.clear();
    	in.seekg(0);

    	//read to set
	   	start = high_resolution_clock::now();

    	while (in >> temp)
	   		set.insert(temp);

    	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
	   	setRs[0][i] = duration.count();

	   	//close file
	   	in.close();

	   	//sort the vector
	   	start = high_resolution_clock::now();

    	sort(vector.begin(), vector.end());

	   	stop = high_resolution_clock::now();
    	duration = duration_cast<milliseconds>(stop - start);
	   	vectorRs[1][i] = duration.count();

    	//sort the list
	   	start = high_resolution_clock::now();

    	list.sort();

    	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
	   	listRs[1][i] = duration.count();

	   	//set is already sorted
	   	setRs[1][i] = -1;

	   	//insert TESTCODE into vector
	   	start = high_resolution_clock::now();

	   	vector.insert(vector.begin() + (vector.size() / 2), "TESTCODE");

    	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
	   	vectorRs[2][i] = duration.count();


    	//insert TESTCODE into list
	   	start = high_resolution_clock::now();

    	auto it = list.begin();
	   	for (int i = 0; i < (list.size() / 2); i++)
	   		it++;
    	list.insert(it, "TESTCODE");

	   	stop = high_resolution_clock::now();
    	duration = duration_cast<milliseconds>(stop - start);
	   	listRs[2][i] = duration.count();

    	//insert TESTCODE into set
    	start = high_resolution_clock::now();

	   	set.insert("TESTCODE");

	   	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
    	setRs[2][i] = duration.count();

	   	//delete the middle element of the vector
    	start = high_resolution_clock::now();

	   	vector.erase(vector.begin() + (vector.size() / 2));

	   	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
	   	vectorRs[3][i] = duration.count();

	   	//delete the middle element of the list
    	start = high_resolution_clock::now();

	   	it = list.begin();
    	for (int i = 0; i < (list.size() / 2); i++)
	   		it++;
	   	list.erase(it);

	   	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
    	listRs[3][i] = duration.count();

	   	//delete the middle element of the set
    	start = high_resolution_clock::now();

	   	auto setIt = set.begin();
    	for (int i = 0; i < (set.size() / 2); i++)
	   		setIt++;
	   	set.erase(setIt);

	   	stop = high_resolution_clock::now();
	   	duration = duration_cast<milliseconds>(stop - start);
    	setRs[3][i] = duration.count();

    	//clear containers
    	vector.clear();
    	list.clear();
    	set.clear();
	}

	//calculate averages
	for (int i = 0; i < RACE_NUM; i++){
		double sum = 0;
		for (int c = 0; c < TRIAL_NUM; c++){
			sum = sum + vectorRs[i][c];
		}
		vectorRs[i][TRIAL_NUM] = sum / TRIAL_NUM;
	}

	for (int i = 0; i < RACE_NUM; i++){
		double sum = 0;
		for (int c = 0; c < TRIAL_NUM; c++){
			sum = sum + listRs[i][c];
		}
		listRs[i][TRIAL_NUM] = sum / TRIAL_NUM;
	}

	for (int i = 0; i < RACE_NUM; i++){
		double sum = 0;
		for (int c = 0; c < TRIAL_NUM; c++){
			sum = sum + setRs[i][c];
		}
		setRs[i][TRIAL_NUM] = sum / TRIAL_NUM;
	}

	//display results
    cout << "Trials done: " << TRIAL_NUM << endl;
    cout << "Time taken in milliseconds:\n";
	cout << setw(10) << "Operation" << setw(10) << "Vector"
	   	 << setw(10) << "List" << setw(10) << "Set" << endl;
    for (int i = 0; i < RACE_NUM; i++)
	   	cout << fixed << setprecision(2)
		     << setw(10) << races[i] << setw(10) << vectorRs[i][TRIAL_NUM]
	   		 << setw(10) << listRs[i][TRIAL_NUM] << setw(10) << setRs[i][TRIAL_NUM] << endl;

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/
