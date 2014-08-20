//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_MAKE_INJECTOR_HPP
#define BOOST_DI_MAKE_INJECTOR_HPP

#include "boost/di/aux_/mpl.hpp"
#include "boost/di/injector.hpp"

namespace boost {
namespace di {

//BOOST_DI_HAS_MEMBER_TYPE(scope);

template<typename... TArgs>
injector<typename get_bindings<TArgs...>::type>
inline make_injector(const TArgs&... args) {
    return injector<
        typename get_bindings<
            TArgs...
          //, aux::mpl::if_<
                //has_scope<aux::mpl::_2>
              //, detail::default_scope<aux::mpl::_2>
              //, aux::mpl::_2 // argument not supported
            //>
        >::type
    >(args...);
}

} // namespace di
} // namespace boost

#endif

