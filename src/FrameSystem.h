
#pragma once

#include "Common.h"

extern void Main(const C35::StrVec&);

namespace sf
{
class Event;
class RenderWindow;
}

namespace C35
{
class UpdateTarget
{
	public:
	virtual ~UpdateTarget()  = default;
	virtual void Update(int) = 0;
	virtual bool Done() =0;//{ return false; }
};

class InputTarget
{
	public:
	virtual ~InputTarget()              = default;
	virtual bool ParseInput(sf::Event&) = 0;
	virtual bool Done() =0;//{ return false; }
};

class Frame;

typedef std::shared_ptr<Frame>        FramePtr;
typedef std::shared_ptr<UpdateTarget> UpdatePtr;
typedef std::shared_ptr<InputTarget>  InputPtr;

class Frame : public UpdateTarget, InputTarget
{
public:
	virtual void Display(sf::RenderWindow&) = 0;
	virtual bool Done() = 0;

	static void PushUnder(FramePtr);
	static void Push(FramePtr);

	static void Modal(FramePtr);
	static void System(FramePtr);

	static void AddListener(InputPtr);
	static void AddActive(UpdatePtr);

private:
	static std::vector<FramePtr>  stack;
	static FramePtr               modal;
	static FramePtr               system;
	static std::vector<UpdatePtr> actives;
	static std::vector<InputPtr>  listeners;

	static void Init(std::string);
	static void Run(sf::RenderWindow&);

friend
	void ::Main(const C35::StrVec&);
};

}  // namespace C35
