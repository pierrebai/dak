#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

#include <sstream>
#include <iomanip>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(stream_op_tests)
	{
	public:
      TEST_METHOD(ostream_any)
      {
         ostream_op_t::register_ops();

         std::wostringstream ostream;

         any_t e_t1(text_t(L"text"));
         any_t e_t2(L"strptr");
         any_t e_c1('c');
         any_t e_c2(L'w');
         any_t e_b(true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

         ostream
            << e_t1 << L" -- "
            << e_t2 << L" -- "
            << e_c1 << L" -- "
            << e_c2 << L" -- "
            << e_b << L" -- "
            << e_i2 << L" -- "
            << e_i1 << L" -- "
            << e_i3 << L" -- "
            << e_u1 << L" -- "
            << e_u2 << L" -- "
            << e_u3 << L" -- "
            << e_r1 << L" -- "
            << e_r2 << L" -- ";

         Assert::AreEqual(
            L"text -- "
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
            ostream.str().c_str());
      }

      TEST_METHOD(istream_any)
      {
         ostream_op_t::register_ops();

         std::wostringstream ostream;

         // Note: we do *not* test for str_ptr_t nor char:
         //          - str_ptr_t cannot be written to.
         //          - Trying toread a single char from a wide input stream is doomed to failure.

         any_t e_t1(text_t(L"text"));
         any_t e_c2(L'w');
         any_t e_b(true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

         ostream
            << e_t1 << L" -- "
            << e_c2 << L" -- "
            << e_b << L" -- "
            << e_i2 << L" -- "
            << e_i1 << L" -- "
            << e_i3 << L" -- "
            << e_u1 << L" -- "
            << e_u2 << L" -- "
            << e_u3 << L" -- "
            << e_r1 << L" -- "
            << e_r2 << L" -- ";

         std::wistringstream istream(ostream.str());

         any_t i_t1(text_t(L""));
         any_t i_c2(L' ');
         any_t i_b(false);
         any_t i_i2((int16_t)0);
         any_t i_i1((int32_t)0);
         any_t i_i3((int64_t)0);
         any_t i_u1((uint16_t)0u);
         any_t i_u2((uint32_t)0u);
         any_t i_u3((uint64_t)0u);
         any_t i_r1(0.0f);
         any_t i_r2(0.0);

         text_t separator;

         istream
            >> i_t1 >> std::ws >> separator
            >> i_c2 >> std::ws >> separator
            >> i_b  >> std::ws >> separator
            >> i_i2 >> std::ws >> separator
            >> i_i1 >> std::ws >> separator
            >> i_i3 >> std::ws >> separator
            >> i_u1 >> std::ws >> separator
            >> i_u2 >> std::ws >> separator
            >> i_u3 >> std::ws >> separator
            >> i_r1 >> std::ws >> separator
            >> i_r2 >> std::ws >> separator;

         Assert::AreEqual(e_t1, i_t1);
         Assert::AreEqual(e_c2, i_c2);
         Assert::AreEqual(e_b,  i_b );
         Assert::AreEqual(e_i2, i_i2);
         Assert::AreEqual(e_i1, i_i1);
         Assert::AreEqual(e_i3, i_i3);
         Assert::AreEqual(e_u1, i_u1);
         Assert::AreEqual(e_u2, i_u2);
         Assert::AreEqual(e_u3, i_u3);
         Assert::AreEqual(e_r1, i_r1);
         Assert::AreEqual(e_r2, i_r2);
      }

      TEST_METHOD(ostream_data)
      {
         ostream_op_t::register_ops();

         std::wostringstream ostream;

         const text_t e_t1(L"text");
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

         stream(ostream, e_t1);
         stream(ostream, e_t2);
         stream(ostream, e_c1);
         stream(ostream, e_c2);
         stream(ostream, e_b);
         stream(ostream, e_i2);
         stream(ostream, e_i1);
         stream(ostream, e_i3);
         stream(ostream, e_u1);
         stream(ostream, e_u2);
         stream(ostream, e_u3);
         stream(ostream, e_r1);
         stream(ostream, e_r2);

         Assert::AreEqual(
            L"text"
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
            ostream.str().c_str());
      }

      TEST_METHOD(istream_data)
      {
         ostream_op_t::register_ops();

         std::wostringstream ostream;

         // Note: we do *not* test for str_ptr_t nor char:
         //          - str_ptr_t cannot be written to.
         //          - Trying toread a single char from a wide input stream is doomed to failure.

         const text_t e_t1(L"text");
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

         stream(ostream, e_t1); ostream << "\n";
         stream(ostream, e_c2); ostream << "\n";
         stream(ostream, e_b);  ostream << "\n";
         stream(ostream, e_i2); ostream << "\n";
         stream(ostream, e_i1); ostream << "\n";
         stream(ostream, e_i3); ostream << "\n";
         stream(ostream, e_u1); ostream << "\n";
         stream(ostream, e_u2); ostream << "\n";
         stream(ostream, e_u3); ostream << "\n";
         stream(ostream, e_r1); ostream << "\n";
         stream(ostream, e_r2); ostream << "\n";

         std::wistringstream istream(ostream.str());

         text_t i_t1(L" ");
         wchar_t i_c2(L' ');
         bool i_b(false);
         int16_t i_i2(0);
         int32_t i_i1(0);
         int64_t i_i3(0);
         uint16_t i_u1(0u);
         uint32_t i_u2(0u);
         uint64_t i_u3(0u);
         float i_r1(0.0f);
         double i_r2(0.0);

         stream(istream, i_t1);
         stream(istream, i_c2);
         stream(istream, i_b);
         stream(istream, i_i2);
         stream(istream, i_i1);
         stream(istream, i_i3);
         stream(istream, i_u1);
         stream(istream, i_u2);
         stream(istream, i_u3);
         stream(istream, i_r1);
         stream(istream, i_r2);

         Assert::AreEqual(e_t1, i_t1);
         Assert::AreEqual(e_c2, i_c2);
         Assert::AreEqual(e_b, i_b);
         Assert::AreEqual(e_i2, i_i2);
         Assert::AreEqual(e_i1, i_i1);
         Assert::AreEqual(e_i3, i_i3);
         Assert::AreEqual(e_u1, i_u1);
         Assert::AreEqual(e_u2, i_u2);
         Assert::AreEqual(e_u3, i_u3);
         Assert::AreEqual(e_r1, i_r1);
         Assert::AreEqual(e_r2, i_r2);
      }
   };
}
