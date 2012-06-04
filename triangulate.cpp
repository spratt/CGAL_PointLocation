#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_2<K>             Triangulation;
typedef Triangulation::Point                 Point;
typedef Triangulation::Segment               Segment;
typedef Triangulation::Finite_edges_iterator Edges_iterator;

using namespace std;

int main(int argc, char** argv) {
  istream_iterator<Point> begin(cin);
  istream_iterator<Point> end;

  // Create the triangulation
  Triangulation t;
  t.insert(begin, end);

  // print the segments
  Edges_iterator iter = t.finite_edges_begin();
  while(iter != t.finite_edges_end()) {
    cout << t.segment(iter) << endl;
    ++iter;
  }

  return 0;
}
