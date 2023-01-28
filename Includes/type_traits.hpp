#pragma once

namespace ft {

	struct false_type {
		static const bool value = false;
	};
	struct true_type {
		static const bool value = true;
	};

	template <bool v>
	struct bool_type : true_type{};

	template<>
	struct bool_type<false> : false_type {};

	template<class T1, class T2>
	struct is_same : false_type{};

	template<class T>
	struct is_same<T, T> : true_type{};

	template<class T>
	struct remove_const {
		typedef T type;
	};

	template<class T>
	struct remove_const<const T> {
		typedef T type;
	};

	template<class T>
	struct remove_volatile {
		typedef T type;
	};

	template<class T>
	struct remove_volatile<volatile T> {
		typedef T type;
	};

	template<class T>
	struct remove_cv : remove_const<typename remove_volatile<T>::type> {};

	namespace detail {
		template<class>
		struct is_integral : false_type{};

		template<>
		struct is_integral<bool> : true_type{};

		template<>
		struct is_integral<char> : true_type{};

		template<>
		struct is_integral<unsigned char> : true_type{};

		template<>
		struct is_integral<short> : true_type{};

		template<>
		struct is_integral<unsigned short> : true_type{};

		template<>
		struct is_integral<int> : true_type{};

		template<>
		struct is_integral<unsigned int> : true_type{};

		template<>
		struct is_integral<long> : true_type{};

		template<>
		struct is_integral<unsigned long> : true_type{};
		/*lmao
		template<>
		struct is_integral<long long int> : true_type{};

		template<>
		struct is_integral<unsigned long long> : true_type{};
		*/
	}

	template <class T>
	struct is_integral
		: detail::is_integral<typename remove_cv<T>::type>{};

	namespace detail {
		template<class>
		struct is_floating_point : false_type{};

		template<>
		struct is_floating_point<float> : true_type{};

		template<>
		struct is_floating_point<double> : true_type{};

		template<>
		struct is_floating_point<long double> : true_type{};
	}

	template <class T>
	struct is_floating_point
		: detail::is_floating_point<typename remove_cv<T>::type>{};


	namespace detail {
		template<class>
		struct is_void : false_type{};

		template<>
		struct is_void<void> : true_type{};
	}

	template<class T>
	struct is_void : detail::is_void<typename remove_cv<T>::type> {};

	namespace detail {
		template<class>
		struct is_pointer : false_type{};

		template<class T>
		struct is_pointer<T*> : true_type{};
	}

	template <class T>
	struct is_pointer
		: detail::is_pointer<typename remove_cv<T>::type>{};

	//template<class T>
	//struct is_class : typename bool_type<!is_scalar<T>>{};

	template<bool, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	namespace detail {
		template<class T>
		struct type_sink : true_type{};

		template<class T, class Ptr = void>
		struct is_union_or_class : false_type{};

		template<class T>
		struct is_union_or_class
			< T
			, typename enable_if
				< type_sink
					<int (T::*)()>::value
				>::type
			> : true_type{};
	}

	template<class T>
	struct is_union_or_class
		: detail::is_union_or_class<T> {};

	namespace detail {
		template <typename B, typename D>
		struct Host {
			operator B*() const;
			operator D*();
		};

		template <typename B, typename D>
		struct is_base_of {
			typedef char (&yes)[1];
			typedef char (&no)[2];

			template <typename T>
			static yes check(D*, T);
			static no check(B*, int);

			static const bool value = sizeof(check(Host<B,D>(), int())) == sizeof(yes);
		};
	}

	template <class Base, class Derived>
	struct is_base_of
	: bool_type
		< detail::is_base_of
			<typename remove_cv<Base>::type
			, typename remove_cv<Derived>::type
			> ::value
		>::type {};
#if 0
	namespace detail {
		struct dummy_type {};
		//compiler does not like the following smh.
		template<class T>
		struct derive : T {
			typedef T type;
		};

		template<class T, class Ptr = void>
		struct is_class : false_type{};
#if 0
		template<class T>
		struct is_class
			< T
			, typename enable_if
				<
					type_sink<typename derive<T>::type>::value
				>::type
			> : true_type{};
#endif
	}

	template<class T>
	struct is_class : detail::is_class<typename remove_cv<T>::type> {};
#endif
}
