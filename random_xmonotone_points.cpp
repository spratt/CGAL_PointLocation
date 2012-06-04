#include <iostream>
#include <vector>
#include <CGAL/Random.h>

typedef CGAL::Random Random;

using namespace std;

int main(int argc, char** argv) {
  // print a helpful message if not enough parameters given
  if(argc < 4) {
    cout << "Usage: " << argv[0] << " [n] [lower] [upper]" << endl
	 << "Where" << endl
	 << "\t n is the number of points to generate" << endl
	 << "\t each coordinate is between lower (inclusive), and upper (not inclusive)"
	 << endl;
    return 0;
  }

  // grab the parameters
  int n = atoi(argv[1]);
  int lower = atoi(argv[2]);
  int upper = atoi(argv[3]);
  vector<int> xs;

  // generate the x's
  Random random;
  for(int i = 0; i < n; ++i)
    xs.push_back(random.get_int(lower,upper));

  // sort the x's
  sort(xs.begin(),xs.end());

  // print the points
  for(int i = 0; i < n; ++i) {
    cout << xs[i] << " "
	 << random.get_int(lower,upper) << endl;
  }

  return 0;
}
