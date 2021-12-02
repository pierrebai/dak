#include "CppUnitTest.h"

#include "dak/object/namespace.h"
#include "dak/object/name.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::object;
using namespace dak::object::voc;
using namespace std;

namespace dak::object::tests
{		
   TEST_CLASS(namespace_tests)
	{
	public:
		TEST_METHOD(namespace_base)
		{
         edit_ref_t<namespace_t> root = namespace_t::make();
         edit_ref_t<namespace_t> sub_ns_a = namespace_t::make(L"a", root);
         edit_ref_t<namespace_t> sub_ns_b = namespace_t::make(text_t(L"b"), root);

         Assert::AreEqual(root->to_text(), text_t(L""));
         Assert::AreEqual(sub_ns_a->to_text(), text_t(L"a"));
         Assert::AreEqual(sub_ns_b->to_text(), text_t(L"b"));

         Assert::IsTrue(sub_ns_a->get_parent() == ref_t<namespace_t>(root));
         Assert::IsTrue(sub_ns_b->get_parent() == ref_t<namespace_t>(root));

         Assert::IsTrue(ref_t<namespace_t>(sub_ns_a) == root->get_namespace(L"a"));
         Assert::IsTrue(ref_t<namespace_t>(sub_ns_b) == root->get_namespace(L"b"));
         Assert::IsTrue(ref_t<namespace_t>() == root->get_namespace(L"d"));
         Assert::IsTrue(ref_t<namespace_t>() == root->get_namespace(nullptr));

         Assert::IsTrue(root->get_namespaces().count(sub_ns_a->to_text()) == 1);
         Assert::IsTrue(root->get_namespaces().count(L"b") == 1);

         root->clear();

         Assert::IsTrue(root->get_namespaces().count(sub_ns_a->to_text()) == 0);
         Assert::IsTrue(root->get_namespaces().count(L"b") == 0);

         name_t a_x(sub_ns_a, L"x");
         name_t a_y(sub_ns_a, text_t(L"y"));

         Assert::IsTrue(ref_t<namespace_t>(sub_ns_a) == ref_t<namespace_t>(a_x.get_namespace()));
         Assert::IsTrue(ref_t<namespace_t>(sub_ns_a) == ref_t<namespace_t>(a_y.get_namespace()));

         Assert::AreEqual(a_x, sub_ns_a->get_name(L"x"));
         Assert::AreEqual(a_y, sub_ns_a->get_name(text_t(L"y")));
         Assert::AreEqual(name_t(), sub_ns_a->get_name(text_t(L"z")));
         Assert::AreEqual(name_t(), sub_ns_a->get_name(nullptr));

         Assert::AreEqual(a_x, name_t(sub_ns_a->get_names().at(L"x")));
         Assert::AreEqual(a_y, name_t(sub_ns_a->get_names().at(text_t(L"y"))));

         edit_ref_t<namespace_t> sub_ns_c = namespace_t::make(text_t(L"c"), sub_ns_a);

         Assert::AreEqual(name_t(), sub_ns_b->search_name(nullptr));
         Assert::AreEqual(name_t(), sub_ns_b->search_name(L"x"));
         Assert::AreEqual(name_t(), sub_ns_b->search_name(text_t(L"y")));
         Assert::AreEqual(a_x, sub_ns_c->search_name(L"x"));
         Assert::AreEqual(a_y, sub_ns_c->search_name(text_t(L"y")));

         sub_ns_b->swap(*sub_ns_c);

         Assert::AreEqual(a_x, sub_ns_b->search_name(L"x"));
         Assert::AreEqual(a_y, sub_ns_b->search_name(text_t(L"y")));
         Assert::AreEqual(name_t(), sub_ns_c->search_name(L"x"));
         Assert::AreEqual(name_t(), sub_ns_c->search_name(text_t(L"y")));

         edit_ref_t<namespace_t> sub_ns_d = namespace_t::make(sub_ns_b);
         edit_ref_t<namespace_t> sub_ns_e = namespace_t::make(*sub_ns_b);

         Assert::IsTrue(*sub_ns_d == *sub_ns_b);
         Assert::IsTrue(*sub_ns_e == *sub_ns_d);

         name_t a_x2(sub_ns_c, a_x);
         Assert::AreEqual(a_x2, sub_ns_c->search_name(L"x"));

      }

   };
}
