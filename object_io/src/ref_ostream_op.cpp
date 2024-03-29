#include <dak/object_io/ref_ostream_op.h>

#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/object.h>
#include <dak/object/weak_ref.h>

#include <dak/any_op/stream_op.h>

#include <iomanip>

namespace dak::object
{
   namespace
   {
      //////////////////////////////////////////////////////////////////////////
      //
      // Output stream printing.

      bool print_weak_ref_ns(const ref_ostream_t& ref_ostr, const weak_ref_t<namespace_t>& ns)
      {
         if (!ns.is_valid())
            return false;

         auto& ostr = ref_ostr.get_stream();

         valid_ref_t<namespace_t> valid_ns(ns);

         print_weak_ref_ns(ref_ostr, valid_ns->get_parent());

         ostr << L" : " << std::quoted(valid_ns->to_text());

         return true;
      }

      bool print_name(const ref_ostream_t& ref_ostr, const name_t& n)
      {
         auto& ostr = ref_ostr.get_stream();

         const auto id = ref_ostr.get_name_id(exact_name_t(n));
         ostr << L"/ " << id;
         if (id <= 0)
            return true;

         print_weak_ref_ns(ref_ostr, n.get_namespace());

         ostr << L" / " << std::quoted(n.to_text());

         const auto& metadata = n.get_metadata();
         if (metadata.size() <= 0)
            return true;

         ref_ostream_indent_t indent(ref_ostr, L" {", L"}");

         for (const name_t& n : metadata)
         {
            ref_ostr.end_line();
            ref_ostr <<  n;
            ostr << L',';
         }

         return true;
      }

      bool print_object(const ref_ostream_t& ref_ostr, const object_t& o)
      {
         auto& ostr = ref_ostr.get_stream();

         ref_ostream_indent_t indent(ref_ostr, L"{", L"}");

         for (const auto& [n, e] : o)
         {
            ref_ostr.end_line();
            ref_ostr << n;
            ostr << L": ";
            ref_ostr << e;
            ostr << L',';
         }

         return true;
      }

      bool print_ref_object(const ref_ostream_t& ref_ostr, const ref_t<object_t>& o)
      {
         auto& ostr = ref_ostr.get_stream();

         const auto id = ref_ostr.get_object_id(o);
         ostr << id;
         if (id <= 0)
            return true;

         ostr << L' ';
         print_object(ref_ostr, *valid_ref_t<object_t>(o));

         return true;
      }

      bool print_weak_ref_object(const ref_ostream_t& ref_ostr, const weak_ref_t<object_t>& w)
      {
         return print_ref_object(ref_ostr, ref_t<object_t>(w));
      }

      bool print_array(const ref_ostream_t& ref_ostr, const array_t& a)
      {
         auto& ostr = ref_ostr.get_stream();

         ref_ostream_indent_t indent(ref_ostr, L"[", L"]");

         for (const value_t& e : a)
         {
            ref_ostr.end_line();
            ref_ostr << e;
            ostr << L',';
         }

         return true;
      }

      bool print_dict(const ref_ostream_t& ref_ostr, const dict_t& d)
      {
         auto& ostr = ref_ostr.get_stream();

         ref_ostream_indent_t indent(ref_ostr, L"{", L"}");

         for (const auto& [n, e] : d)
         {
            ref_ostr.end_line();
            ref_ostr << n;
            ostr << L": ";
            ref_ostr << e;
            ostr << L',';
         }

         return true;
      }

      bool print_value(const ref_ostream_t& ref_ostr, const value_t& e)
      {
         ref_ostr << e.as_any();
         return true;
      }

      bool print_type(const ref_ostream_t& ref_ostr, const any_t& arg_a)
      {
         const auto id = ref_ostr.get_type_id(arg_a.type());

         auto& ostr = ref_ostr.get_stream();
         ostr << L"@ " << id << L' ';

         if (id > 0)
         {
            const text_t tn = utility::get_type_name(arg_a);
            if (tn.empty())
            {
               // Note: if it has an unknown, unsupported type, then we either
               //       write the void type name and no data or abort the streaming.
               ref_ostr.abort_on_unknown();
               ostr << L"void ";
               return false;
            }

            ostr << tn << L' ';
         }
         return true;
      }

      struct ref_ostream_op_init_t
      {
         ref_ostream_op_init_t()
         {
            ref_ostream_op_t::make<>::op<bool, value_t              >(std::function<bool(const ref_ostream_t&, const value_t&)              >(print_value));
            ref_ostream_op_t::make<>::op<bool, dict_t               >(std::function<bool(const ref_ostream_t&, const dict_t&)               >(print_dict));
            ref_ostream_op_t::make<>::op<bool, array_t              >(std::function<bool(const ref_ostream_t&, const array_t&)              >(print_array));
            ref_ostream_op_t::make<>::op<bool, weak_ref_t<object_t> >(std::function<bool(const ref_ostream_t&, const weak_ref_t<object_t>&) >(print_weak_ref_object));
            ref_ostream_op_t::make<>::op<bool, ref_t<object_t>      >(std::function<bool(const ref_ostream_t&, const ref_t<object_t>&)      >(print_ref_object));
            ref_ostream_op_t::make<>::op<bool, edit_ref_t<object_t> >(std::function<bool(const ref_ostream_t&, const edit_ref_t<object_t>&) >(print_ref_object));
            ref_ostream_op_t::make<>::op<bool, valid_ref_t<object_t>>(std::function<bool(const ref_ostream_t&, const valid_ref_t<object_t>&)>(print_ref_object));
            ref_ostream_op_t::make<>::op<bool, name_t               >(std::function<bool(const ref_ostream_t&, const name_t&)               >(print_name));
         }
      };

      ref_ostream_op_init_t ref_ostream_op_init;
   }

   void ref_ostream_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   const ref_ostream_t& operator <<(const ref_ostream_t& ref_ostr, const any_t& arg_a)
   {
      if (!print_type(ref_ostr, arg_a))
         return ref_ostr;

      auto* ros_func = ref_ostream_op_t::find_any<>::op(arg_a);
      if (ros_func)
      {
         any_t res = (*ros_func)(ref_ostr, arg_a);
         if (res.has_value() && any_op::as<bool>(res))
            return ref_ostr;
      }

      auto* os_func = any_op::ostream_op_t::find_any<>::op(arg_a);
      if (os_func)
      {
         any_t res = (*os_func)(ref_ostr.get_stream(), arg_a);
         if (res.has_value() && any_op::as<bool>(res))
            return ref_ostr;
      }

      ref_ostr.get_stream().setstate(std::ios::failbit);
      return ref_ostr;
   }
}

