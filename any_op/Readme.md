# The Worst of Both Worlds

C++ certainly is one of the most complex programming languages.
A particularly tough part of C++ are the templates. As a late
addition to the language, it had to fit within the existing syntax.
On top of that, starting from the STL, the C++ language designers
discovered that templates had more power than was initially apparent.
In short, they had created by accident a very pure functional
language. Unfortunately, this accidental origin meant its functional
syntax is barely usable. But, given its power and the need to address
the need for advance C++ techniques, the templating part of C++ keeps
gaining new features and power.

In extreme contrast, Python is often described as one of the easiest
programming language to learn and read. It is also very dynamic,
allowing to pass around any data to any function easily. Better,
functions can be defined and re-defined at run-time. When you call
a function, you are never sure what code *really* will be executed.

So, why not combine both? The complexity and obscure syntax of C++
templates with Python dynamic typing and dynamic extensibility.
If this kind of unappealing brew interest you, then I've got something
for you!


# Now, Seriously....

The real story is, I wanted to have overloaded function resolution
at run-time instead of compile-time.

I wanted to create a dynamic function-dispatch system that could
call a function with any data. I wanted this system to be dynamically
extensible, to allow new overloads of the function for new data types
at any time. I also wanted to be able to call the functions with either
concrete data or a bunch of `std::any`. I also wanted all this to be
reasonably efficient.

To achieve all these goals, I turned to templates. Not just simple ones
though, but the more complex variadic templates.


# Variadic Template Syntax

What's a variadic template? Normal templates take a fixed number
of types as argument. That's fine when you know in advance how many
types you need. In contrast, a variadic template takes a variable
number of types as argument. It can be zero, one, two, ...
any number of types.

In addition to receiving these types, the template must be able to
use them. As you may already know, templates are compile-time beasts.
They need to work without modifying any data. So, to manipulate
a variable number of types, a new syntax had to be added to C++.
The new syntax for both receing the types and using them was created
around the ellipsis: ...

The basic trick is that whenever the ellipsis is used, it tells the
C++ compiler to repeat the surrouding piece of code as many times
as needed for each type. For example, the types of the variadic
template are received with the ellipsis. In the following example,
the `VARIA` template argument represents any number of types.

   ```C++
   template <class... VARIA>
   struct example
   {
      // template implementation.
   };
   ```

Later on, in the template implementation, the variadic type arguments
can be used in the code with the ellipsis. For example, the variadic
template above could have a function that receives arguments of the
corresponding types and pass these values into a call to another
function, like this:

   ```C++
   // Receive a variable number of arguments...
   void foo(VARIA... function_arguments)
   {
      // ... and pass them on to another function.
      other_bar_function(function_arguments...);
   }
   ```

These examples only scratch at the surface of what is possible with
variadic templates, but they will be sufficient for our purpose in
this article.


# Dynamic Dispatch Design

Before delving into the design of our dynamic dispatch, we need to
to outline our requirements more concretely. I said it should mimick
the compile-time function overload of C++. What does that mean?
Here is what we require the design to be capable of:

- The function itself is declared at compile-time and is referred to
  by its name, like a normal function.
- The number of arguments of a given function is fixed.
- The function can be overloaded using the normal compile-time
  overload mechanism with different number of arguments.
- Each overload of a function can return different type of values.
- Each such function can be overloaded for any type.
- New function overload can be added dynamically, at run-time, for
  any type.

While these requirements would be sufficient for our goal, there
were a few additional use cases I wanted to cover. The first addition
is to support function arguments that always have the same type.
For example, a text-streaming function would always receive a
`std::ostream` argument. The second addition is to allow selecting
a function implementation without having to pass a value to the
function. This allows specifying the return type of the function
or implementing functions that take no argument at all. I'll be
showing you an example of each later on.

To support these use case, we add two requirements to the list:

- Not all arguments have to play a part in the type-based selection
  of the function.
- Some additional types *can* play a part in the typed-based selection
  of the function without being an argument.

The result should look like compile-time function overload. For
example here is how a call to the dynamic-dispatch `to_text` function
looks like:

   ```C++
   std::wstring result = to_text(7);
   // result == "7"
   std::any seven(7);
   std::wstring result = to_text(seven);
   // result ==  "7"
   ```

To achieve such simplicity, a lot of complex code is working behind
the scene. Of note, while the dynamic dispatch system can support
functions with any number of arguments, we will provide explicit help
for nullary, unary and binary function. (Yes, yes, nullary is a word,
it means a function taking zero argument.)


# Smooth Operator

Before showing the how the dynamic dispatch is implemented, we'll
take a look at how it looks from the perspective of the programmer
creating a new operation. How do we create a new function?

To create a new binary operation called `foo`, declare a class to
represent it. For our example, we named it `foo_op_t`. Since we
want it to be a binary operation, we derive from `binary_op_t`.
The `foo_op_t` class identifies the operation. It can be entirely empty.
Afterward, we can write the `foo` function, the real entry-point
for the operation. That is the function that the user of the `foo`
operation will call. This function only needs to call the `call_op()`
function on the operation, which takes care of the dynamic dispatch:

   ```C++
   struct foo_op_t : binary_op_t<foo_op_t> { /* empty! */ };

   inline std::any foo(const std::any& arg_a, const std::any& arg_b)
   {
      return foo_op_t::call_op(arg_a, arg_b);
   }

   template<class A, class B, class RET>
   inline RET foo(const A& arg_a, const A& arg_b)
   {
      return any_cast<RET>( foo(std::any(arg_a), std::any(arg_b)) );
   }
   ```

Note that the base class of the new operation takes the operation
itself as a template parameter. This is a well-known trick in template
programming. It is so well known it even has a name: the curiously
recursive template pattern. In our case, this trick is used so that
the `binary_op_t` can refer to the specific operation being used.

Now we can create overloads of the `foo` operation. This is done
by calling `make_op` with a function that implements the overload.
To create an overload taking types `A` and `B` and returning the
type `RET`, we call `make_op<RET, A, B>`. This registers the overload
in the `foo_op_t` class. As an example, let's implement our `foo`
operation for the type `int` and `double` and make it return
a `float`:

   ```C++
   // Some code in your program that implements the operation.
   float foo_for_int_and_double(int i, double d)
   {
      return float(i + d);
   }

   // Registration!
   foo_op_t::make_op<float, int, double>(foo_for_int_and_double);
   ```

Of course, we could make the code shorter by writing the implementation
right there in the call to `make_op`, with a lambda:

   ```C++
   foo_op_t::make_op<float, int, double>(
      [](int i, double d) -> float
      {
         return float(i + d);
      }
   );
   ```

Now we are ready to get into the meat of the subject: implementing
the dynamic function dispatch.


# Enter Selector

The first problem to tackle is how each overload is identified
within a function family. The obvious solution is to identify it by
the types or its argument and extra selection types. C++ provides
the `std::type_info` and `std::type_index` to identify a type.
What we need is a `tuple` of these `type_index`. We achieve that
with a pair of templates: the selector converter and the selector.

The selector converter maps any type to `std::type_index`. It is
a very idiomatic trick in template programming, where each step
in an algorithm is implemented in a type so it can be executed
at compile-time. Here is the converter, converting any type `A`
into a `type_index`:

   ```C++
   template <class A>
   struct op_selector_converter_t
   {
      using type_index = std::type_index;
   };
   ```

The full type selector can then be written as a variadic template
by applying the converter to all types given as argument and
declaring a `tuple` type named `selector_t` with the result.
   ```C++
   template <class... SELECTORS>
   struct op_selector_t
   {
      // The selector_t type is a tuple of type index.
      using selector_t = std::tuple<
         typename op_selector_converter_t<SELECTORS>::selector_t...
      >;
   };
   ```

Note how the ellipsis is applied to the line:

   ```C++
   typename op_selector_converter_t<SELECTORS>::selector_t...
   ```

How the C++ language applies the ellipsis is a bit of the black magic
of variadic templates. Sometimes, you will have to try what works
and what doesn't.

Now we have a selector type, but how do we use it? For this, we provide
yet more templates. I will only describe the one for a binary operation,
the version for unary and nullary are similar. The goal is to have
a function that makes a selector already filled with the concrete types.
Naturally, we call our function `make`:

   ```C++
   template <class... EXTRA_SELECTORS>
   struct binary_op_selector_t
   : op_selector_t<std::any, std::any, EXTRA_SELECTORS...>
   {
      template <class A, class B>
      static selector_t make()
      {
         return selector_t(
            std::type_index(typeid(A)),
            std::type_index(typeid(B)),
            std::type_index(typeid(EXTRA_SELECTORS))...);
      }
   };
   ```

Since I want to support calls with `std::any`, we need to provide
the `make` function taking `std::any` as input. (As an optimization,
a version with the extra selector already converted to `type_index`
is provided, but is not shown here.)

   ```C++
   static selector_t make(const std::any& arg_a, const std::any& arg_b)
   {
      return selector_t(
         std::type_index(arg_a.type()),
         std::type_index(arg_b.type()),
         std::type_index(typeid(EXTRA_SELECTORS))...);
   }
   ```


# Diving into Delivery

Finally, we can dive into the mechanical details of the registration
and calling of the operations. We will once again use the binary
operator as an example. The binary operation base class is declared
as a template taking the operation itself and a list of optional
unchanging extra arguments, `EXTRA_ARGS`, which will have fixed types.
(Remember our earlier streaming operation example, which always
received a `std::ostream`.) The first thing that the binary op
declares is the internal function signature of the operation:

   ```C++
   template <class OP, class... EXTRA_ARGS>
   struct binary_op_t
   {
      using op_func_t = std::function<
         std::any(
            EXTRA_ARGS ...,
            const std::any& arg_a,
            const std::any& arg_b)>;
   };
   ```

Next the template declares its constructors. Indeed, the binary
operation class is the one being instantiated when a function is
registered. It declares two constructors: one default, representing
an empty do-nothing implementation and one containing a given overload
of the operation.

   ```C++
   binary_op_t() = default;
   binary_op_t(const op_func_t& an_op) : my_op_func(an_op) {}
   ```

To finish up the whole system, only a few more functions are actually
needed:

- A public way to call the operation: `call_op` and `call_any_op`
- A public way to make a new overload: `make_op`
- A private way to register the new overload: `register_op`
- A private way to lookup the correct overload: `get_ops`

We will tackle each in reverse order, from the lowest implementation
details up to the finality: calling an overload.

## Keeper of Wonders

The lowest implementation detail is the function that holds the
available, already registered overloads. There is a very important
reason why `get_ops` needs to exist. The problem it solves is that
the overloads need to be kept in a container, but the binary operation
base class is a template. We cannot keep all overloads for all operations
together. Fortunately, the C++ language specifies that a static variable
contained in a function in a template is specific to each instantiation
of the template. This let us hide the registration location inside.
The `get_ops` contains safely our list of overload for a given `SELECTOR`:

   ```C++
   template <class SELECTOR>
   static std::map<SELECTOR, op_base_t>& get_ops()
   {
      static std::map<SELECTOR, op_base_t> ops;
      return ops;
   }
   ```

## Register Regimen

The purpose of the `register_op` private function is to isolate the
complexity of creating the type-based selector. It is a function
template taking all the selecting concrete types, including the
optional extra selectors named `EXTRA_SELECTORS`. It then uses
them to create the selector and register the overload.

   ```C++
   template <class A, class B, class... EXTRA_SELECTORS>
   static void register_op(const op_base_t& an_op)
   {
      using selector_t = typename
         binary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
      auto& ops = get_ops<selector_t>();
      const auto selector =
         binary_op_selector_t<EXTRA_SELECTORS...>::template make<A, B>();
      ops[selector] = an_op;
   }
   ```

This shows some of the inherent complexity of template programming.
There are many bits that would normally be totally unnecessary but
are required due to the internal workings of templates. For example,
`typename` is necessary to tell the compiler that what follows really
is a type. This happens when a template refer to elements of another
template. The C++ syntax is too ambiguous to let the compiler infer
that we are using a type. Another very peculiar bit is the extra
`template` keyword right in the middle of the call to `make`.
It is necessary to let the compiler know that it really is a templated
function.

## Making Up Your Op

The `make_op` function is a template taking a concrete overload
for concrete types, wraps it into the internal function signature
and registers it. The wrapping takes care of converting the `std::any`
arguments to the concrete types. This is safe, since the concrete
overload for these concrete types is only ever called when the types
match. This is where the optional extra selection types may be given
as the `EXTRA_SELECTORS` template arguments.

   ```C++
   template <class RET, class A, class B, class... EXTRA_SELECTORS>
   static void make_op(std::function<RET(
      EXTRA_ARGS... args, const A& arg_a, const B& arg_b)> a_func)
   {
      // Wrapper kept as a lambda mapping the internal
      // function signature to the concrete function signature.
      op_base_t op(
         [a_func](
            EXTRA_ARGS... args,
            const std::any& arg_a,
            const std::any& arg_b) -> std::any
         {
            // Conversion to concrete types.
            return std::any(
               a_func(args...,
               *std::any_cast<A>(&arg_a),
               *std::any_cast<B>(&arg_b)));
         }
      );

      // Registration.
      register_op<A, B, EXTRA_SELECTORS...>(op);
   }
   ```

## Call Me Up, Call My Op

We finally reach the function used to dispatch a call. There are
two version of the function, but the second one is only an optimization
when the optional extra selectors have already been converted to
`std::type_index`. We won't show it here. The `call_op` function needs
to do a few things:

- Create a selector from the types of its arguments, plus the optional
  extra selectors.
- Retrieve the list of available overloads.
- Lookup the function overload using the selector.
- Return an empty value if no overload matches the arguments.
- Call the function if an overload matches the arguments.

   ```C++
   template <class... EXTRA_SELECTORS>
   static std::any call_op(
      EXTRA_ARGS... args, const std::any& arg_a, const std::any& arg_b)
   {
      // The type of the selector used to look-up an overload.
      using selector_t =
         typename binary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
      // The available overloads.
      const auto& ops = get_ops<selector_t>();
      // Try to find a match.
      const auto pos = ops.find(
         binary_op_selector_t<EXTRA_SELECTORS...>::make(arg_a, arg_b));
      // Return an empty result if no overload matches.
      if (pos == ops.end())
         return std::any();
      // Call the matching overload.
      return pos->second.my_op_func(args..., arg_a, arg_b);
   }
   ```


# Wrapping Up

This completes the description of the dynamic dispatch design and
its implementation. The repo of the source code contains multiple
examples of operations with a complete suite of tests.

The examples of operations are:

- `compare`, a binary operation to compare two values.
- `convert`, an unary operation to convert a value to another type.
  This is an example of an operation with an extra selector argument,
  the final type of the conversion.
- `is_compatible`, a nullary operation taking two extra selection
  types to verify if one can be converted to the other.
- `size`, an unary operation returning the number of elements in
  a container, or returning zero if no overload was found.
- `stream`, an unary operation to write a value to a text stream.
  This is an example of an operation with an extra unchanging argument,
  the destination `std::ostream`.
- `to_text`, an unary operation converting a value to text.

The whole code base is found in the `any_op` library that is part of
my `dak_utility` repo: https://github.com/pierrebai/dak_utility
