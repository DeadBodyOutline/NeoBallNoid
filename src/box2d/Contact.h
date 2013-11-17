#ifndef __CONTACT_H__
#define __CONTACT_H__

#include "Box2D/Box2D.h"

using namespace std;

class Contact
{
public:
    Contact(b2Contact *contact = NULL, const b2Manifold *manifold = NULL) {
        m_contact = contact;
        m_manifold = manifold;
    }

    void setContact(b2Contact *contact) { m_contact = contact; }
    b2Contact *getContact() { return m_contact; }

    void setManifold(const b2Manifold *manifold) { m_manifold = manifold; }
    const b2Manifold *getManifold() { return m_manifold; }

private:
    b2Contact *m_contact;
    const b2Manifold *m_manifold;
};

#endif // __CONTACT_H__
