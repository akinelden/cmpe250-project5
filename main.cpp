#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define Prime 1000000007
#define H 26
#define first ('a'-1)

struct word {
	string w;
	int hash = 0;
	int over = 0;
};

struct letter {
	char c;
	bool visited = false;
	unsigned int patterns = 0;
};

vector<vector<word>> words(27);
vector<letter> letters;


void HashWord(word& w) {
	long int hx = 0;
	for (int i = 0; i < w.w.size(); i++) {
		hx = hx * H + w.w[i] - first;
		//w.hash = w.hash * H + w.w[i] - first;
		if (hx > Prime) {
			hx = hx%Prime;
			w.over=(w.over+1)%Prime;
		}
	}
	w.hash = hx;
}

bool WordComp (word w1, word w2) { return (w1.w.size() < w2.w.size()); }


int FindPattern(int i) {
	if (i == letters.size()) {
		return 1;
	}
	letter& l = letters[i];

	if (l.visited)
		return l.patterns;

	
	if(!l.visited) {
		unsigned int total = 0;
		int h = 0;
		int o = 0;
		int M = l.c - first;
		if (!words[M].size())
			return 0;
		int j = 0;
		for (int k = 0; k < words[M].size(); k++) {
			word& w = words[M][k];
			if (j < w.w.size() && (i + w.w.size()) <= letters.size()) {
				long int hx = h;
				for (; j < w.w.size(); j++) {
					hx = hx * H + letters[j + i].c - first;
					//h = h * H + letters[j + i].c - first;
					if (hx > Prime) {
						hx = hx % Prime;
						o = (o + 1) % Prime;
					}
				}
				h = hx;
			}
			if (h == w.hash && o == w.over)
				total = (total + FindPattern(j + i)) % Prime;
		}
		l.patterns = total % Prime;
		l.visited = true;
		return l.patterns;
	}
	
}

int main(int argc, char* argv[]) {
	
    if (argc != 3) {
        cout << "Run the code with the following command: ./project5 [input_file] [output_file]" << endl;
        return 1;
    }

	ifstream infile(argv[1]);

	string line;
	infile >> line;
	letters.reserve(line.size());
	for (int i = 0; i < line.size(); i++) {
		letter l;
		l.c = line[i];
		letters.push_back(l);
	}
	infile >> line;
	int N = stoi(line);
	

    for (int i=0; i<N; i++) {
		infile >> line;
		word w;
		w.w = line;
		HashWord(w);
		words[w.w[0]-first].push_back(w);
    }

	for (int i = 0; i < words.size(); i++)
		sort(words[i].begin(), words[i].end(), WordComp);

	unsigned long long int result = 0;
	
	result = FindPattern(0);

	int res = result % Prime;
	if (res < 0)
		res += Prime;
	//cout << res << endl;



    ofstream myfile;
	myfile.open(argv[2]);
	myfile << res << endl;
    myfile.close();


    


    return 0;
}


