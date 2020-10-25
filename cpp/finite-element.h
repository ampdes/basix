// Copyright (c) 2020 Chris Richardson
// FEniCS Project
// SPDX-License-Identifier:    MIT

#include "cell.h"
#include <Eigen/Dense>
#include <vector>

#pragma once

namespace libtab
{

class FiniteElement
{
  /// Finite element base class, taking the cell type and degree,
  /// The basis is stored as a set of coefficients, which are applied to the
  /// underlying expansion set for that cell type, when tabulating.

public:
  /// Element of given dimension (1, 2 or 3) and degree.
  FiniteElement(cell::Type cell_type, int degree);

  /// Destructor
  ~FiniteElement() = default;

  /// Compute basis values and derivatives at set of points. If no derivatives
  /// are required, use nderiv=0. Higher derivatives are stored in
  /// triangular (2D) or tetrahedral (3D) ordering, i.e. for the (x,y)
  /// derivatives in 2D: (0,0),(1,0),(0,1),(2,0),(1,1),(0,2),(3,0)... If
  /// a vector result is expected, it will be stacked with all x values,
  /// followed by all y-values (and then z, if any).
  std::vector<
      Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>
  tabulate(int nderiv,
           const Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic,
                              Eigen::RowMajor>& pts) const;

  /// Get the cell type of the space's cell
  /// @return The cell type
  cell::Type cell_type() const { return _cell_type; }

protected:
  // Applies nodal constraints from dualmat to original
  // coeffs on basis, and stores to _coeffs.
  void apply_dualmat_to_basis(
      const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic,
                          Eigen::RowMajor>& coeffs,
      const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic,
                          Eigen::RowMajor>& dualmat);

  // cell type
  cell::Type _cell_type;

  // degree
  int _degree;

  // value size
  int _value_size;

  // Coefficient of expansion sets on cell
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
      _coeffs;
};
} // namespace libtab
