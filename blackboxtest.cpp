#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

class Test {
private:
std::stringbuf sbuf;
std::streambuf* oldbuf;
int n;

void update_state() {
this->n += 1;
this->sbuf = std::stringbuf(std::ios::out);
this->oldbuf = std::cout.rdbuf(std::addressof(this->sbuf));
}
public:
Test() {
this->update_state();
};
void out_stream_to_be(std::string expect) {

std::cout.rdbuf(this->oldbuf);

std::string output = this->sbuf.str();

if (output == expect) {
std::cout << "Тест " << this->n << " пройден\n";
}
else {
std::cout << "Тест " << this->n << " не пройден.\n" << "Ожидаемый результат: " << expect << "\n" << "Полученный результат: " << output << "\n";
}
this->update_state();
}
};


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

int task(double a, double b, double c)
{

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

int main() {
Test test = Test();
setlocale(LC_ALL, "Russian");
task(3, 4, 5);
test.out_stream_to_be("Type=Right Perimeter=12 Square=6\n");
task(9,5,6);
test.out_stream_to_be("Type=Obtuse Perimeter=20 Square=14.1421\n");
task(8, 5, 9);
test.out_stream_to_be("Type=Acute Perimeter=22 Square=19.8997\n");
task(0, 1, 2);
test.out_stream_to_be("Не треугольник");
task(0, 0, 2);
test.out_stream_to_be("Не треугольник");
task(10, 1, 1);
test.out_stream_to_be("Не треугольник");
task(-1, 1, 2);
test.out_stream_to_be("Не треугольник");
}
