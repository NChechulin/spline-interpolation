#include "interpolation.h"
#include <QTextStream>
#include <cmath>
#include <fstream>
#include <vector>
#include "polynomial.h"

const double EPS = 1e-6;

Interpolation Interpolation::FromFile(QString path) {
  Interpolation result;

  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    throw std::runtime_error(file.errorString().toStdString());
  }

  QTextStream in(&file);

  while (!in.atEnd()) {
    QString line = in.readLine();

    QStringList fields = line.split(' ');
    if (fields.length() == 2) {
      QPointF point(fields[0].toDouble(), fields[1].toDouble());
      result.points.push_back(point);
    }
  }
  file.close();

  std::sort(result.points.begin(), result.points.end(),
            [](QPointF a, QPointF b) { return (a.x() < b.x()); });

  result.check_points();
  return result;
}

void Interpolation::check_points() const {
  if (this->points.size() <= 2) {
    throw std::length_error("Less than 3 points were provided");
  }

  for (size_t i = 0; i < this->points.size() - 1; ++i) {
    if (std::abs(points[i].x() - points[i + 1].x()) < EPS) {
      throw std::range_error(
          "There are at least 2 points with the same X coordinate");
    }
  }
}

void RREF(std::vector<std::vector<double>>& mat) {
  size_t lead = 0;
  for (size_t r = 0; r < mat.size(); r++) {
    if (mat[0].size() <= lead) {
      return;
    }
    size_t i = r;
    while (mat[i][lead] == 0) {
      i++;
      if (mat.size() == i) {
        i = r;
        lead++;
        if (mat[0].size() == lead) {
          return;
        }
      }
    }

    std::swap(mat[i], mat[r]);

    double val = mat[r][lead];
    for (size_t j = 0; j < mat[0].size(); j++) {
      mat[r][j] /= val;
    }

    for (size_t i = 0; i < mat.size(); i++) {
      if (i == r) continue;
      val = mat[i][lead];
      for (size_t j = 0; j < mat[0].size(); j++) {
        mat[i][j] = mat[i][j] - val * mat[r][j];
      }
    }
    lead++;
  }
}

std::vector<Polynomial> Interpolation::Interpolate() {
  size_t size = this->points.size();
  size_t solution_index = (size - 1) * 4;
  size_t row = 0;
  std::vector<std::vector<double>> matrix(
      solution_index, std::vector<double>(solution_index + 1, 0));

  // splines through equations
  for (size_t functionNr = 0; functionNr < size - 1; functionNr++, row++) {
    QPointF p0 = this->points[functionNr], p1 = this->points[functionNr + 1];
    matrix[row][functionNr * 4 + 0] = std::pow(p0.x(), 3);
    matrix[row][functionNr * 4 + 1] = std::pow(p0.x(), 2);
    matrix[row][functionNr * 4 + 2] = p0.x();
    matrix[row][functionNr * 4 + 3] = 1;
    matrix[row][solution_index] = p0.y();

    matrix[++row][functionNr * 4 + 0] = std::pow(p1.x(), 3);
    matrix[row][functionNr * 4 + 1] = std::pow(p1.x(), 2);
    matrix[row][functionNr * 4 + 2] = p1.x();
    matrix[row][functionNr * 4 + 3] = 1;
    matrix[row][solution_index] = p1.y();
  }

  // first derivative
  for (size_t functionNr = 0; functionNr < size - 2; functionNr++, row++) {
    QPointF p1 = this->points[functionNr + 1];
    matrix[row][functionNr * 4 + 0] = std::pow(p1.x(), 2) * 3;
    matrix[row][functionNr * 4 + 1] = p1.x() * 2;
    matrix[row][functionNr * 4 + 2] = 1;
    matrix[row][functionNr * 4 + 4] = std::pow(p1.x(), 2) * -3;
    matrix[row][functionNr * 4 + 5] = p1.x() * -2;
    matrix[row][functionNr * 4 + 6] = -1;
  }

  // second derivative
  for (size_t functionNr = 0; functionNr < size - 2; functionNr++, row++) {
    QPointF p1 = this->points[functionNr + 1];
    matrix[row][functionNr * 4 + 0] = p1.x() * 6;
    matrix[row][functionNr * 4 + 1] = 2;
    matrix[row][functionNr * 4 + 4] = p1.x() * -6;
    matrix[row][functionNr * 4 + 5] = -2;
  }

  matrix[row][0 + 0] = this->points[0].x() * 6;
  matrix[row++][0 + 1] = 2;
  matrix[row][solution_index - 4 + 0] = this->points[size - 1].x() * 6;
  matrix[row][solution_index - 4 + 1] = 2;

  RREF(matrix);

  std::vector<double> coefficients;
  coefficients.reserve(matrix.size());
  for (auto& i : matrix) {
    coefficients.push_back(i[i.size() - 1]);
  }

  std::vector<Polynomial> functions;
  for (size_t i = 0; i < coefficients.size(); i += 4) {
    Polynomial p = Polynomial::GetCoefficientsFromVector(coefficients.begin() + i);
    p.from = this->points[i / 4].x();
    p.to = this->points[i / 4 + 1].x();
    functions.push_back(p);
  }
  return functions;
}
