#include <iostream>
#include <fstream>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
// #include <CGAL/Cartesian.h>
// #include <CGAL/MP_Float.h>
// #include <CGAL/Quotient.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arrangement_2.h>

// typedef CGAL::Quotient<CGAL::MP_Float>     Number_type;
//typedef CGAL::Cartesian<Number_type>       Kernel;
typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel> Traits_2;
typedef Traits_2::Point_2                  Point_2;
typedef Traits_2::X_monotone_curve_2       Segment_2;
typedef CGAL::Arrangement_2<Traits_2>      Arrangement_2;

using namespace std;

int main(int argc, char** argv) {
  // if not enough parameters provided, print a helpful message and quit
  if(argc < 3) {
    cout << "usage: " << argv[0] << " [segments file] [points file]" << endl
	 << "\t where [segments file] is a file containing line segments" << endl
	 << "\t and   [points file]   is a file containing query points" << endl;
    return 0;
  }
  ifstream segment_file(argv[1]);
  istream_iterator<Segment_2> segment_begin(segment_file);
  istream_iterator<Segment_2> segment_end;
  
  ifstream point_file(argv[2]);
  istream_iterator<Point_2> point_begin(point_file);
  istream_iterator<Point_2> point_end;
  
  Arrangement_2   arr;

  /////////////////////////////////////////////////////////////////////////////
  // CGAL Documentation on insert:
  // http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Arrangement_on_surface_2_ref/Function_insert.html#Cross_link_anchor_1192
  /////////////////////////////////////////////////////////////////////////////

  // read in the segments
  //CGAL::insert(arr, segment_begin, segment_end);
  while(segment_begin != segment_end) {
    CGAL::insert(arr, *segment_begin);
    ++segment_begin;
  }

  // locate and print the containing polygon for each point
  
  
  return 0;
}
