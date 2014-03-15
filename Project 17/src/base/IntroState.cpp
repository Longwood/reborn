
#include "base/IntroState.h"

#include "psapi.h"
#pragma comment( lib,"psapi.lib")

using namespace Ogre;
using namespace mySharedData;

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
//  Ogre::TextureManager::getSingleton().reloadAll();


  Light* introLight= mSceneMgr->createLight("Light1");
  introLight->setPosition(Vector3( 100, 100, 100));
  introLight->setDirection(Vector3(-100,-100,-100));
  introLight->setType(Ogre::Light::LT_DIRECTIONAL);
  introLight->setDiffuseColour( ColourValue(1,1,1));
  introLight->setSpecularColour( ColourValue(1,1,1));
  introLight->setCastShadows(true);
  //буквы меню
  /*
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
  node3->pitch(Degree(90));*/
  /*
  //sky
  Sky = new SkyManager(mSceneMgr, mCamera);
    LogManager::getSingletonPtr()->logMessage("********************************* SkyManager *********************************");
  Sky->VolumeCloudsCreate();
    LogManager::getSingletonPtr()->logMessage("********************************* VolumeCloudsCreate *********************************");
  Sky->SimpleCloudsCreate();
    LogManager::getSingletonPtr()->logMessage("********************************* SimpleCloudsCreate *********************************");
  Sky->initSkyXManager();
    LogManager::getSingletonPtr()->logMessage("********************************* initSkyXManager *********************************");
  Sky->getSkyXSystem()->setTimeMultiplier(0.1);
//  Sky->setLightingModeHDR();
  Sky->setCurrentTime(Vector3(8, 6, 14));
  */
// mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
//  mSceneMgr->addRenderQueueListener( mOverlaySystem);
//  mOverlayMgr = OGRE_NEW Ogre::OverlayManager();
//  mIntroOverlay = mOverlayMgr->create("IntroOverlay");
//  mMouseOverlay     = mOverlayMgr->getByName("Overlay/MousePointer");
//  mMousePointer     = mOverlayMgr->getOverlayElement("MousePointer/Pointer");
//  mIntroOverlay->add3D(node0);
//  mIntroOverlay->add3D(node1);
//  mIntroOverlay->add3D(node2);
//  mIntroOverlay->add3D(node3);
//  node0->setPosition(0, 15, -90);
//  node1->setPosition(0, 5, -90);
//  node2->setPosition(0, -5, -90);
//  node3->setPosition(0, -15, -90);
//  mIntroOverlay->show();
//  mIntroOverlay->setZOrder(0);
  /*
  Entity* ePointer = mSceneMgr->createEntity("pointer", "ogrehead.mesh");
  ePointer->setMaterialName("Examples/RustySteel");
  fNode =  mSceneMgr->createSceneNode("h");
  mSceneMgr->getRootSceneNode()->addChild(fNode);
  fNode->attachObject(ePointer);
  fNode->setPosition(0,0,0);
  */
/*
  mSceneMgr->createSceneNode("gun_knife");
  mSceneMgr->getRootSceneNode()->addChild(mSceneMgr->getSceneNode("gun_knife"));
  mSceneMgr->getSceneNode("gun_knife")->attachObject(mSceneMgr->createEntity("gun_knife", "gun_knife.mesh"));
  mSceneMgr->getSceneNode("gun_knife")->setScale(0.3,0.3,0.3);
  */
  Entity* crate = mSceneMgr->createEntity("crate", "crate.mesh");
  crate->setMaterialName("myMaterial");
  mSceneMgr->createSceneNode("crate");
  mSceneMgr->getRootSceneNode()->addChild(mSceneMgr->getSceneNode("crate"));
  mSceneMgr->getSceneNode("crate")->attachObject( crate);;
  mSceneMgr->getSceneNode("crate")->setScale(30,30,30);
  mSceneMgr->createLight("l1");



//  myOgSdk = new myOgreSdk();
// mSceneMgr->addListener(myOgSdk);

	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5));
	mViewport->setBackgroundColour( ColourValue( 1,0,0));
	
	/*
	mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);
	mSceneMgr->setShadowColour(ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTextureSize(1024);
	mSceneMgr->setShadowTextureCount(1);
	*/

	// create a floor mesh resource
/*		MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, -30), 1000, 1000, 10, 10, true, 1, 8, 8, Vector3::UNIT_Z);

		// create a floor entity, give it a material, and place it at the origin
        Entity* floor = mSceneMgr->createEntity("Floor", "floor");
        floor->setMaterialName("Examples/BumpyMetal");
        mSceneMgr->getRootSceneNode()->attachObject(floor);

		// create an ogre head entity and place it at the origin
        mSceneMgr->getRootSceneNode()->attachObject(mSceneMgr->createEntity("Head", "ogrehead.mesh"));*/

				// create a floor mesh resource
		MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);
		mSceneMgr->setSkyDome(true, "Examples/CloudySky",10, 10);
		 Entity* floor = mSceneMgr->createEntity("Floor", "floor");
        floor->setMaterialName("Examples/Rockwall");
		floor->setCastShadows(false);
        mSceneMgr->getRootSceneNode()->attachObject(floor);

	Char = new SinbadCharacterController(mCamera);

//  Terrain = new MyTerrain( mSceneMgr, "terrain");

//  Terrain = new MyTerrain( mSceneMgr, introLight);

//  ExtCamera = new ExtendedCamera("ExtCamera", mSceneMgr, mCamera);

	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(0);

  PROCESS_MEMORY_COUNTERS pmemory;
  GetProcessMemoryInfo(GetCurrentProcess(), &pmemory, sizeof(PROCESS_MEMORY_COUNTERS));
  LogManager::getSingletonPtr()->logMessage("*************** Memory Usage before ogscene loader" + StringConverter::toString(pmemory.WorkingSetSize / 1048575) + "mb");
  ogSceneLoader *ogscn = new ogSceneLoader(mSceneMgr, mRoot->getAutoCreatedWindow());
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmemory, sizeof(PROCESS_MEMORY_COUNTERS));
  LogManager::getSingletonPtr()->logMessage("*************** Memory Usage after ogscene loader" + StringConverter::toString(pmemory.WorkingSetSize / 1048575) + "mb");
  //курсор. отображаем и помещаем в центр экрана
//  mMouseOverlay->show();
  mExitGame = false;
  LogManager::getSingletonPtr()->logMessage("********************************* IntroState::enter() DONE!! *********************************");
}

void IntroState::exit()
{
  OGRE_DELETE mOverlaySystem;
 // Sky->~SkyManager();
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
	Char->addTime(evt.timeSinceLastFrame);
    return true;
}
bool IntroState::frameStarted(const FrameEvent& evt)
{
      if(mTerrainGroup)
      {
        mTerrainGroup->update();
      }
//	Terrain->update(evt.timeSinceLastFrame);
	Char->addTime(evt.timeSinceLastFrame);
//	ExtCamera->update(evt.timeSinceLastFrame,  mSceneMgr->getSceneNode("crate")->getPosition(), false);
//	Sky->update(evt.timeSinceLastFrame);
	/*
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
  }*/
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

  Char->injectKeyDown(e);

  if(e.key == OIS::KC_LEFT)
  {
	  mCamera->setOrientation( mCamera->getOrientation()+ Quaternion(0, 1, 0,0));  
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
  if(e.key == OIS::KC_E)
  {
  }

  if(e.key == OIS::KC_ESCAPE)
  {
    mExitGame = true;
  }
}

void IntroState::keyReleased(const OIS::KeyEvent &e)
{
	Char->injectKeyUp(e);
}

void IntroState::mouseMoved(const OIS::MouseEvent &e)
{
//	ExtCamera->setAngles(e.state.X.rel, e.state.Y.rel);
//	ExtCamera->setRadius(-e.state.Z.rel);
	Char->injectMouseMove(e);
}

void IntroState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	Char->injectMouseDown(e, id);
}

void IntroState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}
