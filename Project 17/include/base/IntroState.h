#pragma once

#include <Ogre.h>
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>

#include "myOgreSdk.h"
#include "OgreCharacterController.h"

#include "base/GameManager.h"
#include "base/GameState.h"
#include "base/PauseState.h"
#include "base/PlayState.h"
#include "base/IntroState.h"

#include "ExtendedCamera.h"

#include "TerrainManager.h"

#include "SkyManager.h"

#include "SceneLoader.h"

#include "SharedData.h"

using namespace Ogre;

class IntroState : public GameState, public RenderTargetListener
{
  public:
    void enter();
    void exit();

    void pause();
    void resume();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    bool frameStarted(const Ogre::FrameEvent& evt);
    bool frameEnded(const Ogre::FrameEvent& evt);

    void keyPressed(const OIS::KeyEvent &e);
    void keyReleased(const OIS::KeyEvent &e);

    void mouseMoved(const OIS::MouseEvent &e);
    void mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	
    static IntroState* getInstance()
    {
      return &mIntroState;
    }

    Ogre::String model;
  protected:
    IntroState() { }

    Ogre::Root *mRoot;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Viewport* mViewport;
    Ogre::Camera* mCamera;
	
	ExtendedCamera *ExtCamera;

	myOgreSdk		*myOgSdk;
	SinbadCharacterController	*Char;

	SkyManager      *Sky;
	MyTerrain		*Terrain;

	Ogre::OverlaySystem  *mOverlaySystem;
    Ogre::OverlayManager *mOverlayMgr;
    Ogre::Overlay        *mIntroOverlay;
    Ogre::Overlay        *mMouseOverlay;
    Ogre::OverlayElement *mMousePointer;

    Ogre::SceneNode   *fNode;
    Ogre::Light		  *omni_light;
    int SelPos;
	int mSceneDetailIndex;

    bool mExitGame;
  private:
    static IntroState mIntroState;
};
