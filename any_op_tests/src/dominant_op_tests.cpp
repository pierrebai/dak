#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(dominant_op_tests)
	{
	public:
      TEST_METHOD(dominant)
      {
         dominant_op_t::register_ops();

         Assert::AreEqual<std::any>(int32_t(1),    dominant_op_t::call<int32_t, bool>(true));
         Assert::AreEqual<std::any>(int32_t(97),   dominant_op_t::call<int32_t, char>('a'));
         Assert::AreEqual<std::any>(int32_t(98),   dominant_op_t::call<int32_t, wchar_t>(L'b'));
         Assert::AreEqual<std::any>(int32_t(2),    dominant_op_t::call<int32_t, int8_t>(2));
         Assert::AreEqual<std::any>(int32_t(3),    dominant_op_t::call<int32_t, int16_t>(3));
         Assert::AreEqual<std::any>(int32_t(4),    dominant_op_t::call<int32_t, int32_t>(4));
         Assert::AreEqual<std::any>(int64_t(5),    dominant_op_t::call<int32_t, int64_t>(5));
         Assert::AreEqual<std::any>(int32_t(6),    dominant_op_t::call<int32_t, uint8_t>(6));
         Assert::AreEqual<std::any>(int32_t(7),    dominant_op_t::call<int32_t, uint16_t>(7));
         Assert::AreEqual<std::any>(uint32_t(8),   dominant_op_t::call<int32_t, uint32_t>(8));
         Assert::AreEqual<std::any>(uint64_t(9),   dominant_op_t::call<int32_t, uint64_t>(9));
         Assert::AreEqual<std::any>(float(10),     dominant_op_t::call<int32_t, float>(10.f));
         Assert::AreEqual<std::any>(double(11),    dominant_op_t::call<int32_t, double>(11.));

         Assert::AreEqual<std::any>(int64_t(1),    dominant_op_t::call<int64_t, bool>(true));
         Assert::AreEqual<std::any>(int64_t(65),   dominant_op_t::call<int64_t, char>('A'));
         Assert::AreEqual<std::any>(int64_t(66),   dominant_op_t::call<int64_t, wchar_t>(L'B'));
         Assert::AreEqual<std::any>(int64_t(2),    dominant_op_t::call<int64_t, int8_t>(2));
         Assert::AreEqual<std::any>(int64_t(3),    dominant_op_t::call<int64_t, int16_t>(3));
         Assert::AreEqual<std::any>(int64_t(4),    dominant_op_t::call<int64_t, int32_t>(4));
         Assert::AreEqual<std::any>(int64_t(5),    dominant_op_t::call<int64_t, int64_t>(5));
         Assert::AreEqual<std::any>(int64_t(6),    dominant_op_t::call<int64_t, uint8_t>(6));
         Assert::AreEqual<std::any>(int64_t(7),    dominant_op_t::call<int64_t, uint16_t>(7));
         Assert::AreEqual<std::any>(int64_t(8),    dominant_op_t::call<int64_t, uint32_t>(8));
         Assert::AreEqual<std::any>(uint64_t(9),   dominant_op_t::call<int64_t, uint64_t>(9));
         Assert::AreEqual<std::any>(float(10),     dominant_op_t::call<int64_t, float>(10.f));
         Assert::AreEqual<std::any>(double(11),    dominant_op_t::call<int64_t, double>(11.));

         Assert::AreEqual<std::any>(1.,  dominant_op_t::call<double, bool>(true));
         Assert::AreEqual<std::any>(65., dominant_op_t::call<double, char>('A'));
         Assert::AreEqual<std::any>(66., dominant_op_t::call<double, wchar_t>(L'B'));
         Assert::AreEqual<std::any>(2.,  dominant_op_t::call<double, int8_t>(2));
         Assert::AreEqual<std::any>(3.,  dominant_op_t::call<double, int16_t>(3));
         Assert::AreEqual<std::any>(4.,  dominant_op_t::call<double, int32_t>(4));
         Assert::AreEqual<std::any>(5.,  dominant_op_t::call<double, int64_t>(5));
         Assert::AreEqual<std::any>(6.,  dominant_op_t::call<double, uint8_t>(6));
         Assert::AreEqual<std::any>(7.,  dominant_op_t::call<double, uint16_t>(7));
         Assert::AreEqual<std::any>(8.,  dominant_op_t::call<double, uint32_t>(8));
         Assert::AreEqual<std::any>(9.,  dominant_op_t::call<double, uint64_t>(9));
         Assert::AreEqual<std::any>(10., dominant_op_t::call<double, float>(10.f));
         Assert::AreEqual<std::any>(11., dominant_op_t::call<double, double>(11.));

         Assert::AreEqual<std::any>(true, dominant_op_t::call<bool, bool>(true));
         Assert::AreEqual<std::any>(char('A'), dominant_op_t::call<bool, char>('A'));
         Assert::AreEqual<std::any>(wchar_t(L'B'), dominant_op_t::call<bool, wchar_t>(L'B'));
         Assert::AreEqual<std::any>(int8_t(2), dominant_op_t::call<bool, int8_t>(2));
         Assert::AreEqual<std::any>(int16_t(3), dominant_op_t::call<bool, int16_t>(3));
         Assert::AreEqual<std::any>(int32_t(4), dominant_op_t::call<bool, int32_t>(4));
         Assert::AreEqual<std::any>(int64_t(5), dominant_op_t::call<bool, int64_t>(5));
         Assert::AreEqual<std::any>(uint8_t(6), dominant_op_t::call<bool, uint8_t>(6));
         Assert::AreEqual<std::any>(uint16_t(7), dominant_op_t::call<bool, uint16_t>(7));
         Assert::AreEqual<std::any>(uint32_t(8), dominant_op_t::call<bool, uint32_t>(8));
         Assert::AreEqual<std::any>(uint64_t(9), dominant_op_t::call<bool, uint64_t>(9));
         Assert::AreEqual<std::any>(float(10.f), dominant_op_t::call<bool, float>(10.f));
         Assert::AreEqual<std::any>(double(11.), dominant_op_t::call<bool, double>(11.));
         Assert::AreEqual<std::any>(text_t(L"hello"), dominant_op_t::call<bool, text_t>(L"hello"));
      }
   };
}
