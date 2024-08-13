# GoldUserCoins

The epic texture swapping mod by the best smelling cologne in the GD community himself... now **without patches**!

This was mainly done as an excuse to learn some raw reverse engineering (thank you to whoever leaked IDA 9.0 for your immense hard work 🫡), but also to make this mod truly multi-platform (mostly; it doesn't work on Android32 due to __int128 not working there :/).
This mod does use some bindings that are currently unavailable for m1 and mainly imac atm, but here are the bindings for them both that you can put in your own bindings repo if you wish:
```
void EnhancedGameObject::updateUserCoin() = win 0x19c930, m1 0x4f958c, imac 0x5ca6b0;
void GameObject::playPickupAnimation(cocos2d::CCSprite*, float, float, float, float) = win 0x19ff10, m1 0x20184c, imac 0x259e00;
void GameObject::playDestroyObjectAnim(GJBaseGameLayer*) = win 0x1a04e0, m1 0x201d4c, imac 0x25a310;
cocos2d::CCParticleSystemQuad*  GJBaseGameLayer::spawnParticle(char const*, int, cocos2d::tCCPositionType, cocos2d::CCPoint) = win 0x22f3f0, m1 0x1222ec, imac 0x151480;
```
Cocos bindings are needed as well (yes, for CCAnimate & CCAnimation you *need* to put in the entire thing in this manner otherwise they won't link properly for m1 and imac):
```
[[link(win, android)]]
class cocos2d::CCAnimation {
	static cocos2d::CCAnimation *createWithSpriteFrames(CCArray *, float) = m1 0x235a88, imac 0x2927e0;
}

[[link(win, android)]]
class cocos2d::CCAnimate {
	static cocos2d::CCAnimate *create(cocos2d::CCAnimation*) = m1 0x342ea0, imac 0x3bf2f0;
}

void cocos2d::CCSpriteFrameCache::removeSpriteFrameByName(char const*) = m1 0x2acbec, imac 0x31bda0;
void cocos2d::CCSpriteFrameCache::addSpriteFrame(cocos2d::CCSpriteFrame*, char const*) = m1 0x2aca14, imac 0x30e2e0;
```

This does result in a little bit of a conflict with QOLMod (but honestly everything does so don't worry too much).