#include "base/PlayState.h"

//
#include "psapi.h"
#pragma comment( lib,"psapi.lib")


using namespace Ogre;

static Vector2  curtime;
static int    FPS;
static int    TringleCount;
static Vector3  currentPos;
static Vector3  PlayerDispVec;
static int    Playerhealth;
static int    npc2health;
static int    lightintense;
static Vector3  lightpos;
static Vector3  lightdir;
static Vector3  skelpos;

static SceneNode *target;

PlayState PlayState::mPlayState;

void PlayState::enter(void)
{
  LogManager::getSingletonPtr()->logMessage("********************************* PlayState::enter() *********************************");
  PROCESS_MEMORY_COUNTERS pmemory;
  GetProcessMemoryInfo(GetCurrentProcess(), &pmemory,
                       sizeof(PROCESS_MEMORY_COUNTERS));
  LogManager::getSingletonPtr()->logMessage("*************** Memory Usage play state enter " + StringConverter::toString(pmemory.WorkingSetSize / 1048575) + "mb");
  mRoot     = Root::getSingletonPtr();
  mSceneMgr = mRoot->createSceneManager(ST_GENERIC);
  mCamera = mSceneMgr->createCamera("Camera");
  mViewport = mRoot->getAutoCreatedWindow()->addViewport(mCamera);
  mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
  mSceneDetailIndex = 0;

  target = mSceneMgr->getRootSceneNode()->createChildSceneNode("target");
  Entity *dbox = mSceneMgr->createEntity("box", "Crate.mesh");
  target->attachObject(dbox);
  target->scale(50, 50, 50);
  mKeyPressed_UP = false;
  mKeyPressed_DOWN = false;
  mKeyPressed_LEFT = false;
  mKeyPressed_RIGHT = false;
  mKeyPressed_SHIFT = false;
  mKeyPressed_CTRL = false;
  mKeyPressed_ENTER = false;
  mKeyPressed_SPACE = false;
  mKeyPressed_LMOUSE = false;
  mKeyPressed_RMOUSE = false;





  mExitGame = false;
  return;
}

void PlayState::exit(void)
{

  return;
}

void PlayState::pause(void)
{
  return;
}

void PlayState::resume(void)
{
}

bool PlayState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  return true;
}

bool PlayState::frameStarted(const FrameEvent& evt)
{

  //и камеры
//  mPlayerCamera->update(evt.timeSinceLastFrame, mPlayer->getWorldPosition() + Vector3(0, 6, 0), mKeyPressed_UP);
  //обновление дебуг вывода
  FPS = mRoot->getAutoCreatedWindow()->getLastFPS();
  TringleCount = mRoot->getAutoCreatedWindow()->getTriangleCount();

  return true;
}

bool PlayState::frameEnded(const FrameEvent& evt)
{
  if(mExitGame)
  {
    return false;
  }

  return true;
}


void PlayState::keyPressed(const OIS::KeyEvent &e)
{
  using namespace OIS;

  switch(e.key)
  {
    case KC_UP:
    case KC_W:
      mKeyPressed_UP = true;
      keyHandler();
      break;
    case KC_DOWN:
    case KC_S:
      mKeyPressed_DOWN = true;
      keyHandler();
      break;
    case KC_LEFT:
    case KC_A:
      mKeyPressed_LEFT = true;
      keyHandler();
      break;
    case KC_RIGHT:
    case KC_D:
      mKeyPressed_RIGHT = true;
      keyHandler();
      break;
    case KC_LSHIFT:
    case KC_RSHIFT:
      mKeyPressed_SHIFT = true;
      keyHandler();
      break;
    case KC_LCONTROL:
    case KC_RCONTROL:
      mKeyPressed_CTRL = true;
      keyHandler();
      break;
    case KC_NUMPADENTER:
      mKeyPressed_ENTER = true;
      keyHandler();
      break;
    case KC_SPACE:
      mKeyPressed_SPACE = true;
      keyHandler();
      break;
    case KC_R:
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
  }

  return;
}

void PlayState::keyReleased(const OIS::KeyEvent &e)
{
  using namespace OIS;

  switch(e.key)
  {
    case KC_F1:

      if(mSceneMgr->getAmbientLight() != ColourValue(0.0, 0.0, 0.0))
      {
        mSceneMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0));
      }
      else
      {
        mSceneMgr->setAmbientLight(ColourValue(0.3, 0.3, 0.3));
      }

    case KC_UP:
    case KC_W:
      mKeyPressed_UP = false;
      keyHandler();
      break;
    case KC_DOWN:
    case KC_S:
      mKeyPressed_DOWN = false;
      keyHandler();
      break;
    case KC_LEFT:
    case KC_A:
      mKeyPressed_LEFT = false;
      keyHandler();
      break;
    case KC_RIGHT:
    case KC_D:
      mKeyPressed_RIGHT = false;
      keyHandler();
      break;
    case KC_LSHIFT:
    case KC_RSHIFT:
      mKeyPressed_SHIFT = false;
      keyHandler();
      break;
    case KC_LCONTROL:
    case KC_RCONTROL:
      mKeyPressed_CTRL = false;
      keyHandler();
      break;
    case KC_NUMPADENTER:
      mKeyPressed_ENTER = false;
      keyHandler();
      break;
    case KC_SPACE:
      mKeyPressed_SPACE = false;
      keyHandler();
      break;
    case KC_ESCAPE:
      changeState(IntroState::getInstance());
      break;
    case KC_PAUSE:
      pushState(PauseState::getInstance());
      break;
    case KC_T:
      break;
    case KC_Y:
      break;
    case KC_U:
      break;
    case KC_I:
      break;
    case KC_G:
      break;
    case KC_H:
      break;
    case KC_J:
      //    mGuiMgr->closeIngameMenu();
      break;
    case KC_K:
      break;
  }

  return;
}

void PlayState::mouseMoved(const OIS::MouseEvent &e)
{
  using namespace OIS;
  //задаём углы для камеры
  mPlayerCamera->setAngles(e.state.X.rel, e.state.Y.rel);
  mPlayerCamera->setRadius(-e.state.Z.rel);
  //  }
}

void PlayState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  return;
}

void PlayState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  return;
}

void PlayState::keyHandler()
{
  return;
}

void PlayState::createScene()
{

  //теран физика и плэер
  mViewport->setBackgroundColour(ColourValue(0.5, 0.5, 0.5));
  mSceneMgr->setAmbientLight(ColourValue(0.4, 0.4, 0.4));

  mCamera->setNearClipDistance(0.5f);  //если сделать меньше почемуто глючит тест глубины
  mCamera->setFarClipDistance(100000);


  Light* L = mSceneMgr->createLight("Light1");
  L->setPosition(Vector3(3133.07, 1436.233, -4350.63));
  L->setType(Light::LT_DIRECTIONAL);
  L->setDiffuseColour(1, 1, 1);
  L->setSpecularColour(1, 1, 1);
  L->setCastShadows(true);
  L->setShadowFarDistance(2000);
  L->setDirection(Vector3(1, -1, 0));


  mPlayerCamera = new ExtendedCamera("PlayerCamera", mSceneMgr, mCamera, Vector3(0, 0, 0));

}

