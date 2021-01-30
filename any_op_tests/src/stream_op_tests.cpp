#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(stream_op_tests)
	{
	public:
		TEST_METHOD(stream_any)
		{
         stream_op_t::register_ops();

         std::wostringstream text_stream;

         std::any e_t1(text_t(L"text_t"));
         std::any e_t2(L"strptr");
         std::any e_c1('c');
         std::any e_c2(L'w');
         std::any e_b(true);
         std::any e_i2((int16_t)2);
         std::any e_i1((int32_t)1);
         std::any e_i3((int64_t)3);
         std::any e_u1((uint16_t)4u);
         std::any e_u2((uint32_t)5u);
         std::any e_u3((uint64_t)6u);
         std::any e_r1(7.0f);
         std::any e_r2(8.0);

         text_stream
            << e_t1 << L" -- "
            << e_t2 << L" -- "
            << e_c1 << L" -- "
            << e_c2 << L" -- "
            << e_b  << L" -- "
            << e_i2 << L" -- "
            << e_i1 << L" -- "
            << e_i3 << L" -- "
            << e_u1 << L" -- "
            << e_u2 << L" -- "
            << e_u3 << L" -- "
            << e_r1 << L" -- "
            << e_r2 << L" -- ";

         Assert::AreEqual(
            L"text_t -- "
            L"strptr -- "
            L"c -- "
            L"w -- "
            L"1 -- "
            L"2 -- "
            L"1 -- "
            L"3 -- "
            L"4 -- "
            L"5 -- "
            L"6 -- "
            L"7 -- "
            L"8 -- ",
            text_stream.str().c_str());
      }

      TEST_METHOD(stream_data)
      {
         stream_op_t::register_ops();

         std::wostringstream text_stream;

         const text_t e_t1(L"text_t");
         const str_ptr_t e_t2(L"strptr");
         const char e_c1('c');
         const wchar_t e_c2(L'w');
         const bool e_b(true);
         const int16_t e_i2(2);
         const int32_t e_i1(1);
         const int64_t e_i3(3);
         const uint16_t e_u1(4u);
         const uint32_t e_u2(5u);
         const uint64_t e_u3(6u);
         const float e_r1(7.0f);
         const double e_r2(8.0);

         stream(text_stream, e_t1);
         stream(text_stream, e_t2);
         stream(text_stream, e_c1);
         stream(text_stream, e_c2);
         stream(text_stream, e_b);
         stream(text_stream, e_i2);
         stream(text_stream, e_i1);
         stream(text_stream, e_i3);
         stream(text_stream, e_u1);
         stream(text_stream, e_u2);
         stream(text_stream, e_u3);
         stream(text_stream, e_r1);
         stream(text_stream, e_r2);

         Assert::AreEqual(
            L"text_t"
            L"strptr"
            L"c"
            L"w"
            L"1"
            L"2"
            L"1"
            L"3"
            L"4"
            L"5"
            L"6"
            L"7"
            L"8",
            text_stream.str().c_str());
      }
   };
}
