#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/EnhancedGameObject.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

bool swappedTextures = false;

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		// test if already swapped textures
		if (swappedTextures) return true;
		else swappedTextures = true;

		// swaps all user coin textures with their golden counterparts
		for (int i = 1; i <= 4; i++) {
			std::string suffix = ("_00" + std::to_string(i) + ".png");
			swapTexture("secretCoin_01" + suffix, "secretCoin_2_01" + suffix);
			swapTexture("secretCoin_b_01" + suffix, "secretCoin_2_b_01" + suffix);
		}
		
		return true;
	} 

	void swapTexture(std::string oldKey, std::string newKey) {
		auto textureCache = CCSpriteFrameCache::get();
		auto goldTexture = textureCache->spriteFrameByName(oldKey.c_str());
		textureCache->removeSpriteFrameByName(newKey.c_str());
		textureCache->addSpriteFrame(goldTexture, newKey.c_str());
	}
};

class $modify(CCSprite) {
	// removes the bronze tint on unverified coins
	void setColor(cocos2d::ccColor3B const& col) {
		GameObject* gameObj = typeinfo_cast<GameObject*>(this);
		if (gameObj && gameObj->m_objectID == 1329) CCSprite::setColor({255, 255, 255});
		else CCSprite::setColor(col);
	}
};

class $modify(LoadingLayer) {
	bool init(bool p0) {
		swappedTextures = false;
		return LoadingLayer::init(p0);
	}
};

class $modify(EnhancedGameObject) {
    static void onModify(auto& self) {
        self.setHookPriority("EnhancedGameObject::updateUserCoin", 1024);
    }

	void updateUserCoin() {
		// time for a complete reverse engineer!!!

  		bool hasUniqueCoin; // w0
  		cocos2d::CCParticleSystemQuad *v4; // x0
  		cocos2d::CCParticleSystemQuad *v5; // x20
  		int v6; // s0
  		int v12; // s0
        #if !defined (GEODE_IS_WINDOWS)
  		__int64_t v13; // [xsp+0h] [xbp-20h] BYREF (its __int64_t and not __int64 because __int64 doesnt exist on mac :>)
        #else
        __int64 v13; // [xsp+0h] [xbp-20h] BYREF (its __int64_t and not __int64 because __int64 doesnt exist on mac :>)
        #endif
  		int v14; // [xsp+8h] [xbp-18h]
  		int v15; // [xsp+Ch] [xbp-14h]

		if (!this->m_editorEnabled) {
			hasUniqueCoin = GJBaseGameLayer::get()->hasUniqueCoin((EffectGameObject *)this);
			this->m_obAnchorPointInPoints.x = hasUniqueCoin;
			if (!hasUniqueCoin) {
				v4 = this->createAndAddParticle((int)this->m_objectType, "coinEffect.plist", 0, kCCPositionTypeGrouped);
				if (v4) {
					if (this->m_objectID != 142) {
						/*
						v6 = v4->getStartColor().a;
						v13 = 0x3F8000003F800000LL;
						v14 = 1065353216;
						v15 = v6;
						v4->setStartColor(ccc4f(v13, v13, v13, v14));;
						v12 = v4->getEndColor().a;
						v13 = 0x3F0000003F000000LL;
						v15 = 1056964608;
						v15 = v12;
						v4->setEndColor(ccc4f(v13, v13, v13, 0));
						*/
					}
				}
				auto vNumber = cocos2d::CCPoint(0.0, -19.0);
				this->m_unk31c = vNumber;
			}
		}
	}
};

class $modify(GameObject)
{
    void playDestroyObjectAnim(GJBaseGameLayer *p0)
    {
        #if !defined (GEODE_IS_WINDOWS)
        __int64_t v2;                       // x20
        __int64_t v4;                       // x23
        bool v5;                            // w8
        int v6;                             // w9
        cocos2d::CCSprite *m_colorSprite;   // x0
        double *v8;                         // x0
        double v9;                          // d0 OVERLAPPED
        GameObjectType m_objectType;        // w24
        bool hasUniqueCoin;                 // w21
        double *v12;                        // x0
        double v13;                         // d0 OVERLAPPED
        cocos2d::CCParticleSystemQuad *v14; // x0
        cocos2d::CCParticleSystemQuad *v15; // x22
        int v16;                            // s0
        int v22;                            // s0
        CCCircleWave *v23;                  // x22
        __int128 __dst;                     // [xsp+60h] [xbp-90h] BYREF
        __int64_t v130;                     // x0
        CCCircleWave *v131;                 // x0
        __int64_t v132;                     // x22
        int v133;                           // w8
        __int64_t v134;                     // x0
        const char *v135;                   // x8
        GameObjectType v136;                // w9
        const char *v137;                   // x10
        const char *v138;                   // x23
        char *v139;                         // x0
        char *v140;                         // x20
        cocos2d::CCNode *v141;              // x21
        __int64_t v142;                     // x0
        __int64_t v143;                     // x0
        __int64_t v144;                     // x0
        __int64_t v211;                     // [xsp+70h] [xbp-80h]
        __int64_t v212;                     // [xsp+78h] [xbp-78h] BYREF
        __int64_t v213;                     // [xsp+80h] [xbp-70h] BYREF
        float v214;                         // xmm3_4
        float v215;                         // xmm2_4
        cocos2d::CCSprite *v216;            // rdx
        GameObject *v217;                   // rcx
        int v7;
        #else
        __int64 v2;                       // x20
        __int64 v4;                       // x23
        bool v5;                            // w8
        int v6;                             // w9
        cocos2d::CCSprite *m_colorSprite;   // x0
        double *v8;                         // x0
        double v9;                          // d0 OVERLAPPED
        GameObjectType m_objectType;        // w24
        bool hasUniqueCoin;                 // w21
        double *v12;                        // x0
        double v13;                         // d0 OVERLAPPED
        cocos2d::CCParticleSystemQuad *v14; // x0
        cocos2d::CCParticleSystemQuad *v15; // x22
        int v16;                            // s0
        int v22;                            // s0
        CCCircleWave *v23;                  // x22
        __int128 __dst;                     // [xsp+60h] [xbp-90h] BYREF
        __int64 v130;                     // x0
        CCCircleWave *v131;                 // x0
        __int64 v132;                     // x22
        int v133;                           // w8
        __int64 v134;                     // x0
        const char *v135;                   // x8
        GameObjectType v136;                // w9
        const char *v137;                   // x10
        const char *v138;                   // x23
        char *v139;                         // x0
        char *v140;                         // x20
        cocos2d::CCNode *v141;              // x21
        __int64 v142;                     // x0
        __int64 v143;                     // x0
        __int64 v144;                     // x0
        __int64 v211;                     // [xsp+70h] [xbp-80h]
        __int64 v212;                     // [xsp+78h] [xbp-78h] BYREF
        __int64 v213;                     // [xsp+80h] [xbp-70h] BYREF
        float v214;                         // xmm3_4
        float v215;                         // xmm2_4
        cocos2d::CCSprite *v216;            // rdx
        GameObject *v217;                   // rcx
        int v7;
        #endif


        if (this->m_objectType == GameObjectType::UserCoin) {
            hasUniqueCoin = p0->hasUniqueCoin((EffectGameObject *)this);
            auto v12     = this->getPosition();
            auto point = CCPoint(v12.x, v12.y);
            v14           = p0->spawnParticle("coinPickupEffect.plist", 0, kCCPositionTypeGrouped, point);
            if (this->m_objectType == GameObjectType::Collectible && v14) {
                /*
                v16   = v14->getStartColor().a;
                __dst = 0x3F8000003F800000LL;
                v6    = 1065353216;
                v14->setStartColor(ccc4f(__dst, __dst, __dst, v6));
                v22   = v14->getEndColor().a;
                __dst = 0x3F0000003F000000LL;
                v7    = 1056964608;
                v14->setEndColor(ccc4f(__dst, __dst, __dst, v7));
                */
            }
            v23             = CCCircleWave::create(25.0, 5.0, 0.3, 0, 0);
            v23->m_color.r  = -14136;
            v23->m_color.b  = -56;
            auto vSomething = this->getPosition();
            v23->setPosition(vSomething);
            p0->m_objectLayer->addChild(v23, 0);
            v131             = CCCircleWave::create(5.0, 60.0, 0.3, 0);
            if (this->m_objectType == GameObjectType::Collectible) {
                v131->m_color.r  = -14136;
                v131->m_color.b  = -56;
            }
            else {
                v131->m_color.r  = -14081;
                v131->m_color.b  = 0;
            }
            auto vAnotherOne = this->getPosition();
            v131->setPosition(vAnotherOne);
            p0->m_objectLayer->addChild(v131, 0);
            v131->m_circleMode = CircleMode::Outline;
            v131->m_lineWidth = 4;

            if (this->m_objectType == GameObjectType::Collectible) {
                v135 = "secretCoin_2_01_001.png";
                v137 = "secretCoin_2_b";
                v138 = "secretCoin_2";
            }
            else
            {
                v135 = "secretCoin_01_001.png";
                v137 = "secretCoin";
                v138 = "secretCoin_b";
            }

            if (!hasUniqueCoin)
                v138 = v137;

            auto wow   = cocos2d::CCSprite::createWithSpriteFrameName(v135);
            auto scale = this->getScaleX();
            wow->setScaleX(scale);
            v141 = this->m_pParent;
            if (v141) {
                auto defaultOrder = this->m_zOrder;
                if (!defaultOrder)
                    defaultOrder = this->m_defaultZOrder;
                v141->addChild(wow, defaultOrder);
            }
            auto again = this->getPosition();
            wow->setPosition(again);
            if (this->m_objectType == GameObjectType::Collectible) {
                auto color_but_with_a_u = this->getColor();
                wow->setColor(color_but_with_a_u);
            }
            auto v145 = cocos2d::CCArray::create();
            auto v146 = cocos2d::CCString::createWithFormat("%s_01_001.png", v138);
            auto v147 = v146->getCString();
            auto v149 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
            auto v150 = v149->spriteFrameByName(v147);
            v145->addObject(v150);
            auto v151 = cocos2d::CCString::createWithFormat("%s_01_002.png", v138);
            auto v152 = v151->getCString();
            auto v154 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
            auto v155 = v154->spriteFrameByName(v152);
            v145->addObject(v155);
            auto v156 = cocos2d::CCString::createWithFormat("%s_01_003.png", v138);
            auto v157 = v156->getCString();
            auto v159 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
            auto v160 = v159->spriteFrameByName(v157);
            v145->addObject(v160);
            auto v161 = cocos2d::CCString::createWithFormat("%s_01_004.png", v138);
            auto v162 = v161->getCString();
            auto v163 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
            auto v164 = v163->spriteFrameByName(v162);
            v145->addObject(v164);
            auto v165 = cocos2d::CCAnimation::createWithSpriteFrames(v145, 0.1);
            auto v166 = cocos2d::CCAnimate::create(v165);
            auto v167 = cocos2d::CCRepeatForever::create(v166);
            wow->runAction(v167);
            this->playPickupAnimation(wow, 1.0, 1.0, 0.0, 0.0);
            return;
        }
        else
            GameObject::playDestroyObjectAnim(p0);
    }
};

/*
// ~patches
// applies a patch that prevents the game from making the particles in coinEffect.plist silver
// it's somewhere in EnhancedGameObject::updateUserCoin
// first one makes it so (if (isCoin && objectID != 142) { ... }) never runs, 142 is secret coin ID
// second and third changes the coin pickup effect to not be silver for user coins (somewhere in GameObject::playDestroyObjectAnim)
#ifdef GEODE_IS_WINDOWS
$execute {
        Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x19c9e8), { 0x83 });
        Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1a14c1), { 0x74 }); // something 0xc8ffff
        Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1a154d), { 0x74 }); // something concat21 0xffff
    }
 #elif defined(GEODE_IS_ARM_MAC)
$execute {
        // applies a patch that prevents the game from making the particles in coinEffect.plist silver
        // it's somewhere in EnhancedGameObject::updateUserCoin
        // first one makes it so (if (isCoin && objectID != 142) { ... }) never runs, 142 is secret coin ID
        // second and third changes the coin pickup effect to not be silver for user coins
        Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4f95f8), { 0x83 });
        Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x2026a0), { 0x74 }); // something 0xc8ffff
        Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x202718), { 0x74 }); // something concat21 0xffff
}
#endif
// todo: android support. but that requires arm knowledge
*/
