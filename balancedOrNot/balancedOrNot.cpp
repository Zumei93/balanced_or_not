// balancedOrNot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

// Complete balancedOrNot function
// DO NOT MODIFY anything outside the below function
vector<bool> balancedOrNot(const vector<string>& expressions, const vector<unsigned int>& maxReplacements) {
	// NEED TO INCLUDE <STRING>, because the main function cannot be compiled due to lacking of the binary operator >> for std::string;
	unsigned int expressionsSize = expressions.size();

	vector<bool> res;
	res.reserve(expressionsSize);

	for (unsigned index = 0; index < expressionsSize; ++index)
	{
		// fast check if an expression isn't balanced and cannot be balanced;
		char lastSymbolOfExpression = *(expressions[index].end() - 1);
		int countOfOpeningAngleBracket = count(expressions[index].begin(), expressions[index].end(), '<');
		int countOfClosingAngleBracket = count(expressions[index].begin(), expressions[index].end(), '>');
		if (lastSymbolOfExpression == '<' || countOfOpeningAngleBracket > countOfClosingAngleBracket)
		{
			res.push_back(false);
			continue;
		}
		// check if an expression is balanced;
		unsigned sizeOfExpression = expressions[index].size();
		vector<char> checkVector;
		checkVector.reserve(sizeOfExpression);
		bool isBalanced = true;
		bool cannotBeBalanced = false;
		bool startClosing = false;  // the control variable that says about starting to close all open angle brackets;
		for (const char ch : expressions[index])
		{
			if (ch == '<')
			{
				if (!startClosing)
					checkVector.push_back(ch);
				else
				{
					cannotBeBalanced = true;
					res.push_back(false);  // an expression is not balanced and cannot be balanced because the opening bracket has left while we are trying to insert the new one;
					break;  // exit from the balance check loop;
				}
			}
			else if (ch == '>')
			{
				if (any_of(checkVector.begin(), checkVector.end(), [](char i) {return i == '<'; }))  // if there is no any open brackets the expression is considered unbalanced;
				{
					checkVector.pop_back();
					if (!startClosing)
						startClosing = true;  // we signal that all open brackets must have a pair - the close one;
				}
				else
					isBalanced = false;  // an expression is not balanced but we continue our check balance work in order to know if it can be balanced;
			}

			if (startClosing && none_of(checkVector.begin(), checkVector.end(), [](char i) {return i == '<'; }))
				startClosing = false;  // we successfully have closed all open brackets;
		}
		// we have reached the end of the string and we have to find out that if some open brackets exist;
		if (any_of(checkVector.begin(), checkVector.end(), [](char i) {return i == '<'; }))
		{
			cannotBeBalanced = true;
			res.push_back(false);
		}

		if (!isBalanced && !cannotBeBalanced)
		{
			int numberOfNecessaryReplacements = countOfClosingAngleBracket - countOfOpeningAngleBracket;  // if we are here we know already that closeBrackets > OpenBrackets;
			if (numberOfNecessaryReplacements > maxReplacements[index])
				res.push_back(false);  // we cannot make any replacements due to the maxReplacements restriction;
			else
				res.push_back(true);  // everything is okay, we can balance the current expression;
		}

		checkVector.clear();
	}

	return res;
}
// DO NOT MODIFY anything outside the above function

int main() {

	/* Read input from STDIN. Print output to STDOUT */
	int n = 0, m = 0;

	cin >> n;

	vector<string> expressions;
	expressions.reserve(n);
	for (int i = 0; i < n; ++i) {
		string expression;
		cin >> expression;
		expressions.push_back(expression);
	}

	cin >> m;

	vector<unsigned int> maxReplacements;
	maxReplacements.reserve(m);
	for (int i = 0; i < m; ++i) {
		unsigned int maxReplacement;
		cin >> maxReplacement;
		maxReplacements.push_back(maxReplacement);
	}

	// call balancedOrNot function
	vector<bool> results = balancedOrNot(expressions, maxReplacements);

	for (int i = 0; i < n; ++i) {
		cout << results[i] << endl;
	}

	system("pause");
	return 0;
}

