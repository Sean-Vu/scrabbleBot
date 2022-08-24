#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;
const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

void lexiconPopulate(istream& dictfile, string dict[], int& count)
{
    if (count >= MAXDICTWORDS) // if entries exceed MAXDICTWORDS
    {
        ++count; // increment count
        return;
    }
    if (!dictfile) return; // if all strings are read in dictfile
    dictfile >> dict[0]; // read in each line
    ++count; // increment count
    lexiconPopulate(dictfile, dict + 1, count); // move onto next line to read in

}
int lexiconBuilder(istream& dictfile, string dict[])
{
    int count = 0; // keeps count of current entries
    lexiconPopulate(dictfile, dict, count);
    if (count == 0) return count;
    return --count; // subtract 1 since the last line of nothing is read ( would be wrong if dict is 30000 words???) 
}








void printPermutations(string prefix, string rest, const string dict[], const int& dictSize, string results[], int& counter); // forward declaration
void Loop(int i, const int& max, string prefix, string rest, const string dict[], const int& dictSize, string results[], int& counter) {
    if (i >= max)
        return;
    printPermutations(prefix + rest[i], rest.substr(0, i) + rest.substr(i + 1, rest.length() - 1), dict, dictSize, results, counter); // evaluates each possible letter when permuting
    Loop(i + 1, max, prefix, rest, dict, dictSize, results, counter); // loops through to find all permutations
}

bool loopDict(int i, const int& max, const string& prefix, const string dict[])
{
    if (i >= max) return false;
    if (prefix == dict[i]) return true;  // if the current permutation is in the dictionary return true
    return loopDict(i + 1, max, prefix, dict);
}
bool loopResult(int i, const int& max, const string& prefix, string results[])
{
    if (i >= max) return true;
    if (prefix == results[i]) return false; // if the current permutation is in results return true
    return loopResult(i + 1, max, prefix, results);
}
void printPermutations(string prefix, string rest, const string dict[], const int& dictSize, string results[], int& counter) {
    if (rest.length() == 0) { // when a permutation is found
        int i = 0;
        int j = 0;
        if (loopDict(i, dictSize, prefix, dict)) // if the permutation found is in dictionary return true
        {
            if (loopResult(j, counter, prefix, results)) // if the permuation found is in results return true
            {
                if (counter >= MAXRESULTS) return; // don't add the permutation if the results array is already full
                results[counter] = prefix; // adds to result array
                ++counter; // increments the number of items in the results array
                return;
            }

        }

    }
    else
    {
        int i = 0;
        Loop(i, static_cast<int>(rest.length()), prefix, rest, dict, dictSize, results, counter); // loop to next possible permutation
    }
}
void loopDivulge(int i, int max, const string results[])
{
    if (i >= MAXRESULTS) return; // if the size passed in is larger than maxresults return (this might be redundant since we check if MAXRESULTS was exceeded in the jumbler)
    if (i >= max) return;
    cout << "Matching word " << results[i] << endl; // print out each result string
    loopDivulge(i + 1, max, results);
}
void divulgeSolutions(const string results[], int size)
{
    if (size <= 0) return; // if the size passed in is 0 or negative return 
    int i = 0;
    loopDivulge(i, size, results);
}


int theJumbler(string word, const string dict[], int size, string results[])
{
    int counter = 0;
    printPermutations("", word, dict, size, results, counter); // all nonredudanec perms of word
    return counter; // returns the number of permutations that are found in dict and are not duplictes
}


int main()
{
    return 0;
}

/*
int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    //dictfile.open("/Users/Sean/Desktop/wordsStress.txt");
    dictfile.open("words.txt");
    //dictfile.open("/Users/Sean/Desktop/emptyWords.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }


    nwords = lexiconBuilder(dictfile, dict);
    cout << "DEBUG:: The number of words in the dictionary are " << nwords << endl;



    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = theJumbler(word, dict, nwords, results);
    //assert(numMatches == 3);

    cout << "DEBUG:: The number of matches are " << numMatches << endl;

    /*
    for (int i = 0; i < numMatches; ++i)
    {
        cout << results[i] << endl;
    }
    */
    /*
        if (!numMatches) 
        {
            cout << "No matches found" << endl;
        }
        else {
            divulgeSolutions(results, numMatches);
        }
        return 0;
        /*
    
}
*/