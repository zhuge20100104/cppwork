#ifndef _FREDRIC_CSM_TRAITS_HPP_
#define _FREDRIC_CSM_TRAITS_HPP_

#include "is_class_t/is_class_t.hpp"
#include "csm1.hpp"

template <typename T>
class CSMTraits: public BitOrClassCSM<T, IsClassT<T>::NO>{};


#endif