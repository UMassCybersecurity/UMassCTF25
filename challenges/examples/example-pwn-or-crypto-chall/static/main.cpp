# include <iostream> 

using namespace std; 

int main() { 
  int input = 0; 
  cout << "Enter a number (1 to get flag): "; 
  cin >> input; 

  if (input == 1) {
    cout << "UMASS{example-pwn-or-crypto!92}";
  } else { 
    cout << "Wrong number :(";
  }

  return 0; 
}

