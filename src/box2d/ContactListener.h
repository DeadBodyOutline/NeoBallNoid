#ifndef __CONTACTLISTENER_H__
#define __CONTACTLISTENER_H__

#include "Box2D/Box2D.h"

using namespace std;

class ContactListener : public b2ContactListener
{
public:
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    virtual void PreSolve(b2Contact *contact, const b2Manifold *manifold);
    virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // __CONTACTLISTENER_H__
