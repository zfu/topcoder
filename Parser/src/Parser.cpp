//============================================================================
// Name        : Parser.cpp
// Author      : anson
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Parser {
public:
    Parser(string signiture) {
        mSignature = signiture;
        size_t start = 0;
        size_t end = signiture.find(' ');
        mReturnType = signiture.substr(start, end-start);
        mIsList = (mReturnType == "ListNode*");
        mIsTree = (mReturnType == "TreeNode*");
        mReturnName = "result";
        start = end+1;
        end = signiture.find('(');
        mMethodName = signiture.substr(start, end-start);
        //        cout << mReturnType << "," << mMethodName << endl;
        start = end+1;
        while (signiture[end] != ')') {
            if (signiture[end] == ',') {
                mArguments.push_back(signiture.substr(start, end-start));
                start = end+2;
                end = start;
            }
            else end++;
        }
        mArguments.push_back(signiture.substr(start, end-start));
        for (size_t i = 0; i < mArguments.size(); i++) {
            size_t pos = mArguments[i].find(' ');
            mArgTypes.push_back(mArguments[i].substr(0, pos));
            mArgNames.push_back(mArguments[i].substr(pos+1, mArguments[i].size()-pos));
        }

        //        for (size_t i = 0; i < mArguments.size(); i++) {
        //            cout << mArguments[i] << ";" << endl;
        //            cout << mArgTypes[i] << " " << mArgNames[i] << ";" << endl;
        //        }
        mIncludes.push_back("#include <vector>");
        mIncludes.push_back("#include <list>");
        mIncludes.push_back("#include <map>");
        mIncludes.push_back("#include <set>");
        mIncludes.push_back("#include <queue>");
        mIncludes.push_back("#include <deque>");
        mIncludes.push_back("#include <bitset>");
        mIncludes.push_back("#include <algorithm>");
        mIncludes.push_back("#include <functional>");
        mIncludes.push_back("#include <numeric>");
        mIncludes.push_back("#include <utility>");
        mIncludes.push_back("#include <sstream>");
        mIncludes.push_back("#include <iostream>");
        mIncludes.push_back("#include <iomanip>");
        mIncludes.push_back("#include <cstdio>");
        mIncludes.push_back("#include <cmath>");
        mIncludes.push_back("#include <cstdlib>");
        mIncludes.push_back("#include <ctime>");
        mIncludes.push_back("#include <climits>");
        for (size_t i = 0; i < mArguments.size(); i++) {
            if (mArgTypes[i] == "ListNode*") {
                mIsList = true;
                break;
            }
            else if (mArgTypes[i] == "TreeNode*") {
                mIsTree = true;
                break;
            }
        }
        if (mIsList) mIncludes.push_back("#include \"ListNode.h\"");
        if (mIsTree) mIncludes.push_back("#include \"TreeNode.h\"");
    };

    void generateCode() {
        ostringstream stream;
        generateIncludes(stream);
        generateClass(stream);
        generateTests(stream);
        generateMain(stream);
        string code = stream.str();
        cout << code << endl;
    }

private:
    void generateIncludes(ostringstream &stream) {
        for (size_t i = 0; i < mIncludes.size(); i++) {
            stream << mIncludes[i] << "\n";
        }
        stream << "\n";
        stream << "using namespace std;" << "\n";
        stream << "\n";
    };

    void generateClass(ostringstream &stream) {
        stream << "class Solution {" << "\n";
        stream << "public:" << "\n";
        stream << "\t" + mSignature + " {\n";
        stream << "\n";
        stream << "\t}" << "\n";
        stream << "};" << "\n";
        stream << "\n";
    };

    void showInputs(ostringstream &stream) {
        stream << "\t" << "cout << \"Test \" << testNum << \": [\"";
        size_t N = mArguments.size();
        for (size_t i = 0; i < N; i++) {
            if (mArgTypes[i] == "string") {
                if (i == N-1) stream << " << " << mArgNames[i] << " << \"]\"";
                else stream << " << " << mArgNames[i] << " << \", \"";
            }
            else if (mArgTypes[i] == "ListNode*" || mArgTypes[i] == "TreeNode*" ) {
                if (i == N-1) stream << " << toPretty(" << mArgNames[i] << ") << \"]\"";
                else stream << " << toPretty(" << mArgNames[i] << ") << \", \"";
            }
            else {
                cerr << "unkown input type"  << endl;
            }
        }
        stream  << "<< endl;" << "\n";
    }

    void checkAnswer(ostringstream &stream) {
        if (mReturnType == "string") {
            stream << "\t" << "if (hasAnswer) {" << "\n";
            stream << "\t\t" << "cout << \"Desired answer:\" << endl;" << "\n";
            stream << "\t\t" << "cout << \"\\t\" << ";
            stream << mReturnName;
            stream << " << endl;" << "\n";
            stream << "\t" << "}" << "\n";
            stream << "\t" << "cout << \"Your answer:\" << endl;" << "\n";
            stream << "\t" << "cout << \"\\t\" << answer << endl;" << "\n";
            stream << "\t" << "if (hasAnswer) {" << "\n";
            stream << "\t\t" << "if (answer.size() != ";
            stream << mReturnName << ".size()) {" << "\n";
            stream << "\t\t\t" << "res = false;" << "\n";
            stream << "\t\t" << "} else {" << "\n";
            stream << "\t\t\t" << "if (answer != ";
            stream << mReturnName << ") {" << "\n";
            stream << "\t\t\t\t" << "res = false;" << "\n";
            stream << "\t\t\t" << "}" << "\n";
            stream << "\t\t" << "}" << "\n";
        }
        else if (mReturnType == "ListNode*" || mReturnType == "TreeNode*") {
            stream << "\t" << "if (hasAnswer) {" << "\n";
            stream << "\t\t" << "cout << \"Desired answer:\" << endl;" << "\n";
            stream << "\t\t" << "cout << \"\\t\" << toPretty(";
            stream << mReturnName;
            stream << ") << endl;" << "\n";
            stream << "\t" << "}" << "\n";
            stream << "\t" << "cout << \"Your answer:\" << endl;" << "\n";
            stream << "\t" << "cout << \"\\t\" << toPretty(answer) << endl;" << "\n";
            stream << "\t" << "if (hasAnswer) {" << "\n";
            stream << "\t\t" << "if (toString(answer) != toString(";
            stream << mReturnName << ")) {" << "\n";
            stream << "\t\t\t" << "res = false;" << "\n";
            stream << "\t\t" << "}" << "\n";
        }
        else {
            cerr << "unknown return type" << endl;
        }
    }

    void generateTests(ostringstream &stream) {
        stream << "bool runTest(int testNum, ";
        for (size_t i = 0; i < mArguments.size(); i++) {
            stream << mArguments[i] << ", ";
        }
        stream << "bool hasAnswer, " << mReturnType << " " << mReturnName << ") {" << "\n";
        showInputs(stream);
        stream << "\t" << "Solution *obj;" << "\n";
        stream << "\t" << mReturnType << " answer;" << "\n";
        stream << "\t" << "obj = new Solution();" << "\n";
        stream << "\t" << "clock_t startTime = clock();" << "\n";
        stream << "\t" << "answer = obj->minWindow(";
        size_t i = 0;
        for (; i < mArguments.size()-1; i++) {
            stream << mArgNames[i] << ", ";
        }
        stream << mArgNames[i];
        stream << ");" << "\n";
        stream << "\t" << "clock_t endTime = clock();" << "\n";
        stream << "\t" << "delete obj;" << "\n";
        stream << "\t" << "bool res;" << "\n";
        stream << "\t" << "res = true;" << "\n";
        stream << "\t" << "cout << \"Time: \" << double(endTime - startTime) / CLOCKS_PER_SEC << \" seconds\" << endl;" << "\n";

        checkAnswer(stream);
        stream << "\t" << "}" << "\n";

        stream << "\t" << "if (!res) {" << "\n";
        stream << "\t\t" << "cout << \"DOESN'T MATCH!!!!\" << endl;" << "\n";
        stream << "\t" << "} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {" << "\n";
        stream << "\t\t" << "cout << \"FAIL the timeout\" << endl;" << "\n";
        stream << "\t\t" << "res = false;" << "\n";
        stream << "\t" << "} else if (hasAnswer) {" << "\n";
        stream << "\t\t" << "cout << \"Match :-)\" << endl;" << "\n";
        stream << "\t" << "} else {" << "\n";
        stream << "\t\t" << "cout << \"OK, but is it right?\" << endl;" << "\n";
        stream << "\t" << "}" << "\n";
        stream << "\t" << "cout << \"\" << endl;" << "\n";
        stream << "\t" << "return res;" << "\n";

        stream << "}" << '\n';
        stream << "\n";
    };

    // TODO replace this dummy case generator
    void generateCase(ostringstream &stream, int i) {
        // generate test cases
        stream << "\t" << "{" << "\n";
        stream << "\t\t" << "// ----- test " << i << " -----" << "\n";
        for (size_t i = 0; i < mArguments.size(); i++) {
            if (mArgTypes[i] == "string") {
                stream << "\t\t" << mArgNames[i] << " = " << "\"a\"" << ";\n";
            }
            else if (mArgTypes[i] == "ListNode*" || mArgTypes[i] == "TreeNode*") {
                stream << "\t\t" << mArgNames[i] << " = fromString(" << "\"{2,1,3}\"" << ");\n";
            }
            else {
                cerr << "unknown argument type" << endl;
            }
        }
        if (mReturnType == "string") {
            stream << "\t\t" << mReturnName << " = " << "\"a\"" << ";\n";
        }
        else if (mReturnType == "ListNode*" || mReturnType == "TreeNode*") {
            stream << "\t\t" << mReturnName << " = fromString(" << "\"{2,1,3}\"" << ");\n";
        }
        else {
            cerr << "unknown return type" << endl;
        }
        stream << "\t\t" << "all_right = runTest(0, ";
        for (size_t i = 0; i < mArguments.size(); i++) {
            stream << mArgNames[i] << ", ";
        }
        stream << "true, ";
        stream << mReturnName;
        stream << ") && all_right;" << "\n";
        stream << "\t\t" << "// ------------------" << "\n";
        stream << "\t" << "}" << "\n";

    }

    void generateMain(ostringstream &stream) {
        // main function
        stream << "int main() {" << "\n";
        stream << "\t" << "bool all_right;" << "\n";
        stream << "\t" << "all_right = true;" << "\n";
        for (size_t i = 0; i < mArguments.size(); i++) {
            stream << "\t" << mArguments[i] << ";" << "\n";
        }
        stream << "\t" << mReturnType << " " << mReturnName << ";" << "\n";
        stream << "\n";
        generateCase(stream, 0);
        stream << "\n";
        stream << "\t" << "if (all_right) {" << "\n";
        stream << "\t\t" << "cout << \"You're a stud (at least on the example cases)!\" << endl;" << "\n";
        stream << "\t" << "} else {" << "\n";
        stream << "\t\t" << "cout << \"Some of the test cases had errors.\" << endl;" << "\n";
        stream << "\t" << "}" << "\n";
        stream << "\t" << "return 0;" << "\n";
        stream << "}" << "\n";
    };

    string mSignature;
    string mReturnType;
    string mReturnName;
    string mMethodName;
    vector<string> mArguments;
    vector<string> mArgTypes;
    vector<string> mArgNames;
    vector<string> mIncludes;
    bool mIsList;
    bool mIsTree;
};

int main() {
    Parser parser("ListNode* minWindow(ListNode* S, string T)");
    parser.generateCode();
    return 0;
}
