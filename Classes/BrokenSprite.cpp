//
//  BrokenSpritecpp
//  Tools
//
//  Created by apple on 16/11/5.
//
//

#include "BrokenSprite.h"



USING_NS_CC;


namespace YXTools {
    
    
    BrokenSprite * BrokenSprite::create(std::string filename)
    {
        BrokenSprite * broken = new (std::nothrow) BrokenSprite();
        if (broken && broken->init(filename)) {
            broken->autorelease();
            return broken;
        }
        
        CC_SAFE_DELETE(broken);
        return nullptr;
    }
    
    BrokenSprite * BrokenSprite::create(int fragment, std::string filename)
    {
        BrokenSprite * broken = new (std::nothrow) BrokenSprite();
        if (broken && broken->init(fragment, filename)) {
            broken->autorelease();
            return broken;
        }
        
        CC_SAFE_DELETE(broken);
        return nullptr;
    }
    
    
    bool BrokenSprite::init(std::string filename)
    {
        _sprite = Sprite::create(filename);
        this->addChild(_sprite);
        
        _brokenScale = 1.0f;
        _fragmentNumber = 0;
        
        return (_sprite != nullptr);
    }
    
    bool BrokenSprite::init(int flagment, std::string filename)
    {
        bool ret = init(filename);
        
        setFragment(flagment);
        
        return ret;
    }
    
    
    void BrokenSprite::setFragment(int fragment)
    {
        if (_fragmentNumber == fragment) {
            return;
        }
        
        CCASSERT(fragment >= 5, "framgent must more than 5");
        
        _fragmentNumber = fragment;
        
        
        bool isDouble = (fragment%2==0);
        if (!isDouble) {
            fragment ++;
        }
        
        int pointLength = (6+fragment)/2;
        std::vector<V2F_C4B_T2F_Triangle>               triangles;

        Size textureSize = _sprite->getTexture()->getContentSize();
        
        V2F_C4B_T2F firstPoint[5];
        firstPoint[0].vertices = Vec2(0, 0);
        firstPoint[1].vertices = Vec2(0, textureSize.height);
        firstPoint[2].vertices = Vec2(textureSize.width, 0);
        firstPoint[3].vertices = Vec2(textureSize.width, textureSize.height);
        firstPoint[4].vertices = Vec2(random(0.0f, textureSize.width), random(0.0f, textureSize.height));
        
        firstPoint[0].colors = Color4B::WHITE;
        firstPoint[1].colors = Color4B::WHITE;
        firstPoint[2].colors = Color4B::WHITE;
        firstPoint[3].colors = Color4B::WHITE;
        firstPoint[4].colors = Color4B::WHITE;
        
        firstPoint[0].texCoords = Tex2F(0, 1);
        firstPoint[1].texCoords = Tex2F(0, 0);
        firstPoint[2].texCoords = Tex2F(1, 1);
        firstPoint[3].texCoords = Tex2F(1, 0);
        firstPoint[4].texCoords = Tex2F(firstPoint[4].vertices.x/textureSize.width, 1-firstPoint[4].vertices.y/textureSize.height);
        
        triangles.push_back({firstPoint[0], firstPoint[1], firstPoint[4]});
        triangles.push_back({firstPoint[0], firstPoint[2], firstPoint[4]});
        triangles.push_back({firstPoint[1], firstPoint[3], firstPoint[4]});
        triangles.push_back({firstPoint[2], firstPoint[3], firstPoint[4]});
        
        for (int i = 5; i<pointLength; ++i)
        {
            if (i == pointLength-1 && !isDouble)
            {
                break;
            }
            do
            {
                
                V2F_C4B_T2F p, a, b, c;
                p.vertices = Vec2(random(0.0f, textureSize.width), random(0.0f, textureSize.height));
                
                std::vector<V2F_C4B_T2F_Triangle>::iterator itera;
                
                for (itera = triangles.begin(); itera != triangles.end(); ++itera) {
                    
                    a = (*itera).a;
                    b = (*itera).b;
                    c = (*itera).c;
                    
                    if (isTriangleContainPoint((*itera), p))
                    {
                        itera = triangles.erase(itera);

                        p.texCoords = Tex2F(p.vertices.x/textureSize.width, 1-p.vertices.y/textureSize.height);
                        p.colors = Color4B::WHITE;
                        
                        triangles.push_back(V2F_C4B_T2F_Triangle{p, b, c});
                        
                        triangles.push_back(V2F_C4B_T2F_Triangle{p, b, a});
                        
                        triangles.push_back(V2F_C4B_T2F_Triangle{p, a, c});
                        break;
                    }
                }
                
                if (itera != triangles.end()) {
                    break;
                }
                
            }while(1);
        }

        setSpritePolygonInfoByTriangleVector(triangles);
    }
    
    void BrokenSprite::setSpritePolygonInfoByTriangleVector(std::vector<V2F_C4B_T2F_Triangle> triangles)
    {
        _triangles = triangles;

        Size textureSize = _sprite->getTexture()->getContentSize();
        
        PolygonInfo info;
        
        info.triangles.verts = (V3F_C4B_T2F *)malloc(triangles.size()*sizeof(V3F_C4B_T2F)*3);
        info.triangles.indices = (unsigned short *)malloc(triangles.size()*3*sizeof(unsigned short));
        info.triangles.vertCount = triangles.size()*3;
        info.triangles.indexCount = triangles.size()*3;
        
        for (int i = 0; i<triangles.size(); ++i) {
            
            transformBrokenTriangle(triangles[i], textureSize, _brokenScale);
            
            info.triangles.verts[i*3].texCoords = triangles[i].a.texCoords;
            info.triangles.verts[i*3].vertices = Vec3(triangles[i].a.vertices.x, triangles[i].a.vertices.y, 0);
            info.triangles.verts[i*3].colors = Color4B::WHITE;
            info.triangles.indices[i*3] = i*3;
            
            info.triangles.verts[i*3+1].texCoords = triangles[i].b.texCoords;
            info.triangles.verts[i*3+1].vertices = Vec3(triangles[i].b.vertices.x, triangles[i].b.vertices.y, 0);
            info.triangles.verts[i*3+1].colors = Color4B::WHITE;
            info.triangles.indices[i*3+1] = i*3+1;
            
            info.triangles.verts[i*3+2].texCoords = triangles[i].c.texCoords;
            info.triangles.verts[i*3+2].vertices = Vec3(triangles[i].c.vertices.x, triangles[i].c.vertices.y, 0);
            info.triangles.verts[i*3+2].colors = Color4B::WHITE;
            info.triangles.indices[i*3+2] = i*3+2;
        }
        
        _sprite->setPolygonInfo(info);
        
        CC_SAFE_FREE(info.triangles.indices);
        CC_SAFE_FREE(info.triangles.verts);
    }
    
    void BrokenSprite::setBrokenScale(float scale)
    {
        CCASSERT(_fragmentNumber > 0, "must use setFragment function first");
        
        if (_brokenScale != scale){
            
            _brokenScale = scale;
            
            Size textureSize = _sprite->getTexture()->getContentSize();

            for (int i = 0; i<_triangles.size(); ++i) {
                transformBrokenTriangle(_triangles[i], textureSize, _brokenScale);
            }
            
            setSpritePolygonInfoByTriangleVector(_triangles);
        }
    }
    
    bool BrokenSprite::isTriangleContainPoint(cocos2d::V2F_C4B_T2F_Triangle triangle, V2F_C4B_T2F p)
    {
        Vec2 ab = triangle.b.vertices-triangle.a.vertices;
        Vec2 bc = triangle.c.vertices-triangle.b.vertices;
        Vec2 ca = triangle.a.vertices-triangle.c.vertices;
        
        Vec2 pa = triangle.a.vertices-p.vertices;
        Vec2 pb = triangle.b.vertices-p.vertices;
        Vec2 pc = triangle.c.vertices-p.vertices;
        
        if ((ab.x*bc.y-ab.y*bc.x) * (pb.x*bc.y-pb.y*bc.x) > 0 &&
            (bc.x*ca.y-bc.y*ca.x) * (pc.x*ca.y-pc.y*ca.x) > 0 &&
            (ca.x*ab.y-ca.y*ab.x) * (pa.x*ab.y-pa.y*ab.x) > 0 )
        {
            return true;
        }
        return false;
    }
        
    void BrokenSprite::transformBrokenTriangle(cocos2d::V2F_C4B_T2F_Triangle &triangle, cocos2d::Size textureSize, float distancScale)
    {
        Vec2 centerPoint = (triangle.a.vertices+triangle.b.vertices+triangle.c.vertices)/3;
        
        if (centerPoint.x - textureSize.width/2 != 0) {
            
            float xDist = centerPoint.x*distancScale-centerPoint.x;
            
            triangle.a.vertices.x += xDist;
            triangle.b.vertices.x += xDist;
            triangle.c.vertices.x += xDist;
        }
        if (centerPoint.y - textureSize.height/2 != 0) {
            
            float yDist = centerPoint.y*distancScale-centerPoint.y;

            triangle.a.vertices.y += yDist;
            triangle.b.vertices.y += yDist;
            triangle.c.vertices.y += yDist;
        }
    }
    
    
    const Size& BrokenSprite::getContentSize() const
    {
        return _sprite->getContentSize();
    }
    
    
    
    
    
    
    
    
    BrokenBangAction * BrokenBangAction::create(float duration, float speed)
    {
        return BrokenBangAction::create(duration, speed, 0);
    }
    
    BrokenBangAction * BrokenBangAction::create(float duration, float speed, float accelerated)
    {
        BrokenBangAction * broken = new BrokenBangAction();
        if (broken && broken->init(duration, speed, accelerated)) {
            broken->autorelease();
            return broken;
        }
        
        CC_SAFE_DELETE(broken);
        return nullptr;
    }
    
    
    bool BrokenBangAction::init(float duration, float speed, float accelerated)
    {
        if (!ActionInterval::initWithDuration(duration)) {
            return false;
        }
        
        _speed = speed;
        _accelerated = accelerated;
        _lastUpdateTime = 0;
        
        return true;
    }
    
    void BrokenBangAction::update(float time)
    {
        float dt = time - _lastUpdateTime;
        BrokenSprite * brokenSprite = static_cast<BrokenSprite *>(_target);
        std::vector<V2F_C4B_T2F_Triangle> triangles = brokenSprite->getSpritePolygonInfoByTriangleVector();
        Size contentSize = brokenSprite->getContentSize();
        
        float moveDistance = dt*_speed;
        
        for (int i = 0; i<triangles.size(); ++i) {
            
            Vec2 center = (triangles[i].a.vertices+triangles[i].b.vertices+triangles[i].c.vertices)/3;
            Vec2 v = center-Vec2(contentSize/2);
            
            float d = v.distance(Vec2());
            
            float distX = 0;
            if (v.x != 0) {
                distX = v.x/d*moveDistance;
            }
            
            float distY = 0;
            if (v.y != 0 ) {
                distY = v.y/d*moveDistance;
            }
            
            V2F_C4B_T2F *tri = (V2F_C4B_T2F *)&triangles[i];
            for (int j = 0; j<3; ++j) {
                tri[j].vertices.x += distX;
                tri[j].vertices.y += distY;
            }
        }
        
        brokenSprite->setSpritePolygonInfoByTriangleVector(triangles);
        
        _speed += _accelerated;
        _lastUpdateTime = time;
    }
    
    void BrokenBangAction::startWithTarget(cocos2d::Node *target)
    {
        ActionInterval::startWithTarget(target);

        BrokenSprite * broken = dynamic_cast<BrokenSprite *>(target);
        CCASSERT(broken, "target must be BrokenSprite");
    }
    
    BrokenBangAction * BrokenBangAction::clone() const
    {
        BrokenBangAction * broken = new BrokenBangAction();
        broken->init(_duration, _speed, _accelerated);
        return broken;
    }
    
    BrokenBangAction * BrokenBangAction::reverse() const
    {
        return BrokenBangAction::create(_duration, -_speed, _accelerated);
    }
}

