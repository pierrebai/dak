# The Worst of Both Worlds

C++ certainly is one of the most complex programming languages
there is. The templates are a particularly tough part of C++.
They were a late addition to the language, it had to fit within
he existing syntax. On top of that, the C++ language designers
discovered that templates had more power than was initially apparent;
they had created by accident a very pure functional language!
Unfortunately, this accidental origin meant its syntax is barely
usable as a functional language. Even though the syntax might
at first repel trying to use it, given its power and the
developping needs of advanced C++, programmer have pushed it
further and further. The templating part of C++ keeps
gaining new features and power with each new C++ language
vresion.

In extreme contrast, Python is one of the easiest programming
language to learn and read. It is also very dynamic, allowing
to pass around any data to any function easily. Better still,
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

Just receiving a variable number of types is just the start.
The template must also be able to *use* them. And that's tricky.
As you may already know, templates are compile-time beasts.
They need to work without modifying any data. So, to manipulate
a variable number of types, a new syntax was added to C++.
This new syntax for receiving the types and using them was designed
around the ellipsis: ...

The basic trick is that whenever the ellipsis is used, it tells the
C++ compiler to repeat the surrounding piece of code as many times
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

Afterward, in the template implementation, the variadic type arguments
can be used with the ellipsis. For example, we could add a function to
the variadic template that receives arguments of the corresponding types
and pass these values into a call to another function, like this:

   ```C++
   // Receive a variable number of arguments...
   void foo(VARIA... function_arguments)
   {
      // ... and pass them on to another function.
      other_bar_function(function_arguments...);
   }
   ```

These examples only scratch the surface of what is possible with variadic
templates, but they should be enough to understand how we use them in
the rest of this article.


# Dynamic Dispatch Design

Before delving into the implementation of our dynamic dispatch, we need
to outline our requirements more concretely. I said it should mimick
the compile-time function overload of C++. What does that mean?
Here is what we require the design to be capable of:

- The function itself is declared at compile-time and is referred to
  by its name, like a normal function.
- The number of arguments of a given function can vary.
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

To support these use cases, we add two requirements to the list:

- Not all arguments have to play a part in the type-based selection
  of the function.
- Some additional types *can* play a part in the typed-based selection
  of the function without being an argument.

The result should look like compile-time function overload. For
example here is how we would call a `to_text` function using
our dynamic dispatch mechanism:

   ```C++
   std::wstring result = to_text(7);
   // result == "7"
   std::any seven(7);
   std::wstring result = to_text(seven);
   // result ==  "7"
   ```

To achieve such simplicity, a lot of complex code is working behind
the scene.


# Smooth Operator

Before showing the how the dynamic dispatch is implemented, we'll
take a look at how it looks from the perspective of the programmer
creating a new operation. How do we create a new function?

To create a new operation called `foo`, declare a class to represent it.
For our example, we named it `foo_op_t`. We make it derive from `op_t`,
which is the class provided by our system. The `foo_op_t` class merely
identify the operation; it can be entirely empty! Afterward, we can write
a `foo` function, the real entry-point for the operation. That is the
function that the user of the `foo` operation would call. This function
simply needs to call `call<>::op()` (for concrete values) or `call_any<>::op()`
(for `std::any` values). Both are provided by the `op_t` base class
of our `foo_op_t`, this base class takes care of the dynamic dispatch:

   ```C++
   struct foo_op_t : op_t<foo_op_t> { /* empty! */ };

   inline std::any foo(const std::any& arg_a, const std::any& arg_b)
   {
      return foo_op_t::call_any<>::op(arg_a, arg_b);
   }

   template<class A, class B, class RET>
   inline RET foo(const A& arg_a, const A& arg_b)
   {
      std::any result = foo_op_t::call<>::op(arg_a, arg_b);
      // Note: we could test if the std::any really contains
      //       a RET, instead of blindly trusting it.
      return any_cast<RET>(result);
   }
   ```

Note that the base class of the new operation takes the operation
itself as a template parameter. This is a well-known trick in template
programming. It is so well known it even has a name: the curiously
recursive template pattern. In our case, this trick is used so that
the `op_t` can refer to the specific operation being used.

Now we can create overloads of the `foo` operation. This is done
by calling `make<>::op` with a function that implements the overload.
To create an overload taking types `A` and `B` and returning the
type `RET`, we call `make<>::op<RET, A, B>`. This registers the overload
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
   foo_op_t::make<>::op<float, int, double>(foo_for_int_and_double);
   ```

Of course, we could make the code shorter by writing the implementation
right there in the call to `make<>::op`, with a lambda:

   ```C++
   foo_op_t::make<>::op<float, int, double>(
      [](int i, double d) -> float
      {
         return float(i + d);
      }
   );
   ```

You might be wondering why the `call<>` and `make<>` take the
template sigils. The sigil is necessary because `call` and `make`
are themselves variadic templates. The optional template arguments
are the extra selection types, used to choose a more specific overload
based on types that are *not* passed as argument to the `foo` operation.
We will explain this in more details later.

Now we are ready to get into the meat of the subject: implementing
the dynamic function dispatch.


# Enter Selector

The first problem to tackle is how each overload is identified
within a function family. The obvious solution is to identify it by
the types or its argument and extra selection types. C++ provides
the `std::type_info` and `std::type_index` to identify a type.
What we need is a `tuple` of these `type_index`. We achieve that
with a pair of templates: the type converter and the selector.

The type converter maps any type to `std::type_index`. It is
a very idiomatic trick in template programming, where each step
in an algorithm is implemented in a type so it can be executed
at compile-time. Here is the converter, converting any type `A`
into a `type_index` or `std::any`:

   ```C++
   template <class A>
   struct type_converter_t
   {
      // Convert to std::type_index, for the selector.
      using type_index = std::type_index;

      // Convert to std::any, to be used in functin arguments.
      using any = std::any;
   };
   ```

The full type selector can then be written as a variadic template
by applying the converter to all types given as argument and
declaring a `tuple` type named `selector_t` with the result.
It uses both the function argument types, `N_ARY`, and the extra
selection types, `EXTRA_SELECTORS`, to create the full selector:

   ```C++
   template <class... EXTRA_SELECTORS>
   struct op_selector_t
   {
      template <class... N_ARY>
      struct n_ary_t
      {
         // The selector_t type is a tuple of type_index.
         using selector_t = std::tuple<
            typename type_converter_t<EXTRA_SELECTORS>::type_index...,
            typename type_converter_t<N_ARY>::type_index...>;
      };
   };
   ```

How the C++ language applies the ellipsis is the black magic
of variadic templates. Many times, you have to try and find out what works
and what doesn't through experimentations.

OK, now we have a selector type, but how do we use it? The goal is to have
a function that makes a selector already filled with concrete types. Naturally,
we call this function `make`:

   ```C++
   template <class... EXTRA_SELECTORS>
   struct op_selector_t
   {
      template <class... N_ARY>
      struct n_ary_t
      {
         template <class A, class B>
         static selector_t make()
         {
            return selector_t(
               std::type_index(typeid(EXTRA_SELECTORS))...,
               std::type_index(typeid(N_ARY))...);
         }
      };
   };
   ```

Since we want to support calls with `std::any`, we need to provide
a `make_any` function taking `std::any` as input:

   ```C++
   static selector_t make_any(const typename type_converter_t<N_ARY>::any&... args)
   {
      return selector_t(
         std::type_index(typeid(EXTRA_SELECTORS))...,
         std::type_index(args.type())...);
   }
   ```
(As an optimization, a version with the extra selector already converted
to `type_index` is provided, named `make_extra_any`, but is not shown here.)

# Diving into Delivery

Finally, we can dive into the mechanical details of the registration
of implementation of our operations and how to call them.

We start with the base class of all operators. It is a template taking
the operation itself and a list of optional unchanging extra arguments,
called `EXTRA_ARGS`, which will have fixed types. Remember the earlier
example of a streaming operation, which would always receive a `std::ostream`
as the first argument. That is the reason for the existence of EXTRA_ARGS.

   ```C++
   template <class OP, class... EXTRA_ARGS>
   struct op_t
   {
      // Internal details will come next...
   };
   ```

Now we can show a few types that are used repeatedly in the implementation
of `op_t`: the selector class, `op_sel_t`, the selector tuple, `selector_t`
and the internal function signature of the operation, `op_func_t`.

   ```C++
   using op_sel_t = typename op_selector_t<EXTRA_SELECTORS...>::template n_ary_t<N_ARY...>;
   using selector_t = typename op_sel_t::selector_t;
   using op_func_t = std::function<std::any(EXTRA_ARGS ..., typename type_converter_t<N_ARY>::any...)>;
   ```

The code above shows some of the inherent complexity of template programming.
There are many bits that would normally be totally unnecessary but
are required due to the internal workings of templates. For example,
`typename` is necessary to tell the compiler that what follows really
is a type. This happens when a template refers to an element of another
template. The C++ syntax is too ambiguous to let the compiler infer by itself
that we are using a type. Another very peculiar bit is the second extra
`template` keyword right before accessing `n_ary_t`. It is necessary
to let the compiler know that `n_ary_t` really is a template.

With these types, we're now ready to explain the whole system, which is put
together with just a few functions:

- A public way to call the operation: `call<>::op`
- A public way to make a new overload: `make<>::op`
- A private way to lookup the correct overload: `get_ops`

We will tackle each in reverse order, from the lowest implementation
details up to the finality: calling an overload.


## Keeper of Wonders

The lowest implementation detail is the container of registered overloads.
The container is the function `get_ops`. There is an important reason why
`get_ops` needs to exist. The problem is that the overloads need to be kept
in a container, but the `op_t` base class is a template. We cannot keep all
overloads for all derived operations together. Fortunately, the C++ language
says that a static variable contained in a function in a template will be
specific and unique to each instantiation of the template. Using this trick,
we can hide the registration container inside `get_ops`: it will safely
contain our list of overloads.

   ```C++
   template <class SELECTOR, class OP_FUNC>
   static std::map<SELECTOR, OP_FUNC>& get_ops()
   {
      static std::map<SELECTOR, OP_FUNC> ops;
      return ops;
   }
   ```

We template `get_ops` with `SELECTOR` and `OP_FUNC` parameters
to allow the operation to be overloaded for different numbers
of arguments if desired.


## Making Up Your Op

The `make<>::op` function is a template taking a concrete overload
implementation for concrete types. It wraps the given implementation
to conform to the internal function signature and then registers it.
The wrapping takes care of converting the `std::any` arguments to the
concrete types of the overload. This is safe, since the concrete
overload for these concrete types is only ever called when the types
match. The `make<>::op` templated function is where the optional extra
selection types may be given. They are named `EXTRA_SELECTORS`.

   ```C++
   template <class... EXTRA_SELECTORS>
   struct make
   {
      template <class RET, class... N_ARY>
      static void op(
         std::function<RET(EXTRA_ARGS... extra_args, N_ARY... args)> a_func)
      {
         // Wrapper kept as a lambda mapping the internal
         // function signature to the concrete function signature.
         op_func_t op(
            [a_func](
               EXTRA_ARGS... extra_args,
               const typename type_converter_t<N_ARY>::any&... args) -> std::any
            {
               // Conversion to concrete argument types.
               return std::any(a_func(extra_args..., *std::any_cast<N_ARY>(&args)...));
            }
         );

         // Registration.
         auto& ops = get_ops<selector_t, op_func_t>();
         ops[op_sel_t::make()] = op;
      }
   };
   ```


## Call Me Up, Call My Op

We finally reach the function used to dispatch a call: `call<>::op`.
There are three versions of this function. The difference between
them is if the arguments have already been converted to `std::any` or
`std::type_index`. The `call<>::op` function needs to do a few things:

- Create a selector from the types of its arguments, plus the optional
  extra selectors.
- Retrieve the list of available overloads.
- Lookup the function overload using the selector.
- Return an empty value if no overload matches the arguments.
- Call the function if an overload matches the arguments.

   ```C++
   template <class... EXTRA_SELECTORS>
   struct call
   {
      template <class... N_ARY>
      static std::any op(EXTRA_ARGS... extra_args, N_ARY... args)
      {
         // The available overloads.
         const auto& ops = get_ops<selector_t, op_func_t>();
         // Try to find a matching overload.
         const auto pos = ops.find(op_sel_t::make());
         // Return an empty result if no overload matches.
         if (pos == ops.end())
            return std::any();
         // Otherwise call the matching overload.
         return pos->second(extra_args..., args...);
      }
   };
   ```


# Wrapping Up

This completes the description of the dynamic dispatch design and
its implementation. The repo of the source code contains multiple
examples of operations with a complete suite of tests.

The examples of operations are:

- `compare`, a binary operation to compare two values.
- `convert`, an unary operation to convert a value to another type.
  This is an example of an operation with an extra selector argument:
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
my `dak` repo: https://github.com/pierrebai/dak
