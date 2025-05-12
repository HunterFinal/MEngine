#include <iostream>

using namespace std;

int main()
{
  // Vector3 a {1,2,3};
  // Vector3 b {4,6,5};

  // Vector3 c = a.Cross(b);

  // cout << c.X << endl;

  // c = a + a;

  // c = 2.5 * a;
  
  // cout << c.Dot(c) << endl;

  // cout << ((a == a) ? "true" : "false") << endl;

  // cout << ((b != b) ? "true" : "false") << endl;

  // c *= 2;

  // cout << c.X << endl;

  // cout << MMath::DOUBLE_PI << endl;

  // cout << (c.Equals(a) ? "Equals" : "Not equals") << endl;

  Vector3 a {1.0,2.0,3.0};
  Vector3f b {4.0f,5.0f,6.0f};

  Vector3 c(b);

  cout << c.X << endl;

  Vector2 a2 {1,2};

  

  return 0;
}