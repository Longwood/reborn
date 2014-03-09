
#include "base/IntroState.h"

using namespace Ogre;

IntroState IntroState::mIntroState;

void IntroState::enter()
{
  LogManager::getSingletonPtr()->logMessage("********************************* IntroState::enter() *********************************");
  mRoot         = Root::getSingletonPtr();
  mSceneMgr     = mRoot->createSceneManager(ST_GENERIC);
  mCamera       = mSceneMgr->createCamera("IntroCamera");
  mViewport     = mRoot->getAutoCreatedWindow()->addViewport(mCamera);
  mSceneDetailIndex = 1;
  SelPos = 0;
  Ogre::TextureManager::getSingleton().reloadAll();
 
  //буквы меню
  Entity *ent0 = mSceneMgr->createEntity("MenuContinue", "menu_continue.mesh");
  Entity *ent1 = mSceneMgr->createEntity("MenuNew", "menu_new.mesh");
  Entity *ent2 = mSceneMgr->createEntity("MenuBattle", "menu_battle.mesh");
  Entity *ent3 = mSceneMgr->createEntity("MenuExit", "menu_exit.mesh");
  ent0->setMaterialName("Menu/Text");
  ent0->setCastShadows(true);
  ent1->setMaterialName("Menu/Text");
  ent1->setCastShadows(true);
  ent2->setMaterialName("Menu/Text");
  ent2->setCastShadows(true);
  ent3->setMaterialName("Menu/Text");
  ent3->setCastShadows(true);
  SceneNode *node0 =  mSceneMgr->createSceneNode();
  SceneNode *node1 =  mSceneMgr->createSceneNode();
  SceneNode *node2 =  mSceneMgr->createSceneNode();
  SceneNode *node3 =  mSceneMgr->createSceneNode();
  node0->attachObject(ent0);
  node1->attachObject(ent1);
  node2->attachObject(ent2);
  node3->attachObject(ent3);
  node0->scale(Vector3(0.08, 0.08, 0.08));
  node1->scale(Vector3(0.08, 0.08, 0.08));
  node2->scale(Vector3(0.08, 0.08, 0.08));
  node3->scale(Vector3(0.08, 0.08, 0.08));
  node0->pitch(Degree(90));
  node1->pitch(Degree(90));
  node2->pitch(Degree(90));
  node3->pitch(Degree(90));
  mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
  mSceneMgr->addRenderQueueListener( mOverlaySystem);
  mOverlayMgr = OGRE_NEW Ogre::OverlayManager();
  mIntroOverlay = mOverlayMgr->create("IntroOverlay");
  mIntroOverlay->add3D(node0);
  mIntroOverlay->add3D(node1);
  mIntroOverlay->add3D(node2);
  mIntroOverlay->add3D(node3);
  node0->setPosition(0, 15, -90);
  node1->setPosition(0, 5, -90);
  node2->setPosition(0, -5, -90);
  node3->setPosition(0, -15, -90);
  mIntroOverlay->show();
  mIntroOverlay->setZOrder(0);

  Entity* ePointer = mSceneMgr->createEntity("pointer", "ogrehead.mesh");
  ePointer->setMaterialName("Examples/RustySteel");
  fNode =  mSceneMgr->createSceneNode();
  fNode->attachObject(ePointer);

  Entity *knife = mSceneMgr->createEntity("gun_knife", "gun_knife.mesh");
  knife->setMaterialName("gun_knife");
  knife->setCastShadows(true);
  SceneNode *knifeNode =  mSceneMgr->createSceneNode();
  knifeNode->attachObject(knife);
  knifeNode->setPosition( 0,0,0);

 
  //камера
  mCamera->setPosition(0, 0, 100);
  mCamera->setNearClipDistance(0.1);
  mCamera->lookAt(node2->getPosition());

  mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5));

   // Skybox
   mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");

  //курсор. отображаем и помещаем в центр экрана
  mMouseOverlay->show();
  mExitGame = false;
  LogManager::getSingletonPtr()->logMessage("********************************* IntroState::enter() DONE!! *********************************");
}

void IntroState::exit()
{
	OGRE_DELETE mOverlaySystem;

  mSceneMgr->clearScene();
  mSceneMgr->destroyAllCameras();
  mRoot->getAutoCreatedWindow()->removeAllViewports();
  TextureManager::getSingleton().destroyAllResourcePools();
  TextureManager::getSingleton().unloadAll();
  MeshManager::getSingleton().destroyAllResourcePools();
  MeshManager::getSingleton().unloadAll();
  MaterialManager::getSingleton().destroyAllResourcePools();
  MaterialManager::getSingleton().unloadAll();
  mRoot = nullptr;
  mSceneMgr->~SceneManager();

}

void IntroState::pause()
{
}

void IntroState::resume()
{
  mMouseOverlay->show();
  mIntroOverlay->show();
}

bool IntroState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

  return true;
}
bool IntroState::frameStarted(const FrameEvent& evt)
{
  switch(SelPos)
  {
    case(0):
		 fNode->setPosition(0, 15, -100);
      break;
    case(1):
		 fNode->setPosition(0, 5, -100);
      break;
    case(2):
		 fNode->setPosition(0, -5, -100);
      break;
    case(3):
	     fNode->setPosition(0, -15, -100);
      break;
    default:
      break;
  }
  return true;
}

bool IntroState::frameEnded(const FrameEvent& evt)
{
  if(mExitGame)
  {
    return false;
  }

  return true;
}

void IntroState::keyPressed(const OIS::KeyEvent &e)
{
  if(e.key == OIS::KC_UP)
  {
    SelPos = SelPos - 1;

    if(SelPos < 0)
    {
      SelPos = 3;
    }
  }

  if(e.key == OIS::KC_DOWN)
  {
    SelPos = SelPos + 1;

    if(SelPos > 3)
    {
      SelPos = 0;
    }
  }

  if(e.key == OIS::KC_RETURN)
    switch(SelPos)
    {
      case(0):
        this->changeState(PlayState::getInstance());
        break;
      case(1):
        this->changeState(PlayState::getInstance());
        break;
      case(2):
        break;
      case(3):
        mExitGame = true;
        break;
      default:
        break;
    }

  if(e.key==OIS::KC_R)
      mSceneDetailIndex = (mSceneDetailIndex + 1) % 3 ;
      switch(mSceneDetailIndex)
      {
        case 0 :
          mCamera->setPolygonMode(PM_SOLID);
          break;
        case 1 :
          mCamera->setPolygonMode(PM_WIREFRAME);
          break;
        case 2 :
          mCamera->setPolygonMode(PM_POINTS);
          break;
          break;
      }

  if(e.key == OIS::KC_ESCAPE)
  {
    mExitGame = true;
  }
}

void IntroState::keyReleased(const OIS::KeyEvent &e)
{
}

void IntroState::mouseMoved(const OIS::MouseEvent &e)
{
}

void IntroState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void IntroState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}
