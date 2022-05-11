#ifndef _SERIALIZATION_OBJECT_H_
#define _SERIALIZATION_OBJECT_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class SBindName {
    private:
        friend class boost::serialization::access;

        template <class Archive> 
        void serialize(Archive& ar, const unsigned int version) {
            ar & m_bindName;
        }
        
        std::string m_bindName;

    public:
        SBindName(std::string name): m_bindName(std::move(name)) {}
        SBindName() {}
        const std::string& bindName() const { return m_bindName; }
};

class SChatInfo {
    private: 
        friend class boost::serialization::access;

        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & m_chatInformation;
        }
        
        std::string m_chatInformation;

    public:
        SChatInfo(std::string info): m_chatInformation(std::move(info)) {}
        SChatInfo() {}
        const std::string& chatInformation() const { return m_chatInformation; }
};


class SRoomInfo {

    public:
        SRoomInfo(std::string name, std::string info): m_bind(std::move(name)), m_chat(std::move(info)) {}
        SRoomInfo() {}

        const std::string& name() const { return m_bind.bindName(); }
        const std::string& information() const { return m_chat.chatInformation(); }
    private:
        friend class boost::serialization::access;
        template <class Archive> 
        void serialize(Archive& ar, const unsigned int version) {
            ar & m_bind;
            ar & m_chat;
        }
        SBindName m_bind;
        SChatInfo m_chat;
};

#endif
