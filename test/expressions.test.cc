#include <tensor.hh>
#include <catch.hh>

using namespace tensor;

TEST_CASE("Basic Tensor Arithmetic, Non-scalar") {
  auto tensor_1 = Tensor<int32_t, 3>({2, 3, 4});
  auto tensor_2 = Tensor<int32_t, 3>({2, 3, 4});
  for (size_t i = 1; i <= tensor_1.dimension(1); ++i)
    for (size_t j = 1; j <= tensor_1.dimension(2); ++j)
      for (size_t k = 1; k <= tensor_1.dimension(3); ++k)
        tensor_1(i, j, k) = 100000 * i + 10000 * j + 1000 * k;

  for (size_t i = 1; i <= tensor_2.dimension(1); ++i)
    for (size_t j = 1; j <= tensor_2.dimension(2); ++j)
      for (size_t k = 1; k <= tensor_2.dimension(3); ++k)
        tensor_2(i, j, k) = 100 * i + 10 * j + 1 * k;


  SECTION("Two Term Addition/Subtract") {
    Tensor<int32_t, 3> tensor_3 = tensor_1 + tensor_2;
    Tensor<int32_t, 3> tensor_4 = tensor_3 - tensor_1;

    for (size_t i = 1; i <= tensor_3.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_3.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_3.dimension(3); ++k)
          REQUIRE(tensor_3(i, j, k) == (int)(100100 * i + 10010 * j + 1001 * k));

    for (size_t i = 1; i <= tensor_4.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_4.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_4.dimension(3); ++k)
          REQUIRE(tensor_4(i, j, k) == (int)(100 * i + 10 * j + 1 * k));
  }

  SECTION("Multi-Term Addition/Subtract") {
    Tensor<int32_t, 3> tensor_3 = tensor_2 + tensor_1 + tensor_2;

    for (size_t i = 1; i <= tensor_3.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_3.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_3.dimension(3); ++k)
          REQUIRE(tensor_3(i, j, k) == (int)(100200 * i + 10020 * j + 1002 * k));

    Tensor<int32_t, 3> tensor_4 = tensor_3 - tensor_2 + tensor_1;

    for (size_t i = 1; i <= tensor_4.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_4.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_4.dimension(3); ++k)
          REQUIRE(tensor_4(i, j, k) == (int)(200100 * i + 20010 * j + 2001 * k));
  }

  SECTION("Negation") {
    auto tensor_3 = -tensor_1;
    for (size_t i = 1; i <= tensor_3.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_3.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_3.dimension(3); ++k)
          REQUIRE(tensor_3(i, j, k) == (int)(-100000 * i + -10000 * j + -1000 * k));
  }
}

TEST_CASE("Scalar Arithmatic") {
  auto tensor_1 = Tensor<int32_t>(10);
  auto tensor_2 = Tensor<int32_t>(-10);

  SECTION("Binary Addition/Subtract") {
    REQUIRE(tensor_1() + tensor_2() == 0);
    REQUIRE((tensor_1 + tensor_2)() == 0);
    REQUIRE(tensor_1() - tensor_2() == 20);
    REQUIRE((tensor_1 - tensor_2)() == 20);
    REQUIRE(tensor_1 + 10 == 20);
    REQUIRE(10 + tensor_1 == 20);
    REQUIRE(tensor_1 - 10 == 0);

    Tensor<int32_t> tensor_3 = tensor_1 + tensor_2;
    REQUIRE(tensor_3 == 0);

    Tensor<int32_t> tensor_4 = tensor_1 - tensor_2;
    REQUIRE(tensor_4 == 20);
  }

  SECTION("Multi-Term Addition/Subtract") {
    REQUIRE(tensor_1 + 10 + tensor_2 + 5 == 15);
    REQUIRE(tensor_1 - 10 - tensor_2 - 5 == 5);
    REQUIRE(tensor_1 - 10 + tensor_2 - 5 == -15);
    REQUIRE(tensor_1 + 10 - tensor_2 + 5 == 35);
  }

  SECTION("Multiplication") {
    REQUIRE(tensor_1() * tensor_2() == -100);
    REQUIRE((tensor_1 * tensor_2)() == -100);
    REQUIRE(tensor_1 * 4 == 40);

    Tensor<int32_t> tensor_3 = tensor_1 * tensor_2;
    REQUIRE(tensor_3 == -100);
  }

  SECTION("Negation") {
    REQUIRE(-tensor_1 == -10);
    REQUIRE(-tensor_1 - 10 + -tensor_2 - 5 == -15);
  }
}

TEST_CASE("Elementwise Arithmatic") {
  auto tensor_1 = Tensor<int32_t, 3>({2, 3, 4}, 1);
  SECTION("Scalar Tensor") {

    Tensor<int32_t, 3> tensor_2 = elem_wise(tensor_1, 4, 
        [](int x, int y) -> int { return x + y; });
    for (size_t i = 1; i <= tensor_2.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_2.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_2.dimension(3); ++k)
          REQUIRE(tensor_2(i, j, k) == 5);

    tensor_2 = elem_wise(tensor_1, 6, 
        [](int x, int y) -> int { return y - x; });
    for (size_t i = 1; i <= tensor_2.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_2.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_2.dimension(3); ++k)
          REQUIRE(tensor_2(i, j, k) == 5);

    tensor_2 = elem_wise(tensor_1, 100,
        [](int x, int y) -> int { return x * (-y); });
    for (size_t i = 1; i <= tensor_2.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_2.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_2.dimension(3); ++k)
          REQUIRE(tensor_2(i, j, k) == -100);

    tensor_2 = elem_wise(tensor_1, tensor_1,
        [](int x, int y) -> int { return (x + 9)/(x + y); });
    for (size_t i = 1; i <= tensor_2.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_2.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_2.dimension(3); ++k)
          REQUIRE(tensor_2(i, j, k) == 5);
  }
}

TEST_CASE("Tensor Multplication") {
  auto tensor_1 = Tensor<int32_t, 3>({2, 3, 4});
  auto tensor_2 = Tensor<int32_t, 3>({4, 3, 2});
  for (size_t i = 1; i <= tensor_1.dimension(1); ++i)
    for (size_t j = 1; j <= tensor_1.dimension(2); ++j)
      for (size_t k = 1; k <= tensor_1.dimension(3); ++k)
        tensor_1(i, j, k) = 1;

  for (size_t i = 1; i <= tensor_2.dimension(1); ++i)
    for (size_t j = 1; j <= tensor_2.dimension(2); ++j)
      for (size_t k = 1; k <= tensor_2.dimension(3); ++k)
        tensor_2(i, j, k) = 1;

  SECTION("Binary Multiplication") {
    Tensor<int32_t, 4> tensor_3 = tensor_1 * tensor_2;
    REQUIRE(tensor_3.rank() == 4);
    REQUIRE(tensor_3.dimension(1) == 2);
    REQUIRE(tensor_3.dimension(2) == 3);
    REQUIRE(tensor_3.dimension(3) == 3);
    REQUIRE(tensor_3.dimension(4) == 2);
    for (size_t i = 1; i <= tensor_3.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_3.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_3.dimension(3); ++k)
          for (size_t l = 1; l <= tensor_3.dimension(4); ++l)
            REQUIRE(tensor_3(i, j, k, l) == 4);

    Tensor<int32_t, 2> tensor_4 = tensor_1.slice<1, 2>(1) * tensor_2(1);
    REQUIRE(tensor_4.rank() == 2);
    REQUIRE(tensor_4.dimension(1) == 2);
    REQUIRE(tensor_4.dimension(2) == 2);
    for (size_t i = 1; i <= tensor_4.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_4.dimension(2); ++j)
        REQUIRE(tensor_4(i, j) == 3);

    Tensor<int32_t, 4> tensor_5 = tensor_4 * tensor_3 * tensor_4;
    REQUIRE(tensor_5.rank() == 4);
    REQUIRE(tensor_5.dimension(1) == 2);
    REQUIRE(tensor_5.dimension(2) == 3);
    REQUIRE(tensor_5.dimension(3) == 3);
    REQUIRE(tensor_5.dimension(4) == 2);

    Tensor<int32_t, 2> tensor_6({2, 2});
    tensor_6(1, 1) = 2;
    tensor_6(1, 2) = 1;
    tensor_6(2, 1) = 3;
    tensor_6(2, 2) = 2;
 
    Tensor<int32_t, 2> tensor_7 = tensor_6 * tensor_6;
    REQUIRE(tensor_7(1, 1) == 7);
    REQUIRE(tensor_7(1, 2) == 4);
    REQUIRE(tensor_7(2, 1) == 12);
    REQUIRE(tensor_7(2, 2) == 7);
  }

  SECTION("Combined Multiplication and Addition/Subtraction") {
    Tensor<int32_t, 4> tensor_3 = tensor_1 * tensor_2 + tensor_1 * tensor_2;
    for (size_t i = 1; i <= tensor_3.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_3.dimension(2); ++j)
        for (size_t k = 1; k <= tensor_3.dimension(3); ++k)
          for (size_t l = 1; l <= tensor_3.dimension(4); ++l)
            REQUIRE(tensor_3(i, j, k, l) == 8);

    Tensor<int32_t, 2> tensor_4 = (tensor_1.slice<1, 2>(1) - tensor_1.slice<1, 2>(1)) * tensor_2(1);
    for (size_t i = 1; i <= tensor_4.dimension(1); ++i)
      for (size_t j = 1; j <= tensor_4.dimension(2); ++j)
        REQUIRE(tensor_4(i, j) == 0);
  }
}
TEST_CASE("Miscillaneous") {
  auto tensor = Tensor<int32_t, 4>({2, 4, 6, 8});
  for (size_t i = 1; i <= tensor.dimension(1); ++i)
    for (size_t j = 1; j <= tensor.dimension(2); ++j)
      for (size_t k = 1; k <= tensor.dimension(3); ++k)
        for (size_t l = 1; l <= tensor.dimension(4); ++l)
          tensor(i, j, k, l) = 1000 * i + 100 * j + 10 * k + l;

  SECTION("Tranpose") {
    Tensor<int32_t, 2> mat = tensor.slice<2, 4>(2, 2);
    auto mat_t = transpose(mat);
    REQUIRE(mat_t.rank() == 2);
    REQUIRE(mat_t.dimension(1) == 8);
    REQUIRE(mat_t.dimension(2) == 4);
    for (size_t i = 1; i <= mat.dimension(1); ++i)
      for (size_t j = 1; j <= mat.dimension(2); ++j)
          REQUIRE(mat(i, j) == mat_t(j, i));

    Tensor<int32_t, 1> vec = mat.slice<2>(3);
    Tensor<int32_t, 2> vec_t = transpose(vec);
    REQUIRE(vec_t.rank() == 2);
    REQUIRE(vec_t.dimension(1) == 1);
    REQUIRE(vec_t.dimension(2) == 8);
    for (size_t i = 1; i <= vec.dimension(1); ++i)
      REQUIRE(vec(i) == vec_t(1, i));
  }

  SECTION("Resize") {
    Tensor<int32_t, 2> mat = tensor.slice<2, 4>(2, 2);
    Tensor<int32_t, 1> vec = mat.resize(Shape<1>({32}));
    REQUIRE(vec.rank() == 1);
    REQUIRE(vec.dimension(1) == 32);
    int32_t correct_number = 2121;
    int32_t countdown = 8;
    for (size_t i = 1; i <= vec.dimension(1); ++i) {
      REQUIRE(correct_number == vec(i));
      ++correct_number;
      --countdown;
      if (!countdown) {
        correct_number += 92;
        countdown = 8;
      }
    }
  }
}
