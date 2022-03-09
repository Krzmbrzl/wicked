#ifndef _wicked_diag_operator_set_h_
#define _wicked_diag_operator_set_h_

#include <map>
#include <vector>

#include "helpers/algebra.hpp"
#include "operator_product.h"
#include "wicked-def.h"

using dop_expr_t = std::map<OperatorProduct, scalar_t>;

/// A class to represent operators
class OperatorExpression : public Algebra<OperatorProduct, scalar_t> {
public:
  /// Construct an empty sum
  OperatorExpression();

  /// Construct sum with a vector of diagrams
  OperatorExpression(const std::vector<OperatorProduct> &vec_vec_dop,
                     scalar_t factor = scalar_t(1));

  void add2(const OperatorExpression &expr, scalar_t factor = 1);

  void canonicalize();

  using Algebra<OperatorProduct, scalar_t>::operator*=;

  /// Return a string representation of the operator
  std::string str() const;
};

/// multiplication
OperatorExpression operator*(OperatorExpression lhs,
                             const OperatorExpression &rhs);

/// Write a string representation of the operator to a stream
std::ostream &operator<<(std::ostream &os, const OperatorExpression &opsum);

// Helper functions

/// Helper function to create a sum of diagrammatic operators
/// @param components a vector of strings of the form "oo->vv" which specify the
/// components of this operator
/// E.g.
/// auto T1 = make_diag_operator("T1", {"o->v"});
/// auto F = make_diag_operator("F", {"o->o","o->v","v->o","v->v"});
OperatorExpression
make_diag_operator_expression(const std::string &label,
                              const std::vector<std::string> &components);

/// Helper function to create a sum of diagrammatic operators
/// @param components a vector of strings of the form "oo->vv" which specify the
/// components of this operator
/// E.g.
/// auto T1 = make_operator("T1", {"v+ o"});
/// auto F = make_operator("F", {"o+ o","v+ o","o+ v","v+ v"});
OperatorExpression
make_diag_operator_expression2(const std::string &label,
                               const std::vector<std::string> &components);

/// Creates a new object with the commutator [A,B]
OperatorExpression commutator(const OperatorExpression &A,
                              const OperatorExpression &B);

// /// Creates a new object with the commutator [A,B]
// OperatorExpression
// nested_commutator(const std::vector<OperatorExpression> &expr_vec);

// /// Creates a new object with the exponential exp(A) truncated at a given
// order OperatorExpression exp(const OperatorExpression &A, int order);

/// Creates a new object with the Baker-Campbell-Hausdorff expansion of the
/// quantity exp(-B) A exp(B) truncated at a given order n
OperatorExpression bch_series(const OperatorExpression &A,
                              const OperatorExpression &B, int n);

#endif // _wicked_diag_operator_set_h_