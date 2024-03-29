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
      TEST_METHOD(dominant_test)
      {
         dominant_op_t::register_ops();

         Assert::AreEqual<any_t>(int32_t(1),    dominant<int32_t, bool>(true));
         Assert::AreEqual<any_t>(int32_t(97),   dominant<int32_t, char>('a'));
         Assert::AreEqual<any_t>(int32_t(98),   dominant<int32_t, wchar_t>(L'b'));
         Assert::AreEqual<any_t>(int32_t(2),    dominant<int32_t, int8_t>(2));
         Assert::AreEqual<any_t>(int32_t(3),    dominant<int32_t, int16_t>(3));
         Assert::AreEqual<any_t>(int32_t(4),    dominant<int32_t, int32_t>(4));
         Assert::AreEqual<any_t>(int64_t(5),    dominant<int32_t, int64_t>(5));
         Assert::AreEqual<any_t>(int32_t(6),    dominant<int32_t, uint8_t>(6));
         Assert::AreEqual<any_t>(int32_t(7),    dominant<int32_t, uint16_t>(7));
         Assert::AreEqual<any_t>(uint32_t(8),   dominant<int32_t, uint32_t>(8));
         Assert::AreEqual<any_t>(uint64_t(9),   dominant<int32_t, uint64_t>(9));
         Assert::AreEqual<any_t>(float(10),     dominant<int32_t, float>(10.f));
         Assert::AreEqual<any_t>(double(11),    dominant<int32_t, double>(11.));

         Assert::AreEqual<any_t>(int64_t(1),    dominant<int64_t, bool>(true));
         Assert::AreEqual<any_t>(int64_t(65),   dominant<int64_t, char>('A'));
         Assert::AreEqual<any_t>(int64_t(66),   dominant<int64_t, wchar_t>(L'B'));
         Assert::AreEqual<any_t>(int64_t(2),    dominant<int64_t, int8_t>(2));
         Assert::AreEqual<any_t>(int64_t(3),    dominant<int64_t, int16_t>(3));
         Assert::AreEqual<any_t>(int64_t(4),    dominant<int64_t, int32_t>(4));
         Assert::AreEqual<any_t>(int64_t(5),    dominant<int64_t, int64_t>(5));
         Assert::AreEqual<any_t>(int64_t(6),    dominant<int64_t, uint8_t>(6));
         Assert::AreEqual<any_t>(int64_t(7),    dominant<int64_t, uint16_t>(7));
         Assert::AreEqual<any_t>(int64_t(8),    dominant<int64_t, uint32_t>(8));
         Assert::AreEqual<any_t>(uint64_t(9),   dominant<int64_t, uint64_t>(9));
         Assert::AreEqual<any_t>(float(10),     dominant<int64_t, float>(10.f));
         Assert::AreEqual<any_t>(double(11),    dominant<int64_t, double>(11.));

         Assert::AreEqual<any_t>(1.,  dominant<double, bool>(true));
         Assert::AreEqual<any_t>(65., dominant<double, char>('A'));
         Assert::AreEqual<any_t>(66., dominant<double, wchar_t>(L'B'));
         Assert::AreEqual<any_t>(2.,  dominant<double, int8_t>(2));
         Assert::AreEqual<any_t>(3.,  dominant<double, int16_t>(3));
         Assert::AreEqual<any_t>(4.,  dominant<double, int32_t>(4));
         Assert::AreEqual<any_t>(5.,  dominant<double, int64_t>(5));
         Assert::AreEqual<any_t>(6.,  dominant<double, uint8_t>(6));
         Assert::AreEqual<any_t>(7.,  dominant<double, uint16_t>(7));
         Assert::AreEqual<any_t>(8.,  dominant<double, uint32_t>(8));
         Assert::AreEqual<any_t>(9.,  dominant<double, uint64_t>(9));
         Assert::AreEqual<any_t>(10., dominant<double, float>(10.f));
         Assert::AreEqual<any_t>(11., dominant<double, double>(11.));

         Assert::AreEqual<any_t>(true, dominant<bool, bool>(true));
         Assert::AreEqual<any_t>(char('A'), dominant<bool, char>('A'));
         Assert::AreEqual<any_t>(wchar_t(L'B'), dominant<bool, wchar_t>(L'B'));
         Assert::AreEqual<any_t>(int8_t(2), dominant<bool, int8_t>(2));
         Assert::AreEqual<any_t>(int16_t(3), dominant<bool, int16_t>(3));
         Assert::AreEqual<any_t>(int32_t(4), dominant<bool, int32_t>(4));
         Assert::AreEqual<any_t>(int64_t(5), dominant<bool, int64_t>(5));
         Assert::AreEqual<any_t>(uint8_t(6), dominant<bool, uint8_t>(6));
         Assert::AreEqual<any_t>(uint16_t(7), dominant<bool, uint16_t>(7));
         Assert::AreEqual<any_t>(uint32_t(8), dominant<bool, uint32_t>(8));
         Assert::AreEqual<any_t>(uint64_t(9), dominant<bool, uint64_t>(9));
         Assert::AreEqual<any_t>(float(10.f), dominant<bool, float>(10.f));
         Assert::AreEqual<any_t>(double(11.), dominant<bool, double>(11.));
         Assert::AreEqual<any_t>(text_t(L"hello"), dominant<bool, text_t>(L"hello"));
      }

      TEST_METHOD(dominant_implicit_from_test)
      {
         dominant_op_t::register_ops();

         Assert::AreEqual<any_t>(int32_t(1),  dominant<int32_t>(true));
         Assert::AreEqual<any_t>(int32_t(97), dominant<int32_t>('a'));
         Assert::AreEqual<any_t>(int32_t(98), dominant<int32_t>(L'b'));
         Assert::AreEqual<any_t>(int32_t(2),  dominant<int32_t>(int8_t(2)));
         Assert::AreEqual<any_t>(int32_t(3),  dominant<int32_t>(int16_t(3)));
         Assert::AreEqual<any_t>(int32_t(4),  dominant<int32_t>(int32_t(4)));
         Assert::AreEqual<any_t>(int64_t(5),  dominant<int32_t>(int64_t(5)));
         Assert::AreEqual<any_t>(int32_t(6),  dominant<int32_t>(uint8_t(6)));
         Assert::AreEqual<any_t>(int32_t(7),  dominant<int32_t>(uint16_t(7)));
         Assert::AreEqual<any_t>(uint32_t(8), dominant<int32_t>(uint32_t(8)));
         Assert::AreEqual<any_t>(uint64_t(9), dominant<int32_t>(uint64_t(9)));
         Assert::AreEqual<any_t>(float(10),   dominant<int32_t>(10.f));
         Assert::AreEqual<any_t>(double(11),  dominant<int32_t>(11.));

         Assert::AreEqual<any_t>(int64_t(1),  dominant<int64_t>(true));
         Assert::AreEqual<any_t>(int64_t(97), dominant<int64_t>('a'));
         Assert::AreEqual<any_t>(int64_t(98), dominant<int64_t>(L'b'));
         Assert::AreEqual<any_t>(int64_t(2),  dominant<int64_t>(int8_t(2)));
         Assert::AreEqual<any_t>(int64_t(3),  dominant<int64_t>(int16_t(3)));
         Assert::AreEqual<any_t>(int64_t(4),  dominant<int64_t>(int32_t(4)));
         Assert::AreEqual<any_t>(int64_t(5),  dominant<int64_t>(int64_t(5)));
         Assert::AreEqual<any_t>(int64_t(6),  dominant<int64_t>(uint8_t(6)));
         Assert::AreEqual<any_t>(int64_t(7),  dominant<int64_t>(uint16_t(7)));
         Assert::AreEqual<any_t>(int64_t(8),  dominant<int64_t>(uint32_t(8)));
         Assert::AreEqual<any_t>(uint64_t(9), dominant<int64_t>(uint64_t(9)));
         Assert::AreEqual<any_t>(float(10),   dominant<int64_t>(10.f));
         Assert::AreEqual<any_t>(double(11),  dominant<int64_t>(11.));

         Assert::AreEqual<any_t>(1.,   dominant<double>(true));
         Assert::AreEqual<any_t>(97.,  dominant<double>('a'));
         Assert::AreEqual<any_t>(98.,  dominant<double>(L'b'));
         Assert::AreEqual<any_t>(2.,   dominant<double>(int8_t(2)));
         Assert::AreEqual<any_t>(3.,   dominant<double>(int16_t(3)));
         Assert::AreEqual<any_t>(4.,   dominant<double>(int32_t(4)));
         Assert::AreEqual<any_t>(5.,   dominant<double>(int64_t(5)));
         Assert::AreEqual<any_t>(6.,   dominant<double>(uint8_t(6)));
         Assert::AreEqual<any_t>(7.,   dominant<double>(uint16_t(7)));
         Assert::AreEqual<any_t>(8.,   dominant<double>(uint32_t(8)));
         Assert::AreEqual<any_t>(9.,   dominant<double>(uint64_t(9)));
         Assert::AreEqual<any_t>(10.,  dominant<double>(10.f));
         Assert::AreEqual<any_t>(11.,  dominant<double>(11.));

         Assert::AreEqual<any_t>(true,          dominant<bool>(true));
         Assert::AreEqual<any_t>(char('A'),     dominant<bool>('A'));
         Assert::AreEqual<any_t>(wchar_t(L'B'), dominant<bool>(L'B'));
         Assert::AreEqual<any_t>(int8_t(2),     dominant<bool>(int8_t(2)));
         Assert::AreEqual<any_t>(int16_t(3),    dominant<bool>(int16_t(3)));
         Assert::AreEqual<any_t>(int32_t(4),    dominant<bool>(int32_t(4)));
         Assert::AreEqual<any_t>(int64_t(5),    dominant<bool>(int64_t(5)));
         Assert::AreEqual<any_t>(uint8_t(6),    dominant<bool>(uint8_t(6)));
         Assert::AreEqual<any_t>(uint16_t(7),   dominant<bool>(uint16_t(7)));
         Assert::AreEqual<any_t>(uint32_t(8),   dominant<bool>(uint32_t(8)));
         Assert::AreEqual<any_t>(uint64_t(9),   dominant<bool>(uint64_t(9)));
         Assert::AreEqual<any_t>(float(10.f),   dominant<bool>(10.f));
         Assert::AreEqual<any_t>(double(11.),   dominant<bool>(11.));
         Assert::AreEqual<any_t>(text_t(L"hi"), dominant<bool>(L"hi"));
      }
   };
}
