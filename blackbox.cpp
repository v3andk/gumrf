#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

enum class Triangle_type { right, obtuse, acute };

const char* triangle_string_type[] = { "Right", "Obtuse", "Acute" };

bool is_triangle(double a, double b, double c) {
if (a <= 0 || b <= 0 || c <= 0) {
return false;
}
return a < b + c && b < a + c && c < b + a;
}

std::vector<double> get_triangle_sides(double a, double b, double c) {
std::vector<double> sides{ a, b, c };
std::sort(sides.begin(), sides.end());
return sides;
}

Triangle_type get_triangle_type(double a, double b, double c) {
double aSquared = pow(a, 2.);
double bSquared = pow(b, 2.);
double cSquared = pow(c, 2.);

std::vector<double> triangle_sides = get_triangle_sides(aSquared, bSquared, cSquared);

if (triangle_sides[2] > triangle_sides[1] + triangle_sides[0]) {
return Triangle_type::obtuse;
}
if (triangle_sides[2] == triangle_sides[1] + triangle_sides[0]) {
return Triangle_type::right;
}
return Triangle_type::acute;
}

int main()
{
setlocale(LC_ALL, "Russian");
double a, b, c;

std::cin >> a >> b >> c;

std::cout << std::endl;

if (!is_triangle(a, b, c)) {
std::cout << "Не треугольник";
return 1;
}

std::vector<double> triangle_sides = get_triangle_sides(a, b, c);

Triangle_type triangle_type = get_triangle_type(triangle_sides[0], triangle_sides[1], triangle_sides[2]);


double perimeter = a + b + c;
double half_perimeter = perimeter / 2.;
double square = sqrt(half_perimeter * (half_perimeter - a) * (half_perimeter - b) * (half_perimeter - c));

std::cout << "Type=" << triangle_string_type[static_cast<int>(triangle_type)] << " Perimeter=" << perimeter << " Square=" << square << std::endl;
return 0;
}
