#pragma once

#include <Ogre.h>
#include <vector>

#include "base/GameManager.h"
#include "base/GameState.h"
#include "base/PauseState.h"
#include "base/IntroState.h"
#include "base/InputManager.h"


#include "ExtendedCamera.h"



class PlayState : public GameState
{

  public:
    ~PlayState(void) {}

    void enter(void);
    void exit(void);

    void pause(void);
    void resume(void);

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    bool frameStarted(const Ogre::FrameEvent& evt);
    bool frameEnded(const Ogre::FrameEvent& evt);

    void keyPressed(const OIS::KeyEvent &e);
    void keyReleased(const OIS::KeyEvent &e);

    void mouseMoved(const OIS::MouseEvent &e);
    void mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

    static PlayState* getInstance()
    {
      return &mPlayState;
    }

  private:

    PlayState(void) { }

    Ogre::Root           *mRoot;
    Ogre::SceneManager   *mSceneMgr;
    Ogre::Viewport       *mViewport;
	Ogre::Camera		 *mCamera;
	ExtendedCamera		 *mPlayerCamera;


    static PlayState     mPlayState;

    bool mExitGame;

  protected:
	void createScene();






    //флаг для переключения верфрейма
    int mSceneDetailIndex;

    //переменные для отслеживания нажатий клавиш
    bool mKeyPressed_UP;
    bool mKeyPressed_DOWN;
    bool mKeyPressed_LEFT;
    bool mKeyPressed_RIGHT;
    bool mKeyPressed_SHIFT;
    bool mKeyPressed_CTRL;
    bool mKeyPressed_ENTER;
    bool mKeyPressed_SPACE;
    bool mKeyPressed_LMOUSE;
    bool mKeyPressed_RMOUSE;

    void keyHandler();
};