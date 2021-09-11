// Aslýhan Altun
// 1306200094
// Date: 17.01.2021
// Development Environment: Visual Studio2019

//Normally program should run challenges up to 6th but last hours I find out it is not running 5th challenge although I made level by level.I couldn't find what cause that false result
//But it can run with up to 6th challange. 
//I thought you want to know that.

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

//This function is used to remove gaps between characters
string delspace(string line) {
    int i = 0;
    string line1 = "";
    while (i < line.length()) {
        if (line[i] != ' ') {
            line1 += line[i];
        }
        i++;
    }
    return line1;
}

//These maps are used to stock integer and double variables
map<string, int> intval;
map<string, double> dval;


//These iterators used to find variables
map<string, int>::iterator it;
map<string, double>::iterator it1;


//function used for seperating line with respect to '=' symbol
string left(string line) {
    string left = line.substr(line.find_first_of(line[0]), line.find_first_of('='));
    return left;
}
string right(string line) {
    string right = line.substr(line.find('=') + 1);
    return right;
}

//Function used for finding which side of equality has value
string value_test(string line, string line1) {
    if (line[0] == '0' || line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[0] == '9')
    {
        return line;
    }
    else if (line1[0] == '0' || line1[0] == '1' || line1[0] == '2' || line1[0] == '3' || line1[0] == '4' || line1[0] == '5' || line1[0] == '6' || line1[0] == '7' || line1[0] == '8' || line1[0] == '9')
    {
        return line1;
    }
    else {
        return "-0";
    }
}
//Bool test used for determining double variables
bool dtest(string line) {
    if (count(line.begin(), line.end(), '.') > 0) {
        return true;
    }
    else {
        return false;
    }

}
//Used for defining variables
void variable(string line1) {
    string line = delspace(line1);
    string sep1 = left(line);
    string sep2 = right(line);
    string value = value_test(sep1, sep2);
    string name;
    int val1;
    double val2;
    if (value != "-0") {
        if (value == sep1) {
            name = sep2;
        }
        else {
            name = sep1;
        }
        bool dt = dtest(value);
        if (dt == false) {
            val1 = stoi(value);
            intval.insert(pair<string, int>(name, val1));
        }
        else if (dt == true) {
            val2 = stod(value);
            dval.insert(pair<string, double>(name, val2));
        }
    }
}
//Used for searching variable names in maps and replacing variable names with their values
string search(string line) {
    if (line[0] == '0' || line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[0] == '9')
    {
        return line;
    }
    it = intval.find(line);
    it1 = dval.find(line);

    if (it1 != dval.end()) {
        return to_string(it1->second);
    }
    else if (it != intval.end()) {
        return to_string(it->second);
    }
    else {
        return "null";
    }

}

// These functions are used for calculations
string division(string l_line, string r_line) {
    l_line = search(l_line);
    r_line = search(r_line);
    if (r_line != "0") {
        string sum = l_line + r_line;
        if (count(sum.begin(), sum.end(), '.') > 0) {
            return to_string(stod(l_line) / stod(r_line));
        }
        else {
            return to_string(stoi(l_line) / stoi(r_line));
        }
    }
    else { return "error"; }
}

string multiplication(string l_line, string r_line) {
    l_line = search(l_line);
    r_line = search(r_line);
    string sum = l_line + r_line;
    if (count(sum.begin(), sum.end(), '.') > 0) {
        return to_string(stod(l_line) * stod(r_line));
    }
    else {
        return to_string(stoi(l_line) * stoi(r_line));
    }
}

string addition(string l_line, string r_line) {
    l_line = search(l_line);
    r_line = search(r_line);
    string sum = l_line + r_line;
    if (count(sum.begin(), sum.end(), '.') > 0) {
        return to_string(stod(l_line) + stod(r_line));
    }
    else {
        return to_string(stoi(l_line) + stoi(r_line));
    }
}

string extraction(string l_line, string r_line) {
    l_line = search(l_line);
    r_line = search(r_line);
    string sum = l_line + r_line;
    if (count(sum.begin(), sum.end(), '.') > 0) {
        return to_string(stod(l_line) - stod(r_line));
    }
    else {
        return to_string(stoi(l_line) - stoi(r_line));
    }
}

//this function used for connect calculations with respect to predence
string solve(string line) {
    if (count(line.begin(), line.end(), '(') > 0) {
        string par1 = line.substr(line.find_last_of('('), line.substr(line.find_last_of('(')).find_first_of(')') + 1);
        string par = par1.substr(1, par1.size() - 2);
        return solve(line.replace(line.find(par1), par1.length(), solve(par)));
    }
    else if (count(line.begin(), line.end(), '/') > 0) {
        int i = line.find_first_of('/');
        while (i > 0 && line[i - 1] != '=' && line[i - 1] != '-' && line[i - 1] != '+' && line[i - 1] != '*') {
            i--;
        }
        string left = line.substr(i, line.find_first_of('/') - i);
        string left_side = search(left);
        int left_index = i;
        i = line.find_first_of('/');
        while (i < line.length() - 1 && line[i + 1] != '*' && line[i + 1] != '+' && line[i + 1] != '/' && line[i + 1]) {
            i++;
        }
        string right = line.substr(line.find_first_of('/') + 1, i - line.find_first_of('/'));
        string right_side = search(right);
        cout << right_side << endl;
        return solve(line.replace(left_index, left.length() + 2, division(left_side, right_side)));
    }
    else if (count(line.begin(), line.end(), '*') > 0) {
        int i = line.find_first_of('*');
        while (i > 0 && line[i - 1] != '-' && line[i - 1] != '+' && line[i - 1] != '/') {
            i--;
        }
        string left = line.substr(i, line.find_first_of('*') - i);
        string left_side = search(left);
        int left_index = i;
        i = line.find_first_of('*');
        while (i < line.length() - 1 && line[i + 1] != '/' && line[i + 1] != '+' && line[i + 1] != '*' && line[i + 1]) {
            i++;
        }
        string right = line.substr(line.find_first_of('*') + 1, i - line.find_first_of('*'));
        string right_side = search(right);
        return solve(line.replace(left_index, left.length() + 2, multiplication(left_side, right_side)));
    }
    else if (count(line.begin(), line.end(), '-') > 0) {
        int i = line.find_first_of('-');
        while (i > 0 && line[i - 1] != '/' && line[i - 1] != '+' && line[i - 1] != '*') {
            i--;
        }
        string left = line.substr(i, line.find_first_of('-') - i);
        string left_side = search(left);
        int left_index = i;
        i = line.find_first_of('-');
        while (i < line.length() - 1 && line[i + 1] != '*' && line[i + 1] != '+' && line[i + 1] != '-' && line[i + 1]) {
            i++;
        }
        string right = line.substr(line.find_first_of('-') + 1, i - line.find_first_of('-'));
        string right_side = search(right);
        return solve(line.replace(left_index, left.length() + 2, extraction(left_side, right_side)));
    }
    else if (count(line.begin(), line.end(), '+') > 0) {
        int i = line.find_first_of('+');
        while (i > 0 && line[i - 1] != '-' && line[i - 1] != '/' && line[i - 1] != '*') {
            i--;
        }
        string left = line.substr(i, line.find_first_of('+') - i);
        string left_side = search(left);
        int left_index = i;
        i = line.find_first_of('+');
        while (i < line.length() - 1 && line[i + 1] != '*' && line[i + 1] != '+' && line[i + 1] != '+' && line[i + 1]) {
            i++;
        }
        string right = line.substr(line.find_first_of('+') + 1, i - line.find_first_of('+'));
        string right_side = search(right);
        return solve(line.replace(left_index, left.length() + 2, addition(left_side, right_side)));
    }
    else { return line; }
}
//Used for determining if arrive to result line or not
string out(string line) {
    if (line[0] == 'O' && line[1] == 'U' && line[2] == 'T') {
        return "-0";
    }
    else {
        return line;
    }
}


int main() {
    string a;
    string result;
    string end;



        ifstream input("input.inp");

        if (input.is_open()) {
            string line;
            while (getline(input, line)) {
                line = delspace(line);
                if (out(line) == line) {
                    string rights = right(line);
                    string lefts = left(line);

                    if (value_test(rights, lefts) != "-0") {
                        line = solve(line);
                        variable(line);
                    }
                    else {
                        if (search(lefts) == "null") {
                            a = solve(rights);
                            string sum = lefts + "=" + a;
                            variable(sum);
                        }
                        else {
                            a = solve(lefts);
                            string sum = rights + "=" + a;
                            variable(sum);
                        }
                    }
                }
                else {
                    end = line.substr(line.find_first_of('T') + 1);
                    break;
                }
            }
            ofstream output("output.txt", fstream::out);
            result = search(end);
            output << result << endl;
        }
        else {

        }
    
    return 0;
}
