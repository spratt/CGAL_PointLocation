#include <iostream>
#include <fstream>

#include <CGAL/Object.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_trapezoid_ric_point_location.h>

///////////////////////////////////////////////////////////////////////////////
// CGAL doc for Object:
// http://www.cgal.org/Manual/latest/doc_html/cgal_manual/STL_Extension_ref/Class_Object.html#Cross_link_anchor_1888
///////////////////////////////////////////////////////////////////////////////
typedef CGAL::Object Object;
using CGAL::object_cast;

///////////////////////////////////////////////////////////////////////////////
// CGAL doc for kernel:
// http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Kernel_23_ref/Concept_Kernel.html#Cross_link_anchor_318
///////////////////////////////////////////////////////////////////////////////

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;

///////////////////////////////////////////////////////////////////////////////
// CGAL Doc for Arrangement_2:
// http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Arrangement_on_surface_2_ref/Class_Arrangement_2.html#Cross_link_anchor_1186
///////////////////////////////////////////////////////////////////////////////
typedef CGAL::Arr_segment_traits_2<Kernel> Traits_2;
typedef Traits_2::Point_2                  Point_2;
typedef Traits_2::X_monotone_curve_2       Segment_2;
typedef CGAL::Arrangement_2<Traits_2>      Arrangement_2;

///////////////////////////////////////////////////////////////////////////////
// CGAL doc for ArrrangementPointLocation_2:
// http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Arrangement_on_surface_2_ref/Concept_ArrangementPointLocation_2.html
// http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Arrangement_on_surface_2_ref/Class_Arr_trapezoid_ric_point_location.html#Cross_link_anchor_1273
///////////////////////////////////////////////////////////////////////////////
typedef CGAL::Arr_trapezoid_ric_point_location<Arrangement_2> PointLocation_2;
typedef Arrangement_2::Face_handle Face_handle;
typedef Arrangement_2::Halfedge_handle Halfedge_handle;
typedef Arrangement_2::Vertex_handle Vertex_handle;
typedef Arrangement_2::Face_const_handle Face_const_handle;
typedef Arrangement_2::Halfedge_const_handle Halfedge_const_handle;
typedef Arrangement_2::Vertex_const_handle Vertex_const_handle;

typedef Arrangement_2::Ccb_halfedge_circulator Halfedge_circulator;

using namespace std;

int main(int argc, char** argv) {
  // if not enough parameters provided, print a helpful message and quit
  if(argc < 3) {
    cout << "usage: " << argv[0] << " [segments file] [points file]" << endl
	 << "\t where [segments file] is a file containing line segments" << endl
	 << "\t and   [points file]   is a file containing query points" << endl;
    return 0;
  }

  // for segment input
  ifstream segment_file(argv[1]);
  istream_iterator<Segment_2> segment_begin(segment_file);
  istream_iterator<Segment_2> segment_end;
  
  // for point input
  ifstream point_file(argv[2]);
  istream_iterator<Point_2> point_begin(point_file);
  istream_iterator<Point_2> point_end;

  // for storing the planar subdivision
  Arrangement_2   arr;

  /////////////////////////////////////////////////////////////////////////////
  // CGAL Documentation on insert:
  // http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Arrangement_on_surface_2_ref/Function_insert.html#Cross_link_anchor_1192
  /////////////////////////////////////////////////////////////////////////////

  // read in the segments
  while(segment_begin != segment_end) {
    CGAL::insert(arr, *segment_begin);
    ++segment_begin;
  }

  // build the point location
  PointLocation_2 pl;
  pl.attach(arr);

  // locate and print the containing polygon for each point
  while(point_begin != point_end) {
    Object o = pl.locate(*point_begin);
    cout << "(" << *point_begin << "): ";
    ++point_begin;

    // determine what type is stored in the object
    if(const Face_const_handle * face_handle_c = object_cast<Face_const_handle>(&o)) {
      Face_handle face_handle = arr.non_const_handle(*face_handle_c);
      if(face_handle->has_outer_ccb()) {
	Halfedge_circulator hc = face_handle->outer_ccb();
	Halfedge_circulator first = hc;
	do {
	  cout << "("
	       << hc->source()->point()
	       << " "
	       << hc->target()->point()
	       << ") ";
	} while(++hc != first);
	cout << endl;
      } else {
	cout << "outer" << endl;
      }
    } else if(const Halfedge_const_handle * halfedge_handle =
	      object_cast<Halfedge_const_handle>(&o)) {
      cout << "Edge: ("
	   << (*halfedge_handle)->source()->point()
	   << " "
	   << (*halfedge_handle)->target()->point()
	   << ")" << endl;
    } else if(const Vertex_const_handle * vertex_handle =
	      object_cast<Vertex_const_handle>(&o)) {
      cout << "Vertex" << endl;
    } else {
      cout << "Error: unknown point location result" << endl;
      return 1;
    }
  }
  
  return 0;
}
