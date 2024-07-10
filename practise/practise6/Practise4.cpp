#include <iostream>
#include "console.h"
#include "filelib.h"
#include "map.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

bool getFrequencies(string filename, Map<string, int>& map){
    ifstream ifs(filename);

    if (! ifs.is_open())
    {
        cout << "Failed to open file in getFrequencies(): " << filename << endl;
        return false;
    }

    Map<int, Vector<string>> result;

    Vector<string> lines = readLines(ifs);
    for (string line : lines)
    {
        Vector<string> words = stringSplit(line, " ");
        for (string word : words)
        {
            map[word]++;
        }
    }

    for (string key : map) {
        result[map.get(key)].add(key);
    }

    for (int i : result.keys())
    {
        cout << i << ": " << result.get(i) << endl;
    }

    return true;
}
