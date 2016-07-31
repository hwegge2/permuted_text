#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

vector< vector<string> > generate (const vector<string>& list)	//generate creates a vector of vector strings
																//containing the user input data implemented for each element.
{
  vector<string> copy (list);
        vector< vector<string> > rotate;

        copy.push_back("END_OF_LINE");
        vector<string>::iterator iter = copy.begin();

        while (*(copy.begin()) != "END_OF_LINE") {
                rotate.push_back(copy);
                string rotated = *(copy.begin());
                copy.erase(copy.begin());
                copy.push_back(rotated);
        }

        return rotate;

}

vector<string> split (const string& set)
{
  typedef string::size_type size;
        vector<string> vect;

        size i = 0;

        while (i != set.size()) {

                while (i != set.size() && isspace(set[i])) {
                        i++;
                }

                size j = i;
                while (j != set.size() && !isspace(set[j])) {
                        j++;
                }

                if (i != j) {
                        vect.push_back(set.substr(i, (j - i)));
                        i = j;
                }

        }

        return vect;
}

//compare function will compare and convert the given elements in the vector string
//to lower case
bool compare(const vector<string>& rotatation_beg, const vector<string>& rotation_end)
{
  vector<string>::const_iterator first = rotatation_beg.begin();	//first iterator will compare with the second
  vector<string>::const_iterator second = rotation_end.begin();

        while (*first == *second) {			//skip over same values in the element
                first++;
                second++;
        }

        string one = *first;
        string two = *second;
        transform (one.begin(), one.end(), one.begin(), ::tolower);		//transform will appropriate the strings to correct lowercase ASCII values
        transform (two.begin(), two.end(), two.begin(), ::tolower);
        return one < two;
}
//this functions allows us to appropriate the max length needed to correctly output the permuted index.
//
string::size_type vector_string (vector< vector<string> >& rotation,vector<string>& left_side, vector<string>& right_side)
{
	 for (vector< vector<string> >::iterator i = rotation.begin() ; i <rotation.end() ; i++) {
                string left;
                string right;

                vector<string>::iterator j = (*i).begin();
                while (j != (*i).end()) {
                        while (*j != "END_OF_LINE") {
                                right += *j;
                                right += " ";
                                j++;
                        }
                        if (*j == "END_OF_LINE") {
                                j++;
                        }
                        while (j != (*i).end()) {
                                left += *j;
                                left += " ";
                                j++;
                        }
                }
				left_side.push_back(left);
                right_side.push_back(right);
        }

        string::size_type max_size = 0;
        vector<string>::iterator j = left_side.begin();
        while (j < left_side.end()) {
                max_size = max (max_size, (*j).size());
                j++;
        }

        return max_size;
}
int main()
{
   vector<string> set;
   string x;
  vector<vector<string> > rotation;
    vector<string> input_set;
	vector< vector<string> > input_rotation;
	 vector<string> left_side;
        vector<string> right_side;
   cout << "Please enter a set of words followed by Ctrl-Z on Windows or Ctrl-D on Unix: ";

	while (getline(cin,x)){

		//the values that were entered by the user
	set.push_back(x);
	input_set = split (x);
	input_rotation = generate (input_set);	//sends the vector of vector string to the generate function

	rotation.insert (rotation.end(), input_rotation.begin(),input_rotation.end());

	}

    if (set.empty()) // error handle if the vector is empty
   {

      cout << "ERROR: No input was entered. Please try again."<<endl;
      return 1;

   }

   sort(rotation.begin(),rotation.end(), compare);

   string::size_type left_shift = vector_string (rotation,left_side, right_side);

   cout<<endl;
     for (int i = 0 ; i < left_side.size() ; i++)	//outputs the permuted index with the left and corresponding right string.
     {
		cout << setw(left_shift+1) << left_side[i];
		cout << "\t" << right_side[i] << endl;
     }

   return 0;
}

