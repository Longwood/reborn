#include "base/PauseState.h"


using namespace Ogre;

PauseState PauseState::mPauseState;

void PauseState::enter(void)
{
  mRoot            = Root::getSingletonPtr();
  mViewport        = mRoot->getAutoCreatedWindow()->getViewport(0);
  mExitGame = false;
}

void PauseState::exit(void)
{
  mInfoOverlay->hide();
  mPauseOverlay->hide();
}

void PauseState::pause(void)
{
  mInfoOverlay->hide();
  mPauseOverlay->hide();
}

void PauseState::resume(void)
{
}

bool PauseState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  return true;
}

bool PauseState::frameStarted(const FrameEvent& evt)
{
  return true;
}

bool PauseState::frameEnded(const FrameEvent& evt)
{
  return true;
}


void PauseState::keyPressed(const OIS::KeyEvent &e)
{
}

void PauseState::keyReleased(const OIS::KeyEvent &e)
{
  if(e.key == OIS::KC_PAUSE)
  {
    this->popState();
  }
}

void PauseState::mouseMoved(const OIS::MouseEvent &e)
{
  const OIS::MouseState &mouseState = e.state;
}

void PauseState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void PauseState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

