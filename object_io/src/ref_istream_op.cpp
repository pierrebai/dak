#include <dak/object_io/ref_istream_op.h>

#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/object.h>
#include <dak/object/weak_ref.h>

#include <dak/any_op/stream_op.h>

#include <iomanip>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream parsing.

   namespace
   {
      value_t parse_value(const ref_istream_t& ref_istr);
      void parse_object(const ref_istream_t& ref_istr, object_t& o);
      dict_t parse_dict(const ref_istream_t& ref_istr);
      array_t parse_array(const ref_istream_t& ref_istr);
      weak_ref_t<object_t> parse_weak_ref_object(const ref_istream_t& ref_istr);
      ref_t<object_t> parse_ref_object(const ref_istream_t& ref_istr);
      name_t parse_name(const ref_istream_t& ref_istr);

      name_t parse_name(const ref_istream_t& ref_istr)
      {
         auto& istr = ref_istr.get_stream();

         if (!ref_istr.parse_sigil(L'/'))
            return {};

         int64_t id = 0;
         istr >> std::ws >> id;
         if (id <= 0)
            return ref_istr.get_name_with_id(-id);

         bool in_top = true;
         valid_ref_t<namespace_t> current_ns = ref_istr.get_namespace();
         while (ref_istr.parse_optional_sigil(L':'))
         {
            text_t text;
            istr >> std::quoted(text);
            if (!in_top || current_ns->to_text() != text)
            {
               ref_t<namespace_t> sub_ns = current_ns->get_namespace(text);
               if (sub_ns.is_null())
               {
                  current_ns = namespace_t::make(current_ns->modify(ref_istr.get_transaction()), text);
               }
               else
               {
                  current_ns = sub_ns;
               }
            }
            in_top = false;
         }

         if (!ref_istr.parse_sigil(L'/'))
            return {};

         text_t text;
         istr >> std::ws >> std::quoted(text);
         name_t n = current_ns->get_name(text);
         if (!n.is_valid())
         {
            edit_ref_t edit_ns = current_ns->modify(ref_istr.get_transaction());
            n = name_t(edit_ns, text);
         }

         // Parse metadata.
         if (ref_istr.parse_optional_sigil(L'{'))
         {
            while (istr.good())
            {
               name_t metaname;
               ref_istr >> metaname;

               if (metaname.is_valid())
                  n.add_metadata(metaname, ref_istr.get_transaction());

               if (!ref_istr.parse_sigil(L','))
                  break;
            }
         }

         ref_istr.add_name_with_id(exact_name_t(n), id);

         return n;
      }

      edit_ref_t<object_t> parse_edit_ref_object(const ref_istream_t& ref_istr)
      {
         auto& istr = ref_istr.get_stream();

         int64_t id = 0;
         istr >> std::ws >> id;
         if (id > 0)
         {
            edit_ref_t new_obj = object_t::make();
            ref_istr.add_object_with_id(new_obj, id);
            parse_object(ref_istr, *new_obj);
            return new_obj;
         }
         else
         {
            return ref_istr.get_object_with_id(-id);
         }
      }

      ref_t<object_t> parse_ref_object(const ref_istream_t& ref_istr)
      {
         return ref_t<object_t>(parse_edit_ref_object(ref_istr));
      }

      valid_ref_t<object_t> parse_valid_ref_object(const ref_istream_t& ref_istr)
      {
         return valid_ref_t<object_t>(parse_edit_ref_object(ref_istr));
      }

      weak_ref_t<object_t> parse_weak_ref_object(const ref_istream_t& ref_istr)
      {
         ref_t<object_t> r = parse_ref_object(ref_istr);
         return weak_ref_t<object_t>(r);
      }

      array_t parse_array(const ref_istream_t& ref_istr)
      {
         auto& istr = ref_istr.get_stream();

         if (!ref_istr.parse_sigil(L'['))
            return {};

         array_t a;

         while (istr.good()) {
            if (ref_istr.is_end(L']'))
               break;

            value_t e;
            istr >> std::ws;
            ref_istr >> e;
            a.append(e);

            if (!ref_istr.parse_sigil(L','))
               break;
         }

         return a;
      }

      dict_t parse_dict(const ref_istream_t& ref_istr)
      {
         auto& istr = ref_istr.get_stream();

         if (!ref_istr.parse_sigil(L'{'))
            return {};

         dict_t d;

         while (istr.good()) {

            if (ref_istr.is_end(L'}'))
               break;

            name_t n;
            istr >> std::ws;
            ref_istr >> n;

            if (!ref_istr.parse_sigil(L':'))
               break;

            value_t e;
            istr >> std::ws;
            ref_istr >> e;
            d[n] = e;

            if (!ref_istr.parse_sigil(L','))
               break;
         }

         return d;
      }

      void parse_object(const ref_istream_t& ref_istr, object_t& o)
      {
         auto& istr = ref_istr.get_stream();

         if (!ref_istr.parse_sigil(L'{'))
            return;

         while (istr.good()) {

            if (ref_istr.is_end(L'}'))
               break;

            name_t n;
            istr >> std::ws;
            ref_istr >> n;

            if (!ref_istr.parse_sigil(L':'))
               break;

            value_t e;
            istr >> std::ws;
            ref_istr >> e;
            o[n] = e;

            if (!ref_istr.parse_sigil(L','))
               break;
         }
      }

      value_t parse_value(const ref_istream_t& ref_istr)
      {
         any_t value;
         ref_istr >> value;
         return value_t(value);
      }

      struct ref_istream_op_init_t
      {
         ref_istream_op_init_t()
         {
            ref_istream_op_t::make<value_t              >::op<value_t              >(std::function<value_t              (const ref_istream_t&)>(parse_value          ));
            ref_istream_op_t::make<dict_t               >::op<dict_t               >(std::function<dict_t               (const ref_istream_t&)>(parse_dict           ));
            ref_istream_op_t::make<array_t              >::op<array_t              >(std::function<array_t              (const ref_istream_t&)>(parse_array          ));
            ref_istream_op_t::make<weak_ref_t<object_t> >::op<weak_ref_t<object_t> >(std::function<weak_ref_t<object_t> (const ref_istream_t&)>(parse_weak_ref_object));
            ref_istream_op_t::make<ref_t<object_t>      >::op<ref_t<object_t>      >(std::function<ref_t<object_t>      (const ref_istream_t&)>(parse_ref_object     ));
            ref_istream_op_t::make<valid_ref_t<object_t>>::op<valid_ref_t<object_t>>(std::function<valid_ref_t<object_t>(const ref_istream_t&)>(parse_valid_ref_object     ));
            ref_istream_op_t::make<edit_ref_t<object_t> >::op<edit_ref_t<object_t> >(std::function<edit_ref_t<object_t> (const ref_istream_t&)>(parse_edit_ref_object     ));
            ref_istream_op_t::make<name_t               >::op<name_t               >(std::function<name_t               (const ref_istream_t&)>(parse_name           ));
         }
      };

      ref_istream_op_init_t ref_istream_op_init;
   }

   void ref_istream_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   const ref_istream_t& operator >>(const ref_istream_t& ref_istr, any_t& arg_a)
   {
      auto& istr = ref_istr.get_stream();

      if (!ref_istr.parse_sigil(L'@'))
         return ref_istr;

      const datatype_t* type = nullptr;

      int64_t id = 0;
      istr >> std::ws >> id;

      if (id > 0)
      {
         text_t tn;
         istr >> std::ws >> tn >> std::ws;
         type = &any_op::get_type_info(tn);
         if (*type == typeid(void))
         {
            // Note: if it has an unknown, unsupported type, then the type is
            //       void and we either read empty no data or abort the streaming.
            if (ref_istr.abort_on_unknown())
               istr.setstate(std::ios::failbit);
            return ref_istr;
         }
         ref_istr.add_type_with_id(*type, id);
      }
      else
      {
         type = &ref_istr.get_type_with_id(-id);
      }

      auto* ris_func = ref_istream_op_t::find_any_with_types<any_t>::op(std::type_index(*type));
      if (ris_func)
      {
         arg_a = (*ris_func)(ref_istr);
         if (arg_a.has_value())
         {
            return ref_istr;
         }
      }

      auto* is_func = any_op::istream_op_t::find_any_with_types<any_t>::op(std::type_index(*type));
      if (is_func)
      {
         arg_a = (*is_func)(ref_istr.get_stream());
         if (arg_a.has_value())
         {
            return ref_istr;
         }
      }

      istr.setstate(std::ios::failbit);
      return ref_istr;
   }
}

