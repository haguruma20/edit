#ifndef SPHERE_H
#define SPHERE_H

// "Copyright [2015] <haguruma20>"

// a few polydisperse spheres are given.
// The function in this header-like cpp file returns a sphere
// which contacts them.

// There are 4 main functions as follows:

// Function "another" makes 4th sphere from 3 sphere.

// Function "anotherx" makes 3th sphere from 2 sphere, whose x coordinate
// we can indicate.

// Function "anothery" makes 3th sphere from 2 sphere, whose y coordinate
// we can indicate.

// Function "anotherz" makes 3th sphere from 2 sphere, whose z coordinate
// we can indicate.

#include<math.h>
#include<iostream>
#include<vector>
#include<algorithm>

class Point3{
 public:
  Point3() {xcoord_ = ycoord_ = zcoord_ = 0;}
  Point3(double, double, double);
  ~Point3() {}
  double norm() const;
  double xcoord() const {return xcoord_;}
  double ycoord() const {return ycoord_;}
  double zcoord() const {return zcoord_;}

 private:
  double xcoord_;
  double ycoord_;
  double zcoord_;
};

Point3::Point3(double x, double y, double z) {
  xcoord_ = x;
  ycoord_ = y;
  zcoord_ = z;
}

double Point3::norm() const {
  return sqrt(xcoord_*xcoord_+ycoord_*ycoord_+zcoord_*zcoord_);
}

std::ostream& operator << (std::ostream& os, const Point3& pt) {
  os << pt.xcoord() << "\t" << pt.ycoord() << "\t" << pt.zcoord() << "\n";
  return os;
}

bool operator < (const Point3& lhs, const Point3& rhs) {
    return(lhs.zcoord() < rhs.zcoord() ||
           (lhs.zcoord() == rhs.zcoord() &&
            lhs.ycoord() < rhs.ycoord()) ||
           (lhs.zcoord() == rhs.zcoord() &&
            lhs.ycoord() == rhs.ycoord() &&
            lhs.xcoord() < rhs.xcoord()));
}

Point3 operator + (const Point3& lhs, const Point3& rhs) {
  Point3 pt(lhs.xcoord()+rhs.xcoord(),
            lhs.ycoord()+rhs.ycoord(),
            lhs.zcoord()+rhs.zcoord());
  return pt;
}

Point3 operator - (const Point3& lhs, const Point3& rhs) {
  Point3 pt(lhs.xcoord()-rhs.xcoord(),
            lhs.ycoord()-rhs.ycoord(),
            lhs.zcoord()-rhs.zcoord());
  return pt;
}

// inner product
double operator * (const Point3& lhs, const Point3& rhs) {
  return lhs.xcoord()*rhs.xcoord()
    +lhs.ycoord()*rhs.ycoord()
    +lhs.zcoord()*rhs.zcoord();
}

// exterior product
Point3 operator ^ (const Point3& lhs, const Point3& rhs) {
  Point3 pt(lhs.ycoord()*rhs.zcoord()-lhs.zcoord()*rhs.ycoord(),
            lhs.zcoord()*rhs.xcoord()-lhs.xcoord()*rhs.zcoord(),
            lhs.xcoord()*rhs.ycoord()-lhs.ycoord()*rhs.xcoord());
  return pt;
}

// double(+*/...)Point3 operator
Point3 operator + (const double& val, const Point3& pt) {
  Point3 ptn(val+pt.xcoord(), val+pt.ycoord(), val+pt.zcoord());
  return ptn;
}

Point3 operator + (const Point3& pt, const double& val) {
  return val+pt;
}

Point3 operator * (const double& val, const Point3& pt) {
  Point3 ptn(val*pt.xcoord(), val*pt.ycoord(), val*pt.zcoord());
  return ptn;
}

Point3 operator * (const Point3& pt, const double& val) {
  return val*pt;
}


Point3 operator / (const Point3& pt, const double& val) {
  // std::cout << "division: " << val << std::endl;
  Point3 ptn(pt.xcoord()/val, pt.ycoord()/val, pt.zcoord()/val);
  return ptn;
}

// addition with vector<double>
Point3 operator + (const std::vector<double>& vec, const Point3 pt) {
  if (vec.size() != 3) {
      std::cout << "addition(vector,Point3) is illegal!" << std::endl;
      throw;
    }
  Point3 ptn(pt.xcoord()+vec.at(0),
             pt.ycoord()+vec.at(1),
             pt.zcoord()+vec.at(2));
  return ptn;
}

Point3 operator + (const Point3 pt, const std::vector<double>& vec) {
  return vec+pt;
}

// Euclidean distance between 2 points
double distance(const Point3& p1, const Point3& p2) {
  return pow((p1.xcoord()-p2.xcoord())*(p1.xcoord()-p2.xcoord())
             +(p1.ycoord()-p2.ycoord())*(p1.ycoord()-p2.ycoord())
             +(p1.zcoord()-p2.zcoord())*(p1.zcoord()-p2.zcoord()), 0.5);
}

class Sphere {
 public:
  // Sphere();
  Sphere(Point3, double);
  Sphere(double, double, double, double);
  ~Sphere() {}
  Point3 center() const {return center_;}
  double radius() const {return radius_;}
 private:
  Point3 center_;
  double radius_;
};

Sphere::Sphere(Point3 p0, double r) {
  center_ = p0;
  radius_ = r;
}

Sphere::Sphere(double x, double y, double z, double r) {
  const Point3 pt(x, y, z);
  center_ = pt;
  radius_ = r;
}

std::ostream& operator << (std::ostream& os, const Sphere& sp) {
  os << sp.center().xcoord() << "\t"
     << sp.center().ycoord() << "\t"
     << sp.center().zcoord() << "\t"
     << sp.radius() << "\n";
  return os;
}

bool operator < (const Sphere& lhs, const Sphere& rhs) {
    return(lhs.center().zcoord() < rhs.center().zcoord() ||
           (lhs.center().zcoord() == rhs.center().zcoord() &&
            lhs.center().ycoord() < rhs.center().ycoord()) ||
           (lhs.center().zcoord() == rhs.center().zcoord() &&
            lhs.center().ycoord() == rhs.center().ycoord() &&
            lhs.center().xcoord() < rhs.center().xcoord()));
}

Sphere operator + (const double val, const Sphere& sp) {
  Sphere nsp(sp.center()+val, sp.radius());
  return nsp;
}

Sphere operator + (const Sphere& sp, const double val) {
  return val+sp;
}

Sphere operator * (const double val, const Sphere& sp) {
  Sphere nsp(val*sp.center(), val*sp.radius());
  return nsp;
}

Sphere operator * (const Sphere& sp, const double val) {
  return val*sp;
}

Sphere operator + (const std::vector<double> vec, const Sphere& sp) {
  Sphere nsp(sp.center()+vec, sp.radius());
  return nsp;
}

Sphere operator + (const Sphere& sp, const std::vector<double> vec) {
  return vec+sp;
}

// This function returns the intersection circle of 2 spheres.
// It is also written as a Sphere here.
Sphere intersection(const Sphere& sp1, const Sphere& sp2) {
  // dist of sp1&sp2, dist of new_sp&sp1, dist of new_sp&sp2
  double d = distance(sp1.center(), sp2.center());
  double d1 = (d*d+sp1.radius()*sp1.radius()
               -sp2.radius()*sp2.radius())/(2*d);
  double d2 = d-d1;

  double ratio1 = d1/d;
  double ratio2 = d2/d;
  // std::cout << "ratio: " << ratio1 << std::endl;

  double new_radius = sqrt(sp1.radius()*sp1.radius()-d1*d1);
  Point3 new_center = ratio2*sp1.center()+ratio1*sp2.center();

  Sphere new_sp(new_center, new_radius);
  return new_sp;
}

Sphere intersection(const Sphere& sp1,
                    const Sphere& sp2,
                    const Sphere& sp3) {
  Sphere circle1 = intersection(sp1, sp2);

  Point3 normalvec = sp1.center()-sp2.center();
  normalvec = normalvec/normalvec.norm();

  Point3 circle2pt = sp3.center()
    -(normalvec*(sp3.center()-circle1.center()))*normalvec;
  double circle2rad = sqrt(sp3.radius()*sp3.radius()
                           -distance(sp3.center(), circle2pt)
                           *distance(sp3.center(), circle2pt));
  Sphere circle2(circle2pt, circle2rad);

  Sphere spnew = intersection(circle1, circle2);

  return spnew;
}

// main function
Sphere another(const Sphere& sp1, const Sphere& sp2, const Sphere& sp3,
               double new_radius, bool which) {
  Point3 pt1 = sp1.center();
  Point3 pt2 = sp2.center();
  Point3 pt3 = sp3.center();

  // normal vector against the plane generated by the 3 points

  Point3 n = (pt2-pt1)^(pt3-pt1);

  // normalization
  n = n/n.norm();
  // std::cout << n;

  // intersection circle of sp1&sp2&sp3 growed as the size of
  // "new_radius".
  Sphere gsp1(sp1.center(), sp1.radius()+new_radius);
  Sphere gsp2(sp2.center(), sp2.radius()+new_radius);
  Sphere gsp3(sp3.center(), sp3.radius()+new_radius);
  Sphere midsp = intersection(gsp1, gsp2, gsp3);
  // std::cout << "Hi\n" << intersection(gsp1,gsp2) << midsp << "Hi\n";

  // height is the distance between the plane and 4th pt (or 5th pt),
  // which is the radius of midsp.
  double height = midsp.radius();
  // std::cout << "height: " << height << std::endl;
  Point3 forth_pt = midsp.center()+height*n;
  Sphere forth_sp(forth_pt, new_radius);
  Point3 fifth_pt = midsp.center()-height*n;
  Sphere fifth_sp(fifth_pt, new_radius);
  std::vector<Sphere> sps = {forth_sp, fifth_sp};
  std::sort(sps.begin(), sps.end());

  if (which) {
      return sps.at(0);
    } else {
      return sps.at(1);
    }
}

// return the new sphere which contacts sp1&sp2 and whose center is
// on x=x0 plane.
Sphere anotherx(const Sphere& sp1, const Sphere& sp2, double x0,
                double new_radius, bool which) {
  // growed circle with the length of new_radius
  Point3 gcircle1point(x0, sp1.center().ycoord(), sp1.center().zcoord());
  double gcircle1radius = sqrt((sp1.radius()+new_radius)
                               *(sp1.radius()+new_radius)
                               -distance(gcircle1point, sp1.center())
                               *distance(gcircle1point, sp1.center()));
  Sphere gcircle1(gcircle1point, gcircle1radius);

  Point3 gcircle2point(x0, sp2.center().ycoord(), sp2.center().zcoord());
  double gcircle2radius = sqrt((sp2.radius()+new_radius)
                               *(sp2.radius()+new_radius)
                               -distance(gcircle2point, sp2.center())
                               *distance(gcircle2point, sp2.center()));
  Sphere gcircle2(gcircle2point, gcircle2radius);

  if (distance(gcircle1point, gcircle2point)
      == gcircle1radius+gcircle2radius) {
      Sphere newsp((gcircle1point+gcircle2point)/2.0, new_radius);
      return newsp;
    }

  Sphere nsp = intersection(gcircle1, gcircle2);

  // normal vector for x=x0 plane
  Point3 nx(1, 0, 0);
  // normal vector from the center of the nsp to the target point.
  Point3 n = (gcircle1.center()-gcircle2.center())^nx;
  n = n/n.norm();

  Point3 third_pt = nsp.center()+nsp.radius()*n;
  Sphere third_sp(third_pt, new_radius);
  Point3 forth_pt = nsp.center()-nsp.radius()*n;
  Sphere forth_sp(forth_pt, new_radius);

  std::vector<Sphere> sps = {third_sp, forth_sp};
  std::sort(sps.begin(), sps.end());

  if (which) {
      return sps.at(0);
    } else {
      return sps.at(1);
    }
}

Sphere anothery(const Sphere& sp1, const Sphere& sp2, double y0,
                double new_radius, bool which) {
  // growed circle with the length of new_radius
  Point3 gcircle1point(sp1.center().xcoord(), y0, sp1.center().zcoord());
  double gcircle1radius = sqrt((sp1.radius()+new_radius)
                               *(sp1.radius()+new_radius)
                               -distance(gcircle1point, sp1.center())
                               *distance(gcircle1point, sp1.center()));
  Sphere gcircle1(gcircle1point, gcircle1radius);

  Point3 gcircle2point(sp2.center().xcoord(), y0, sp2.center().zcoord());
  double gcircle2radius = sqrt((sp2.radius()+new_radius)
                               *(sp2.radius()+new_radius)
                               -distance(gcircle2point, sp2.center())
                               *distance(gcircle2point, sp2.center()));
  Sphere gcircle2(gcircle2point, gcircle2radius);

  if (distance(gcircle1point, gcircle2point)
      == gcircle1radius+gcircle2radius) {
      Sphere newsp((gcircle1point+gcircle2point)/2.0, new_radius);
      return newsp;
    }

  Sphere nsp = intersection(gcircle1, gcircle2);

  // normal vector for y=y0 plane
  Point3 nx(0, 1, 0);
  // normal vector from the center of the nsp to the target point.
  Point3 n = (gcircle1.center()-gcircle2.center())^nx;
  n = n/n.norm();

  Point3 third_pt = nsp.center()+nsp.radius()*n;
  Sphere third_sp(third_pt, new_radius);
  Point3 forth_pt = nsp.center()-nsp.radius()*n;
  Sphere forth_sp(forth_pt, new_radius);

  std::vector<Sphere> sps = {third_sp, forth_sp};
  std::sort(sps.begin(), sps.end());

  if (which) {
      return sps.at(0);
    } else {
      return sps.at(1);
    }
}

Sphere anotherz(const Sphere& sp1, const Sphere& sp2, double z0,
                double new_radius, bool which) {
  // growed circle with the length of new_radius
  Point3 gcircle1point(sp1.center().xcoord(), sp1.center().ycoord(), z0);
  double gcircle1radius = sqrt((sp1.radius()+new_radius)
                               *(sp1.radius()+new_radius)
                               -distance(gcircle1point, sp1.center())
                               *distance(gcircle1point, sp1.center()));
  Sphere gcircle1(gcircle1point, gcircle1radius);

  Point3 gcircle2point(sp2.center().xcoord(), sp2.center().ycoord(), z0);
  double gcircle2radius = sqrt((sp2.radius()+new_radius)
                               *(sp2.radius()+new_radius)
                               -distance(gcircle2point, sp2.center())
                               *distance(gcircle2point, sp2.center()));
  Sphere gcircle2(gcircle2point, gcircle2radius);

  if (distance(gcircle1point, gcircle2point)
      == gcircle1radius+gcircle2radius) {
      Sphere newsp((gcircle1point+gcircle2point)/2.0, new_radius);
      return newsp;
    }

  Sphere nsp = intersection(gcircle1, gcircle2);

  // normal vector for z=z0 plane
  Point3 nx(0, 0, 1);
  // normal vector from the center of the nsp to the target point.
  Point3 n = (gcircle1.center()-gcircle2.center())^nx;
  n = n/n.norm();

  Point3 third_pt = nsp.center()+nsp.radius()*n;
  Sphere third_sp(third_pt, new_radius);
  Point3 forth_pt = nsp.center()-nsp.radius()*n;
  Sphere forth_sp(forth_pt, new_radius);

  std::vector<Sphere> sps = {third_sp, forth_sp};
  std::sort(sps.begin(), sps.end());

  if (which) {
      return sps.at(0);
    } else {
      return sps.at(1);
    }
}

#endif  // SPHERE_H
