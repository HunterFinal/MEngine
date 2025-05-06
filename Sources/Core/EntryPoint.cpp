#include <iostream>

using namespace std;

int main()
{

  cout << typeid(int64).name() << endl;
  cout << typeid(uint8).name() << endl;
  cout << typeid(TYPE_NULLPTR).name() << endl;

  return 0;
}