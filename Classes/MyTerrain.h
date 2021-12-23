#ifndef __Prefix__MyTerrain__
#define __Prefix__MyTerrain__

#include "cocos2d.h"
#include "Block.h"
#include "Player.h"

USING_NS_CC;
using namespace std;


class MyTerrain : public Sprite {
    
    Vector<Block *> _blockPool;
	int _blockPoolIndex;
	
    Vector<Block *> _blocks;
	int _lastBlockHeight;
    int _lastBlockWidth;
	int _minTerrainWidth;
    
    bool _showGap;
    Size _screenSize;
    
    int _currentPatternIndex;
    int _currentPatternCnt;
    int _currentWidthIndex;
    int _currentHeightIndex;
    int _currentTypeIndex;
    
    int _increaseGapInterval;
    float _increaseGapTimer;
    int _gapSize;
    
    void initMyTerrain(void);
    void addBlocks(int currentWidth);
	
    void distributeBlocks();
    void initBlock(Block * block);
    
    inline int getWidth () {
        
        int width = 0;
        for (auto block : _blocks) {
            width += block->getWidth();
        }
        return width;
    }
    
		
public:
	
	MyTerrain(void);
	virtual ~MyTerrain(void);
	
	CC_SYNTHESIZE(bool, _startTerrain, StartTerrain);
	
    static MyTerrain * create();
    
	void activateChimneysAt (Player * player);
    void checkCollision (Player * player);
	
	void move (float xMove);
    void reset (void);
	
};
     

#endif // __Prefix__MyTerrain__
