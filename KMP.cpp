#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>
#include <fstream>

std::string operator*(const std::string& str, size_t times) // https://stackoverflow.com/questions/35506712/string-multiplication-in-c
{
	std::stringstream stream;
	for (size_t i = 0; i < times; i++) stream << str;
	return stream.str();
}

using namespace std;
using chrono::duration_cast;
using chrono::nanoseconds;

typedef chrono::steady_clock the_clock;


map<char, int> CreateFailureTable(string pattern)
{
	map<char, int> patternMap;
	map<char, int> skipTable;

	for (int x = 0; x < pattern.length(); x++) //If letter hasn't already been added to the skip table then add it and it's index
	{
		if (skipTable.count(pattern.at(x)) == 0)
		{
			skipTable.insert(pair<char, int>(pattern.at(x), 0));
		}
		else
		{
			int originalIndex;

			for (int z = 0; z < x; z++)
			{
				if (pattern.at(z) == pattern.at(x) && skipTable.count(pattern.at(x)) >= 1)
				{
					originalIndex = z;
					skipTable.insert(pair<char, int>(pattern.at(x), originalIndex));
				}
			}

		}
	}
	return skipTable;
}

vector<int> Search(string pattern, string stringToSearch)
{
	int p = 0;
	int s = 0;
	map<char, int> skipTable = CreateFailureTable(pattern);
	vector<int> matchFound;
	while (s <= stringToSearch.length() - 1)
	{
		if (pattern.at(p) == stringToSearch.at(s))
		{
			p++;
		}
		else
		{
			p = skipTable[p];
		}

		s++;

		if (p == pattern.length() - 1)
		{
			p = 0;
			matchFound.push_back(s);
		}
	}

	return matchFound;
}

int KMP()
{
	// This is the Knuth-Morris-Pratt string search

	string pattern = "everything";
	//ifstream textFile("Flex Tape.txt");
	string stringToSearch = "Hi, Phil Swift here with Flex Tape! The super-strong waterproof tape! That can instantly patch, bond, seal, and repair! Flex tape is no ordinary tape; its triple thick adhesive virtually welds itself to the surface, instantly stopping the toughest leaks. Leaky pipes can cause major damage, but Flex Tape grips on tight and bonds instantly! Plus, Flex Tape’s powerful adhesive is so strong, it even works underwater! Now you can repair leaks in pools and spas in water without draining them! Flex Tape is perfect for marine, campers and RVs! Flex Tape is super strong, and once it's on, it holds on tight! And for emergency auto repair, Flex Tape keeps its grip, even in the toughest conditions! Big storms can cause big damage, but Flex Tape comes super wide, so you can easily patch large holes. To show the power of Flex Tape, I sawed this boat in half! And repaired it with only Flex Tape! Not only does Flex Tape’s powerful adhesive hold the boat together, but it creates a super strong water tight seal, so the inside is completly dry! Yee-doggy! Just cut, peel, stick and seal! Imagine everything you can do with the power of Flex Tape!\
Hi Phil Swift here for FlexSeal Clear.The crystal clear way to coat, seal and stop leaks fast.Just a quick shot and Flex Seal Clear fills in cracks and holes while remaining virtually invisible.This clear rubberized coating seals and protects without changing the look of your beautiful surfaces.Protecting your car, RV or boat has never been easier.\
To show you the crystal clear sealing power of Flex Seal Clear, we replaced the bottom of this boat with plexiglass, drilled over 100 holes and covered them in FlexSeal Clear.Not only does it stay afloat but Flex Seal Clear keeps all the water out of the boat.And you can see right through!Hello fishy!Perfect for counter tops, windows and tubs.With Flex Seal Clear everything in plain sight can be sealed water tight.Don’t waste time and money fixing leaks the old fashioned way.Get Flex Seal Clear today for just $19.99.Flex Seal Clear is guaranteed to coat, seal and stop leaks fast.But hold everything!We’re going to double your order and send you two cans of Flex Seal Clear.Now you can get the incredible power of Flex Seal in original Brite for surfaces that are light and Flex Seal Clear for everything in sight.Two cans of Flex Seal and our guarantee is clearly the most amazing deal on TV and it’s all yours for just $19.99.Call now!";
	stringToSearch = stringToSearch * 100;

	//string stringToSearch((istreambuf_iterator<char>(textFile)), (istreambuf_iterator<char>()));

	the_clock::time_point start = the_clock::now();

	vector<int> matches = Search(pattern, stringToSearch);
	//textFile.close();

	the_clock::time_point end = the_clock::now();

	cout << matches[0];

	for (int x = 1; x <= matches.size() -1; x++)
	{
		cout << "," << matches[x];
	}

	auto miliSecs = duration_cast<nanoseconds>(end - start).count();

	return miliSecs;
}

void main() {
	// This runs the KMP function and collects time taken

	std::vector<std::string> results;
	std::ofstream outFile("results.csv");
	// from https://stackoverflow.com/questions/6406356/how-to-write-vector-values-to-a-file

	for (int x = 0; x < 100; x++)
	{
		outFile << KMP() << "\n";
	}
}