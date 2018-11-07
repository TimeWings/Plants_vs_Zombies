//
//  BrokenSprite.hpp
//  Tools
//
//  Created by apple on 16/11/5.
//
//

#ifndef BrokenSprite_hpp
#define BrokenSprite_hpp

#include <stdio.h>
#include "cocos2d.h"


namespace YXTools {

    USING_NS_CC;
    
    class BrokenSprite: public Node  {
        
        
    public:
        
                
        
        static BrokenSprite * create(std::string filename);
        
        static BrokenSprite * create(int fragment, std::string filename);
        
        
        
        bool init(std::string filename);
        
        bool init(int flagment, std::string filename);
        
        void setFragment(int fragment);
        
        int getFragment()           { return _fragmentNumber; }
        
        void setSpritePolygonInfoByTriangleVector(std::vector<V2F_C4B_T2F_Triangle> triangles);
        std::vector<V2F_C4B_T2F_Triangle>& getSpritePolygonInfoByTriangleVector() { return _triangles; }
        
        void setBrokenScale(float scale);
        float getBrokenScale()                      { return _brokenScale; }
        
        
        
        virtual const Size& getContentSize() const;

        
        
        void startBang(float speed, float time);
        
        
    protected:
        
        bool isTriangleContainPoint(V2F_C4B_T2F_Triangle triangle, V2F_C4B_T2F point);
        
        void transformBrokenTriangle(V2F_C4B_T2F_Triangle &triangle, Size textureSize, float distancScale);
        
        
        
        Sprite *                                        _sprite;
        
        std::vector<V2F_C4B_T2F_Triangle>               _triangles;
        
        
        bool                                            _triangleDirty;
        int                                             _fragmentNumber;
        
        
        float                                           _brokenScale;
        
        
        float                                           _bangSpeed;
        
        
    private:
        
        
        
    };
    
    
    
    class BrokenBangAction : public ActionInterval
    {
        
    public:
        
        
        static BrokenBangAction* create(float duration, float speed);
        static BrokenBangAction* create(float duration, float speed, float accelerated);
        
        
        
        
        virtual BrokenBangAction* clone() const override;
        virtual BrokenBangAction* reverse(void) const  override;
        virtual void startWithTarget(Node *target) override;
        
        
        virtual void update(float time) override;
        
        
        
        bool init(float duration, float speed, float accelerated);
        
        
    protected:
        
        float _speed;
        float _accelerated;
        float _lastUpdateTime;
    };

}




#endif /* BrokenSprite_hpp */
