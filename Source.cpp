#include <iostream>
#include <optional>


// C++17
class Vector3D {
public:
   double X, Y, Z;

   Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

   // �������� ��������� ��������
   Vector3D operator-(const Vector3D& v) const {
      return Vector3D(X - v.X, Y - v.Y, Z - v.Z);
   }

   // �������� �������� ��������
   Vector3D operator+(const Vector3D& v) const {
      return Vector3D(X + v.X, Y + v.Y, Z + v.Z);
   }

   // �������� ��������� ������� �� ������
   Vector3D operator*(double scalar) const {
      return Vector3D(X * scalar, Y * scalar, Z * scalar);
   }

   // �������� ��������� ��������
   bool operator==(const Vector3D& v) const {
      return X == v.X && Y == v.Y && Z == v.Z;
   }

   // ��������� ������������
   double dot(const Vector3D& v) const {
      return X * v.X + Y * v.Y + Z * v.Z;
   }

   // ����� ��� ������ �������
   void print() const {
      std::cout << "(" << X << ", " << Y << ", " << Z << ")\n";
   }
};


class Segment3D {
public:

   Vector3D start, end;

   // �����������
   Segment3D(const Vector3D& s, const Vector3D& e) : start(s), end(e) {}
};

// ������� ��� ���������� ����� ����������� ���� ��������
std::optional<Vector3D> Intersect(const Segment3D& seg1, const Segment3D& seg2) {
   Vector3D p1 = seg1.start;
   Vector3D p2 = seg1.end;
   Vector3D p3 = seg2.start;
   Vector3D p4 = seg2.end;

   // ������������ ������� ��������
   Vector3D d1 = p2 - p1; 
   Vector3D d2 = p4 - p3; 

   if (d1.dot(d1) < std::numeric_limits<double>::epsilon() || d2.dot(d2) < std::numeric_limits<double>::epsilon())
   {
      return std::nullopt; 
   }

   // ������ ����� ���������� ������� ��������
   Vector3D r = p1 - p3;

   double d2121 = d1.dot(d1);
   double d4321 = d1.dot(d2);
   double d4343 = d2.dot(d2);
   double d1321 = d1.dot(r);
   double d1343 = d2.dot(r);

   // ���������� ����������� ��� ����������
   double denom = d2121 * d4343 - d4321 * d4321;

   // �������� �� �������������� ��� �������������� ��������
   if (fabs(denom) < std::numeric_limits<double>::epsilon()) {
      return std::nullopt; // ������� ����������� ��� ����������� 
   }

   double t = (d1343 * d4321 - d1321 * d4343) / denom;
   double s = (d1343 + t * d4321) / d4343;

   if (s < 0 || s > 1 || t < 0 || t > 1) {
      return std::nullopt; // ����������� ���
   }

   // ������ ����� ����������� �������
   Vector3D intersection = p1 + d1 * s;


   Vector3D intersection_check = p3 + d2 * t;

   // �������� ���������� ����������� ����� �����������
   if (intersection == intersection_check) {
      return intersection;
   }

   return std::nullopt;
}

int main() {

   // ������ ������������� ������� � ������� Intersect
   Vector3D p1(0, 0, 0);
   Vector3D p2(-1, -1, -1);
   Segment3D seg1(p1, p2);

   Vector3D p3(-1, 0, 0);
   Vector3D p4(0, -1, -1);
   Segment3D seg2(p3, p4);

   auto intersection = Intersect(seg1, seg2);
   if (intersection) {
      std::cout << "Intersection: ";
      intersection->print();
   }
   else {
      std::cout << "No intersection\n";
   }

   return 0;
}
