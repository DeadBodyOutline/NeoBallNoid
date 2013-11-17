#include "ContactListener.h"
#include "Contact.h"
#include "sprites/Sprite.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    Sprite *spriteA = static_cast<Sprite *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Sprite *spriteB = static_cast<Sprite *>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (spriteA && spriteB) {
        spriteA->beginContact(spriteB);
        spriteB->beginContact(spriteA);
    }
}

void ContactListener::EndContact(b2Contact *contact)
{
    Sprite *spriteA = static_cast<Sprite *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Sprite *spriteB = static_cast<Sprite *>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (spriteA && spriteB) {
        spriteA->endContact(spriteB);
        spriteB->endContact(spriteA);
    }
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *manifold)
{
    Sprite *spriteA = static_cast<Sprite *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Sprite *spriteB = static_cast<Sprite *>(contact->GetFixtureB()->GetBody()->GetUserData());
    Contact *cont = new Contact(contact, manifold);

    if (spriteA && spriteB) {
        spriteA->preContact(spriteB, cont);
        spriteB->preContact(spriteA, cont);
    }
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    B2_NOT_USED(impulse);

    Sprite *spriteA = static_cast<Sprite *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Sprite *spriteB = static_cast<Sprite *>(contact->GetFixtureB()->GetBody()->GetUserData());
    Contact *cont = new Contact(contact);

    if (spriteA && spriteB) {
        spriteA->posContact(spriteB, cont);
        spriteB->posContact(spriteA, cont);
    }
}
