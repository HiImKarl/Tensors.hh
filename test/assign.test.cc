#include <tensor.hh>
#include "catch.hh"

using namespace tensor;

#define TEST_CASES(CONTAINER) \
  TEST_CASE(#CONTAINER ": Tensor Assignment", "[int]") { \
 \
    auto tensor_1 = Tensor<int32_t, 4, CONTAINER<int32_t>>({1, 2, 3, 4}); \
    for (size_t i = 0; i < tensor_1.dimension(0); ++i) \
      for (size_t j = 0; j < tensor_1.dimension(1); ++j) \
        for (size_t k = 0; k < tensor_1.dimension(2); ++k) \
          for (size_t l = 0; l < tensor_1.dimension(3); ++l) \
            tensor_1(i, j, k, l) = 1000 * i + 100 * j + 10 * k + l; \
 \
    SECTION("Assigning Tensors to Tensors") { \
 \
      Tensor<int32_t, 2, CONTAINER<int32_t>> t2({3, 4}); \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          t2(i, j) = tensor_1(0, 0, i, j); \
 \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          REQUIRE(t2(i, j) == (int)(10 * i + j)); \
 \
      tensor_1(0, 0) = t2; \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 0, i, j) == (int)(10 * i + j)); \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
      Tensor<double, 4, CONTAINER<double>> t3({1, 2, 3, 4}); \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              t3(i, j, k, l) = -1 * (int)(i + 10 * j + 100 * k + 1000 * l); \
 \
      tensor_1 = t3; \
 \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              REQUIRE(tensor_1(i, j, k, l) == -1 * (int)(i + 10 * j + 100 * k + 1000 * l)); \
    } \
 \
    SECTION("Assigning Integral Different-Typed Tensors to Tensors") { \
      Tensor<long double, 2, CONTAINER<long double>> t2({3, 4}); \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          t2(i, j) = tensor_1(0, 0, i, j); \
 \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          REQUIRE(t2(i, j) == tensor_1(0, 0, i, j)); \
 \
      tensor_1(0, 0) = t2; \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 0, i, j) == (int)(10 * i + j)); \
 \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
      Tensor<int64_t, 4, CONTAINER<int64_t>> t3({1, 2, 3, 4}); \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              t3(i, j, k, l) = -1 * (int)(i + 10 * j + 100 * k + 1000 * l); \
 \
      tensor_1 = t3; \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              REQUIRE(tensor_1(i, j, k, l) == -1 * (int)(i + 10 * j + 100 * k + 1000 * l)); \
    } \
 \
    SECTION("Assigning Tensors to Reference Tensors") { \
 \
      Tensor<int32_t, 4, CONTAINER<int32_t>> tensor_1_ref = tensor_1.ref(); \
      Tensor<int32_t, 2, CONTAINER<int32_t>> t2({3, 4}); \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          t2(i, j) = tensor_1(0, 0, i, j); \
 \
      tensor_1_ref(0, 0) = t2; \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 0, i, j) == (int)(10 * i + j)); \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
      Tensor<double, 4, CONTAINER<double>> t3({1, 2, 3, 4}); \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              t3(i, j, k, l) = -1 * (int)(i + 10 * j + 100 * k + 1000 * l); \
 \
      tensor_1_ref  = t3; \
 \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              REQUIRE(tensor_1(i, j, k, l) == -1 * (int)(i + 10 * j + 100 * k + 1000 * l)); \
    } \
 \
    SECTION("Assigning Scalar Values to Tensors") { \
      int32_t VALUE = -1200; \
      tensor_1(0, 0, 0, 0) = VALUE; \
      REQUIRE(tensor_1(0, 0, 0, 0) == -1200); \
      VALUE = -1500; \
      tensor_1(0, 1, 2, 3) = VALUE; \
      REQUIRE(tensor_1(0, 1, 2, 3) == VALUE); \
    } \
 \
    SECTION("Assigning Scalar Integral Different-Type Values to Tensors") { \
      long double VALUE = -1200; \
      tensor_1(0, 0, 0, 0) = VALUE; \
      REQUIRE(tensor_1(0, 0, 0, 0) == -1200); \
      VALUE = -1500; \
      tensor_1(0, 1, 2, 3) = VALUE; \
      REQUIRE(tensor_1(0, 1, 2, 3) == VALUE); \
    } \
 \
    SECTION("Assigning Scalar Tensors to Tensors") { \
      Scalar<int32_t, CONTAINER<int32_t>> scalar_1(0); \
      tensor_1.at(0, 0, 0, 0) = scalar_1(); \
      REQUIRE(tensor_1(0, 0, 0, 0) == 0); \
      REQUIRE(tensor_1(0, 0, 0, 0) == scalar_1()); \
 \
      Scalar<double, CONTAINER<double>> scalar_2(-12); \
      tensor_1.at(0, 0, 0, 0) = scalar_2(); \
      REQUIRE(tensor_1(0, 0, 0, 0) == -12); \
      REQUIRE(tensor_1(0, 0, 0, 0) == scalar_2()); \
    } \
 \
    SECTION("Assigning Tensors to Lvalues") { \
      int32_t VALUE = -tensor_1(0, 1, 1, 1); \
      REQUIRE(VALUE == -111); \
 \
      float fVALUE = -tensor_1(0, 1, 1, 1); \
      REQUIRE(fVALUE == -111); \
    } \
  } \
 \
  TEST_CASE(#CONTAINER ": Scalar Assignment", "[int]") { \
 \
    auto tensor_1 = Tensor<int32_t, 4, CONTAINER<int32_t>>({1, 2, 3, 4}); \
 \
    Scalar<int32_t, CONTAINER<int32_t>> scalar_1{}; \
 \
    for (size_t i = 0; i < tensor_1.dimension(0); ++i) \
      for (size_t j = 0; j < tensor_1.dimension(1); ++j) \
        for (size_t k = 0; k < tensor_1.dimension(2); ++k) \
          for (size_t l = 0; l < tensor_1.dimension(3); ++l) { \
            tensor_1(i, j, k, l) = 1000 * i + 100 * j + 10 * k + l; \
          } \
 \
    scalar_1 = 0; \
 \
    SECTION("Assigning Tensors to Tensors") { \
      Tensor<int32_t, 2, CONTAINER<int32_t>> t2({3, 4}); \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          t2(i, j) = tensor_1(0, 1, i, j); \
 \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          REQUIRE(t2(i, j) == (int)(100 + 10 * i + j)); \
 \
      tensor_1(0, 0) = t2; \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
      Tensor<int32_t, 4, CONTAINER<int32_t>> t3({1, 2, 3, 4}); \
 \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              t3(i, j, k, l) = -1 * (int)(i + 10 * j + 100 * k + 1000 * l); \
 \
      tensor_1 = t3; \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              REQUIRE(tensor_1(i, j, k, l) == -1 * (int)(i + 10 * j + 100 * k + 1000 * l)); \
    } \
 \
    SECTION("Assigning Integral Different-Typed Tensors to Tensors") { \
      Tensor<long double, 2, CONTAINER<long double>> t2({3, 4}); \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          t2(i, j) = tensor_1(0, 0, i, j); \
 \
      for (size_t i = 0; i < t2.dimension(0); ++i) \
        for (size_t j = 0; j < t2.dimension(1); ++j) \
          REQUIRE(t2(i, j) == tensor_1(0, 0, i, j)); \
 \
      tensor_1(0, 0) = t2; \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
 \
      for (size_t i = 0; i < tensor_1.dimension(2); ++i) \
        for (size_t j = 0; j < tensor_1.dimension(3); ++j) \
          REQUIRE(tensor_1(0, 1, i, j) == (int)(100 + 10 * i + j)); \
 \
      Tensor<int64_t, 4, CONTAINER<int64_t>> t3({1, 2, 3, 4}); \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              t3(i, j, k, l) = -1 * (int)(i + 10 * j + 100 * k + 1000 * l); \
 \
      tensor_1 = t3; \
      for (size_t i = 0; i < t3.dimension(0); ++i) \
        for (size_t j = 0; j < t3.dimension(1); ++j) \
          for (size_t k = 0; k < t3.dimension(2); ++k) \
            for (size_t l = 0; l < t3.dimension(3); ++l) \
              REQUIRE(tensor_1(i, j, k, l) == -1 * (int)(i + 10 * j + 100 * k + 1000 * l)); \
    } \
 \
    SECTION("Assigning Scalar Values to Tensors") { \
      int32_t VALUE = -1200; \
      tensor_1(0, 0, 0, 0) = VALUE; \
      REQUIRE(tensor_1(0, 0, 0, 0) == -1200); \
      VALUE = -1500; \
      tensor_1(0, 1, 2, 3) = VALUE; \
      REQUIRE(tensor_1(0, 1, 2, 3) == VALUE); \
    } \
 \
    SECTION("Assigning Scalar Integral Different-Type Values to Tensors") { \
      long double VALUE = -1200; \
      tensor_1(0, 0, 0, 0) = VALUE; \
      REQUIRE(tensor_1(0, 0, 0, 0) == -1200); \
      VALUE = -1500; \
      tensor_1(0, 1, 2, 3) = VALUE; \
      REQUIRE(tensor_1(0, 1, 2, 3) == VALUE); \
    } \
 \
    SECTION("Assigning Scalar Tensors to Tensors") { \
      tensor_1(0, 0, 0, 0) = scalar_1(); \
      REQUIRE(tensor_1(0, 0, 0, 0) == 0); \
      REQUIRE(tensor_1(0, 0, 0, 0) == scalar_1()); \
    } \
 \
    SECTION("Assigning Scalar Values to Scalar Tensors") { \
      int32_t VALUE = -1200; \
      scalar_1 = VALUE; \
      REQUIRE(scalar_1 == VALUE); \
    } \
 \
    SECTION("Assigning Tensors to Lvalues") { \
      int32_t VALUE = -tensor_1(0, 1, 1, 1); \
      REQUIRE(VALUE == -111); \
    } \
 \
    SECTION("Assigning Scalar Tensors to Lvalues") { \
      int32_t VALUE = scalar_1(); \
      REQUIRE(VALUE == 0); \
    } \
  } \

// Instantiate test cases
TEST_CASES(data::Array);
TEST_CASES(data::HashMap);

