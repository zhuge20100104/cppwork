// Generated by gencpp from file person_msg/Person.msg
// DO NOT EDIT!


#ifndef PERSON_MSG_MESSAGE_PERSON_H
#define PERSON_MSG_MESSAGE_PERSON_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace person_msg
{
template <class ContainerAllocator>
struct Person_
{
  typedef Person_<ContainerAllocator> Type;

  Person_()
    : name()
    , age(0)
    , height(0.0)  {
    }
  Person_(const ContainerAllocator& _alloc)
    : name(_alloc)
    , age(0)
    , height(0.0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  _name_type name;

   typedef uint16_t _age_type;
  _age_type age;

   typedef double _height_type;
  _height_type height;





  typedef boost::shared_ptr< ::person_msg::Person_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::person_msg::Person_<ContainerAllocator> const> ConstPtr;

}; // struct Person_

typedef ::person_msg::Person_<std::allocator<void> > Person;

typedef boost::shared_ptr< ::person_msg::Person > PersonPtr;
typedef boost::shared_ptr< ::person_msg::Person const> PersonConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::person_msg::Person_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::person_msg::Person_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::person_msg::Person_<ContainerAllocator1> & lhs, const ::person_msg::Person_<ContainerAllocator2> & rhs)
{
  return lhs.name == rhs.name &&
    lhs.age == rhs.age &&
    lhs.height == rhs.height;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::person_msg::Person_<ContainerAllocator1> & lhs, const ::person_msg::Person_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace person_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::person_msg::Person_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::person_msg::Person_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::person_msg::Person_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::person_msg::Person_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::person_msg::Person_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::person_msg::Person_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::person_msg::Person_<ContainerAllocator> >
{
  static const char* value()
  {
    return "81ccf2097ef38ca6466e5a60ea1f8e49";
  }

  static const char* value(const ::person_msg::Person_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x81ccf2097ef38ca6ULL;
  static const uint64_t static_value2 = 0x466e5a60ea1f8e49ULL;
};

template<class ContainerAllocator>
struct DataType< ::person_msg::Person_<ContainerAllocator> >
{
  static const char* value()
  {
    return "person_msg/Person";
  }

  static const char* value(const ::person_msg::Person_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::person_msg::Person_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string name\n"
"uint16 age\n"
"float64 height\n"
;
  }

  static const char* value(const ::person_msg::Person_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::person_msg::Person_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.name);
      stream.next(m.age);
      stream.next(m.height);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Person_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::person_msg::Person_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::person_msg::Person_<ContainerAllocator>& v)
  {
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
    s << indent << "age: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.age);
    s << indent << "height: ";
    Printer<double>::stream(s, indent + "  ", v.height);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERSON_MSG_MESSAGE_PERSON_H